#pragma once

#ifndef GP_PLAID_LAYERS
#    define GP_PLAID_LAYERS

#    include QMK_KEYBOARD_H
#    include <keymap_french_osx.h>
#    include "./defs.h"
#    include "./keycodes.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Annie Layeer
     * ,-----------------------------------------------------------------------------------------------------------.
     * | Tab              |   Q  |   C   |   L  |   P  |   B   |   K   |   F  |   O  |   Y  |   K  | Bksp          |
     * |------------------+------+-------+------+------+-------+-------+------+------+------+------+---------------|
     * | Esc or AnnieAlt  |   A  |   S   |   R  |   T  |   G   |   M   |   N  |   E  |   I  |   U  | AnneAlt       |
     * |------------------+------+-------+------+------+-------|-------+------+------+------+------+---------------|
     * | Ctrl + Alt       |   Z  |   V   |   J  |   D  |   W   |   X   |   H  |   ,  |   .  |   /  | Ctrl + Alt    |
     * |------------------+------+-------+------+------+-------+-------+------+------+------+------+---------------|
     * | RAlt             | Ctrl | LALT  | LGUI | LSFT | NMSBC | CDENT | RSFT | RGUI | RALT | Ctrl | RAlt          |
     * `--------------------------------------------------------------------------------------------------------'
     */
    // clang-format off
[_ANNIE] = LAYOUT_plaid_grid(
  KC_TAB,  FR_Q,    FR_C,    FR_L,    FR_P,    FR_B,   FR_K,   FR_F,    FR_O,    FR_Y,    FR_MINS, KC_BSPC,
  FR_ESC,  LCTL_A,  LALT_S,  LGUI_R,  FR_T,    FR_G,   FR_M,   FR_N,    RGUI_E,  RALT_I,  RCTL_U,  FRENCH,
  CT_ALT,  FR_Z,    FR_V,    FR_J,    FR_D,    FR_W,   FR_X,   FR_H,    FR_COMM, FR_DOT,  FR_SLSH, CT_ALT,
  KC_RALT, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, NM_SPC, CD_ENT, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, KC_RALT
),

[_QWERTY] = LAYOUT_plaid_grid(
  KC_TAB,  FR_Q,    FR_W,    FR_E,    FR_R,    FR_T,    FR_Y,    FR_U,    FR_I,    FR_O,    FR_P,    KC_BSPC,
  KC_ESC,  FR_A,    FR_S,    FR_D,    FR_F,    FR_G,    FR_H,    FR_J,    FR_K,    FR_L,    FR_SCLN, FR_QUOT,
  CT_ALT,  FR_Z,    FR_X,    FR_C,    FR_V,    FR_B,    FR_N,    FR_M,    FR_COMM, FR_DOT,  FR_SLSH, CT_ALT,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* French Layer
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   œ  |   «  |   ê  |   ù  |   °  |      |   ‘  |   ’  |   –  |   –  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ___  |   à  |   ’  |   é  |   è  |   ç  |      |   @  |   €  |   ˆ  |   @  |  €   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ___  |   æ  |   »  |   ¨  |   ˆ  |   €  |   +  |   -  |   #  |   …  |   \  | ___  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ___  | ___  | ___  | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * `-----------------------------------------------------------------------------------'
 */
[_FRENCH] = LAYOUT_plaid_grid(
  FR_GRV,  FR_OE,   FR_LDAQ, FR_ECIR, FR_LUGR, FR_DEG,  XXXXXXX, FR_LSQU, FR_LRQU, XXXXXXX, FR_NDSH, _______,
  _______, FR_LAGR, FR_LRQU, FR_LEAC, FR_LEGR, FR_LCCE, XXXXXXX, FR_AT,   FR_EURO, FR_CIRC, FR_AT,   FR_DLR,
  _______, FR_AE,   FR_RDAQ, FR_DIAE, FR_CIRC, FR_EURO, FR_PLUS, FR_MINS, FR_HASH, FR_ELLP, FR_BSLS, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Code Layer
 *
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   &  |   <  |   [  |   ]  |   /  |      |   "  |   '  |      |      | DEL  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ESC  |   `  |   =  |   (  |   )  |   !  |   ^  |   :  |   ;  |      |   @  |  $   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ____ |   |  |   >  |   {  |   }  |   %  |   +  |   -  |   #  |   …  |   \  | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ___  | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * `-----------------------------------------------------------------------------------'
 */
[_CODE] = LAYOUT_plaid_grid(
  __TILD,  FR_AMPR, FR_LABK, FR_LBRC, FR_RBRC, FR_SLSH, XXXXXXX, FR_DQUO, FR_QUOT, XXXXXXX, FR_UNDS, KC_DEL,
  KC_ESC,  __GRV,   FR_EQL,  FR_LPRN, FR_RPRN, FR_EXLM, __CIRC,  FR_COLN, FR_SCLN, XXXXXXX, FR_AT,   FR_DLR,
  _______, FR_PIPE, FR_RABK, FR_LCBR, FR_RCBR, FR_PERC, FR_PLUS, FR_MINS, FR_HASH, FR_ELLP, FR_BSLS, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Numbers Layer
 * ,-------------------------------------------------------------------------------------------.
 * | ____ |   1  |   2  |    3    |     4     |   5  |   6  |   7  |   8  |   9  |   0  | ____ |
 * |------+------+------+---------+-----------+------+------+------+------+------+------+------|
 * | ____ |      | home | page up | page down | end  | Left | Down | Up   | Right|   *  | ____ |
 * |------+------+------+---------+-----------+------|------+------+------+------+------+------|
 * | ____ |      |      |         |           |      |   +  |   -  |   ,  |   .  |   /  | ____ |
 * |------+------+------+---------+-----------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | _______ | _________ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * `-------------------------------------------------------------------------------------------'
 */
[_NUMBERS] = LAYOUT_plaid_grid(
    _______, FR_1,    FR_2,    FR_3,    FR_4,      FR_5,    FR_6,    FR_7,    FR_8,    FR_9,    FR_0,    _______,
    _______, XXXXXXX, KC_HOME, KC_PGUP, KC_PGDOWN, KC_END,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, FR_ASTR, _______,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, FR_PLUS, FR_MINS, FR_COMM, FR_DOT,  FR_SLSH, _______,
    _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______
),


/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Reset |      |      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Norman|Annie |Fou   |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_plaid_grid(
    RESET,   LED_1,   LED_2,   MAGIC_TOGGLE_GUI, MAGIC_UNSWAP_GRAVE_ESC, LED_5,   LED_6,   LED_7,   LED_8,   LED_9,   LED_0,   KC_DEL,
    ANNIE,   KC_F1,   KC_F2,   KC_F3,            KC_F4,                  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
    QWERTY,  DT_DOWN, KC_BRID, KC_BRIU,          DT_UP,                  DT_PRNT, KC_MUTE, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______,
    _______, _______, _______, _______,          _______,                _______, _______, _______, _______, _______, _______, _______
)
    // clang-format on
};
#endif
