// Copyright 2022 Diego Palacios (@diepala)
// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H

enum custom_keycodes {
    // used for vim movements
    WORD_FORWARDS = SAFE_RANGE,
    WORD_BACKWARDS
};

// Used for simulating the vim motions
enum OS {
    MAC,
    LINUX,
    WIN
};
enum OS currentOS = MAC;

// Put base layers before function layers
enum layers{
  BASE,
  MOUSE_THUMB,
  GAMING,
  GAMING_SHIFTED,
  NUMBERS,
  LEFT_MODS,
  RIGHT_MODS,
  VIM,
  MOUSE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │CAP│ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │ { │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │ESC│ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │ ' │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │ ~ │ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │ } │
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │SWP├───┐           ┌───┤DEL│
      *               └───┤   ├───┐   ┌───┤Ent├───┘
      *                   └───┤TAB│   │BSP├───┘
      *                       └───┘   └───┘
      */
    [BASE] = LAYOUT_split_3x6_3(
        CAPS_WORD, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        KC_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_GRAVE,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RBRC,
                            SH_TT, LT(LEFT_MODS, KC_SPC), LT(NUMBERS, KC_TAB),   LT(NUMBERS, KC_BSPC), LT(RIGHT_MODS, KC_ENT), LT(VIM, KC_DEL)
    ),
    [MOUSE_THUMB] = LAYOUT_split_3x6_3(
        _______, _______,  _______, _______, _______, _______,                                _______, _______, _______, _______, _______, _______,
        _______, _______,  _______, _______, _______, _______,                                _______, _______, _______, _______, _______, _______,
        _______, _______,  _______, _______, _______, _______,                                _______, _______, _______, _______, _______, _______,
                                           MO(MOUSE), _______, _______,                     _______, _______, _______
    ),
    [GAMING] = LAYOUT_split_3x6_3(
        KC_CAPS, _______,  _______, _______, _______, _______,                                _______, _______, _______, _______, _______, _______,
        _______, _______,  _______, _______, _______, _______,                                _______, _______, _______, _______, _______, _______,
        _______, _______,  _______, _______, _______, _______,                                _______, _______, _______, _______, _______, _______,
                                           _______, KC_SPC, _______,                     _______, _______, _______
    ),
    [GAMING_SHIFTED] = LAYOUT_split_3x6_3(
        KC_CAPS,  KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,                                   _______, _______, _______, _______, _______, _______,
        _______,  KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,                                   _______, _______, _______, _______, _______, _______,
        _______,  KC_LCTRL,  KC_Z,    KC_X,    KC_C,    KC_V,                                   _______, _______, _______, _______, _______, _______,
                                _______, KC_SPC, LT(NUMBERS, KC_LALT),                      _______, _______, _______
    ),
    [NUMBERS] = LAYOUT_split_3x6_3(
        KC_F12,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                               KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_EQL,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS,
        _______, _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______, KC_BSLS,
                                                 _______, _______, _______,          _______, _______, _______
    ),
    [LEFT_MODS] = LAYOUT_split_3x6_3(
        _______,  _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______, _______,
        _______,  KC_LCTRL, KC_LALT,  KC_LGUI,  KC_LSFT,  _______,                             _______, _______, _______, _______, _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______, _______,
                                                      _______, _______, _______,          _______, _______, _______
    ),
    [RIGHT_MODS] = LAYOUT_split_3x6_3(
        _______,  _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,                             KC_LEAD, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTRL, _______,
        _______,  _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______, _______,
                                                      _______, _______, _______,          _______, _______, _______
    ),
    [VIM] = LAYOUT_split_3x6_3(
        _______,  _______,  WORD_FORWARDS,  _______,  _______,  _______,                             _______, _______, _______, _______, _______, _______,
        _______,  _______,  _______,        _______,  _______,  _______,                             KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______,
        _______,  _______,  _______,  _______, _______,  WORD_BACKWARDS,                             _______, _______, _______, _______, _______, _______,
                                                      _______, _______, _______,          _______, _______, _______
    ),
    [MOUSE] = LAYOUT_split_3x6_3(
        _______,  _______,  _______,  _______,  _______,  _______,                             _______, KC_WH_U, _______, _______, _______, _______,
        _______,  _______,  _______,  KC_WH_D,  _______,  _______,                             KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,                             _______, KC_BTN1, KC_BTN2, KC_BTN3, _______, _______,
                                                      _______, _______, _______,          _______, _______, _______
    ),
};
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
  {{5, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}, {0, 4}},
  {{5, 5}, {4, 5}, {3, 5}, {2, 5}, {1, 5}, {0, 5}},
  {{5, 6}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 6}},
  {{0, 3}, {1, 7}, {0, 7}, {5, 7}, {4, 7}, {3, 7}},
  {{5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}, {0, 0}},
  {{5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}, {0, 1}},
  {{5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}, {0, 2}},
  {{2, 3}, {1, 3}, {2, 7}, {5, 3}, {4, 3}, {3, 3}},
};

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    // Different base layers(They aren't base layers in the qmk sense but are used like so)
    SEQ_FOUR_KEYS(KC_B, KC_A, KC_S, KC_E) {
      layer_clear();
    }
    SEQ_FOUR_KEYS(KC_G, KC_A, KC_M, KC_E) {
      layer_move(GAMING);
    }
    SEQ_FIVE_KEYS(KC_G, KC_A, KC_M, KC_E, KC_S) {
      layer_move(GAMING_SHIFTED);
    }
    SEQ_FIVE_KEYS(KC_M, KC_O, KC_U, KC_S, KC_E) {
      layer_move(MOUSE_THUMB);
    }
    // for setting the OS
    SEQ_FIVE_KEYS(KC_L, KC_I, KC_N, KC_U, KC_X) {
        currentOS = LINUX;
    }
    SEQ_THREE_KEYS(KC_W, KC_I, KC_N) {
        currentOS = WIN;
    }
    SEQ_THREE_KEYS(KC_M, KC_A, KC_C) {
        currentOS = MAC;
    }
  }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case WORD_BACKWARDS:
            if (record->event.pressed) {
                // when keycode is pressed
                if(currentOS == MAC) {
                    SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_UP(X_LALT));
                } else {
                    SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_LEFT) SS_UP(X_LCTRL));
                }
            }
            break;
        case WORD_FORWARDS:
            if(record->event.pressed) {
                // when keycode is pressed
                if(currentOS == MAC) {
                    SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_RIGHT) SS_UP(X_LALT));
                } else {
                    SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_RIGHT) SS_UP(X_LCTRL));
                }
            }
    }
    return true;
};
