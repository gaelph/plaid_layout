#include "hid.h"
#include <raw_hid.h>
#include "print.h"
#include "defs.h"

int8_t layer = 0;

void layer_state_set_hid(layer_state_t state) {
	switch (get_highest_layer(state)) {
		case _QWERTY:
		layer = _QWERTY;
			break;

		case _FRENCH: 
		layer = _FRENCH;
			break;

		case _CODE:
		layer = _CODE;
			break;

		case _NUMBERS:
		layer = _NUMBERS;
			break;

		case _ADJUST:
		layer = _ADJUST;
			break;

		case _ANNIE:
		default:
		layer = _ANNIE;
			break;
	}
}


void send_event_to_hid(uint16_t keycode, keyevent_t event) {
  uint8_t upper_keycode = (keycode & 0xff00) >> 8;
  uint8_t lower_keycode = keycode & 0x00ff;
  uint8_t col = event.key.col;
  uint8_t row = event.key.row;
  uint8_t pressed = event.pressed ? 1 : 0;
  uint8_t mods = get_mods();

  uint8_t *data = malloc(32);
  data[0] = upper_keycode;
  data[1] = lower_keycode;
  data[2] = col;
  data[3] = row;
  data[4] = pressed;
  data[5] = mods;
  data[6] = layer;

  raw_hid_send(data, 32);

  free(data);
}

// vim: shiftwidth=2 tabstop=2 softtabstop=2 expandtab
