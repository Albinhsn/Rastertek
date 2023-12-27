#include "positionclass.h"

PositionClass::PositionClass() {
  m_positionX = 0.0f;
  m_positionY = 0.0f;
  m_positionZ = 0.0f;

  m_rotationX = 0.0f;
  m_rotationY = 0.0f;
  m_rotationZ = 0.0f;

  m_frameTime = 0.0f;

  m_leftTurnSpeed = 0.0f;
  m_rightTurnSpeed = 0.0f;

  m_leftSpeed = 0.0f;
  m_rightSpeed = 0.0f;
}
PositionClass::~PositionClass() {}
PositionClass::PositionClass(const PositionClass &other) {}

void PositionClass::SetFrameTime(int time) { m_frameTime = (float)time; }
void PositionClass::GetRotation(float &y) { y = m_rotationY; }
void PositionClass::GetPosition(float &positionX, float &positionY,
                                float &positionZ) {
  positionX = m_positionX;
  positionY = m_positionY;
  positionZ = m_positionZ;
}
void PositionClass::SetPosition(float positionX, float positionY,
                                float positionZ) {
  m_positionX = positionX;
  m_positionY = positionY;
  m_positionZ = positionZ;
}

void PositionClass::TurnLeft(bool keydown) {
  if (keydown) {
    m_leftTurnSpeed += m_frameTime * 0.01f;

    if (m_leftTurnSpeed > (m_frameTime * 0.15f)) {
      m_leftTurnSpeed = m_frameTime * 0.15f;
    }
  } else {
    m_leftTurnSpeed -= m_frameTime * 0.005f;

    if (m_leftTurnSpeed < 0.0f) {
      m_leftTurnSpeed = 0.0f;
    }
  }

  m_rotationY -= m_leftTurnSpeed;
  if (m_rotationY < 0.0f) {
    m_rotationY += 360.0f;
  }
}

void PositionClass::TurnRight(bool keydown) {
  if (keydown) {
    m_rightTurnSpeed += m_frameTime * 0.01f;

    if (m_rightTurnSpeed > (m_frameTime * 0.15f)) {
      m_rightTurnSpeed = m_frameTime * 0.15f;
    }
  } else {
    m_rightTurnSpeed -= m_frameTime * 0.005f;

    if (m_rightTurnSpeed < 0.0f) {
      m_rightTurnSpeed = 0.0f;
    }
  }

  m_rotationY += m_rightTurnSpeed;
  if (m_rotationY > 360.0f) {
    m_rotationY -= 360.0f;
  }
}

void PositionClass::MoveLeft(bool keydown) {
  float radians;

  if (keydown) {
    m_leftSpeed += m_frameTime * 0.001f;
    if (m_leftSpeed > (m_frameTime * 0.5f)) {
      m_leftSpeed = m_frameTime * 0.5f;
    }
  } else {
    m_leftSpeed -= m_frameTime * 0.001f;

    if (m_leftSpeed < 0.0f) {
      m_leftSpeed = 0.0f;
    }
  }

  radians = m_rotationY * 0.174532925f;

  m_positionX -= cosf(radians) * m_leftSpeed;
  m_positionZ -= sinf(radians) * m_leftSpeed;
}

void PositionClass::MoveRight(bool keydown) {
  float radians;

  // Update the right speed movement based on the frame time and whether the
  // user is holding the key down or not.
  if (keydown) {
    m_rightSpeed += m_frameTime * 0.001f;

    if (m_rightSpeed > (m_frameTime * 0.5f)) {
      m_rightSpeed = m_frameTime * 0.5f;
    }
  } else {
    m_rightSpeed -= m_frameTime * 0.001f;

    if (m_rightSpeed < 0.0f) {
      m_rightSpeed = 0.0f;
    }
  }

  // Convert degrees to radians.
  radians = m_rotationY * 0.0174532925f;

  // Update the position.
  m_positionX += cosf(radians) * m_rightSpeed;
  m_positionZ += sinf(radians) * m_rightSpeed;

  return;
}
