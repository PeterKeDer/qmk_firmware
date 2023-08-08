// Copyright 2022 Cole Smith <cole@boadsource.xyz>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include <stdio.h>
#include "bongo.h"

enum layers {
    _QWERTY,
    _COLEMAK,
    _RAISE,
    _LOWER,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  MAC_MODE,
  ALT_WIND,
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

typedef union {
  uint32_t raw;
  struct {
    unsigned char is_mac_mode;
  };
} user_config_t;

user_config_t user_config;

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |BackSP|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   -   |    |    =  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LALT |LOWER | /Enter  /       \Space \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MINS,  KC_EQL,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
                             MOD_L,   MOD_R,   LOWER, KC_ENT,  KC_SPC,   RAISE,   KC_BSPC, KC_RGUI
),


/* COLEMAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_COLEMAK] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_F,    KC_P,    KC_G,                     KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  KC_LCTL,  KC_A,   KC_R,    KC_S,    KC_T,    KC_D,                     KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_MINS,  KC_EQL,   KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
                             MOD_L,   MOD_R,   LOWER, KC_ENT,  KC_SPC,   RAISE,   KC_BSPC, KC_RGUI
),

/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |  !   |  @   |  #   |  $   |  %   |                    |  ^   |  &   |   *  |  (   |  )   | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  *   |  /   |  !   |  @   |      |                    |  \   |   [  |   ]  |   _  |   +  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |  +   |  -   |  _   |  =   |      |-------.    ,-------|   |  |   (  |   )  |   -  |   =  |      |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |  <   |  >   |  |   |  &   |      |-------|    |-------|      |   {  |   }  |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  KC_TILDE, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
  ALT_WIND, KC_ASTR, KC_SLSH, KC_EXLM, KC_AT,   _______,                   KC_BSLS, KC_LBRC, KC_RBRC, KC_UNDS, KC_PLUS, _______,
  KC_CAPS,  KC_PLUS, KC_MINS, KC_UNDS, KC_EQL,  _______,                   KC_PIPE, KC_LPRN, KC_RPRN, KC_MINS, KC_EQL,  _______,
  _______,  KC_LT,   KC_GT,   KC_PIPE, KC_AMPR, _______, _______, _______, XXXXXXX, KC_LCBR, KC_RCBR, _______, _______, _______,
                              _______, _______, _______, _______, _______, _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  |  F11 | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    | VolU | CtL  |   Up  |  CtR | Home |     |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| VolD | Left | Down | Right | End |      |
 * |------+------+------+------+------+------|RGB_TOG|    |    ]  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, _______, _______, _______, _______, _______,                    A(KC_UP), W_PREV, KC_UP,   W_NEXT,  L_START, KC_VOLU,
  _______, _______, _______, _______, _______, _______,                    A(KC_DOWN), KC_LEFT, KC_DOWN, KC_RGHT, L_END, KC_VOLD,
  _______, _______, _______, _______, _______, _______,  _______, _______, _______, NV_BACK, _______, NV_FRWD, _______, KC_BSLS,
                             _______, _______, _______,  _______, _______, _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |Reset |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   Q  |   C  |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |  AG  |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  XXXXXXX, QWERTY,  COLEMAK, MAC_MODE, XXXXXXX, XXXXXXX,                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AG_TOGG,                   XXXXXXX, XXXXXXX, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  ),
};

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

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    // state = update_tri_layer_state(state, _LOWER, _MAC_RAISE, _MAC_ADJUST);
    return state;
}

bool is_changing_windows = false;

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
    case ALT_WIND:
        if (!user_config.is_mac_mode) return false;

        if (record->event.pressed) {
            // Start holding CMD until lower is released
            if (!is_changing_windows) {
                is_changing_windows = true;
                register_code16(KC_LGUI);
            }
            register_code16(KC_TILDE);
        } else {
            unregister_code16(KC_TILDE);
        }
        return false;
    case LOWER:
        if (is_changing_windows) {
            is_changing_windows = false;
            unregister_code16(KC_LGUI);
        }
        // We do want this to continue processing, in this case
        break;
    case MOD_L...MAC_KC_END:
        if (record->event.pressed) {
            register_code16(keycode_mapping[keycode - MOD_L][user_config.is_mac_mode]);
        } else {
            unregister_code16(keycode_mapping[keycode - MOD_L][user_config.is_mac_mode]);
        }
        return false;
    default:
        break;
    }
    return true;
}

// In your rules.mk make sure you have:
// OLED_DRIVER_ENABLE = yes
// WPM_ENABLE = yes

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM logo[] = {
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x60,
      0x30, 0x18, 0x0c, 0x06, 0x03, 0x03, 0x03, 0x03, 0x03, 0x06, 0x0c, 0xf8, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x80, 0x00, 0xc0, 0x40, 0x00, 0x00, 0x80, 0xc0, 0x40, 0x40,
      0x40, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x80, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0xc0, 0x00,
      0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x80,
      0xc0, 0x00, 0x00, 0x00, 0xc0, 0x80, 0x00, 0xc0, 0x40, 0x00, 0x00, 0x80, 0xc0, 0x00, 0x80, 0x40,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x07, 0x03, 0x01, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0x80, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x0f, 0x01, 0x03, 0x0e, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x0b, 0x0b, 0x0b,
      0x00, 0x00, 0x0f, 0x09, 0x18, 0x08, 0x0f, 0x01, 0x00, 0x00, 0x0f, 0x03, 0x06, 0x0e, 0x03, 0x00,
      0x00, 0x0c, 0x07, 0x05, 0x0f, 0x0f, 0x00, 0x00, 0x08, 0x0f, 0x08, 0x08, 0x00, 0x00, 0x00, 0x0f,
      0x00, 0x00, 0x00, 0x0f, 0x01, 0x03, 0x0e, 0x0f, 0x00, 0x00, 0x08, 0x0f, 0x03, 0x07, 0x0c, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x08, 0x0c, 0x0e, 0x0b, 0x09, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
      0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x01, 0xff, 0xc0, 0x00,
      0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x88, 0xc8, 0x78, 0x38, 0x18, 0x08, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x3f, 0x60,
      0xc0, 0xc0, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    oled_write_raw_P(logo, sizeof(logo));
}

// Used to draw on to the oled screen
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        draw_bongo(false);
    } else {
        render_logo();
        oled_scroll_left();
    }
    return false;
}
#endif
