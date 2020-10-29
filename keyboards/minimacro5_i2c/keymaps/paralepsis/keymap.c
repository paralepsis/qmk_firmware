#include QMK_KEYBOARD_H

enum layers {
     _MAIN,
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
    if (clockwise) {
      tap_code(KC_WH_D);
    } else {
      tap_code(KC_WH_U);
    }
  }
}

//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { //buttion closest to usb is first
  [_MAIN] = LAYOUT_ortho_1x5(
     KC_MUTE, LGUI(KC_0), KC_3, KC_PGUP, KC_PGDN
  )
};
