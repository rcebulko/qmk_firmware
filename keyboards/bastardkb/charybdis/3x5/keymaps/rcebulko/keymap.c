#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define LAYER_POINTER 9
// Automatically enable sniping-mode on the pointer layer.
// #define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 800
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 1
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE


/** \brief Mouse emulation and pointer functions. */
#define LAYOUT_wrapper(...) LAYOUT_charybdis_3x5(__VA_ARGS__)
#define XXXXXXX KC_NO
#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
/*#define LAYOUT_LAYER_POINTER                                                                  \
    _______, _______, XXXXXXX, DPI_RMOD, S_D_RMOD, S_D_MOD, DPI_MOD, XXXXXXX, _______, _______, \
    _______, _______, SNIPING, KC_BTN3, _______, _______, KC_BTN3, SNIPING, SNP_TOG, XXXXXXX, \
    _______, _______, SNIPING, KC_BTN3, XXXXXXX, KC_BTN2, KC_BTN3, SNIPING, SNP_TOG, XXXXXXX, \
                      KC_BTN2, KC_BTN1, DRGSCRL, DRGSCRL, KC_BTN1*/
#define LAYOUT_LAYER_POINTER                                                                  \
    LGUI(KC_SPC), _______, DPI_RMOD, S_D_RMOD, _______,   _______, S_D_MOD, DPI_MOD, _______, _______, \
    _______,      KC_BTN2, KC_BTN3,  KC_BTN1,  _______,   _______, KC_BTN1, KC_BTN3, KC_BTN2, _______, \
    KC_CAPS,      _______, _______,  _______,  _______,   _______, _______, _______, _______, _______, \
                           SNP_TOG,  SNIPING,  DRGSCRL,   DRGSCRL, SNP_TOG

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT_split_3x5_3(LT(8,KC_QUOT), KC_COMM, KC_DOT, KC_P, KC_Y, KC_F, KC_G, KC_C, KC_R, LT(8,KC_L), LCTL_T(KC_A), LSFT_T(KC_O), LALT_T(KC_E), LT(1,KC_U), KC_I, KC_D, LT(2,KC_H), LALT_T(KC_T), RSFT_T(KC_N), RCTL_T(KC_S), MEH_T(KC_SCLN), C_S_T(KC_Q), LCA_T(KC_J), LT(6,KC_K), LT(7,KC_X), LT(7,KC_B), KC_M, LCA_T(KC_W), C_S_T(KC_V), MEH_T(KC_Z), LT(6,KC_DEL), KC_SPC, LT(4,KC_BSPC), LT(5,KC_ENT), KC_SPC, LT(6,KC_TAB)),
	[1] = LAYOUT_split_3x5_3(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SLSH, KC_7, KC_8, KC_P9, KC_MINS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PAST, KC_4, KC_5, KC_6, KC_PPLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_EQL, KC_1, KC_2, KC_3, KC_PDOT, KC_ESC, KC_TAB, KC_DEL, KC_TAB, KC_P0, TG(1)),
	[2] = LAYOUT_split_3x5_3(KC_EXLM, KC_AT, KC_LCBR, KC_RCBR, KC_BSLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HASH, KC_DLR, KC_LBRC, KC_RBRC, KC_GRV, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PERC, KC_CIRC, KC_LPRN, KC_RPRN, KC_TILD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ESC, KC_TAB, KC_DEL, KC_TRNS, KC_P0, TG(1)),
	[3] = LAYOUT_split_3x5_3(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[4] = LAYOUT_split_3x5_3(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LCTL(KC_C), KC_HOME, KC_UP, KC_END, KC_PGUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LCTL(KC_V), KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LCTL(KC_X), LCTL(KC_A), KC_TRNS, LCTL(KC_Y), LCTL(KC_Z), KC_TRNS, KC_TRNS, KC_TRNS, LGUI(KC_SPC), KC_TRNS, KC_TRNS),
	[5] = LAYOUT_split_3x5_3(KC_TRNS, KC_BTN2, KC_MS_U, KC_BTN1, KC_WH_U, LCTL(KC_C), KC_HOME, KC_UP, KC_END, KC_PGUP, KC_CAPS, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN3, LCTL(KC_V), KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_TRNS, KC_ACL0, KC_ACL1, KC_ACL2, KC_WH_D, LCTL(KC_X), LCTL(KC_A), KC_TRNS, LCTL(KC_Y), LCTL(KC_Z), KC_TRNS, KC_TRNS, LGUI(KC_SPC), KC_TRNS, RCS(KC_PSCR), RSFT(KC_PSCR)),
	[6] = LAYOUT_split_3x5_3(KC_TRNS, MEH(KC_LEFT), SGUI(KC_UP), MEH(KC_RGHT), KC_TRNS, KC_TRNS, LCA(KC_LEFT), LGUI(KC_UP), LCA(KC_RGHT), KC_TRNS, KC_TRNS, SGUI(KC_LEFT), SGUI(KC_DOWN), SGUI(KC_RGHT), KC_TRNS, KC_TRNS, LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_RGHT), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[7] = LAYOUT_split_3x5_3(KC_F1, KC_F2, KC_F3, KC_F4, KC_TRNS, KC_TRNS, KC_TRNS, LGUI(KC_UP), KC_TRNS, KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8, KC_TRNS, KC_TRNS, LGUI(KC_LEFT), LGUI(KC_DOWN), LGUI(KC_RGHT), KC_TRNS, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[8] = LAYOUT_split_3x5_3(RESET, RGB_M_P, RGB_TOG, RGB_MOD, KC_NO, KC_SLEP, KC_VOLU, KC_VOLU, KC_VOLU, RESET, KC_NO, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, KC_WAKE, KC_VOLD, KC_VOLD, KC_VOLD, KC_NO, KC_NO, RGB_HUD, RGB_SAD, RGB_VAD, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
	[LAYER_POINTER] = LAYOUT_wrapper(LAYOUT_LAYER_POINTER)
};


#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
	  float dist = mouse_report.x * mouse_report.x + mouse_report.y * mouse_report.y;
    if (dist > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD * CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
    	// if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    state = layer_state_set_user(state);
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE
