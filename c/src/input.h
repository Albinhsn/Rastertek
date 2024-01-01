#ifndef INPUT_H
#define INPUT_H

const int KEY_ESCAPE = 0;
const int KEY_LEFT = 1;
const int KEY_RIGHT = 2;

struct Input {
    bool keyboardState[256];
    int mouseX, mouseY;
    bool mousePressed;
};

void InitializeInput(Input *input);
void MouseDown(Input *input);
void MouseUp(Input *input);
void KeyDown(Input *input, int keySymbol);
void KeyUp(Input *input, int keySymbol);
bool IsEscapePressed(Input *input);
bool IsLeftArrowPressed(Input *input);
bool IsRightArrowPressed(Input *input);

#endif
