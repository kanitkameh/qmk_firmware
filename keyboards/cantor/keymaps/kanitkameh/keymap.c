// Copyright 2022 Diego Palacios (@diepala)
// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H

enum custom_keycodes {
    // used for vim movements
    WORD_FORWARDS = SAFE_RANGE,
    WORD_BACKWARDS,
    VISUAL,
    YANK,
    CUT,
    PASTE,
    UNDO,
    MY_LGUI,
    MY_LALT,
    MY_LCTL,
    MY_LSFT,
};
// Non-QMK built ins start
// Used for simulating the vim motions
enum OS {
    MAC,
    LINUX,
    WIN
};

// don't access directly, use vim functions activateVisualMode/deactivateVisualMode
bool isVisualModeActive = false;

enum OS currentOS = MAC;
// Non-QMK built ins end
// vim functions
void activateVisualMode(void){
    if(!isVisualModeActive){
        isVisualModeActive = true;
        SEND_STRING(SS_DOWN(X_LSFT));
    }
}
void deactivateVisualMode(void){
    if(isVisualModeActive){
        isVisualModeActive = false;
        SEND_STRING(SS_UP(X_LSFT));
    }
}

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
  MOUSE,
  TAIPO
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
        CW_TOGG, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
        KC_ESC,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        TG(TAIPO),  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RBRC,
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
        _______,  KC_LCTL,  KC_Z,    KC_X,    KC_C,    KC_V,                                   _______, _______, _______, _______, _______, _______,
                                _______, KC_SPC, LT(NUMBERS, KC_LALT),                      _______, _______, _______
    ),
    [NUMBERS] = LAYOUT_split_3x6_3(
        KC_F12,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                               KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_EQL,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINUS,
        _______, KC_GRAVE,  CW_TOGG,  QK_LOCK,  KC_ESC,  KC_EQL,                              KC_MINUS, KC_QUOT, KC_BSLS, KC_LBRC, KC_RBRC, _______,
                                                 _______, _______, _______,          _______, _______, _______
    ),
    [LEFT_MODS] = LAYOUT_split_3x6_3(
        _______,  _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______, _______,
        _______,  KC_LCTL, KC_LALT,  KC_LGUI,  KC_LSFT,  _______,                             _______, _______, _______, _______, _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______, _______,
                                                      _______, _______, _______,          _______, _______, _______
    ),
    [RIGHT_MODS] = LAYOUT_split_3x6_3(
        _______,  _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,                             QK_LEAD, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, _______,
        _______,  _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______, _______,
                                                      _______, _______, _______,          _______, _______, _______
    ),
    [VIM] = LAYOUT_split_3x6_3(
        _______,  _______,  WORD_FORWARDS,  WORD_FORWARDS,  _______,  _______,                   YANK,    UNDO,    _______, _______, PASTE, _______,
        _______,  _______,  _______,        CUT,  _______,  _______,                             KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______, _______,
        _______,  _______,  CUT,  _______, VISUAL,  WORD_BACKWARDS,                             _______, _______, _______, _______, _______, _______,
                                                      _______, _______, _______,          _______, _______, _______
    ),
    [MOUSE] = LAYOUT_split_3x6_3(
        _______,  _______,  _______,  _______,  _______,  _______,                             _______, KC_WH_U, _______, _______, _______, _______,
        _______,  _______,  _______,  KC_WH_D,  _______,  _______,                             KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
        _______,  _______,  _______,  _______,  _______,  _______,                             _______, KC_BTN1, KC_BTN3, KC_BTN2, _______, _______,
                                                      _______, _______, _______,          _______, _______, _______
    ),
    [TAIPO] = LAYOUT_split_3x6_3(
        _______,  KC_R   , KC_S   , KC_N   , KC_I   , _______,            _______, KC_I   , KC_N   , KC_S   , KC_R,  _______,
        _______,  KC_A   , KC_O   , KC_T   , KC_E   , _______,            _______, KC_E   , KC_T   , KC_O   , KC_A,  _______,
        _______,  KC_A   , KC_O   , KC_T   , KC_E   , _______,            _______, KC_E   , KC_T   , KC_O   , KC_A,  _______,
                                     _______, KC_SPC , KC_BSPC,          KC_BSPC, KC_SPC , _______
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


void leader_end_user_taipo(void);

void leader_end_user(void) {
    // Different base layers(They aren't base layers in the qmk sense but are used like so)
    if (leader_sequence_four_keys(KC_B, KC_A, KC_S, KC_E)) {
        layer_clear();
    }
    if (leader_sequence_four_keys(KC_G, KC_A, KC_M, KC_E)) {
        layer_move(GAMING);
    }
    if (leader_sequence_five_keys(KC_G, KC_A, KC_M, KC_E, KC_S)) {
        layer_move(GAMING_SHIFTED);
    }
    if (leader_sequence_five_keys(KC_M, KC_O, KC_U, KC_S, KC_E)) {
        layer_move(MOUSE_THUMB);
    }
    // for setting the OS
    if (leader_sequence_five_keys(KC_L, KC_I, KC_N, KC_U, KC_X)) {
        currentOS = LINUX;
    }
    if (leader_sequence_three_keys(KC_W, KC_I, KC_N)) {
        currentOS = WIN;
    }
    if (leader_sequence_three_keys(KC_M, KC_A, KC_C)) {
        currentOS = MAC;
    }
    leader_end_user_taipo();
};


bool process_record_user_taipo(uint16_t keycode, keyrecord_t *record);

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case UNDO:
            if (record->event.pressed) {
                // when keycode is pressed
                if(currentOS == MAC) {
                    SEND_STRING(SS_LCMD("z"));
                } else {
                    SEND_STRING(SS_LCTL("z"));
                }
            }
            break;
        case CUT:
            if (record->event.pressed) {
                deactivateVisualMode();
                // when keycode is pressed
                if(currentOS == MAC) {
                    SEND_STRING(SS_LCMD("x"));
                } else {
                    SEND_STRING(SS_LCTL("x"));
                }
            }
            break;
        case PASTE:
            if (record->event.pressed) {
                deactivateVisualMode();
                // when keycode is pressed
                if(currentOS == MAC) {
                    SEND_STRING(SS_LCMD("v"));
                } else {
                    SEND_STRING(SS_LCTL("v"));
                }
            }
            break;
        case YANK:
            if (record->event.pressed) {
                deactivateVisualMode();
                // when keycode is pressed
                if(currentOS == MAC) {
                    SEND_STRING(SS_LCMD("c"));
                } else {
                    SEND_STRING(SS_LCTL("c"));
                }
            }
            break;
        case VISUAL:
            if (record->event.pressed) {
                // when keycode is pressed
                // toggle visual mode
                if(isVisualModeActive){
                    deactivateVisualMode();
                } else {
                    activateVisualMode();
                }
            }
            break;
        case WORD_BACKWARDS:
            if (record->event.pressed) {
                // when keycode is pressed
                if(currentOS == MAC) {
                    SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_UP(X_LALT));
                } else {
                    SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_LEFT) SS_UP(X_LCTL));
                }
            }
            break;
        case WORD_FORWARDS:
            if(record->event.pressed) {
                // when keycode is pressed
                if(currentOS == MAC) {
                    SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_RIGHT) SS_UP(X_LALT));
                } else {
                    SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_RIGHT) SS_UP(X_LCTL));
                }
            }
            break;
    }
    process_record_user_taipo(keycode, record);
    return true;
};

layer_state_t layer_state_set_user(layer_state_t state) {
    deactivateVisualMode();
    return state;
}

// taipo
uint16_t COMBO_LEN = 104;
const uint16_t PROGMEM CM1[] = {KC_E,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM2[] = {KC_T,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM3[] = {KC_O,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM4[] = {KC_A,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM5[] = {KC_E,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM6[] = {KC_T,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM7[] = {KC_O,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM8[] = {KC_A,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM9[] = {KC_I,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM10[] = {KC_N,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM11[] = {KC_S,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM12[] = {KC_R,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM13[] = {KC_I,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM14[] = {KC_N,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM15[] = {KC_S,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM16[] = {KC_R,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM17[] = {KC_E,KC_T,COMBO_END};
const uint16_t PROGMEM CM18[] = {KC_O,KC_A,COMBO_END};
const uint16_t PROGMEM CM19[] = {KC_I,KC_N,COMBO_END};
const uint16_t PROGMEM CM20[] = {KC_S,KC_R,COMBO_END};
const uint16_t PROGMEM CM21[] = {KC_E,KC_T,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM22[] = {KC_O,KC_A,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM23[] = {KC_I,KC_N,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM24[] = {KC_S,KC_R,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM25[] = {KC_E,KC_T,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM26[] = {KC_O,KC_A,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM27[] = {KC_I,KC_N,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM28[] = {KC_S,KC_R,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM29[] = {KC_I,KC_R,COMBO_END};
const uint16_t PROGMEM CM30[] = {KC_T,KC_O,COMBO_END};
const uint16_t PROGMEM CM31[] = {KC_E,KC_A,COMBO_END};
const uint16_t PROGMEM CM32[] = {KC_N,KC_S,COMBO_END};
const uint16_t PROGMEM CM33[] = {KC_I,KC_R,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM34[] = {KC_T,KC_O,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM35[] = {KC_E,KC_A,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM36[] = {KC_N,KC_S,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM37[] = {KC_I,KC_R,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM38[] = {KC_T,KC_O,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM39[] = {KC_E,KC_A,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM40[] = {KC_N,KC_S,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM41[] = {KC_E,KC_O,COMBO_END};
const uint16_t PROGMEM CM42[] = {KC_T,KC_A,COMBO_END};
const uint16_t PROGMEM CM43[] = {KC_I,KC_S,COMBO_END};
const uint16_t PROGMEM CM44[] = {KC_N,KC_R,COMBO_END};
const uint16_t PROGMEM CM45[] = {KC_E,KC_O,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM46[] = {KC_T,KC_A,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM47[] = {KC_I,KC_S,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM48[] = {KC_N,KC_R,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM49[] = {KC_E,KC_O,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM50[] = {KC_T,KC_A,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM51[] = {KC_I,KC_S,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM52[] = {KC_N,KC_R,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM53[] = {KC_S,KC_E,COMBO_END};
const uint16_t PROGMEM CM54[] = {KC_R,KC_T,COMBO_END};
const uint16_t PROGMEM CM55[] = {KC_I,KC_O,COMBO_END};
const uint16_t PROGMEM CM56[] = {KC_N,KC_A,COMBO_END};
const uint16_t PROGMEM CM57[] = {KC_S,KC_E,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM58[] = {KC_R,KC_T,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM59[] = {KC_I,KC_O,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM60[] = {KC_N,KC_A,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM61[] = {KC_S,KC_E,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM62[] = {KC_R,KC_T,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM63[] = {KC_I,KC_O,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM64[] = {KC_N,KC_A,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM65[] = {KC_N,KC_O,COMBO_END};
const uint16_t PROGMEM CM66[] = {KC_I,KC_A,COMBO_END};
const uint16_t PROGMEM CM67[] = {KC_R,KC_E,COMBO_END};
const uint16_t PROGMEM CM68[] = {KC_S,KC_T,COMBO_END};
const uint16_t PROGMEM CM69[] = {KC_N,KC_O,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM70[] = {KC_I,KC_A,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM71[] = {KC_R,KC_E,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM72[] = {KC_S,KC_T,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM73[] = {KC_N,KC_O,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM74[] = {KC_I,KC_A,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM75[] = {KC_R,KC_E,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM76[] = {KC_S,KC_T,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM77[] = {KC_S,KC_A,COMBO_END};
const uint16_t PROGMEM CM78[] = {KC_R,KC_O,COMBO_END};
const uint16_t PROGMEM CM79[] = {KC_I,KC_T,COMBO_END};
const uint16_t PROGMEM CM80[] = {KC_N,KC_E,COMBO_END};
const uint16_t PROGMEM CM81[] = {KC_S,KC_A,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM82[] = {KC_R,KC_O,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM83[] = {KC_I,KC_T,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM84[] = {KC_N,KC_E,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM85[] = {KC_S,KC_A,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM86[] = {KC_N,KC_E,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM87[] = {KC_E,KC_T,KC_O,COMBO_END};
const uint16_t PROGMEM CM88[] = {KC_I,KC_N,KC_S,COMBO_END};
const uint16_t PROGMEM CM89[] = {KC_E,KC_T,KC_O,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM90[] = {KC_I,KC_N,KC_S,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM91[] = {KC_E,KC_T,KC_O,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM92[] = {KC_I,KC_N,KC_S,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM93[] = {KC_A,KC_R,COMBO_END};
const uint16_t PROGMEM CM94[] = {KC_O,KC_S,COMBO_END};
const uint16_t PROGMEM CM95[] = {KC_T,KC_N,COMBO_END};
const uint16_t PROGMEM CM96[] = {KC_E,KC_I,COMBO_END};
const uint16_t PROGMEM CM97[] = {KC_A,KC_R,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM98[] = {KC_O,KC_S,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM99[] = {KC_T,KC_N,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM100[] = {KC_E,KC_I,KC_SPC,COMBO_END};
const uint16_t PROGMEM CM101[] = {KC_A,KC_R,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM102[] = {KC_O,KC_S,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM103[] = {KC_T,KC_N,KC_BSPC,COMBO_END};
const uint16_t PROGMEM CM104[] = {KC_E,KC_I,KC_BSPC,COMBO_END};

combo_t key_combos[] = {
	COMBO(CM1,S(KC_E)),
	COMBO(CM2,S(KC_T)),
	COMBO(CM3,S(KC_O)),
	COMBO(CM4,S(KC_A)),
	COMBO(CM5,KC_LPRN),
	COMBO(CM6,KC_LBRC),
	COMBO(CM7,KC_LCBR),
	COMBO(CM8,KC_LT),
	COMBO(CM9,S(KC_I)),
	COMBO(CM10,S(KC_N)),
	COMBO(CM11,S(KC_S)),
	COMBO(CM12,S(KC_R)),
	COMBO(CM13,KC_RPRN),
	COMBO(CM14,KC_RBRC),
	COMBO(CM15,KC_RCBR),
	COMBO(CM16,KC_GT),
	COMBO(CM17,KC_H),
	COMBO(CM18,KC_L),
	COMBO(CM19,KC_Y),
	COMBO(CM20,KC_B),
	COMBO(CM21,S(KC_H)),
	COMBO(CM22,S(KC_L)),
	COMBO(CM23,S(KC_Y)),
	COMBO(CM24,S(KC_B)),
	COMBO(CM25,KC_1),
	COMBO(CM26,KC_5),
	COMBO(CM27,KC_6),
	COMBO(CM28,KC_0),
	COMBO(CM29,KC_G),
	COMBO(CM30,KC_U),
	COMBO(CM31,KC_D),
	COMBO(CM32,KC_P),
	COMBO(CM33,S(KC_G)),
	COMBO(CM34,S(KC_U)),
	COMBO(CM35,S(KC_D)),
	COMBO(CM36,S(KC_P)),
	COMBO(CM37,KC_HASH),
	COMBO(CM38,KC_3),
	COMBO(CM39,KC_AT),
	COMBO(CM40,KC_8),
	COMBO(CM41,KC_C),
	COMBO(CM42,KC_Q),
	COMBO(CM43,KC_F),
	COMBO(CM44,KC_Z),
	COMBO(CM45,S(KC_C)),
	COMBO(CM46,S(KC_Q)),
	COMBO(CM47,S(KC_F)),
	COMBO(CM48,S(KC_Z)),
	COMBO(CM49,KC_2),
	COMBO(CM50,KC_4),
	COMBO(CM51,KC_7),
	COMBO(CM52,KC_9),
	COMBO(CM53,KC_V),
	COMBO(CM54,KC_X),
	COMBO(CM55,KC_K),
	COMBO(CM56,KC_J),
	COMBO(CM57,S(KC_V)),
	COMBO(CM58,S(KC_X)),
	COMBO(CM59,S(KC_K)),
	COMBO(CM60,S(KC_J)),
	COMBO(CM61,KC_ASTR),
	COMBO(CM62,KC_CIRC),
	COMBO(CM63,KC_PLUS),
	COMBO(CM64,KC_EQL),
	COMBO(CM65,KC_MINS),
	COMBO(CM66,KC_W),
	COMBO(CM67,KC_M),
	COMBO(CM68,KC_SLSH),
	COMBO(CM69,KC_UNDS),
	COMBO(CM70,S(KC_W)),
	COMBO(CM71,S(KC_M)),
	COMBO(CM72,KC_BSLS),
	COMBO(CM73,KC_PERC),
	COMBO(CM74,KC_AMPR),
	COMBO(CM75,KC_DLR),
	COMBO(CM76,KC_PIPE),
	COMBO(CM77,KC_QUOT),
	COMBO(CM78,KC_SCLN),
	COMBO(CM79,KC_QUES),
	COMBO(CM80,KC_COMMA),
	COMBO(CM81,KC_DQT),
	COMBO(CM82,KC_COLN),
	COMBO(CM83,KC_EXLM),
	COMBO(CM84,KC_DOT),
	COMBO(CM85,KC_GRAVE),
	COMBO(CM86,KC_TILDE),
	COMBO(CM87,KC_ENTER),
	COMBO(CM88,KC_TAB),
	COMBO(CM89,KC_ESC),
	COMBO(CM90,KC_DEL),
	COMBO(CM91,KC_ALGR),
	COMBO(CM92,QK_LEAD),
	COMBO(CM93,MY_LGUI),
	COMBO(CM94,MY_LALT),
	COMBO(CM95,MY_LCTL),
	COMBO(CM96,MY_LSFT),
	COMBO(CM97,KC_RIGHT),
	COMBO(CM98,KC_UP),
	COMBO(CM99,KC_DOWN),
	COMBO(CM100,KC_LEFT),
	COMBO(CM101,KC_PGUP),
	COMBO(CM102,KC_HOME),
	COMBO(CM103,KC_END),
	COMBO(CM104,KC_PGDN),

};
// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_advanced_keycodes.md
// This will need some messing with but it's close
bool process_record_user_taipo(uint16_t keycode, keyrecord_t *record) {
    if(record->event.pressed)
        switch(keycode) {
        case MY_LGUI: add_oneshot_mods(MOD_BIT(KC_LGUI)); add_mods(MOD_BIT(KC_LGUI)); break;
        case MY_LALT: add_oneshot_mods(MOD_BIT(KC_LALT)); add_mods(MOD_BIT(KC_LALT)); break;
        case MY_LCTL: add_oneshot_mods(MOD_BIT(KC_LCTL)); add_mods(MOD_BIT(KC_LCTL)); break;
        case MY_LSFT: add_oneshot_mods(MOD_BIT(KC_LSFT)); add_mods(MOD_BIT(KC_LSFT)); break;
        }
    else
        switch(keycode) {
        case MY_LGUI: case MY_LALT: case MY_LCTL: case MY_LSFT: clear_mods(); break;
        }
    return true;
};

// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_leader_key.md
// This lets you do something like F12 with LEADER+0+2
// The timings need fixing though
void leader_end_user_taipo(void) {
    if(leader_sequence_one_key(KC_1)) { tap_code16(KC_F1); }
    if(leader_sequence_one_key(KC_2)) { tap_code16(KC_F2); }
    if(leader_sequence_one_key(KC_3)) { tap_code16(KC_F3); }
    if(leader_sequence_one_key(KC_4)) { tap_code16(KC_F4); }
    if(leader_sequence_one_key(KC_5)) { tap_code16(KC_F5); }
    if(leader_sequence_one_key(KC_6)) { tap_code16(KC_F6); }
    if(leader_sequence_one_key(KC_7)) { tap_code16(KC_F7); }
    if(leader_sequence_one_key(KC_8)) { tap_code16(KC_F8); }
    if(leader_sequence_one_key(KC_9)) { tap_code16(KC_F9); }

    if(leader_sequence_two_keys(KC_0, KC_0)) { tap_code16(KC_F10); }
    if(leader_sequence_two_keys(KC_0, KC_1)) { tap_code16(KC_F11); }
    if(leader_sequence_two_keys(KC_0, KC_2)) { tap_code16(KC_F12); }
    if(leader_sequence_two_keys(KC_0, KC_3)) { tap_code16(KC_F13); }
    if(leader_sequence_two_keys(KC_0, KC_4)) { tap_code16(KC_F14); }
    if(leader_sequence_two_keys(KC_0, KC_5)) { tap_code16(KC_F15); }
    if(leader_sequence_two_keys(KC_0, KC_6)) { tap_code16(KC_F16); }
    if(leader_sequence_two_keys(KC_0, KC_7)) { tap_code16(KC_F17); }
    if(leader_sequence_two_keys(KC_0, KC_8)) { tap_code16(KC_F18); }
    if(leader_sequence_two_keys(KC_0, KC_9)) { tap_code16(KC_F19); }
}

