bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    uint8_t mod_state = get_mods() | get_weak_mods();
    bool is_alt_held = mod_state & MOD_MASK_ALT;

    switch (keycode) {
        // While ALT is held, make thumbs Alt+Tab/Alt+Shift+Tab.
        case LT(3, KC_SPC):
            if (is_alt_held && record->event.pressed) {
                tap_code16(KC_TAB);
                return false;
            }
            break;
        case LT(6, KC_TAB):
        case LT(6, KC_DEL):
            if (is_alt_held && record->event.pressed) {
                tap_code16(LSFT(KC_TAB));
                return false;
            }
            // If ALT isn't held, continue with default handling.
            break;
        
        return false;
    }
    
    return true;
}
