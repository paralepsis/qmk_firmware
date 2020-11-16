#include QMK_KEYBOARD_H

static const char encFnS0[] PROGMEM = "Vol Up/Down/Mute\n";
static const char encFnS1[] PROGMEM = "Zoom In/Out/Reset\n";
static const char encFnS2[] PROGMEM = "Page Up/Down\n";
static const char encFnS3[] PROGMEM = "Scroll Up/Down\n";
static const char encFnS4[] PROGMEM = "Scroll Left/Right\n";

struct encFn {
   const char     *string;
   const uint16_t  clockwise;
   const uint16_t  countercw;
   const uint16_t  press;
};

static struct encFn myFn[] = {
   { encFnS0, KC_VOLU, KC_VOLD, KC_MUTE }, /* 0 */
   { encFnS1, LGUI(KC_EQUAL), LGUI(KC_MINUS), LGUI(KC_0) }, /* 1 */
   { encFnS2, KC_PGDOWN, KC_PGUP, KC_HOME }, /* 2 */
   { encFnS3, KC_WH_D, KC_WH_U, KC_HOME }, /* 3 */
   { encFnS4, KC_WH_R, KC_WH_L, KC_HOME }, /* 4 */
};

enum layers {
     _MAIN,
     _PROG,
};

/* array holding current encoder function assignments */
static int curEncFn[] = { 0, 1, 2 };

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index > 2) return;

  if (clockwise) {
    tap_code16(myFn[curEncFn[index]].clockwise);
  } else {
    tap_code16(myFn[curEncFn[index]].countercw);
  }
}

//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { //buttion closest to usb is first
  [_MAIN] = LAYOUT_ortho_1x5(
     KC_MUTE, LGUI(KC_0), TO(_PROG), KC_PGUP, KC_PGDN
  ),
  [_PROG] = LAYOUT_ortho_1x5(
     KC_MUTE, LGUI(KC_0), TO(_MAIN), KC_PGUP, KC_PGDN
  )
};

#ifdef OLED_DRIVER_ENABLE
void oled_task_user(void) {
    // Host Keyboard Layer Status
    // oled_write_P(PSTR("Vol Up/Down/Mute\n"), false);
    oled_write_P(myFn[curEncFn[0]].string, false);
    oled_write_P(myFn[curEncFn[1]].string, false);
    switch (get_highest_layer(layer_state)) {
        case _MAIN:
            oled_write_P(PSTR("Page Up/Down\n"), false);
            break;
        case _PROG:
            oled_write_P(PSTR("Scroll Up/Down\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    oled_write_P(PSTR("Enc3 changes mode.\n"), false);
}
#endif
