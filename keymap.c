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
#include <keymap_french_osx.h>
#include <sendstring_french_osx.h>
#include <print.h>

#include "./hid.h"
#include "./defs.h"
#include "./keycodes.h"
#include "./combos.h"
#include "./layers.h"

// array of keys considered modifiers for led purposes
const uint16_t modifiers[] = {
    KC_LCTL, KC_RCTL, KC_LALT, KC_RALT, KC_LSFT, KC_RSFT, KC_LGUI, KC_RGUI, CODE, NUMBERS, FRENCH,
};

// Setup consts for LED modes
#define LEDMODE_ON 1       // always on
#define LEDMODE_OFF 0      // always off
#define LEDMODE_MODS 2     // On with modifiers
#define LEDMODE_BLINKIN 3  // blinkinlights - % chance toggle on keypress
#define LEDMODE_KEY 4      // On with any keypress, off with key release
#define LEDMODE_ENTER 5    // On with enter key

// Setup config struct for LED
typedef union {
    uint32_t raw;
    struct {
        uint8_t red_mode : 8;
        uint8_t green_mode : 8;
    };
} led_config_t;
led_config_t led_config;

// Set leds to saved state during powerup
void keyboard_post_init_user(void) {
    debug_enable = true;
    // debug_matrix=true;
    debug_keyboard = true;
    // set LED pin modes
    setPinOutput(LED_RED);
    setPinOutput(LED_GREEN);

    // Call the post init code.
    led_config.raw = eeconfig_read_user();

    if (led_config.red_mode == LEDMODE_ON) {
        writePinHigh(LED_RED);
    }

    if (led_config.green_mode == LEDMODE_ON) {
        writePinHigh(LED_GREEN);
    }
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
    led_config.raw        = 0;
    led_config.red_mode   = LEDMODE_ON;
    led_config.green_mode = LEDMODE_MODS;
    eeconfig_update_user(led_config.raw);
    eeconfig_update_user(led_config.raw);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    layer_state_set_hid(state);
    return update_tri_layer_state(state, _CODE, _NUMBERS, _ADJUST);
}

void led_keypress_update(uint8_t led, uint8_t led_mode, uint16_t keycode, keyrecord_t *record) {
    switch (led_mode) {
        case LEDMODE_MODS:
            for (int i = 0; i < sizeof(modifiers) / sizeof(modifiers[0]); i++) {
                if (keycode == modifiers[i]) {
                    if (record->event.pressed) {
                        writePinHigh(led);
                    } else {
                        writePinLow(led);
                    }
                }
            }
            break;
        case LEDMODE_BLINKIN:
            if (record->event.pressed) {
                if (rand() % 2 == 1) {
                    if (rand() % 2 == 0) {
                        writePinLow(led);
                    } else {
                        writePinHigh(led);
                    }
                }
            }
            break;
        case LEDMODE_KEY:
            if (record->event.pressed) {
                writePinHigh(led);
                return;
            } else {
                writePinLow(led);
                return;
            }
            break;
        case LEDMODE_ENTER:
            if (keycode == KC_ENT) {
                writePinHigh(led);
            } else {
                writePinLow(led);
            }
            break;
    }
}

int shift_count = 0;
int ctrl_count  = 0;
int alt_count   = 0;
int cmd_count   = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uint8_t mods = get_mods();
    uprintf("KC: kc 0x%X, c: %2u, r: %2u, pressed: %u, mods: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, mods);
#endif
    send_event_to_hid(keycode, record->event);
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

        // Modifier counters allow for custom behaviors
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
            return true;
            break;

        case KC_LALT:
        case KC_RALT:
            if (record->event.pressed) {
                if (alt_count == 0) {
                    register_code(keycode);
                }
                alt_count++;
            } else {
                alt_count--;
                if (alt_count == 0) {
                    unregister_code(keycode);
                }
            }
            return false;
            break;

        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                if (ctrl_count == 0) {
                    register_code(keycode);
                }
                ctrl_count++;
            } else {
                ctrl_count--;
                if (ctrl_count == 0) {
                    unregister_code(keycode);
                }
            }
            return false;
            break;

        case KC_LGUI:
        case KC_RGUI:
            if (record->event.pressed) {
                if (cmd_count == 0) {
                    register_code(keycode);
                }
                cmd_count++;
            } else {
                cmd_count--;
                if (cmd_count == 0) {
                    unregister_code(keycode);
                }
            }
            return false;
            break;

        case LCTL_A:
        case RCTL_U:
            if (record->event.pressed) {
                ctrl_count++;
            } else {
                ctrl_count--;
            }
            return true;
            break;

        case LALT_S:
        case RALT_I:
            if (record->event.pressed) {
                alt_count++;
            } else {
                alt_count--;
            }
            return true;
            break;

        case LGUI_R:
        case LGUI_D:
        case RGUI_E:
            if (record->event.pressed) {
                cmd_count++;
            } else {
                cmd_count--;
            }
            return true;
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

        // .!
        case FR_DOT:
            if (record->event.pressed) {
                if (shift_count > 0 && (ctrl_count == 0 && alt_count == 0 && cmd_count == 0)) {
                    unregister_code(KC_LSFT);
                    register_code16(FR_EXLM);
                    register_code(KC_LSFT);

                    return false;
                } else if ((ctrl_count > 0 && alt_count > 0) || (ctrl_count > 0 && alt_count > 0 && cmd_count > 0)) {
                    register_code(KC_LCTL);
                    register_code(KC_LALT);
                    register_code16(KC_DOT);

                    return false;
                }
            } else {
                if (shift_count > 0 && (ctrl_count == 0 && alt_count == 0 && cmd_count == 0)) {
                    unregister_code16(FR_EXLM);
                } else if ((ctrl_count > 0 && alt_count > 0) || (ctrl_count > 0 && alt_count > 0 && cmd_count > 0)) {
                    unregister_code16(KC_DOT);
                    unregister_code(KC_LALT);
                    unregister_code(KC_LCTL);
                }
            }
            break;

        // French special characters
        case __TILD:  // ~ (not dead)
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_N) SS_UP(X_LALT) SS_TAP(X_SPC));
            }
            return false;
            break;

        case __CIRC:  // ^ (not dead)
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_LBRC) SS_TAP(X_SPC));
            }
            return false;
            break;

        case __GRV:  // ` (not dead)
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_BSLS) SS_DELAY(100) SS_TAP(X_SPC));
            }

            return false;
            break;

        case FR_LCCE:  // çÇ
            if (record->event.pressed) {
                if (shift_count > 0) {
                    unregister_code(KC_LSFT);
                    unregister_code(KC_RSFT);
                    register_code16(FR_CCCE);
                    register_code(KC_LSFT);
                    return false;
                }
                return true;
            }
            break;

        case FR_LEGR:  // èÈ
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

        case FR_LEAC:  // éÉ
            if (record->event.pressed) {
                if (shift_count > 0) {
                    unregister_code(KC_LSFT);
                    SEND_STRING(SS_DOWN(X_RALT) SS_DOWN(X_RSFT) SS_TAP(X_1) SS_UP(X_RSFT) SS_UP(X_RALT));
                    SEND_STRING(SS_DOWN(X_RSFT) SS_TAP(X_E) SS_UP(X_RSFT));
                    register_code(KC_LSFT);
                    return false;
                }
                return true;
            }
            break;

        case FR_ECIR:  // êÊ
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

        case FR_LAGR:  // àÀ
            if (record->event.pressed) {
                if (shift_count == 0) {
                    return true;
                }

                if (shift_count > 0) {
                    unregister_code(KC_LSFT);
                    unregister_code(KC_RSFT);
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
                    unregister_code(KC_RSFT);
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
        case FR_RDAQ:
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

        case LED_1:
            if (record->event.pressed) {
                if (led_config.red_mode == LEDMODE_ON) {
                    led_config.red_mode = LEDMODE_OFF;
                    writePinLow(LED_RED);
                } else {
                    led_config.red_mode = LEDMODE_ON;
                    writePinHigh(LED_RED);
                }
            }
            eeconfig_update_user(led_config.raw);
            return false;
            break;

        case LED_2:
            if (record->event.pressed) {
                if (led_config.green_mode == LEDMODE_ON) {
                    led_config.green_mode = LEDMODE_OFF;
                    writePinLow(LED_GREEN);
                } else {
                    led_config.green_mode = LEDMODE_ON;
                    writePinHigh(LED_GREEN);
                }
            }
            eeconfig_update_user(led_config.raw);
            return false;
            break;
        case LED_3:
            led_config.red_mode = LEDMODE_MODS;
            eeconfig_update_user(led_config.raw);
            return false;
            break;
        case LED_4:
            led_config.green_mode = LEDMODE_MODS;
            eeconfig_update_user(led_config.raw);
            return false;
            break;
        case LED_5:
            led_config.red_mode = LEDMODE_BLINKIN;
            eeconfig_update_user(led_config.raw);
            return false;
            break;
        case LED_6:
            led_config.green_mode = LEDMODE_BLINKIN;
            eeconfig_update_user(led_config.raw);
            return false;
            break;
        case LED_7:
            led_config.red_mode = LEDMODE_KEY;
            eeconfig_update_user(led_config.raw);
            return false;
            break;
        case LED_8:
            led_config.green_mode = LEDMODE_KEY;
            eeconfig_update_user(led_config.raw);
            return false;
            break;
        case LED_9:
            led_config.red_mode = LEDMODE_ENTER;
            eeconfig_update_user(led_config.raw);
            return false;
            break;
        case LED_0:
            led_config.green_mode = LEDMODE_ENTER;
            eeconfig_update_user(led_config.raw);
            return false;
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
// vim: expandtab tabstop=2 softtabstop=2 shiftwidth=2
