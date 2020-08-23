#include QMK_KEYBOARD_H


#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _CAPS 3
#define _ADJUST 16
#define _LOWERCAPS 17

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  CAPS,
  ADJUST,
  LOWERCAPS,
  KVM_NXT,
  KVM_PRV,
  KVM_1,
  KVM_2,
  KVM_3,
  KVM_4,
};

// Tap danceの設定
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
};

enum {
  TD_FN_CTL,
  TD_FN_SFT,
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    return DOUBLE_TAP;
  }
  else return 6; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void x_finished_1 (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP:
      register_code(KC_LCTL);
      break;
    case SINGLE_HOLD:
      register_code(KC_LCTL);
      break;
    case DOUBLE_TAP:
      register_code(KC_F13);
      break;
  }
}

void x_reset_1 (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP:  
        unregister_code(KC_LCTL);
        break;
    case SINGLE_HOLD: 
        unregister_code(KC_LCTL);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_F13);
      break;
  }
  xtap_state.state = 0;
}

void x_finished_2 (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP:
      register_code(KC_LSFT);
      break;
    case SINGLE_HOLD: 
      register_code(KC_LSFT);
      break;
    case DOUBLE_TAP:
      register_code(KC_F14);
      break;
  }
}

void x_reset_2 (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP:  
        unregister_code(KC_LSFT);
        break;
    case SINGLE_HOLD: 
        unregister_code(KC_LSFT);
        break;
    case DOUBLE_TAP:
        unregister_code(KC_F14);
      break;
  }
  xtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_FN_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_1, x_reset_1),
  [TD_FN_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_2, x_reset_2)
};

#define CTL_Z LCTL(KC_Z)
#define CTL_X LCTL(KC_X)
#define CTL_C LCTL(KC_C)
#define CTL_V LCTL(KC_V)
#define CTL_S_Z LCTL(LSFT(KC_Z))
#define WIN_V LGUI(KC_V)
#define L_DESC LGUI(LCTL(KC_LEFT))
#define R_DESC LGUI(LCTL(KC_RGHT))
#define M_TASK LGUI(KC_TAB)
#define LO_SPC LT(_LOWER, KC_SPC)
#define RA_ENT LT(_RAISE, KC_ENT)
#define LO_F13 LT(_LOWER, KC_F13)
#define RA_F14 LT(_RAISE, KC_F14)
#define TD_CTL TD(TD_FN_CTL)
#define TD_SFT TD(TD_FN_SFT)
#define ALT_TAB ALT_T(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |  Esc |   Q  |   W  |   E  |   R  |   T  |   -  |                    |   =  |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |   [  |                    |   ]  |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  | Space|                    | Enter|   N  |   M  |   ,  |   .  |   /  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | EISU |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise|||||||| Left | Down |  Up  | Right|
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT( \
    KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_TAB,           KC_RBRC, KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_MINS, \
    KC_SCLN, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_F13,           KC_F14,  KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,   XXXXXXX,          XXXXXXX, KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_EQL, \
    KC_LALT,  KC_LGUI, KC_LALT, KC_LCTL, LOWER,   KC_SPC, XXXXXXX,          XXXXXXX, KC_ENT, RAISE,  KC_LSFT, KC_LALT, KC_APP,  KC_F14 \
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |   `  |   !  |   @  |   #  |   $  |   %  |   _  |                    |   +  |   ^  |   &  |   *  |   (  |   )  |  |   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |   ~  |   1  |   2  |   3  |   4  |   5  |   {  |                    |   }  | Left | Down |  Up  | Right|   :  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   6  |   7  |   8  |   9  |   0  | Space|                    | Enter|   N  |   M  |   <  |   >  |   ?  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | EISU |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise|||||||| Home |PageDn|PageUp|  End |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KVM_1,         KVM_2,   KC_DEL,  XXXXXXX, KC_UP,   KC_TAB, XXXXXXX, XXXXXXX, \
    CAPS,    KC_LCTL, KC_LSFT, KC_LGUI, KC_LALT, KC_ESC,  KVM_3,         KVM_4,   KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  WIN_V,   XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, KC_F14,  KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, _______, _______, _______, LOWER,   _______, XXXXXXX,       XXXXXXX, KC_F13,  RAISE,   _______, _______, _______, _______ \
  ),

  [_CAPS] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, KC_DEL,  XXXXXXX, KC_UP,   KC_TAB,  XXXXXXX, XXXXXXX, \
    CAPS,    KC_LCTL, KC_LSFT, KC_LGUI, KC_LALT, KC_ESC,  XXXXXXX,       XXXXXXX, KC_BSPC, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, \
    XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, _______, _______, _______, LOWER,   _______, XXXXXXX,       XXXXXXX, _______, RAISE,   _______, _______, _______, _______ \
  ),

  /* Raise
  * ,----------------------------------------------------------------------------------------------------------------------.
  * |   `  |   !  |   @  |   #  |   $  |   %  |   _  |                    |   +  |   ^  |   &  |   *  |   (  |   )  |  |   |
  * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
  * |   ~  |   F1 |   F2 |   F3 |   F4 |   F5 |   {  |                    |   }  | Left | Down |  Up  | Right|   :  |  "   |
  * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
  * | Shift|   F6 |   F7 |   F8 |   F9 |  F10 | Space|                    | Enter|   N  |   M  |   <  |   >  |   ?  | Shift|
  * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
  * | Ctrl |  F11 |  F12 | EISU |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise|||||||| Home |PageDn|PageUp|  End |
  * ,----------------------------------------------------------------------------------------------------------------------.
  */
  [_RAISE] = LAYOUT(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LCBR,          KC_RCBR, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, \
    KC_COLN, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXXX,          XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DQT, \
    _______, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_COLN, XXXXXXX,          XXXXXXX, KC_PIPE, KC_BSLS, KC_LT,   KC_GT,   KC_QUES, KC_PLUS, \
    _______, _______, _______, _______, LOWER,   _______, XXXXXXX,          XXXXXXX, _______, RAISE,   _______, _______, KVM_PRV, KVM_NXT \
  ),

  /* Adjust
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      | Reset|RGB ON|  MODE|  HUE-|  HUE+|      |                    |      |  SAT-|  SAT+|  VAL-|  VAL+|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
    KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX,\
    _______, XXXXXXX, L_DESC,  M_TASK,  R_DESC,  KC_DEL,  KC_ENT,           XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_END,  XXXXXXX, XXXXXXX, \
    KC_F11,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX,          XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F12, \
  	_______, KC_APP,  XXXXXXX, XXXXXXX, LOWER,   XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, RAISE,   XXXXXXX, _______, _______, _______ \
  ),

  [_LOWERCAPS] = LAYOUT(
  	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, KC_PGUP, XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,  KC_ENT,           XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_END,  XXXXXXX, XXXXXXX, \
  	CTL_S_Z, CTL_Z,   CTL_X,   CTL_C,   CTL_V,   XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  	_______, _______, _______, _______, LOWER,   _______, XXXXXXX,          XXXXXXX, _______, RAISE,   _______, _______, _______, _______ \
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        update_tri_layer(_LOWER, _CAPS, _LOWERCAPS);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        update_tri_layer(_LOWER, _CAPS, _LOWERCAPS);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case CAPS:
      if (record->event.pressed) {
        layer_on(_CAPS);
        update_tri_layer(_LOWER, _CAPS, _LOWERCAPS);
      } else {
        layer_off(_CAPS);
        update_tri_layer(_LOWER, _CAPS, _LOWERCAPS);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case LOWERCAPS:
      if (record->event.pressed) {
        layer_on(_LOWERCAPS);
      } else {
        layer_off(_LOWERCAPS);
      }
      return false;
      break;
    case KVM_PRV:
      if (record->event.pressed) {
        register_code(KC_SLCK);
        unregister_code(KC_SLCK);
        register_code(KC_SLCK);
        unregister_code(KC_SLCK);
        register_code(KC_PGDN);
        unregister_code(KC_PGDN);
      }
      return false;
      break;
    case KVM_NXT:
      if (record->event.pressed) {
        register_code(KC_SLCK);
        unregister_code(KC_SLCK);
        register_code(KC_SLCK);
        unregister_code(KC_SLCK);
        register_code(KC_PGUP);
        unregister_code(KC_PGUP);
      }
      return false;
      break;
    case KVM_1:
      if (record->event.pressed) {
        register_code(KC_SLCK);
        unregister_code(KC_SLCK);
        register_code(KC_SLCK);
        unregister_code(KC_SLCK);
        register_code(KC_1);
        unregister_code(KC_1);
      }
      return false;
      break;
    case KVM_2:
      if (record->event.pressed) {
        register_code(KC_SLCK);
        unregister_code(KC_SLCK);
        register_code(KC_SLCK);
        unregister_code(KC_SLCK);
        register_code(KC_2);
        unregister_code(KC_2);
      }
      return false;
      break;
    case KVM_3:
      if (record->event.pressed) {
        register_code(KC_SLCK);
        unregister_code(KC_SLCK);
        register_code(KC_SLCK);
        unregister_code(KC_SLCK);
        register_code(KC_3);
        unregister_code(KC_3);
      }
      return false;
      break;
    case KVM_4:
      if (record->event.pressed) {
        register_code(KC_SLCK);
        unregister_code(KC_SLCK);
        register_code(KC_SLCK);
        unregister_code(KC_SLCK);
        register_code(KC_4);
        unregister_code(KC_4);
      }
      return false;
      break;
  }
  return true;
}
void keyboard_post_init_user(void) {
  #ifdef CONSOLE_ENABLE
  // Customise these values to desired behaviour
  debug_enable=true;
  // debug_matrix=true;
  debug_keyboard=true;
  //debug_mouse=true;
  #endif 
}