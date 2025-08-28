// don't access directly, use vim functions activateVisualMode/deactivateVisualMode
bool isVisualModeActive = false;

// Used for simulating the vim motions
enum OS {
    MAC,
    LINUX,
    WIN
};

enum OS currentOS = MAC;

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

enum Operator {
    DELETE_OPERATOR,
    YANK_OPERATOR
};
bool isOperatorPending = false;
enum Operator currentOperator = YANK_OPERATOR;

// forward declarations
void cutSelection(void);
void copySelection(void);
void operatorPendingW(void);
void operatorPendingB(void);
void deleteNextWord(void);
void copyNextWord(void);
void deletePreviousWord(void);
void copyPreviousWord(void);
void moveCursorWordForward(void);
void moveCursorWordBackward(void);

void pressKeyU(void){
    // when keycode is pressed
    if(currentOS == MAC) {
        SEND_STRING(SS_LCMD("z"));
    } else {
        SEND_STRING(SS_LCTL("z"));
    }
}


void pressKeyX(void){
    if(isVisualModeActive){
        cutSelection();
    } else {
        SEND_STRING(SS_TAP(X_DEL));
    }
}

void cutSelection(void){
    deactivateVisualMode();
    if(currentOS == MAC) {
        SEND_STRING(SS_LCMD("x"));
    } else {
        SEND_STRING(SS_LCTL("x"));
    }
}


void pressKeyD(void){
    if(isVisualModeActive){
        cutSelection();
    } else {
        isOperatorPending = true;
        currentOperator = DELETE_OPERATOR;
    }
}

void pressKeyY(void){
    if(isVisualModeActive){
        copySelection();
    } else {
        isOperatorPending = true;
        currentOperator = YANK_OPERATOR;
    }
}

void copySelection(void){
    deactivateVisualMode();
    if(currentOS == MAC) {
        SEND_STRING(SS_LCMD("c"));
    } else {
        SEND_STRING(SS_LCTL("c"));
    }
}

void pressKeyP(void){
    deactivateVisualMode();
    // when keycode is pressed
    if(currentOS == MAC) {
        SEND_STRING(SS_LCMD("v"));
    } else {
        SEND_STRING(SS_LCTL("v"));
    }
}

void pressKeyV(void){
    // toggle visual mode
    if(isVisualModeActive){
        deactivateVisualMode();
    } else {
        activateVisualMode();
    }
}

void pressKeyW(void){
    if(isOperatorPending){
        operatorPendingW();
    } else {
        moveCursorWordForward();
    }
}

void operatorPendingW(void){
    if(currentOperator == DELETE_OPERATOR){
        deleteNextWord();
    }else{ //This is yank operator
        copyNextWord();
    }
    isOperatorPending = false;
}

void copyNextWord(void){
    activateVisualMode();
    moveCursorWordForward();
    copySelection();
}

void deleteNextWord(void){
    if(currentOS == MAC) {
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_DEL) SS_UP(X_LALT));
    } else {
        SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_DEL) SS_UP(X_LCTL));
    }
}

void moveCursorWordForward(void){
    if(currentOS == MAC) {
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_RIGHT) SS_UP(X_LALT));
    } else {
        SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_RIGHT) SS_UP(X_LCTL));
    }
}

void pressKeyB(void){
    if(isOperatorPending){
        operatorPendingB();
    }else{
        moveCursorWordBackward();
    }
}

void operatorPendingB(void){
    if(currentOperator == DELETE_OPERATOR){
        deletePreviousWord();
    }else{ //This is yank operator
        copyPreviousWord();
    }
    isOperatorPending = false;
}

void copyPreviousWord(){
    activateVisualMode();
    moveCursorWordBackward();
    copySelection();
}

void moveCursorWordBackward(void){
    if(currentOS == MAC) {
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_LEFT) SS_UP(X_LALT));
    } else {
        SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_LEFT) SS_UP(X_LCTL));
    }
}

void deletePreviousWord(void){
    if(currentOS == MAC) {
        SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_BACKSPACE) SS_UP(X_LALT));
    } else {
        SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_BACKSPACE) SS_UP(X_LCTL));
    }
}
