#include QMK_KEYBOARD_H
#include "version.h"
#define MOON_LED_LEVEL LED_LEVEL
#ifndef ZSA_SAFE_RANGE
#define ZSA_SAFE_RANGE SAFE_RANGE
#endif

enum custom_keycodes {
  RGB_SLD = ZSA_SAFE_RANGE,
  ST_MACRO_0,
  ST_MACRO_1,
};



#define DUAL_FUNC_0 LT(6, KC_O)
#define DUAL_FUNC_1 LT(10, KC_P)
#define DUAL_FUNC_2 LT(15, KC_J)
#define DUAL_FUNC_3 LT(8, KC_U)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           ST_MACRO_0,                                     KC_TRANSPARENT, KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_TRANSPARENT, 
    KC_DELETE,      KC_QUOTE,       KC_COMMA,       KC_DOT,         KC_P,           KC_Y,           KC_GRAVE,                                       KC_TRANSPARENT, KC_F,           KC_G,           KC_C,           KC_R,           KC_L,           KC_BSLS,        
    KC_ESCAPE,      KC_A,           MT(MOD_LALT, KC_O),MT(MOD_LSFT, KC_E),MT(MOD_LCTL, KC_U),KC_I,           KC_SLASH,                                                                       KC_EQUAL,       KC_D,           MT(MOD_RCTL, KC_H),MT(MOD_RSFT, KC_T),MT(MOD_RALT, KC_N),KC_S,           KC_MINUS,       
    KC_TRANSPARENT, KC_SCLN,        KC_Q,           KC_J,           KC_K,           KC_X,                                           KC_B,           KC_M,           KC_W,           KC_V,           KC_Z,           KC_TRANSPARENT, 
    CW_TOGG,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MT(MOD_LGUI, KC_APPLICATION),KC_DELETE,                                                                                                      KC_BSPC,        KC_LBRC,        KC_RBRC,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    LT(1, KC_SPACE),LT(2, KC_TAB),  DUAL_FUNC_0,                    MO(3),          LT(2, KC_ENTER),LT(1, KC_BSPC)
  ),
  [1] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_WH_LEFT,  KC_MS_WH_RIGHT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, QK_BOOT,        
    KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_BTN1,     KC_MS_UP,       KC_MS_BTN2,     KC_MS_WH_UP,    KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_HOME,        KC_UP,          KC_END,         KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, MT(MOD_LALT, KC_MS_LEFT),MT(MOD_LSFT, KC_MS_DOWN),MT(MOD_LCTL, KC_MS_RIGHT),KC_MS_WH_DOWN,  KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, MT(MOD_RCTL, KC_LEFT),MT(MOD_RSFT, KC_DOWN),MT(MOD_RALT, KC_RIGHT),KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_PGDN,        KC_PAGE_UP,     KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_MEDIA_PLAY_PAUSE,KC_MEDIA_NEXT_TRACK,KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_WWW_BACK,    KC_WWW_FORWARD, LCTL(LSFT(KC_T)),                KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [2] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         
    KC_TRANSPARENT, KC_EXLM,        KC_AT,          KC_LCBR,        KC_RCBR,        KC_PIPE,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_KP_SLASH,    KC_KP_7,        KC_KP_8,        KC_KP_9,        KC_KP_MINUS,    KC_F12,         
    KC_TRANSPARENT, KC_HASH,        DUAL_FUNC_1,    DUAL_FUNC_2,    DUAL_FUNC_3,    KC_GRAVE,       KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_KP_ASTERISK, MT(MOD_RCTL, KC_KP_4),MT(MOD_RSFT, KC_KP_5),MT(MOD_RALT, KC_KP_6),KC_KP_PLUS,     KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_PERC,        KC_CIRC,        KC_LBRC,        KC_RBRC,        KC_TILD,                                        KC_AMPR,        KC_KP_1,        KC_KP_2,        KC_KP_3,        KC_KP_EQUAL,    KC_TRANSPARENT, 
    KC_INSERT,      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 RGB_TOG,        KC_KP_0,        KC_KP_DOT,      KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    RGB_VAD,        RGB_VAI,        KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_moonlander(
    AU_TOGG,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    MU_TOGG,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, ST_MACRO_1,     KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    MU_NEXT,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
};




extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}


const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = { {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221}, {102,191,221} },

    [1] = { {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255}, {205,234,255} },

    [2] = { {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255}, {32,207,255} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );   
    }
  }
}

bool rgb_matrix_indicators_user(void) {
  if (rawhid_state.rgb_control) {
      return false;
  }
  if (keyboard_config.disable_layer_led) { return false; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
  return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_T)SS_DELAY(10)  SS_TAP(X_E)SS_DELAY(10)  SS_TAP(X_S)SS_DELAY(10)  SS_TAP(X_T)SS_DELAY(10)  SS_TAP(X_0));
    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_LCTL(SS_TAP(X_R))SS_DELAY(100)  SS_RSFT(SS_TAP(X_QUOTE)));
    }
    break;

    case DUAL_FUNC_0:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_LEFT_GUI);
        } else {
          unregister_code16(KC_LEFT_GUI);
        }
      } else {
        if (record->event.pressed) {
          layer_on(3);
        } else {
          layer_off(3);
        }  
      }  
      return false;
    case DUAL_FUNC_1:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_DLR);
        } else {
          unregister_code16(KC_DLR);
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_LEFT_ALT);
        } else {
          unregister_code16(KC_LEFT_ALT);
        }  
      }  
      return false;
    case DUAL_FUNC_2:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_LPRN);
        } else {
          unregister_code16(KC_LPRN);
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_LEFT_SHIFT);
        } else {
          unregister_code16(KC_LEFT_SHIFT);
        }  
      }  
      return false;
    case DUAL_FUNC_3:
      if (record->tap.count > 0) {
        if (record->event.pressed) {
          register_code16(KC_RPRN);
        } else {
          unregister_code16(KC_RPRN);
        }
      } else {
        if (record->event.pressed) {
          register_code16(KC_LEFT_CTRL);
        } else {
          unregister_code16(KC_LEFT_CTRL);
        }  
      }  
      return false;
    case RGB_SLD:
        if (rawhid_state.rgb_control) {
            return false;
        }
        if (record->event.pressed) {
            rgblight_mode(1);
        }
        return false;
  }
  return true;
}



