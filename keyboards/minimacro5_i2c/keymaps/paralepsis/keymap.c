#include QMK_KEYBOARD_H

/*
 * This keymap is meant for a modified miniMACRO5 with encoders in
 * positions 0..2 and a switch in position 3. Position 4 is not used:
 * it is covered by an OLED in this implementation to keep a similar
 * footprint as the original.
 *
 * Encoders are assigned functinality at runtime by holding the switch.
 * Current functionality is displayed on the OLED.
 *
 * Functionalities are defined in my_Fn below, which is an array of encFn
 * structures.
 */

/* encFn - describes a particular encoder functionality:
 * - string    - string desc. of the functionality to display on OLED
 * - clockwise - 16-bit tap code for clockwise (i.e., can be modded)
 * - countercw - 16-bit tap code for counter clockwise
 * - press     - 16-bit tap code for press
 */
struct encFn {
   const char     *string;
   const uint16_t  clockwise;
   const uint16_t  countercw;
   const uint16_t  press;
};

/*                                       "XXXXXXXXXXXXXXXXXXXX\n" */
static const char my_encFnS0[] PROGMEM = "Vol Up/Down/Mute\n";
static const char my_encFnS1[] PROGMEM = "Zoom In/Out/Reset\n";
static const char my_encFnS2[] PROGMEM = "Page Up/Down\n";
static const char my_encFnS3[] PROGMEM = "Scroll Up/Down\n";
static const char my_encFnS4[] PROGMEM = "Scroll Left/Right\n";
static const char my_encFnS5[] PROGMEM = "F20/F21/F22\n";
static const char my_encFnS6[] PROGMEM = "Track Nxt/Prv/Pause\n";
// static const char my_encFnS7[] PROGMEM = "App Next/Prev/All\n";


/* my_Fn - array of functionality options for encoders */
static struct encFn my_Fn[] = {
  { my_encFnS0, KC_VOLU, KC_VOLD, KC_MUTE }, /* 0 */
  { my_encFnS1, LGUI(KC_EQUAL), LGUI(KC_MINUS), LGUI(KC_0) }, /* 1 */
  { my_encFnS2, KC_PGDOWN, KC_PGUP, KC_HOME }, /* 2 */
  { my_encFnS3, KC_WH_D, KC_WH_U, KC_HOME }, /* 3 */
  { my_encFnS4, KC_WH_R, KC_WH_L, KC_HOME }, /* 4 */
  { my_encFnS5, KC_F20, KC_F21, KC_F22 }, /* 5 */
  { my_encFnS6, KC_MFFD, KC_MRWD, KC_MPLY }, /* 6 */
  // { my_encFnS7, LGUI(KC_TAB), LGUI(S(KC_TAB)), LCTL(KC_UP) }, /* 7 */
};
static uint16_t my_FnMax = (sizeof(my_Fn) / sizeof(struct encFn)) - 1;
static bool my_Rotate180 = true;

/* array holding current encoder functionality assignments */
static int my_curEncFn[] = { 0, 1, 2 };

/* Add keycodes for the three encoders' presses:
 */
enum my_keycodes {
  MY_S0 = SAFE_RANGE,
  MY_S1,
  MY_S2
};

/* Two layers:
 * - _MAIN - normal operation
 * - _PROG - mode in which functionality assignment may be modified
 */
enum layers {
     _MAIN,
     _PROG,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MY_S0:
      if (record->event.pressed) {
        tap_code16(my_Fn[my_curEncFn[0]].press);
      }
      break;
    case MY_S1:
      if (record->event.pressed) {
        tap_code16(my_Fn[my_curEncFn[1]].press);
      }
      break;
    case MY_S2:
      if (record->event.pressed) {
        tap_code16(my_Fn[my_curEncFn[2]].press);
      }
      break;
    default:
      break;
  }
  return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index > 2) return;

  switch (get_highest_layer(layer_state)) {
    case _MAIN:
      if (clockwise) {
        tap_code16(my_Fn[my_curEncFn[index]].clockwise);
      } else {
        tap_code16(my_Fn[my_curEncFn[index]].countercw);
      }
      break;
    case _PROG:
      if (clockwise) {
        if (my_curEncFn[index] < (my_FnMax)) {
          my_curEncFn[index]++;
        } else {
          my_curEncFn[index] = 0;
        }
      } else {
        if (my_curEncFn[index] > 0) {
          my_curEncFn[index]--;
        } else {
          my_curEncFn[index] = my_FnMax;
        }
      }
      break;
    default:
      break;
  }

#ifdef OLED_DRIVER_ENABLE
  /* OLED code doesn't turn on OLED after encoder_update(). */
  oled_on();
#endif
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT_ortho_1x5(
     MY_S0, MY_S1, MY_S2, MO(_PROG), KC_NO
  ),
  [_PROG] = LAYOUT_ortho_1x5(
     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};

#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return (my_Rotate180) ? OLED_ROTATION_180 : OLED_ROTATION_0;
}

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
