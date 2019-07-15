#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // 0: F13 - 16
    [0] = LAYOUT_all(LT(1, KC_F13), KC_F14, KC_F15, LT(2, KC_F16)),

    // 1: F17 - 19
    [1] = LAYOUT_all(_______, KC_F17, KC_F18, KC_F19),

    // 2: F20 - 22
    [2] = LAYOUT_all(KC_F20, KC_F21, KC_F22, _______),

};
