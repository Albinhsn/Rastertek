#include "input.h"

void InitializeInput(Input *input) {
    for (int i = 0; i < 256; ++i) {
        input->keyboardState[i] = false;
    }
    input->mouseX = 0;
    input->mouseY = 0;
    input->mousePressed = false;
}

void KeyDown(Input *input, int keySymbol) {
    switch (keySymbol) {
    case 65307: {
        input->keyboardState[KEY_ESCAPE] = true;
        break;
    }
    case 65361: {
        input->keyboardState[KEY_LEFT] = true;
        break;
    }
    case 65363: {
        input->keyboardState[KEY_RIGHT] = true;
        break;
    }
    }
}
void KeyUp(Input *input, int keySymbol) {
    switch (keySymbol) {
    case 65307: {
        input->keyboardState[KEY_ESCAPE] = false;
        break;
    }
    case 65361: {
        input->keyboardState[KEY_LEFT] = false;
        break;
    }
    case 65363: {
        input->keyboardState[KEY_RIGHT] = false;
        break;
    }
    }
}

bool IsEscapePressed(Input *input) { return input->keyboardState[KEY_ESCAPE]; }
bool IsLeftArrowPressed(Input *input) { return input->keyboardState[KEY_LEFT]; }
bool IsRightArrowPressed(Input *input) { return input->keyboardState[KEY_RIGHT]; }
