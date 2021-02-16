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


void matrix_init_user() {
	set_unicode_input_mode(UC_MAC);
};
enum plaid_layers {
  _NORMAN,
  _CODE,
  _NUMBERS,
  _FRENCH,
  _ADJUST
};

enum plaid_keycodes {
  NORMAN = SAFE_RANGE,
  CODE,
  NUMBERS,
  FRENCH,
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
    // shifted
  SE_GRV,
  SE_ACU,
  SE_CIR,
  SA_GRV,
  SU_GRV
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
#define FR_ESC LT(_FRENCH,   KC_ESC)   // tap: esc, hold: french layer
#define CT_ALT LCTL(KC_RALT) // control+alt
#define NM_SPC LT(_NUMBERS,  KC_SPACE) // tap: space, hold: number layer
#define CD_ENT LT(_CODE,     KC_ENT)   // tap: enter, hold: number layer
//Code Layer
#define TH_DOT LALT(KC_SCLN) // …
//French Layer
#define F_OE   RALT(KC_Q)    // œŒ
#define F_LQUO RALT(KC_BSLS) // «
#define F_RQUO LSA(KC_BSLS)  // »
#define E_RQUO LSA(KC_RBRC)  // ’
#define E_RDQU LSA(KC_LBRC)  // ”
#define E_LQUO LALT(KC_RBRC) // ‘
#define E_LDQU LALT(KC_LBRC) // “
#define F_DEGR LSA(KC_8)     // °
#define F_GRMD LALT(KC_GRV)  // `
#define F_ACMD LALT(KC_E)    // ´
#define F_CIMD LALT(KC_I)    // ˆ
#define F_TRMD LALT(KC_U)    // ¨
#define F_AE   LALT(KC_QUOT) // æ
#define F_AT   LALT(KC_2)    // @
#define F_EURO LSA(KC_2)     // €
#define F_CCED LALT(KC_C)    // çÇ
#define F_MDOT LSA(KC_9)     // ·

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Norman Layeer
 * ,------------------------------------------------------------------------------------------------------.
 * | Tab            |   Q  |   W  |   D  |   F  |   K  |   Y  |   J  |   R  |   L  |   -  | Bksp          |
 * |----------------+------+------+------+------+-------------+------+------+------+------+---------------|
 * | Esc or French  |   A  |   S  |   E  |   T  |   G  |   H  |   U  |   I  |   O  |   P  | French        |
 * |----------------+------+------+------+------+------|------+------+------+------+------+---------------|
 * | Ctrl + Alt     |   Z  |   X  |   C  |   B  |   V  |   N  |   M  |   ,  |   .  |   /  | Code          |
 * |----------------+------+------+------+------+------+------+------+------+------+------+---------------|
 * | LAlt           | Ctrl | GUI  | LSFT | Spc  | Code | Nums | SEnt | RSFT | GUI  | Ctrl | RAlt          |
 * `------------------------------------------------------------------------------------------------------'
 */
[_NORMAN] = LAYOUT_plaid_grid(
    KC_TAB,  KC_Q,    KC_W,    KC_D,    KC_F,    KC_K,   KC_Y,   KC_J,    KC_R,    KC_L,    KC_MINS,  KC_BSPC,
    FR_ESC,  KC_A,    KC_S,    KC_E,    KC_T,    KC_G,   KC_H,   KC_U,    KC_I,    KC_O,    KC_P,     FRENCH,
    CT_ALT,  KC_Z,    KC_X,    KC_C,    KC_B,    KC_V,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLASH, KC_RALT,
    KC_LALT, KC_LCTL, KC_LGUI, KC_LGUI, KC_LSFT, NM_SPC, CD_ENT, KC_RSFT, KC_RGUI, KC_RGUI, KC_RCTL,  KC_RALT
),

/* Code Layer
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   &  |   <  |   /  |   [  |   ]  |      |   "  |   '  |      |      | ____ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | DEL  |   `  |   =  |   !  |   (  |   )  |   ^  |   :  |   ;  |      |   @  |  $   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ____ |   |  |   >  |   %  |   {  |   }  |   +  |   -  |   #  |   …  |   \  | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ___  | ____ | ____ | ____ | ____ | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_CODE] = LAYOUT_plaid_grid(
    KC_TILDE, KC_AMPR, KC_LT,   KC_SLSH, KC_LBRC, KC_RBRC, XXXXXXX, KC_DQUO, KC_QUOT, XXXXXXX, KC_UNDS, _______,
    KC_DEL,   KC_GRV,  KC_EQL,  KC_EXLM, KC_LPRN, KC_RPRN, KC_CIRC, KC_COLN, KC_SCLN, XXXXXXX, KC_AT,   KC_DLR,
    _______,  KC_PIPE, KC_GT,   KC_PERC, KC_LCBR, KC_RCBR, KC_PLUS, KC_MINS, KC_HASH, TH_DOT,  KC_BSLS, _______,
    _______,  _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),


/* Numbers Layer
 * ,-----------------------------------------------------------------------------------.
 * | ____ |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | ____ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ____ |   a  |   b  |   c  |   d  |   e  | Left | Down | Up   | Right|      | ____ |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ____ |   f  |   x  |      |      |      |   +  |   -  |   ,  |   .  |   /  | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMBERS] = LAYOUT_plaid_grid(
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    _______, KC_A,    KC_B,    KC_C,    KC_D,    KC_E,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, _______,
    _______, KC_F,    KC_X,    XXXXXXX, XXXXXXX, XXXXXXX, KC_PLUS, KC_MINS, KC_COMM, KC_DOT,  KC_SLSH, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),


/* French Layer
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   œ  |   «  |      |      |      |      |   ‘  |   ’  |   °  |   –  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ___  |   à  |   ê  |   é  |   è  |      |      |   ˆ  |   ¨  |   ù  |   @  |  €   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | ___  |   æ  |   »  |   ç  |      |      |   +  |   -  |   #  |   @  |   \  | ___  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ___  | ___  | ___  | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * `-----------------------------------------------------------------------------------'
 */
[_FRENCH] = LAYOUT_plaid_grid(
    KC_GRV,  F_OE,    F_LQUO,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, E_LQUO,  E_RQUO,  F_DEGR,  LALT( KC_MINS ), _______,
    _______, A_GRV,   E_CIR,   E_ACU,   E_GRV,   XXXXXXX, XXXXXXX, F_CIMD,  F_TRMD,  U_GRV,   KC_AT,           F_EURO,
    _______, F_AE,    F_RQUO,  F_CCED,  XXXXXXX, XXXXXXX, KC_PLUS, KC_MINS, KC_HASH, TH_DOT,  KC_BSLS,         _______,
    _______, _______, _______, _______, KC_LSFT, _______, _______, KC_RSFT, KC_RGUI, KC_RGUI, KC_RCTL,         KC_RALT
),

/* Shifted French Layer
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   Œ  | ____ | ____ | ____ | ____ | ____ |   ”  |   ‘  | ____ |   _  | ____ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | ___  |   À  |   Ê  |   É  |   È  | ____ | ____ | ____ | ____ |   Ù  | ____ | ____ |
 * |------+------+------+------+------+------|------+------+-- ---+------+------+------|
 * | ____ |   Æ  | ____ |   Ç  | ____ | ____ | ____ | ____ | ____ |   ·  | ____ | ____ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | ___  | ___  | ___  | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |
 * `-----------------------------------------------------------------------------------'
 */
/* [_SFRENCH] = LAYOUT_plaid_grid( */
/*     KC_TILDE, S( F_OE ), _______, _______,     _______, _______, _______, E_LDQU,  E_LQUO,  _______, KC_UNDS, _______, */
/*     _______,  SA_GRV,    SE_CIR,  SE_ACU,      SE_GRV,  _______, _______, _______, _______, SU_GRV,  _______, _______, */
/*     _______,  S( F_AE ), _______, S( F_CCED ), _______, _______, _______, _______, _______, F_MDOT,  _______, _______, */
/*     _______,  _______,   _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______ */
/* ), */

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Reset |      |      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_plaid_grid(
    RESET,LED_1, LED_2, LED_3, LED_4, LED_5,LED_6, LED_7, LED_8, LED_9, LED_0,KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, NORMAN,  _______, _______,  _______,  _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______,
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
    case NORMAN:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_NORMAN);
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
    case KC_COMM:
      if (shift_count > 0) {
        if (record->event.pressed) {
          register_code16(KC_ASTR);
        } else {
          unregister_code16(KC_ASTR);
        }
        return false;
      } else {
        unregister_code16(KC_ASTR);
        return true;
      }
      break;
      
    // .!
    case KC_DOT:
      if (shift_count > 0) {
        if (record->event.pressed) {
          register_code16(KC_EXLM);
        } else {
          unregister_code16(KC_EXLM);
        }
        return false;
      } else {
        unregister_code16(KC_EXLM);
        return true;
      }
      break;

    // /?
    case KC_SLSH:
      if (shift_count > 0) {
        if (record->event.pressed) {
          register_code16(KC_QUES);
        } else {
          unregister_code16(KC_QUES);
        }
        return false;
      } else {
        unregister_code16(KC_QUES);
        return true;
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
        if (shift_count > 0) {}
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
    case E_GRV: // èÈ
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code(KC_LSFT);
        }
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_GRAVE) SS_UP(X_LALT));
        if (shift_count > 0) {
          register_code(KC_LSFT);
        }
        SEND_STRING("e"); 
      } 
      return false;
      break;

    case E_ACU: // éÉ
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code(KC_LSFT);
        }
        SEND_STRING(SS_LALT("e"));
        if (shift_count > 0) {
          register_code(KC_LSFT);
        }
        SEND_STRING("e");
      }
      return false;
      break;

    case E_CIR: // êÊ
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code(KC_LSFT);
        }
        SEND_STRING(SS_LALT("i"));
        if (shift_count > 0) {
          register_code(KC_LSFT);
        }
        SEND_STRING("e");
      }
      return false;
      break;

    case A_GRV: // àÀ
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code(KC_LSFT);
        }
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_GRAVE) SS_UP(X_LALT));
        if (shift_count > 0) {
          register_code(KC_LSFT);
        }
        SEND_STRING("a");
      }
      return false;
      break;

    case U_GRV:  // ùÙ
      if (record->event.pressed) {
        if (shift_count > 0) {
          unregister_code(KC_LSFT);
        }
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_GRAVE) SS_UP(X_LALT));
        if (shift_count > 0) {
          register_code(KC_LSFT);
        }
        SEND_STRING("u");
      }
      return false;
      break;

    // ”’°–@€+-#· 
    // «“
    case F_LQUO:
      if (record->event.pressed) {
        if (shift_count > 0) {
          register_code16(E_LDQU);
          return false;
        } else {
          return true;
        }
      } else {
        if (shift_count > 0) {
          unregister_code16(E_LDQU);
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
          register_code16(E_RDQU);
          return false;
        } else {
          return true;
        } 
      } else {
        if (shift_count > 0) {
          unregister_code16(E_RDQU);
          return false;
        } else {
          return true;
        }
      }
      break;

    // …·
    case TH_DOT:
      if (record->event.pressed) {
        if (shift_count > 0) {
          register_code16(F_MDOT);
          return false;
        } else {
          return true; 
        }
      } else {
        if (shift_count > 0) {
          unregister_code16(F_MDOT);
          return false;
        } else {
          return true;
        }
      }
      break;
  }
  return true;
}
