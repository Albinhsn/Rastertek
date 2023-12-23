#ifndef POSITIONCLASS_H
#define POSITIONCLASS_H

class PositionClass{
public:
  PositionClass();
  PositionClass(const PositionClass &);
  ~PositionClass();

  void SetFrameTime(int);
  void GetRotation(float&);

  void TurnLeft(bool);
  void TurnRight(bool);

private:
  float m_frameTime;
  float m_rotationY;
  float m_leftTurnSpeed, m_rightTurnSpeed;

};

#endif
