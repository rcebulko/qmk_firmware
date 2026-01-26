/* Copyright 2023 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM top_outer_btns[] = {MS_BTN1, MS_BTN3, COMBO_END};
combo_t key_combos[] = {
    COMBO(top_outer_btns, QK_REBOOT)
};
enum custom_keycodes {
    ALT_TAB = SAFE_RANGE,
    ALT_SHIFT_TAB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        MO(1),      DPI_CONFIG,   DRAG_SCROLL, MS_BTN1,
        MS_BTN2,                               LT(2, MS_BTN3)
    ),
    [1] = LAYOUT(
        _______,    LCTL(KC_TAB), LCS(KC_TAB), ALT_SHIFT_TAB,
        ALT_TAB,                               _______
    ),
    [2] = LAYOUT(
        LCTL(KC_X),    LCS(KC_T),   LCTL(KC_W),   LCTL(KC_V),
        LCTL(KC_C),                         _______
    )
};

bool is_alt_tab_active = false;

layer_state_t layer_state_set_user(layer_state_t state) {
    if (is_alt_tab_active) {
        unregister_code(KC_LALT);
        is_alt_tab_active = false;
    }

    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                tap_code16(KC_TAB);
            }
            break;
        case ALT_SHIFT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                tap_code16(LSFT(KC_TAB));
            }
            break;
        
        return false;
    }
    
    return true;
}
