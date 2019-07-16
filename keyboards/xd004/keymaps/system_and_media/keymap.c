#include QMK_KEYBOARD_H

#define _BASE 0    // Base layer
#define _SYSTEM 1  // System actions
#define _VOLUME 2  // Volume actions

#define SUPER_KEY_TIMER 500  // Timeout on the super keys

/*
    The idea of this is pretty simple: base layer has four action, two of which (the outermost)
    are regular keystrokes on tap, and a momentary layer switch on hold, sending you to layers 1 and 2.

    The other bit of customization here is the 'Super Alt F4' which does Alt-F4, and then Enter if tapped
    again SUPER_ALT_F4_TIMER miliseconds after. This lets you Alt-F4 applications, and finally quickly
    double-tap it to Alt-F4+Enter to shut down the PC.
*/

bool     is_super_key_active  = false;
uint16_t super_key_timer      = 0;

enum custom_keycodes {  // Make sure have the awesome keycode ready
    SUPER_ALT_F4 = SAFE_RANGE,
    SUPER_ALT_TAB,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // 0: Base Layer
    [_BASE] = LAYOUT_all(LT(_SYSTEM, KC_F5), C(G(KC_LEFT)), C(G(KC_RIGHT)), LT(_VOLUME, KC_F7)),

    // 1: System actions
    [_SYSTEM] = LAYOUT_all(_______, SUPER_ALT_F4, SUPER_ALT_TAB, G(KC_L)),

    // 2: Volume actions
    [_VOLUME] = LAYOUT_all(KC_MEDIA_NEXT_TRACK, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, _______),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {  // This will do most of the grunt work with the keycodes.
        case SUPER_ALT_F4:
            if (record->event.pressed) {
                if (!is_super_key_active) {
                    is_super_key_active = true;
                    tap_code16(LALT(KC_F4));  // Alt-F4
                } else {
                    tap_code(KC_ENTER);  // Tap enter
                }
            }
            super_key_timer = timer_read();
            break;
        case SUPER_ALT_TAB:
            if (record->event.pressed) {
                if (!is_super_key_active) {
                    is_super_key_active = true;
                    register_code(KC_LALT);
                }
                super_key_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
    }
    return true;
}

void matrix_scan_user(void) {
    if (is_super_key_active && timer_elapsed(super_key_timer) > SUPER_KEY_TIMER)
    {
        unregister_code(KC_LALT);
        is_super_key_active = false;
    }
};
