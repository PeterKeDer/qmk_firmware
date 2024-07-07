/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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
    _SPACENAV,
    _NAV,
    _FN,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,     KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,       KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,       KC_LBRC, KC_RBRC, KC_BSLS,          KC_HOME,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,    KC_QUOT,          KC_ENT,           KC_END,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,     KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             MO(_NAV), MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Colemak layout
    [_COLEMAK] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,     KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,       KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_HOME,
        KC_CAPS, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,       KC_QUOT,          KC_ENT,           KC_END,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,     KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                            LT(_NAV, KC_SPC),                   MO(_NAV), MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT(
        _______, KC_MYCM,       KC_WHOM,        KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          _______,
        _______, DF(_QWERTY),   DF(_COLEMAK),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, RGB_TOG,       RGB_VAI,        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, _______,       RGB_VAD,        _______, _______, AG_TOGG, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,                _______,        RGB_HUI, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_MOD, _______,
        _______, _______,       _______,                                   _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),

    [_NAV] = LAYOUT(
        _______, _______,   _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______,   _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______,   _______,   _______, _______, _______, _______, C(KC_LEFT), KC_UP, C(KC_RGHT), KC_HOME, _______, _______, _______,          _______,
        _______, _______,   _______,   _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______,          _______,          _______,
        _______,            _______,   _______, _______, _______, _______, KC_PGUP, _______, KC_PGDN, _______, _______,          _______, _______, _______,
        _______, _______,   _______,                              _______,                            _______, _______, _______, _______, _______, _______
    ),

};
// clang-format on


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return true;
}
#endif // ENCODER_ENABLE


// RGB LED layout

// led number, function of the key

//  67, Side led 01    0, ESC      6, F1       12, F2       18, F3       23, F4       28, F5       34, F6       39, F7       44, F8       50, F9       56, F10      61, F11      66, F12      69, Prt       Rotary(Mute)   68, Side led 12
//  70, Side led 02    1, ~        7, 1        13, 2        19, 3        24, 4        29, 5        35, 6        40, 7        45, 8        51, 9        57, 0        62, -_       78, (=+)     85, BackSpc   72, Del        71, Side led 13
//  73, Side led 03    2, Tab      8, Q        14, W        20. E        25, R        30, T        36, Y        41, U        46, I        52, O        58, P        63, [{       89, ]}       93, \|        75, PgUp       74, Side led 14
//  76, Side led 04    3, Caps     9, A        15, S        21, D        26, F        31, G        37, H        42, J        47, K        53, L        59, ;:       64, '"                    96, Enter     86, PgDn       77, Side led 15
//  80, Side led 05    4, Sh_L     10, Z       16, X        22, C        27, V        32, B        38, N        43, M        48, ,<       54, .<       60, /?                    90, Sh_R     94, Up        82, End        81, Side led 16
//  83, Side led 06    5, Ct_L     11,Win_L    17, Alt_L                              33, SPACE                              49, Alt_R    55, FN                    65, Ct_R     95, Left     97, Down      79, Right      84, Side led 17
//  87, Side led 07                                                                                                                                                                                                        88, Side led 18
//  91, Side led 08                                                                                                                                                                                                        92, Side led 19

// static const uint8_t WAVE_LEFT[] = {
//     0, 6,
//     1, 7, 13,
//     2, 8, 14, 20, 25,
//     3, 9, 15, 21, 26, 31, 37,
//     4, 10, 16, 22, 27, 32, 38,
//     5, 11, 17, 33
// };

// static const uint8_t WAVE_CENTER[] = {
//     12, 18, 23, 28, 34, 39,
//     19, 24, 29, 35, 40, 45, 51,
//     30, 36, 41, 46, 52, 58,
//     42, 47, 53, 59,
//     43, 48, 54, 60,
//     49, 55, 65,
// };

// #define NUM_SIDELIGHTS 8

static const uint8_t LEFT_SIDELIGHTS[] = {
    67, 70, 73, 76, 80, 83, 87, 91
};

static const uint8_t RIGHT_SIDELIGHTS[] = {
    68, 71, 74, 77, 81, 84, 88, 92
};

static const uint8_t ROW_0[] = {
    0, 6, 12, 18, 23, 28, 34, 39, 44, 50, 56, 61, 66, 69
};

static const uint8_t ROW_1[] = {
    1, 7, 13, 19, 24, 29, 35, 40, 45, 51, 57, 62, 78, 85, 72
};

static const uint8_t ROW_2[] = {
    2, 8, 14, 20, 25, 30, 36, 41, 46, 52, 58, 63, 89, 93, 75
};

static const uint8_t ROW_3[] = {
    3, 9, 15, 21, 26, 31, 37, 42, 47, 53, 59, 64, 96, 86
};

static const uint8_t ROW_4[] = {
    4, 10, 16, 22, 27, 32, 38, 43, 48, 54, 60, 90, 94, 82
};

static const uint8_t ROW_5[] = {
    5, 11, 17, 33, 49, 55, 65, 95, 97, 79
};

#define WITH_BRIGHTNESS(r, g, b, brightness) ((uint8_t) ((r) * (brightness))), (((uint8_t) ((g) * (brightness)))), (((uint8_t) ((b) * (brightness))))

#define GRADIENT_INTERPOLATE(i, total, start, end) ((uint8_t) (((end) - (start)) * ((i) / (float) ((total) - 1)) + (start)))

#define GET_RGB_GRADIENT(i, total, r_start, g_start, b_start, r_end, g_end, b_end)

static uint8_t brightness = 255;

#define SET_RGB_WITH_BRIGHTNESS(index, r, g, b) rgb_matrix_set_color(index, WITH_BRIGHTNESS((r), (g), (b), brightness / (float) 255))

static void rgb_set_brightness(uint8_t val) {
    brightness = val;
}

/// Set linear gradient color for elements in row
static void rgb_set_row_gradient(
    const uint8_t *row,
    size_t num_elems,
    int offset,
    int offset_end,
    uint8_t r_start,
    uint8_t g_start,
    uint8_t b_start,
    uint8_t r_end,
    uint8_t g_end,
    uint8_t b_end
) {
    int total = num_elems - offset - offset_end;
    for (int i = 0; i < num_elems; i++) {
        if (i < offset) {
            SET_RGB_WITH_BRIGHTNESS(row[i], r_start, g_start, b_start);
        } else if (i > num_elems - 1 - offset_end) {
            SET_RGB_WITH_BRIGHTNESS(row[i], r_end, g_end, b_end);
        } else {
            int index = i - offset;
            SET_RGB_WITH_BRIGHTNESS(row[i],
                GRADIENT_INTERPOLATE(index, total, r_start, r_end),
                GRADIENT_INTERPOLATE(index, total, g_start, g_end),
                GRADIENT_INTERPOLATE(index, total, b_start, b_end)
            );
        }
    }
}

// Set color for all indices in array
#define RGB_MATRIX_SET_COLOR_ARRAY(arr, r, g, b) {\
    for (int i = 0; i < sizeof(arr) / sizeof(uint8_t); i++) \
        SET_RGB_WITH_BRIGHTNESS(arr[i], r, g, b); \
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Set persistent default layer
    switch (keycode) {
        case DF(_QWERTY):
            set_single_persistent_default_layer(_QWERTY);
            return false;
        case DF(_COLEMAK):
            set_single_persistent_default_layer(_COLEMAK);
            return false;
        default:
            break;
    }
    return true;
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    rgb_matrix_set_color_all(200, 240, 255);

    // RGB_MATRIX_SET_COLOR_ARRAY(WAVE_LEFT, 30, 60, 140);
    // RGB_MATRIX_SET_COLOR_ARRAY(WAVE_CENTER, 60, 180, 255);

    // Get brightness
    rgb_set_brightness(rgb_matrix_get_val());

    uint8_t r_start = 0;
    uint8_t g_start = 30;
    uint8_t b_start = 60;
    uint8_t r_end = 170;
    uint8_t g_end = 220;
    uint8_t b_end = 235;

    // Set color based on default layer
    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            // Use default colors
            break;
        case _COLEMAK:
            r_start = 10;
            g_start = 60;
            b_start = 25;
            r_end = 170;
            g_end = 255;
            b_end = 200;
            break;
        default:
            break;
    }

    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        r_start = 180;
        g_start = 100;
        b_start = 0;
    }

    // Set gradient for each row

    rgb_set_row_gradient(
        ROW_0, sizeof(ROW_0) / sizeof(uint8_t), -2, 0,
        r_start, g_start, b_start,
        r_end, g_end, b_end
    );

    rgb_set_row_gradient(
        ROW_1, sizeof(ROW_1) / sizeof(uint8_t), -1, -1,
        r_start, g_start, b_start,
        r_end, g_end, b_end
    );

    rgb_set_row_gradient(
        ROW_2, sizeof(ROW_2) / sizeof(uint8_t), -1, -1,
        r_start, g_start, b_start,
        r_end, g_end, b_end
    );

    rgb_set_row_gradient(
        ROW_3, sizeof(ROW_3) / sizeof(uint8_t), 0, -2,
        r_start, g_start, b_start,
        r_end, g_end, b_end
    );

    rgb_set_row_gradient(
        ROW_4, sizeof(ROW_4) / sizeof(uint8_t), 0, -2,
        r_start, g_start, b_start,
        r_end, g_end, b_end
    );

    rgb_set_row_gradient(
        ROW_5, sizeof(ROW_5) / sizeof(uint8_t), 0, -3,
        r_start, g_start, b_start,
        r_end, g_end, b_end
    );

    // Set side lights
    RGB_MATRIX_SET_COLOR_ARRAY(LEFT_SIDELIGHTS, r_start, g_start, b_start);
    RGB_MATRIX_SET_COLOR_ARRAY(RIGHT_SIDELIGHTS, r_end, g_end, b_end);

    // Caps lock indicator
    // if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
    //     SET_RGB_WITH_BRIGHTNESS(3, 50, 255, 100);
    // }
}

#undef WITH_BRIGHTNESS
#undef GRADIENT_INTERPOLATE
#undef SET_RGB_WITH_BRIGHTNESS
#undef RGB_MATRIX_SET_COLOR_ARRAY
