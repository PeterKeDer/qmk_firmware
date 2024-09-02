/*
Copyright 2022 qwertykeys

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include QMK_KEYBOARD_H

enum keyboard_layout {
    _QWERTY,
    _COLEMAK,
    _NAV,
    _FN,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  MAC_MODE,
  // Special shortcut for windows/mac
  MOD_L,
  MOD_R,
  W_PREV,
  W_NEXT,
  L_START,
  L_END,
  NV_BACK,
  NV_FRWD,
  MAC_KC_END
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_GRV,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, MOD_L,   MOD_R,                              KC_SPC,                    MO(_FN), KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_COLEMAK] = LAYOUT_65_ansi_blocker(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP,
        KC_GRV,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,          KC_ENT,  KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, MOD_L,   MOD_R,                              LT(_NAV, KC_SPC),          MO(_FN), KC_RCTL,          KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT_65_ansi_blocker(
        _______, KC_F1,       KC_F2,        KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, QK_BOOT,
        _______, QWERTY,      COLEMAK,      MAC_MODE,_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME,
        _______, _______,     _______,      _______, _______, AG_TOGG, _______, _______, _______, _______, _______, _______,          _______, KC_END,
        _______,              _______,      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_PSCR,
        _______, _______,     _______,                                 _______,                   _______, _______,          _______, KC_VOLD, _______
    ),

    [_NAV] = LAYOUT_65_ansi_blocker(
        _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______,    _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, W_PREV,     KC_UP,   W_NEXT,     L_START, _______, _______, _______, _______,
        KC_CAPS, _______, _______, _______, _______, _______, _______, KC_LEFT,    KC_DOWN, KC_RGHT,    L_END,  _______,          _______, _______,
        _______,          _______, _______, _______, _______, _______, _______,    NV_BACK, _______,    NV_FRWD, _______, _______, _______, _______,
        _______, _______, _______,                            _______,                      _______,    _______,          _______, _______, _______
    )
};

typedef union {
  uint32_t raw;
  struct {
    unsigned char is_mac_mode;
  };
} user_config_t;

user_config_t user_config;

// Mapping for special keycodes that differ in windows and mac
const uint16_t PROGMEM keycode_mapping[][2] = {
    {KC_LGUI,       KC_LALT},       // MOD_L
    {KC_LALT,       KC_LGUI},       // MOD_R
    {C(KC_LEFT),    A(KC_LEFT)},    // W_PREV
    {C(KC_RGHT),    A(KC_RGHT)},    // W_NEXT
    {KC_HOME,       G(KC_LEFT)},    // L_START
    {KC_END,        G(KC_RGHT)},    // L_END
    {A(KC_LEFT),    G(KC_LBRC)},    // NV_BACK
    {A(KC_RGHT),    G(KC_RBRC)},    // NV_FRWD
    {KC_NO,         KC_NO}
};

void eeconfig_init_user(void) {
  user_config.raw = 0;
  user_config.is_mac_mode = 0;
}

void keyboard_post_init_user(void) {
    user_config.raw = eeconfig_read_user();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case QWERTY:
        if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
        }
        return false;
    case COLEMAK:
        if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
        }
        return false;
    case MAC_MODE:
        if (record->event.pressed) {
            user_config.is_mac_mode = !user_config.is_mac_mode;
            eeconfig_update_user(user_config.raw);
        }
        return false;
    case MOD_L...MAC_KC_END:
        if (record->event.pressed) {
            register_code16(pgm_read_word(&keycode_mapping[keycode - MOD_L][user_config.is_mac_mode]));
        } else {
            unregister_code16(pgm_read_word(&keycode_mapping[keycode - MOD_L][user_config.is_mac_mode]));
        }
        return false;
    default:
        break;
    }
    return true;
}
