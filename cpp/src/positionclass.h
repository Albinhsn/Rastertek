#ifndef POSITIONCLASS_H
#define POSITIONCLASS_H


#include <math.h>
class PositionClass {
public:
  PositionClass();
  PositionClass(const PositionClass &);
  ~PositionClass();

  void SetFrameTime(int);
  void GetRotation(float &);

  void GetPosition(float&, float&, float &);
  void SetPosition(float, float, float );

  void MoveLeft(bool);
  void MoveRight(bool);
  void TurnLeft(bool);
  void TurnRight(bool);

private:
  float m_positionX, m_positionY, m_positionZ;
  float m_rotationX, m_rotationY, m_rotationZ;
  float m_frameTime;
  float m_leftTurnSpeed, m_rightTurnSpeed;
  float m_leftSpeed, m_rightSpeed;
};

#endif
