#include "input.h"

void InitializeInput(Input *input) {
    for (int i = 0; i < 256; ++i) {
        input->keyboardState[i] = false;
    }
}

void KeyDown(Input *input, int keySymbol) {
    if (keySymbol == 65307) {
        input->keyboardState[KEY_ESCAPE] = true;
    }
}
void KeyUp(Input *input, int keySymbol) {
    if (keySymbol == 65307) {
        input->keyboardState[KEY_ESCAPE] = false;
    }
}

bool IsEscapePressed(Input *input) { return input->keyboardState[KEY_ESCAPE]; }
