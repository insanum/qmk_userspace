
#include "quantum_keycodes.h"
#include QMK_KEYBOARD_H

#define _BASE    0
#define _GAMING  1
#define _SYMBOLS 2
#define _FUNCS   3
#define _RGB     4

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] /* _BASE */ = LAYOUT_split_3x6_3(
        XXXXXXX,  KC_Q,          KC_W,          KC_E,          KC_R,          KC_T, /****/ KC_Y,  KC_U,          KC_I,          KC_O,          KC_P,             XXXXXXX,
        XXXXXXX,  LCTL_T(KC_A),  LALT_T(KC_S),  LGUI_T(KC_D),  LSFT_T(KC_F),  KC_G, /****/ KC_H,  RSFT_T(KC_J),  RGUI_T(KC_K),  RALT_T(KC_L),  RCTL_T(KC_SCLN),  XXXXXXX,
        XXXXXXX,  KC_Z,          KC_X,          KC_C,          KC_V,          KC_B, /****/ KC_N,  KC_M,          KC_COMM,       KC_DOT,        KC_SLSH,          XXXXXXX,

                                            KC_LGUI, LT(_SYMBOLS,KC_BSPC), KC_LSFT, /****/ RSFT_T(KC_ENT), LT(_FUNCS,KC_SPC), RGUI_T(KC_ESC)
    ),

    [1] /* _GAMING */ = LAYOUT_split_3x6_3(
        KC_TAB,   KC_Q,  KC_W,  KC_E,  KC_R,  KC_T, /****/ KC_Y,  KC_U,  KC_I,     KC_O,    KC_P,     KC_BSPC,
        KC_LCTL,  KC_A,  KC_S,  KC_D,  KC_F,  KC_G, /****/ KC_H,  KC_J,  KC_K,     KC_L,    KC_SCLN,  KC_QUOT,
        KC_LSFT,  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B, /****/ KC_N,  KC_M,  KC_COMM,  KC_DOT,  KC_SLSH,  KC_BSLS,

                   KC_LGUI, KC_SPC, LSFT_T(KC_ESC), /****/ RSFT_T(KC_ENT), LT(_FUNCS,KC_SPC), MO(_SYMBOLS)
    ),

    [2] /* _SYMBOLS */ = LAYOUT_split_3x6_3(
        XXXXXXX,  KC_TAB,    KC_BSLS,  KC_LCBR,  KC_RCBR,  KC_ASTERISK,   /****/ KC_KP_PLUS,   KC_1,  KC_2,  KC_3,  KC_KP_ASTERISK,  XXXXXXX,
        XXXXXXX,  KC_QUOT,   KC_PIPE,  KC_LPRN,  KC_RPRN,  KC_KP_MINUS,   /****/ KC_KP_MINUS,  KC_4,  KC_5,  KC_6,  KC_KP_SLASH,     XXXXXXX,
        XXXXXXX,  KC_TILDE,  KC_GRV,   KC_LBRC,  KC_RBRC,  KC_UNDERSCORE, /****/ KC_KP_DOT,    KC_7,  KC_8,  KC_9,  KC_KP_EQUAL,     XXXXXXX,

                                             XXXXXXX, _______, KC_LSFT, /****/ KC_RSFT, XXXXXXX, KC_0
    ),

    [3] /* _FUNCS */ = LAYOUT_split_3x6_3(
        XXXXXXX,  KC_F1,        KC_F2,      KC_F3,    KC_F4,    KC_F5,   /****/ KC_F6,      KC_F7,        KC_F8,    KC_F9,     KC_F10,  XXXXXXX,
        XXXXXXX,  XXXXXXX,      KC_VOLD,    KC_VOLU,  KC_MUTE,  XXXXXXX, /****/ KC_LEFT,    KC_DOWN,      KC_UP,    KC_RIGHT,  KC_F11,  XXXXXXX,
        XXXXXXX,  TO(_GAMING),  TO(_BASE),  XXXXXXX,  XXXXXXX,  CW_TOGG, /****/ LSG(KC_4),  LCG(KC_SPC),  XXXXXXX,  XXXXXXX,   KC_F12,  XXXXXXX,

                                              XXXXXXX, XXXXXXX, XXXXXXX, /****/ XXXXXXX, _______, MO(_RGB)
    ),

    [4] /* _RGB */ = LAYOUT_split_3x6_3(
        XXXXXXX,  QK_BOOT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, /****/ XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  RM_TOGG,  RM_HUEU,  RM_SATU,  RM_VALU,  XXXXXXX, /****/ XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
        XXXXXXX,  RM_NEXT,  RM_HUED,  RM_SATD,  RM_VALD,  XXXXXXX, /****/ XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,

                                        XXXXXXX, XXXXXXX, XXXXXXX, /****/ XXXXXXX, _______, _______
    )
};

const uint16_t PROGMEM combo1[] = { RSFT_T(KC_J), RGUI_T(KC_K), COMBO_END };
combo_t key_combos[] = {
    COMBO(combo1, KC_ESC),
};

// my ctrl-s rollover with home row mods needs help...
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LCTL_T(KC_A):
            return 180;
        default:
            return TAPPING_TERM;
    }
}

// LED NUMBERS (6x LEDs per split for under-lighting, 0-5 and 27-52)
//
//    24    23    18    17    10    9  --  36    37    44    45    50    51
//    25    22    19    16    11    8  --  35    38    43    46    49    52
//    26    21    20    15    12    7  --  34    39    42    47    48    53
//                      14    13    6  --  33    40    41

// Layer colors (HSV format)
const uint8_t PROGMEM layer_colors[][3] = {
    [_BASE]    = { HSV_BLUE },
    [_GAMING]  = { HSV_GREEN },
    [_SYMBOLS] = { HSV_RED },
    [_FUNCS]   = { HSV_OFF },
    [_RGB]     = { HSV_OFF },
};

// This callback fires on every RGB refresh cycle
// It runs on BOTH sides of the split automatically
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    int i;

    // Set base color for current layer across all keys
    HSV hsv = {
        .h = pgm_read_byte(&layer_colors[layer][0]),
        .s = pgm_read_byte(&layer_colors[layer][1]),
        .v = pgm_read_byte(&layer_colors[layer][2])
    };

    // Respect current brightness setting
    if (hsv.v > rgb_matrix_get_val())
        hsv.v = rgb_matrix_get_val();

    RGB rgb = hsv_to_rgb(hsv);

    // Paint all LEDs in this side's range with layer color
    for (uint8_t i = led_min; i < led_max; i++)
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);

    const uint8_t off_keys[] = { 24, 25, 26, 51, 52, 53 };
    const uint8_t hrm_keys[] = { 11, 16, 19, 22, 38, 43, 46, 49 };
    const uint8_t num_keys[] = { 10, 11, 12, 15, 16, 17, 37, 38, 39, 42, 43, 44, 45, 46, 47 };
    const uint8_t func_keys[] = { 9, 10, 17, 18, 23, 36, 37, 44, 45, 48, 49, 50 };
    const uint8_t vol_keys[] = { 11, 16, 19 };
    const uint8_t arrow_keys[] = { 35, 38, 43, 46 };
    const uint8_t bt_keys[] = { 15, 20, 21 };
    const uint8_t macos_keys[] = { 34, 39 };
    const uint8_t rgb_keys[] = { 11, 12, 15, 16, 19, 20, 21, 22, 23 };

    HSV hrm_hsv = { HSV_CYAN };
    HSV num_hsv = { HSV_CYAN };
    HSV func_hsv = { HSV_CYAN };
    HSV vol_hsv = { HSV_GREEN };
    HSV arrow_hsv = { HSV_BLUE };
    HSV bt_hsv = { HSV_RED };
    HSV macos_hsv = { HSV_ORANGE };
    HSV rgb_hsv = { HSV_ORANGE };

    // Respect current brightness setting
    if (hrm_hsv.v > rgb_matrix_get_val())
        hrm_hsv.v = rgb_matrix_get_val();
    if (num_hsv.v > rgb_matrix_get_val())
        num_hsv.v = rgb_matrix_get_val();
    if (func_hsv.v > rgb_matrix_get_val())
        func_hsv.v = rgb_matrix_get_val();
    if (vol_hsv.v > rgb_matrix_get_val())
        vol_hsv.v = rgb_matrix_get_val();
    if (arrow_hsv.v > rgb_matrix_get_val())
        arrow_hsv.v = rgb_matrix_get_val();
    if (bt_hsv.v > rgb_matrix_get_val())
        bt_hsv.v = rgb_matrix_get_val();
    if (macos_hsv.v > rgb_matrix_get_val())
        macos_hsv.v = rgb_matrix_get_val();
    if (rgb_hsv.v > rgb_matrix_get_val())
        rgb_hsv.v = rgb_matrix_get_val();

    RGB hrm_rgb = hsv_to_rgb(hrm_hsv);
    RGB num_rgb = hsv_to_rgb(num_hsv);
    RGB func_rgb = hsv_to_rgb(func_hsv);
    RGB vol_rgb = hsv_to_rgb(vol_hsv);
    RGB arrow_rgb = hsv_to_rgb(arrow_hsv);
    RGB bt_rgb = hsv_to_rgb(bt_hsv);
    RGB macos_rgb = hsv_to_rgb(macos_hsv);
    RGB rgb_rgb = hsv_to_rgb(rgb_hsv);

    // Per-key overrides for specific layers
    if (layer == _BASE) {

        for (i = 0; i < sizeof(off_keys); i++) {
            if (off_keys[i] >= led_min && off_keys[i] < led_max)
                rgb_matrix_set_color(off_keys[i], RGB_OFF);
        }

        for (i = 0; i < sizeof(hrm_keys); i++) {
            if (hrm_keys[i] >= led_min && hrm_keys[i] < led_max)
                rgb_matrix_set_color(hrm_keys[i], hrm_rgb.r, hrm_rgb.g, hrm_rgb.b);
        }

    } else if (layer == _SYMBOLS) {

        for (i = 0; i < sizeof(off_keys); i++) {
            if (off_keys[i] >= led_min && off_keys[i] < led_max)
                rgb_matrix_set_color(off_keys[i], RGB_OFF);
        }

        for (i = 0; i < sizeof(num_keys); i++) {
            if (num_keys[i] >= led_min && num_keys[i] < led_max)
                rgb_matrix_set_color(num_keys[i], num_rgb.r, num_rgb.g, num_rgb.b);
        }

    } else if (layer == _FUNCS) {

        // for (i = 0; i < sizeof(off_keys); i++) {
        //     if (off_keys[i] >= led_min && off_keys[i] < led_max)
        //         rgb_matrix_set_color(off_keys[i], RGB_OFF);
        // }

        for (i = 0; i < sizeof(func_keys); i++) {
            if (func_keys[i] >= led_min && func_keys[i] < led_max)
                rgb_matrix_set_color(func_keys[i], func_rgb.r, func_rgb.g, func_rgb.b);
        }

        for (i = 0; i < sizeof(vol_keys); i++) {
            if (vol_keys[i] >= led_min && vol_keys[i] < led_max)
                rgb_matrix_set_color(vol_keys[i], vol_rgb.r, vol_rgb.g, vol_rgb.b);
        }

        for (i = 0; i < sizeof(arrow_keys); i++) {
            if (arrow_keys[i] >= led_min && arrow_keys[i] < led_max)
                rgb_matrix_set_color(arrow_keys[i], arrow_rgb.r, arrow_rgb.g, arrow_rgb.b);
        }

        for (i = 0; i < sizeof(bt_keys); i++) {
            if (bt_keys[i] >= led_min && bt_keys[i] < led_max)
                rgb_matrix_set_color(bt_keys[i], bt_rgb.r, bt_rgb.g, bt_rgb.b);
        }

        for (i = 0; i < sizeof(macos_keys); i++) {
            if (macos_keys[i] >= led_min && macos_keys[i] < led_max)
                rgb_matrix_set_color(macos_keys[i], macos_rgb.r, macos_rgb.g, macos_rgb.b);
        }

    } else if (layer == _RGB) {

        for (i = 0; i < sizeof(rgb_keys); i++) {
            if (rgb_keys[i] >= led_min && rgb_keys[i] < led_max)
                rgb_matrix_set_color(rgb_keys[i], rgb_rgb.r, rgb_rgb.g, rgb_rgb.b);
        }

    }

    return false;  // Continue with other effects if any
}

#ifdef OLED_ENABLE

bool oled_task_user(void) {
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:    oled_write_P(PSTR("base\n"), false); break;
        case _GAMING:  oled_write_P(PSTR("gaming\n"), false); break;
        case _SYMBOLS: oled_write_P(PSTR("symbols\n"), false); break;
        case _FUNCS:   oled_write_P(PSTR("funcs\n"), false); break;
        case _RGB:     oled_write_P(PSTR("rgb\n"), false); break;
        default:       oled_write_P(PSTR("unknown\n"), false); break;
    }

    oled_write_P(PSTR("\n"), false);

    if (is_caps_word_on())
        oled_write_P(PSTR("CAPS WORD ON\n"), false);
    else
        oled_write_P(PSTR("\n"), false);

    return false;
}

#endif

