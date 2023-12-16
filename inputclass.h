#ifndef INPUTCLASS_H
#define INPUTCLASS_H

const int KEY_ESCAPE = 0;

class InputClass {
public:
  InputClass();
  InputClass(const InputClass &);
  ~InputClass();

  void Initialize();

  void KeyDown(int);
  void KeyUp(int);

  bool IsEscapePressed();

private:

  bool m_keyboardState[256];
};

#endif
