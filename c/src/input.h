#ifndef INPUT_H
#define INPUT_H

const int KEY_ESCAPE = 0;
struct Input {
        bool keyboardState[256];
};

void InitializeInput(Input *input);
void KeyDown(Input *input, int keySymbol);
void KeyUp(Input *input, int keySymbol);
bool IsEscapePressed(Input *input);

#endif
