#include QMK_KEYBOARD_H

enum layers {
     _MAIN,
     _ALT,
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder*/
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  } else if (index == 1) { /* Second encoder*/
    if (clockwise) {
      //tap_code(KC_WH_R);
      tap_code16(LGUI(LSFT(KC_EQUAL)));
    } else {
      //tap_code(KC_WH_L);
      tap_code16(LGUI(KC_MINUS));
    }
  } else if (index == 2) { /* Third encoder*/
    switch(biton32(layer_state)) {
      case _MAIN:
        if (clockwise) {
          tap_code(KC_PGDOWN);
        } else {
          tap_code(KC_PGUP);
        }
        break;
      case _ALT:
        if (clockwise) {
          tap_code(KC_WH_D);
        } else {
          tap_code(KC_WH_U);
        }
        break;
      default:
        break;
    }
  }
}

//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { //buttion closest to usb is first
  [_MAIN] = LAYOUT_ortho_1x5(
     KC_MUTE, LGUI(KC_0), TO(_ALT), KC_PGUP, KC_PGDN
  ),
  [_ALT] = LAYOUT_ortho_1x5(
     KC_MUTE, LGUI(KC_0), TO(_MAIN), KC_PGUP, KC_PGDN
  )
};

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Vol Up/Down/Mute\n"), false);
    oled_write_P(PSTR("Zoom In/Out/Reset\n"), false);
    switch (get_highest_layer(layer_state)) {
        case _MAIN:
            oled_write_P(PSTR("Page Up/Down\n"), false);
            break;
        case _ALT:
            oled_write_P(PSTR("Scroll Up/Down\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    oled_write_P(PSTR("Enc3 changes mode.\n"), false);
}
#endif
