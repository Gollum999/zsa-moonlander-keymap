#!/bin/bash

set -xeuo pipefail

# Default values
LAYOUT_ID="lXrnD"
LAYOUT_GEOMETRY="moonlander"
QMK_DIR="/home/tsanders/qmk"
WORK_DIR="$(pwd)"
DOCKER_IMAGE="qmk"

# Function to display usage
usage() {
    echo "Usage: $0 [OPTIONS]"
    echo ""
    echo "Options:"
    echo "  -i, --layout-id ID        Layout ID from Oryx URL (default: $LAYOUT_ID)"
    echo "  -g, --geometry GEOMETRY   Keyboard geometry (default: $LAYOUT_GEOMETRY)"
    echo "  -w, --work-dir DIR        Working directory (default: $WORK_DIR)"
    echo "  -h, --help               Show this help message"
    echo ""
    echo "Available geometries:"
    echo "  voyager, moonlander, ergodox_ez, ergodox_ez/m32u4/glow,"
    echo "  ergodox_ez/m32u4/shine, ergodox_ez/stm32, ergodox_ez/stm32/glow,"
    echo "  ergodox_ez/stm32/shine, planck_ez, planck_ez/glow"
    echo ""
    echo "Example:"
    echo "  $0 -i lXrnD -g moonlander"
}

# Parse command line arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -i|--layout-id)
            LAYOUT_ID="$2"
            shift 2
            ;;
        -g|--geometry)
            LAYOUT_GEOMETRY="$2"
            shift 2
            ;;
        -w|--work-dir)
            WORK_DIR="$2"
            shift 2
            ;;
        -h|--help)
            usage
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            usage
            exit 1
            ;;
    esac
done

# Validate required tools
command -v curl >/dev/null 2>&1 || { echo "Error: curl is required but not installed." >&2; exit 1; }
command -v jq >/dev/null 2>&1 || { echo "Error: jq is required but not installed." >&2; exit 1; }
command -v unzip >/dev/null 2>&1 || { echo "Error: unzip is required but not installed." >&2; exit 1; }
command -v docker >/dev/null 2>&1 || { echo "Error: docker is required but not installed." >&2; exit 1; }
command -v git >/dev/null 2>&1 || { echo "Error: git is required but not installed." >&2; exit 1; }

echo "=== Fetch and Build Layout Script ==="
echo "Layout ID: $LAYOUT_ID"
echo "Geometry: $LAYOUT_GEOMETRY"
echo "Work Directory: $WORK_DIR"
echo ""

# Create and enter work directory
mkdir -p "$WORK_DIR"
cd "$WORK_DIR"

# Step 1: Setup repository (if not already cloned)
echo "=== Setting up repository ==="
# if [ ! -d ".git" ]; then
#     echo "Cloning QMK repository..."
#     git clone --branch oryx https://github.com/Gollum999/zsa-moonlander-keymap.git .
#     git pull --unshallow 2>/dev/null || echo "Repository already has full history"
# else
#     echo "Repository already exists, updating..."
starting_branch=$(git branch --show-current)
git fetch origin
git stash push --include-untracked -m "oryx-builder autostash"
git checkout oryx
git pull
# fi

# Step 2: Download layout source
echo "=== Downloading layout source ==="
response=$(curl --location 'https://oryx.zsa.io/graphql' \
    --header 'Content-Type: application/json' \
    --data "{\"query\":\"query getLayout(\$hashId: String!, \$revisionId: String!, \$geometry: String) {layout(hashId: \$hashId, geometry: \$geometry, revisionId: \$revisionId) {  revision { hashId, qmkVersion, title }}}\",\"variables\":{\"hashId\":\"$LAYOUT_ID\",\"geometry\":\"$LAYOUT_GEOMETRY\",\"revisionId\":\"latest\"}}" \
    | jq '.data.layout.revision | [.hashId, .qmkVersion, .title]')

echo $response  # TODO
hash_id=$(echo "${response}" | jq -r '.[0]')
firmware_version=$(printf "%.0f" $(echo "${response}" | jq -r '.[1]'))
change_description=$(echo "${response}" | jq -r '.[2]')

if [[ -z "${change_description}" || "${change_description}" == "null" ]]; then
    change_description="latest layout modification made with Oryx"
fi

echo "Hash ID: $hash_id"
echo "Firmware Version: $firmware_version"
echo "Description: $change_description"

curl -L "https://oryx.zsa.io/source/${hash_id}" -o source.zip

# Step 3: Unzip the source file
echo "=== Extracting source files ==="
unzip -oj source.zip '*_source/*' -d "$LAYOUT_ID"
rm source.zip

# Step 4: Commit changes (optional - you might want to skip this for standalone usage)
echo "=== Committing layout changes ==="
git config --local user.name "oryx-builder"
git config --local user.email "oryx-builder@local"
git add .
printf "✨(oryx): %s\n" "$change_description" | git commit -F - || echo "No layout changes to commit"
git push

# Merge Oryx with custom QMK
# git checkout -B main origin/main
git switch main
# TODO need better recovery if this fails
git merge -Xignore-all-space oryx
# git push

# Step 5: Update QMK firmware submodule
echo "=== Updating QMK firmware submodule ==="
pushd $QMK_DIR
git submodule update --init --remote --depth=1 --no-single-branch
git fetch
git checkout -B "firmware$firmware_version" "origin/firmware$firmware_version" 2>/dev/null || {
    echo "Warning: Could not checkout firmware$firmware_version branch, using current branch"
}
git submodule update --init --recursive
popd

# # Step 6: Build QMK docker image
# echo "=== Building QMK docker image ==="
# if [ ! -f "Dockerfile" ]; then
#     echo "Creating Dockerfile..."
#     cat > Dockerfile << 'EOF'
# FROM ghcr.io/qmk/qmk_cli

# # Get current user ID and group ID
# ARG USER_ID=1000
# ARG GROUP_ID=1000

# # Create a user with the same UID/GID as the host user
# RUN groupadd -g $GROUP_ID qmkuser && \
#     useradd -u $USER_ID -g $GROUP_ID -m -s /bin/bash qmkuser

# # Switch to the new user
# USER qmkuser
# WORKDIR /home/qmkuser/qmk_firmware

# # ENTRYPOINT ["/bin/bash", "-c"]
# EOF
# fi

# # Build with current user's UID/GID to avoid permission issues
# docker build --build-arg USER_ID=$(id -u) --build-arg GROUP_ID=$(id -g) -t "$DOCKER_IMAGE" .

# Step 7: Build the layout
echo "=== Building the layout ==="

# Set keyboard directory and make prefix based on firmware version
if [ "$firmware_version" -ge 24 ]; then
    # keyboard_directory="/home/tsanders/qmk/keyboards/zsa"
    keyboard_directory="$QMK_DIR/keyboards/zsa"
    make_prefix="zsa/"
else
    # keyboard_directory="/home/tsanders/qmk/keyboards"
    keyboard_directory="$QMK_DIR/keyboards"
    make_prefix=""
fi

echo "Using keyboard directory: $keyboard_directory"
echo "Using make prefix: $make_prefix"

# Copy layout files to the qmk folder
pwd
rm -rf "${keyboard_directory}/$LAYOUT_GEOMETRY/keymaps/$LAYOUT_ID"
mkdir -p "${keyboard_directory}/$LAYOUT_GEOMETRY/keymaps"
ls -la "$LAYOUT_ID"
cp -r "$LAYOUT_ID" "${keyboard_directory}/$LAYOUT_GEOMETRY/keymaps/"
ls -la "${keyboard_directory}/$LAYOUT_GEOMETRY/keymaps/"

# Build the layout with proper volume mounting and user permissions
echo "Building firmware..."
# docker run \
#     -v "$(QMK_DIR):/home/qmkuser/qmk_firmware" \
#     --rm \
#     "$DOCKER_IMAGE" \
#     # /bin/bash -c "qmk setup zsa/qmk_firmware -b firmware$firmware_version -y; make ${make_prefix}$LAYOUT_GEOMETRY:$LAYOUT_ID"
#     /bin/bash -c "pwd; ls -la; qmk setup zsa/qmk_firmware -b firmware$firmware_version -H /home/qmkuser/qmk_firmware -y; tree qmk_firmware/keyboards/zsa/moonlander; make ${make_prefix}$LAYOUT_GEOMETRY:$LAYOUT_ID"
pushd $QMK_DIR
# TODO detect if setup is needed
# qmk setup zsa/qmk_firmware -b firmware$firmware_version -y
make ${make_prefix}$LAYOUT_GEOMETRY:$LAYOUT_ID

popd
git switch $starting_branch
git stash pop || true

# Step 8: Find and copy the built layout
echo "=== Locating built firmware ==="
normalized_layout_geometry="$(echo "$LAYOUT_GEOMETRY" | sed 's/\//_/g')"
# built_layout_file=$(find $QMK_DIR -maxdepth 1 -type f -regex ".*${normalized_layout_geometry}.*\.\(bin\|hex\)$")
built_layout_file=$(find /home/tsanders/qmk -maxdepth 1 -type f -regex ".*${normalized_layout_geometry}.*\.\(bin\|hex\)$")
echo $normalized_layout_geometry
echo $built_layout_file

if [ -n "$built_layout_file" ]; then
    # output_name="${normalized_layout_geometry}_${LAYOUT_ID}$(echo "$built_layout_file" | sed 's/.*\(\.[^.]*\)$/\1/')"
    # cp "$built_layout_file" "./$output_name"
    echo ""
    echo "=== BUILD SUCCESSFUL ==="
    echo "Firmware file: $built_layout_file"
    echo "Full path: $(realpath "$built_layout_file")"
    echo ""
    echo "You can now flash this firmware to your $LAYOUT_GEOMETRY keyboard."
else
    echo "Error: Could not find built firmware file"
    echo "Looking for files matching pattern: .*${normalized_layout_geometry}.*\.(bin|hex)$"
    echo "Files in qmk_firmware directory:"
    find $QMK_DIR -maxdepth 1 -type f -name "*.bin" -o -name "*.hex" | head -10
    exit 1
fi
