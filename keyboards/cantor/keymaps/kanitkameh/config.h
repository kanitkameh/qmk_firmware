#pragma once

// We set timeout per key instead for the whole sequence
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 250
// There is no timeout for the first key after the leader key
#define LEADER_NO_TIMEOUT
// Allows you to use LT(3, KC_A) instead of KC_A thus more flexible
#define LEADER_KEY_STRICT_KEY_PROCESSING

// Taipo config
#define COMBO_TERM 50
#define COMBO_MUST_HOLD_MODS

#define TAP_CODE_DELAY 25
#define TAPPING_FORCE_HOLD
