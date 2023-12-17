#include "inputclass.h"

InputClass::InputClass() {}
InputClass::InputClass(const InputClass &other) {}
InputClass::~InputClass() {}

void InputClass::Initialize() {

  for (int i = 0; i < 256; i++) {
    m_keyboardState[i] = false;
  }

  return;
}

void InputClass::KeyDown(int keySymbol) {
  if (keySymbol == 65307) {
    m_keyboardState[KEY_ESCAPE] = true;
  }

  return;
}

void InputClass::KeyUp(int keySymbol) {
  if (keySymbol == 65307) {
    m_keyboardState[KEY_ESCAPE] = false;
  }

  return;
}

bool InputClass::IsEscapePressed() { return m_keyboardState[KEY_ESCAPE]; }
