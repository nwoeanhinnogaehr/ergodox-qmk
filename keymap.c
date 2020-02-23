#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define BASESHIFT 1 // default + shift key
#define BASESHIFT2 3 // shifted back from symb
#define SYMB 2 // symbols

enum custom_keycodes {
    PLACEHOLDER = SAFE_RANGE, // can always be here
    EPRM,
    VRSN,
    RGB_SLD,
    SAVE,
    TEX_NEQ,
    TEX_LEQ,
    TEX_GEQ,
    TEX_BEGIN,
    TEX_IN,
    TEX_LEQN,
    TEX_REQN,
    TEX_LSET,
    TEX_RSET,
    TEX_FRAC,
    TEX_DOT
};

#define BSFT LM(BASESHIFT, MOD_LSFT)

#define DEFN_BASESHIFT LAYOUT_ergodox(\
        KC_GRV,        KC_NO,        KC_2,   KC_NO,  KC_NO,  KC_NO,  TEX_LEQN,\
        KC_TAB,        KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_DLR,\
        KC_ESC,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,\
        KC_TRNS,       KC_Z,         KC_X,   KC_C,   KC_V,   KC_B,   KC_EQL,\
        KC_LCTRL,      KC_LGUI,      KC_LALT,KC_LEFT,KC_RGHT,\
                                               KC_AMPR,         KC_PLUS,\
                                                                KC_PERC,\
                                               MO(SYMB),KC_BSPC,KC_MINS,\
\
        TEX_REQN,      KC_NO,  KC_NO, KC_NO,  KC_NO,  KC_NO,            S(KC_INS),\
        KC_DLR,        KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_PIPE,\
                       KC_H,   KC_J,  KC_K,   KC_L,   KC_SCLN,          KC_QUOT,\
        KC_BSLS,       KC_N,   KC_M,  KC_COMM,KC_DOT, KC_SLSH,          KC_TRNS,\
                              KC_DOWN,KC_UP, KC_DEL, KC_INS,            KC_TILD,\
        KC_PLUS,   KC_CIRC,\
        KC_EXLM,\
        KC_UNDS,KC_ENT, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT_ergodox( 
        // left hand
        KC_GRV,        KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   TEX_LEQN,
        KC_TAB,        KC_Q,         KC_W,   KC_E,   KC_R,   KC_T,   KC_DLR,
        KC_ESC,        KC_A,         KC_S,   KC_D,   KC_F,   KC_G,
        BSFT,          KC_Z,         KC_X,   KC_C,   KC_V,   KC_B,   KC_EQL,
        KC_LCTRL,      KC_LGUI,      KC_LALT,KC_LEFT,KC_RGHT,
                                               KC_AMPR,         KC_PLUS,
                                                                KC_PERC,
                                               MO(SYMB),KC_BSPC,KC_MINS,
        // right hand
        TEX_REQN,      KC_6,   KC_7,  KC_8,   KC_9,   KC_0,             S(KC_INS),
        KC_DLR,        KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,             KC_PIPE,
                       KC_H,   KC_J,  KC_K,   KC_L,   KC_SCLN,          KC_QUOT,
        KC_BSLS,       KC_N,   KC_M,  KC_COMM,KC_DOT, KC_SLSH,          KC_ASTR,
                              KC_DOWN,KC_UP, KC_DEL, KC_INS,            KC_TILD,
        KC_PLUS,   KC_CIRC,
        KC_EXLM,
        KC_UNDS,KC_ENT, KC_SPC
),
[SYMB] = LAYOUT_ergodox(
       // left hand
       VRSN,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  TEX_LSET,
       KC_TRNS,KC_EXLM,KC_PERC,KC_NO,  KC_EXLM,KC_AMPR,KC_TRNS,
       KC_TRNS,KC_HASH,KC_HASH,KC_NO,  KC_BSLS,KC_PIPE,
       LM(BASESHIFT2,MOD_LSFT),KC_PERC,KC_TILD,KC_TILD,KC_PERC,KC_CIRC,TEX_NEQ,
          EPRM,KC_TRNS,KC_TRNS,TEX_LEQ,TEX_GEQ,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_PLUS,
       // right hand
       TEX_RSET, KC_F6,   KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_LPRN, KC_RPRN,  KC_ASTR, KC_AMPR, KC_TRNS, KC_F12,
                KC_LCBR, KC_RCBR,  KC_PLUS, KC_MINS, KC_TRNS, KC_DQUO,
       KC_PIPE, KC_LBRC, KC_RBRC,  KC_LABK, KC_RABK, KC_TRNS, KC_TRNS,
                         KC_WBAK,  KC_WFWD, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_ASTR,
       KC_TRNS,
       TEX_IN, KC_TRNS, KC_TRNS
),
[BASESHIFT] = DEFN_BASESHIFT,
[BASESHIFT2] = DEFN_BASESHIFT,
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      break;
    case 1:
      if (record->event.pressed) { // For resetting EEPROM
        eeconfig_init();
      }
      break;
  }
  return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
    case SAVE:
      if (record->event.pressed) {
          tap_code(KC_ESC);
          _delay_ms(50);
          tap_code(KC_ESC);
          _delay_ms(50);
          tap_code(KC_ESC);
      }
      return false;
      break;
    case TEX_LEQ:
      if (record->event.pressed) SEND_STRING("\\le ");
      return false;
      break;
    case TEX_GEQ:
      if (record->event.pressed) SEND_STRING("\\ge ");
      return false;
      break;
    case TEX_NEQ:
      if (record->event.pressed) SEND_STRING("\\ne ");
      return false;
      break;
    case TEX_BEGIN:
      if (record->event.pressed) SEND_STRING("\\begin" SS_LCTRL("k"));
      return false;
      break;
    case TEX_IN:
      if (record->event.pressed) SEND_STRING("\\in ");
      return false;
      break;
    case TEX_LEQN:
      if (record->event.pressed) SEND_STRING("\\[");
      return false;
      break;
    case TEX_REQN:
      if (record->event.pressed) SEND_STRING("\\]");
      return false;
      break;
    case TEX_LSET:
      if (record->event.pressed) SEND_STRING("\\{");
      return false;
      break;
    case TEX_RSET:
      if (record->event.pressed) SEND_STRING("\\}");
      return false;
      break;
    case TEX_FRAC:
      if (record->event.pressed) SEND_STRING(SS_LCTRL("f"));
      return false;
      break;
    case TEX_DOT:
      if (record->event.pressed) SEND_STRING("\\.");
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
  rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {
  ergodox_board_led_off();
  ergodox_right_led_1_off();
  ergodox_right_led_2_off();
  ergodox_right_led_3_off();

  uint8_t layer = biton32(state);
  switch (layer) {
      case 0:
        #ifdef RGBLIGHT_COLOR_LAYER_0
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
        #else
        #ifdef RGBLIGHT_ENABLE
          rgblight_init();
        #endif
        #endif
        break;
      case 1:
        ergodox_right_led_1_on();
        #ifdef RGBLIGHT_COLOR_LAYER_1
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
        #endif
        break;
      case 2:
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_2
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
        #endif
        break;
      case 3:
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_3
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
        #endif
        break;
      case 4:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        #ifdef RGBLIGHT_COLOR_LAYER_4
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
        #endif
        break;
      case 5:
        ergodox_right_led_1_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_5
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
        #endif
        break;
      case 6:
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_6
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      case 7:
        ergodox_right_led_1_on();
        ergodox_right_led_2_on();
        ergodox_right_led_3_on();
        #ifdef RGBLIGHT_COLOR_LAYER_7
          rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
        #endif
        break;
      default:
        break;
    }

  return state;
};
