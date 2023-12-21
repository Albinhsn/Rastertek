#include "inputclass.h"

InputClass::InputClass() {}
InputClass::InputClass(const InputClass &other) {}
InputClass::~InputClass() {}

void InputClass::Initialize() {

  for (int i = 0; i < 256; i++) {
    m_keyboardState[i] = false;
  }

  m_mouseX = 0;
  m_mouseY = 0;
  m_mousePressed = false;

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

void InputClass::ProcessMouse(int mouseMotionX, int mouseMotionY) {
  m_mouseX = mouseMotionX;
  m_mouseY = mouseMotionY;
}

void InputClass::GetMouseLocation(int &mouseX, int &mouseY) {
  mouseX = m_mouseX;
  mouseY = m_mouseY;
}

void InputClass::MouseDown() { m_mousePressed = true; }

void InputClass::MouseUp() { m_mousePressed = false; }

bool InputClass::IsMousePressed() { return m_mousePressed; }
