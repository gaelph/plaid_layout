#include QMK_KEYBOARD_H
#include <raw_hid.h>
#include "print.h"
void layer_state_set_hid(layer_state_t state);
void send_event_to_hid(uint16_t keycode, keyevent_t event); 
