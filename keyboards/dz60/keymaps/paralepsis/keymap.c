#include QMK_KEYBOARD_H

/* DZ60 layout:
 * - default is a fairly normal setup with VI style arrows on RHS and ESC/BS in upper right.
 * - if key next to RHS shift is held, BS key can then be used to get into a nonstandard mode I like.
 * - when in that mode, D + top right key is a soft reset button.
 * - getting back out of that mode is as simple as hitting bottom left key.
 */

#define _NORMAL 0
#define _SWAP 1
#define _FN1 2
#define _FN2 3

#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_NORMAL] = LAYOUT(
		KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_ESC,  LCTL(LGUI(KC_Q)), 
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
		LCTL_T(KC_ESC), KC_A, KC_S, LT(_FN1,KC_D), KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_NO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(_SWAP),
		KC_LCTL, KC_LALT, KC_LALT, KC_LGUI, KC_BSPC, KC_SPC, KC_RGUI, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),
	[_SWAP] = LAYOUT( 
		_______, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______, _______, _______,  QK_BOOT,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
	[_FN1] = LAYOUT( /* things that happen when holding the D key */
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, MO(_FN2), _______, KC_LEFT, KC_DOWN, KC_UP , KC_RIGHT, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY),
	[_FN2] = LAYOUT( /* things that happen when holding the D and F keys */
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP  , KC_END, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
};

/* 
uint32_t default_layer_state_set_user(layer_state_t state) {
    rgblight_setrgb (0x00,  0x00, 0x00);
    return state;
}

uint32_t layer_state_set_user(layer_state_t state) {
    switch (biton32(state)) {
    case _NORMAL:
        rgblight_setrgb (0x00,  0x00, 0x00);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (0x00,  0x00, 0x00);
        break;
    }
  return state;
}

*/
