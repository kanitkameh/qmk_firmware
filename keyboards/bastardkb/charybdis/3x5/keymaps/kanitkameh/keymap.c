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
    CLEAR_LAYERS,
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

bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
            currentOS = MAC;
            break;
        case OS_IOS:
            currentOS = MAC;
            break;
        case OS_WINDOWS:
            currentOS = WIN;
            break;
        case OS_LINUX:
            currentOS = LINUX;
            break;
        case OS_UNSURE:
            currentOS = LINUX;
            break;
    }

    return true;
}

enum layers{
  BASE,
  GAMING,
  GAMING_SHIFTED,
  NUMBERS,
  VIM,
  MOUSE,
  MEDIA,
  MOUSE_AND_MEDIA,
  MOUSE_THUMB,
  RGB_LAYER,
  LEFT_MODS,
  RIGHT_MODS
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                            MO(MOUSE_AND_MEDIA), LT(LEFT_MODS, KC_SPC), LT(NUMBERS, KC_TAB),   LT(NUMBERS, KC_BSPC), LT(RIGHT_MODS, KC_ENT)
    ),
    [GAMING] = LAYOUT(
        _______,  _______, _______, _______, _______,                                _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,                                _______, _______, _______, _______, _______,
        _______,  _______, _______, _______, _______,                                _______, _______, _______, _______, _______,
                                TG(MOUSE), KC_SPC, _______,                          _______, _______
    ),
    [GAMING_SHIFTED] = LAYOUT(
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,                                  _______, _______, _______, _______, _______,
        KC_LSFT,   KC_A,    KC_S,    KC_D,    KC_F,                                  _______, _______, _______, _______, _______,
        KC_LCTL,  KC_Z,    KC_X,    KC_C,    KC_V,                                   _______, _______, _______, _______, _______,
                                TG(MOUSE), KC_SPC, LT(NUMBERS, KC_LALT),                      _______, _______
    ),
    [NUMBERS] = LAYOUT(
        KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                               KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                                KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_GRAVE,  CW_TOGG,  QK_LOCK,  KC_ESC,  KC_EQL,                              KC_MINUS, KC_QUOT, KC_BSLS, KC_LBRC, KC_RBRC,
                                                 _______, _______, _______,          _______, _______
    ),
    [VIM] = LAYOUT(
        _______,  WORD_FORWARDS,  WORD_FORWARDS,  _______,  _______,                  YANK,    UNDO,    _______, _______, PASTE,
        _______,  _______,        CUT,  _______,  _______,                            KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, _______,
        _______,  CUT,  _______, VISUAL,  WORD_BACKWARDS,                             _______, _______, _______, _______, _______,
                                                      _______, _______, _______,          _______, _______
    ),
    [MOUSE] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,                             _______, MS_WHLU, _______, _______, _______,
        _______,  _______,  _______,  _______,  _______,                             _______, MS_BTN1, MS_BTN2, MS_BTN3, MS_BTN4,
        _______,  _______,  _______,  _______,  _______,                             _______, MS_BTN5, _______, _______, _______,
                                                      _______, _______, _______,          _______, _______
    ),
    [MEDIA] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______,
        _______,  DRAGSCROLL_MODE, MS_WHLD, KC_VOLU,  KC_BRIU,                       _______, _______, _______, _______, _______,
        _______,  _______,  _______,  KC_VOLD,  KC_BRID,                             _______, _______, _______, _______, _______,
                                                      _______, _______, _______,          _______, _______
    ),
    [MOUSE_AND_MEDIA] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,                             _______, MS_WHLU, _______, _______, _______,
        _______,  DRAGSCROLL_MODE, MS_WHLD, KC_VOLU,  KC_BRIU,                       _______, MS_BTN1, MS_BTN2, MS_BTN3, MS_BTN4,
        _______,  _______,  _______,  KC_VOLD,  KC_BRID,                             _______, MS_BTN5, _______, _______, _______,
                                                      _______, _______, _______,          _______, _______
    ),
    [MOUSE_THUMB] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______,
        _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______,
        _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______,
                                                      TG(MOUSE), _______, _______,          _______, _______
    ),
    [RGB_LAYER] = LAYOUT(
        _______,  _______,  _______,  _______,  UG_TOGG,                             _______, _______, _______, _______, _______,
        _______,  UG_SATU,  _______,  _______,  _______,                             UG_HUEU, _______, _______, _______, _______,
        _______,  UG_SPDU,  _______,  UG_VALU,  _______,                             UG_NEXT, _______, _______, _______, _______,
                                                      _______, _______, _______,          _______, _______
    ),
    [LEFT_MODS] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______,
        KC_LCTL,  KC_LALT,  KC_LGUI,  KC_LSFT,  _______,                             _______, _______, _______, _______, _______,
        _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______,
                                                      _______, _______, _______,          _______, LT(VIM, KC_ENT)
    ),
    [RIGHT_MODS] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,                             _______, _______, _______, _______, _______,
        _______,  _______,  _______,  _______,  _______,                             QK_LEAD, KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL,
        _______,  _______,  _______,  _______,  _______,                             _______, CLEAR_LAYERS, _______, _______, _______,
                                                      _______, LT(VIM, KC_SPC), _______,          _______, _______
    )
};

void leader_end_user(void) {
    // Different base layers(They aren't base layers in the qmk sense but are used like so)
    if (leader_sequence_five_keys(KC_C, KC_L, KC_E, KC_A, KC_R)) {
        layer_clear();
    }
    if (leader_sequence_four_keys(KC_G, KC_A, KC_M, KC_E)) {
        layer_invert(GAMING);
    }
    if (leader_sequence_five_keys(KC_G, KC_A, KC_M, KC_E, KC_S)) {
        layer_invert(GAMING_SHIFTED);
    }
    if (leader_sequence_five_keys(KC_M, KC_O, KC_U, KC_S, KC_E)) {
        layer_invert(MOUSE_THUMB);
    }
    if (leader_sequence_three_keys(KC_R, KC_G, KC_B)) {
        layer_invert(RGB_LAYER);
    }
    // for setting the OS
    if (leader_sequence_five_keys(KC_L, KC_I, KC_N, KC_U, KC_X)) {
        currentOS = LINUX;
    }
    // fallbakc if os detection doesn't work
    if (leader_sequence_three_keys(KC_W, KC_I, KC_N)) {
        currentOS = WIN;
    }
    if (leader_sequence_three_keys(KC_M, KC_A, KC_C)) {
        currentOS = MAC;
    }
};


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
                if(isVisualModeActive){
                    deactivateVisualMode();
                    // when keycode is pressed
                    if(currentOS == MAC) {
                        SEND_STRING(SS_LCMD("x"));
                    } else {
                        SEND_STRING(SS_LCTL("x"));
                    }
                } else {
                    SEND_STRING(SS_TAP(X_DEL));
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
        case CLEAR_LAYERS:
            if (record->event.pressed) {
                // when keycode is pressed
                layer_clear();
            }
            break;
    }
    return true;
};

layer_state_t layer_state_set_user(layer_state_t state) {
    deactivateVisualMode();
    return state;
}
