#include QMK_KEYBOARD_H
#include "hid.h"
#include <raw_hid.h>
#include "print.h"
// void raw_hid_receive(uint8_t *data, uint8_t length) {
//     // Your code goes here. data is the packet received from host.
//   raw_hid_send(data, length);
// }
//
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

  raw_hid_send(data, 32);

  free(data);
}
