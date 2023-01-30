/* Copyright 2019 Takuya Urakawa (dm9records.com)
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
#include "keymap_french_osx.h"
#include "sendstring_french_osx.h"


void matrix_init_user() {
	set_unicode_input_mode(UC_MAC);
};
enum plaid_layers {
  _ANNIE,
  _QWERTY,
  _FRENCH,
  _CODE,
  _NUMBERS,
  _ADJUST
};

enum plaid_keycodes {
  ANNIE = SAFE_RANGE,
  QWERTY,
  FRENCH,
  CODE,
  NUMBERS,
  LED_1,
  LED_2,
  LED_3,
  LED_4,
  LED_5,
  LED_6,
  LED_7,
  LED_8,
  LED_9,
  LED_0,
  E_GRV, // è
  E_ACU, // é
  E_CIR, // ê
  A_GRV, // à
  U_GRV,  // ù
  X_CIRC, // ^
  __GRV, // `
  FR_LRQU
};

enum unicode_names {
  SPACE,
  NBSP,
  NNBSP,
  UNDERSCORE,
  COMMA,
  PERIOD,
  SLASH,
  ASTER,
  EXCLAM,
  QUEST
};

const uint32_t PROGMEM unicode_map[] = {
    [SPACE]  = 0x20,  // regular space
    [NBSP] = 0x00A0, // non-beakable sapce
    [NNBSP] = 0x202F, // narrow non-breakable space
    [UNDERSCORE] = '_',  // 
    [COMMA]  = ',', // 
    [PERIOD] = '.',
    [SLASH] = '/',
    [ASTER] = '*',
    [EXCLAM] = '!',
    [QUEST] = '?'
};

// array of keys considered modifiers for led purposes
const uint16_t modifiers[] = {
    KC_LCTL,
    KC_RCTL,
    KC_LALT,
    KC_RALT,
    KC_LSFT,
    KC_RSFT,
    KC_LGUI,
    KC_RGUI,
    CODE,
    NUMBERS,
    FRENCH,
};

//Setup consts for LED modes
#define LEDMODE_ON 1 //always on
#define LEDMODE_OFF 0 //always off
#define LEDMODE_MODS 2 //On with modifiers
#define LEDMODE_BLINKIN 3 //blinkinlights - % chance toggle on keypress
#define LEDMODE_KEY 4 //On with any keypress, off with key release
#define LEDMODE_ENTER 5 // On with enter key

//Keycode shortcuts
//Default Layer
#define FR_ESC LT(_FRENCH, KC_ESC)   // tap: esc, hold: french layer
#define FR_QUO LT(_FRENCH, KC_DQUO)
#define CT_ALT LCTL(KC_RALT) // control+alt
#define NM_SPC LT(_NUMBERS,  KC_SPACE) // tap: space, hold: number layer
#define CD_ENT LT(_CODE, KC_ENT)   // tap: enter, hold: number layer

// Home Row mods
// left hand
#define LCTL_A LCTL_T(FR_A)
#define LCTL_I LCTL_T(FR_I)
#define LALT_S LALT_T(FR_S)
#define LGUI_R LGUI_T(FR_R)
// qwerty
#define LGUI_D LGUI_T(FR_D)
// right hand
#define RGUI_E RGUI_T(FR_E)
#define RALT_I RALT_T(FR_I)
#define RALT_A RALT_T(FR_A)
#define RCTL_U RCTL_T(FR_U)
// qwerty
#define RGUI_K RGUI_T(KC_K)
#define RALT_L RALT_T(KC_L)
#define RCTL_SC RCTL_T(KC_SCLN)

//Code Layer
#define TH_DOT RALT(KC_SCLN) // …
//French Layer
#define F_OE   RALT(KC_O)    // œŒ
#define F_LQUO RALT(KC_BSLS) // «
#define F_RQUO LSA(KC_BSLS)  // »
#define E_RQUO LSA(KC_RBRC)  // ’
#define E_RDQU LSA(KC_LBRC)  // ”
#define E_LQUO RALT(KC_RBRC) // ‘
#define E_LDQU RALT(KC_LBRC) // “
#define F_DEGR LSA(KC_8)     // °
#define F_GRMD RALT(KC_GRV)  // `
#define F_ACMD RALT(KC_E)    // ´
#define F_CIMD RALT(KC_I)    // ˆ
#define F_TRMD RALT(KC_U)    // ¨
#define F_AE   RALT(KC_QUOT) // æÆ
#define F_AT   RALT(KC_2)    // @
#define F_EURO LSA(KC_2)     // €
#define F_CCED RALT(KC_C)    // çÇ
#define F_MDOT LSA(KC_9)     // ·

const uint16_t PROGMEM CB_ESC[] = { KC_N, RGUI_E, COMBO_END };
const uint16_t PROGMEM CB_TAB[] = { KC_T, LGUI_R, COMBO_END };
const uint16_t PROGMEM CB_BSPC[] = { KC_F, KC_O, COMBO_END };
const uint16_t PROGMEM CB_DEL[] = { KC_L, KC_P, COMBO_END };

combo_t key_combos[COMBO_COUNT] = {
	COMBO(CB_ESC, KC_ESC),
	COMBO(CB_TAB, KC_TAB),
	COMBO(CB_BSPC, KC_BSPC),
	COMBO(CB_DEL, KC_DEL),
};

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
[_ANNIE] = LAYOUT_plaid_grid(
    KC_TAB,  FR_Q,    FR_C,    FR_L,    FR_P,    FR_B,   FR_K,   FR_F,    FR_O,    FR_Y,    FR_MINS, KC_BSPC,
    FR_ESC,  LCTL_A,  LALT_S,  LGUI_R,  FR_T,    FR_G,   FR_M,   FR_N,    RGUI_E,  RALT_I,  RCTL_U,   FRENCH,
    CT_ALT,  FR_Z,    FR_V,    FR_J,    FR_D,    FR_W,   FR_X,   FR_H,    FR_COMM, FR_DOT,  FR_SLSH,  CT_ALT,
    KC_RALT, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, NM_SPC, CD_ENT, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL,  KC_RALT
),

[_QWERTY] = LAYOUT_plaid_grid(
	KC_TAB,  FR_Q,    FR_W,    FR_E,    FR_R,    FR_T,    FR_Y,    FR_U,    FR_I,    FR_O,    FR_P,    KC_BSPC,
	KC_ESC,  FR_A,    FR_S,    FR_D,    FR_F,    FR_G,    FR_H,    FR_J,    FR_K,    FR_L,    FR_SCLN, FR_QUOT,
	CT_ALT,  FR_Z,    FR_X,    FR_C,    FR_V,    FR_B,    FR_N,    FR_M,    FR_COMM, FR_DOT,  FR_SLSH, CT_ALT,
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* French Layer
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   œ  |   «  |   ê  |   ù  |   °  |      |   ‘  |   ’  |   –  |   ù  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ___  |   à  |   ’  |   é  |   è  |   ç  |      |   @  |   €  |   ˆ  |   @  |  €   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ___  |   æ  |   »  |   ¨  |   ˆ  |   €  |   +  |   -  |   #  |   …  |   \  | ___  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ___  | ___  | ___  | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * `-----------------------------------------------------------------------------------'
 */

[_FRENCH] = LAYOUT_plaid_grid(
    FR_GRV,  FR_OE,    FR_LDAQ,  FR_ECIR,   FR_LUGR,   FR_DEG, XXXXXXX, FR_LSQU,  FR_LRQU,  FR_MDSH,   FR_MDSH, _______,
    _______, FR_LAGR,   FR_LRQU,  FR_LEAC,   FR_LEGR,   FR_LCCE,        XXXXXXX, FR_AT,   FR_EURO,  FR_CIRC, RALT(KC_GRV),          FR_EURO,
    _______, FR_AE,    FR_RDAQ,  FR_DIAE,  FR_CIRC,  FR_EURO,        FR_PLUS, FR_MINS, FR_HASH, FR_ELLP,  FR_BSLS,       _______,
    _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,       _______
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
 * | ____ | ____ | ____ | ___  | ____ |  DEL | ____ | ____ | ____ | ____ | ____ | ____ |
 * `-----------------------------------------------------------------------------------'
 */
	
[_CODE] = LAYOUT_plaid_grid(
    FR_TILD, FR_AMPR, FR_LABK,   FR_LBRC, FR_RBRC, FR_SLSH, XXXXXXX, FR_DQUO, FR_QUOT, XXXXXXX, FR_UNDS, KC_DEL,
    KC_ESC,    __GRV,  FR_EQL,  FR_LPRN, FR_RPRN, FR_EXLM,  X_CIRC, FR_COLN, FR_SCLN, XXXXXXX,FR_AT,   FR_DLR,
    _______,  FR_PIPE, FR_RABK,   FR_LCBR, FR_RCBR, FR_PERC, FR_PLUS, FR_MINS, FR_HASH, FR_ELLP,  FR_BSLS, _______,
    _______,  _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______
),


/* Numbers Layer
 * ,-------------------------------------------------------------------------------------------.
 * | ____ |   1  |   2  |    3    |     4     |   5  |   6  |   7  |   8  |   9  |   0  | ____ |
 * |------+------+------+---------+-----------+------+------+------+------+------+------+------|
 * | ____ |      | home | page up | page down |      | Left | Down | Up   | Right|   *  | ____ |
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
    RESET,   LED_1,   LED_2,   LED_3,   LED_4,   LED_5,   LED_6,   LED_7,   LED_8,   LED_9,   LED_0,   KC_DEL,
    ANNIE,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
    QWERTY,  DT_DOWN, KC_BRID, KC_BRIU, DT_UP,   DT_PRNT, KC_MUTE, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)



};

//Setup config struct for LED
typedef union {
  uint32_t raw;
  struct {
    uint8_t  red_mode :8;
    uint8_t  green_mode :8;
  };
} led_config_t;
led_config_t led_config;

//Set leds to saved state during powerup
void keyboard_post_init_user(void) {
  // set LED pin modes
  setPinOutput(LED_RED);
  setPinOutput(LED_GREEN);

  // Call the post init code.
  led_config.raw = eeconfig_read_user();

  if(led_config.red_mode == LEDMODE_ON) {
      writePinHigh(LED_RED);
  }

  if(led_config.green_mode == LEDMODE_ON) {
      writePinHigh(LED_GREEN);
  }
}

void eeconfig_init_user(void) {  // EEPROM is getting reset! 
  led_config.raw = 0;
  led_config.red_mode = LEDMODE_ON;
  led_config.green_mode = LEDMODE_MODS;
      eeconfig_update_user(led_config.raw);
  eeconfig_update_user(led_config.raw);
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _CODE, _NUMBERS, _ADJUST);
}

void led_keypress_update(uint8_t led, uint8_t led_mode, uint16_t keycode, keyrecord_t *record) {
    switch (led_mode) {
      case LEDMODE_MODS:
        for (int i=0;i<sizeof(modifiers) / sizeof(modifiers[0]);i++) {
          if(keycode==modifiers[i]) {
            if (record->event.pressed) {
              writePinHigh(led);
            }
            else {
              writePinLow(led);
            }
          }
        }
        break;
      case LEDMODE_BLINKIN:
        if (record->event.pressed) {
          if(rand() % 2 == 1) {
            if(rand() % 2 == 0) {
              writePinLow(led);
            }
            else {
              writePinHigh(led);
            }
          }
        }
        break;
      case LEDMODE_KEY:
        if (record->event.pressed) {
          writePinHigh(led);
          return;
        }
        else {
          writePinLow(led);
          return;
        }
        break;
      case LEDMODE_ENTER:
        if (keycode==KC_ENT) {
          writePinHigh(led);
        }
        else {
          writePinLow(led);
        }
        break;

    }
}


int shift_count = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  /* If the either led mode is keypressed based, call the led updater
     then let it fall through the keypress handlers. Just to keep 
     the logic out of this procedure */
  if (led_config.red_mode >= LEDMODE_MODS && led_config.red_mode <= LEDMODE_ENTER) {
      led_keypress_update(LED_RED, led_config.red_mode, keycode, record);
  }
  if (led_config.green_mode >= LEDMODE_MODS && led_config.green_mode <= LEDMODE_ENTER) {
      led_keypress_update(LED_GREEN, led_config.green_mode, keycode, record);
  }

  switch (keycode) {
    // Default layer
    case ANNIE:
      if (record->event.pressed) {
        print("mode just switched to annie and this is a huge strig\n");
        set_single_persistent_default_layer(_ANNIE);
      }
      return false;
      break;

    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;

    // Allows for custom shift behavior 
    case KC_LSFT:
    case KC_RSFT:
      if (record->event.pressed) {
        if (shift_count == 0) {
          register_code(KC_LSFT);
        }
        shift_count++;
      } else {
        shift_count--;
        if (shift_count == 0) {
          unregister_code(KC_LSFT);
        }
      }
      return false;
      break;

    // ,*
    case FR_COMM:
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code(KC_LSFT);
          register_code16(FR_ASTR);
          register_code(KC_LSFT);
          return false;
        }
      } else {
        if (shift_count > 0) {
          unregister_code16(FR_ASTR);
        }
      }
      break;

    // .!
    case FR_DOT:
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code(KC_LSFT);
          register_code16(FR_EXLM);
          register_code(KC_LSFT);

          return false;
        }
      } else {
        if (shift_count > 0) {
          unregister_code16(FR_EXLM);
        }
      }
      break;

    // /?
    case FR_SLSH:
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code(KC_LSFT);
          register_code16(FR_QUES);
          register_code(KC_LSFT);

          return false;
        }
      } else {
        if (shift_count > 0) {
          unregister_code16(FR_QUES);
        }
      }
      break;

    // The code layer
    case CODE:
      if (record->event.pressed) {
        layer_on(_CODE);
      } else {
        layer_off(_CODE);
      }
      return false;
      break;

    // The number layer
    case NUMBERS:
      if (record->event.pressed) {
        layer_on(_NUMBERS);
      } else {
        layer_off(_NUMBERS);
      }
      return false;
      break;

    // The french layer
    case FRENCH:
      if (record->event.pressed) {
        layer_on(_FRENCH);
      } else {
        layer_off(_FRENCH);
      }
      return false;
      break;

    case LED_1:
      if (record->event.pressed) {
        if (led_config.red_mode==LEDMODE_ON) {
          led_config.red_mode=LEDMODE_OFF;
          writePinLow(LED_RED);
          }
          else {
          led_config.red_mode=LEDMODE_ON;
          writePinHigh(LED_RED);
        }
      }
      eeconfig_update_user(led_config.raw);
      return false;
      break;

    case LED_2:
      if (record->event.pressed) {
        if (led_config.green_mode==LEDMODE_ON) {
          led_config.green_mode=LEDMODE_OFF;
          writePinLow(LED_GREEN);
          }
          else {
          led_config.green_mode=LEDMODE_ON;
          writePinHigh(LED_GREEN);
        }
      }
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_3:
      led_config.red_mode=LEDMODE_MODS;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_4:
      led_config.green_mode=LEDMODE_MODS;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_5:
      led_config.red_mode=LEDMODE_BLINKIN;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_6:
      led_config.green_mode=LEDMODE_BLINKIN;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_7:
      led_config.red_mode=LEDMODE_KEY;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_8:
      led_config.green_mode=LEDMODE_KEY;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_9:
      led_config.red_mode=LEDMODE_ENTER;
      eeconfig_update_user(led_config.raw);
      return false;
      break;
    case LED_0:
      led_config.green_mode=LEDMODE_ENTER;
      eeconfig_update_user(led_config.raw);
      return false;
      break;

    // French special characters
    case X_CIRC: // ^ (not dead)
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_LBRC)  SS_TAP(X_SPC));
      }
      return false;
      break;

    case __GRV: // ` (not dead)
      if (record->event.pressed) {
        SEND_STRING(SS_TAP(X_BSLS) SS_DELAY(100) SS_TAP(X_SPC));
      }

      return false;
      break;

    case FR_LCCE: // çÇ
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code(KC_LSFT);
          register_code16(FR_CCCE);
          register_code(KC_LSFT);
          return false;
        }
        return true;
      }
      break;

    case FR_LEGR: // èÈ
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code(KC_LSFT);
          register_code16(FR_CEGR);
          register_code(KC_LSFT);
          return false;
        } 
      } else {
        if (shift_count > 0) {
          unregister_code16(FR_CEGR);
        }
      }
      break;

    case FR_LEAC: // éÉ
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code(KC_LSFT);
          SEND_STRING(SS_DOWN(X_RALT) SS_DOWN(X_RSFT) SS_TAP(X_1) SS_UP(X_RSFT) SS_UP(X_RALT) "E");
          register_code(KC_LSFT);
          return false;
        }
        return true;
      }
      break;

    case FR_ECIR: // êÊ
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code(KC_LSFT);
          SEND_STRING(SS_RALT(SS_RSFT("e")));
          register_code(KC_LSFT);
          return false;
        }

        return true;
      }
      break;

    case FR_LAGR: // àÀ
      if (record->event.pressed) {
        if (shift_count == 0) {
          return true;
        }

        if (shift_count > 0) {
          unregister_code(KC_LSFT);
        }
        SEND_STRING(SS_TAP(X_BSLS));
        if (shift_count > 0) {
          register_code(KC_LSFT);
        }
        SEND_STRING("a");

        return false;
      }
      break;

    case FR_LUGR:  // ùÙ
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code(KC_LSFT);
          register_code16(FR_CUGR);
          register_code(KC_LSFT);
          return false;
        } 
      }
      break;

    case FR_LRQU:
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code(KC_LSFT);
        }
        SEND_STRING(SS_DOWN(X_LSFT) SS_RALT("\'") SS_UP(X_LSFT));
        if (shift_count > 0) {
          register_code(KC_LSFT);
        }
        return false;
      }
      break;

    // «“
    case FR_LDAQ:
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code16(KC_LSFT);
          SEND_STRING(SS_DOWN(X_RALT) "\"" SS_UP(X_RALT));
          register_code16(KC_LSFT);
          return false;
        } else {
          return true;
        }
      }
      break;

    // »”
    case F_RQUO:
      if (record->event.pressed) {
        if (shift_count > 0) {
          SEND_STRING(SS_DOWN(X_RALT) "'" SS_UP(X_RALT));
          return false;
        } else {
          return true;
        } 
      } 
      break;

    // …·

    case FR_ELLP:
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code(KC_LSFT);
          register_code16(FR_MDDT);
          register_code(KC_LSFT);
          return false;
        } 
        return true;
      } else {
        if (shift_count > 0) {
          unregister_code16(FR_MDDT);
        }
      }
      break;
  }
  return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
			// escape, space and enter require a swift mod change
        case FR_ESC:
	case NM_SPC:
	case CD_ENT:
	case FR_QUO:
            return 150;

			// a, u, s and i require some lagging
			// because the pinky and ring fingers
			// can lag a bit
	case LCTL_A:
	case RCTL_U:
	case LALT_S:
	case RALT_I:
		return 350;

        default:
            return TAPPING_TERM;
    }
}
