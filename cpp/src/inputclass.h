#ifndef INPUTCLASS_H
#define INPUTCLASS_H

const int KEY_ESCAPE = 0;
const int KEY_LEFT = 1;
const int KEY_RIGHT = 2;

class InputClass {
public:
  InputClass();
  InputClass(const InputClass &);
  ~InputClass();

  void Initialize();

  void KeyDown(int);
  void KeyUp(int);

  bool IsEscapePressed();
  bool IsLeftArrowPressed();
  bool IsRightArrowPressed();

  void ProcessMouse(int, int);
  void GetMouseLocation(int &, int &);

  void MouseDown();
  void MouseUp();

  bool IsMousePressed();

private:
  bool m_keyboardState[256];
  int m_mouseX, m_mouseY;
  bool m_mousePressed;
};

#endif
