#include QMK_KEYBOARD_H
#include "defs.h"
#include "keycodes.h"

const key_override_t ndash_mdash_override = ko_make_with_layers(MOD_MASK_SHIFT, FR_NDSH, FR_MDSH, _FRENCH);
const key_override_t comm_astr_override = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, FR_COMM, FR_ASTR, ~0, MOD_MASK_CAG, ko_option_no_reregister_trigger);
const key_override_t ca_comm_override = ko_make_basic(MOD_MASK_CA, FR_COMM, KC_COMM);
// const key_override_t dot_exlm_override = {
//   .trigger_mods = MOD_MASK_SHIFT, //
//   .trigger = FR_DOT, //
//   .replacement = KC_8, //
//   .layers = ~0, //
//   .negative_mod_mask = MOD_MASK_CAG, //
//   .suppressed_mods = MOD_MASK_SHIFT, //
//   .options = ko_option_no_reregister_trigger, //
//   .enabled = NULL,
//   .custom_action = NULL,
//   .context = NULL
// };


// const key_override_t ca_dot_override = ko_make_basic(MOD_MASK_CA, FR_DOT, KC_DOT);
const key_override_t slash_ques_override = ko_make_with_layers_negmods_and_options(MOD_MASK_SHIFT, FR_SLSH, FR_QUES, ~0, MOD_MASK_CAG, ko_option_no_reregister_trigger);

const key_override_t **key_overrides = (const key_override_t *[]) {
  &ndash_mdash_override,
  &comm_astr_override,
  &ca_comm_override,
  // &dot_exlm_override,
  // &ca_dot_override,
  &slash_ques_override,
  NULL
};
