#include "position.h"

void InitializePosition(Position &position) {
    position.frameTime = 0.0f;
    position.rotationY = 0.0f;
    position.leftTurnSpeed = 0.0f;
    position.rightTurnSpeed = 0.0f;
}

void TurnLeft(Position &position, bool keydown) {
    // If the key is pressed increase the speed at which the camera turns left.  If not slow down the turn speed.
    if (keydown) {
        position.leftTurnSpeed += position.frameTime * 0.01f;

        if (position.leftTurnSpeed > (position.frameTime * 0.15f)) {
            position.leftTurnSpeed = position.frameTime * 0.15f;
        }
    } else {
        position.leftTurnSpeed -= position.frameTime * 0.005f;

        if (position.leftTurnSpeed < 0.0f) {
            position.leftTurnSpeed = 0.0f;
        }
    }

    // Update the rotation using the turning speed.
    position.rotationY -= position.leftTurnSpeed;
    if (position.rotationY < 0.0f) {
        position.rotationY += 360.0f;
    }
}
void TurnRight(Position &position, bool keydown) {
    // If the key is pressed increase the speed at which the camera turns right.  If not slow down the turn speed.
    if (keydown) {
        position.rightTurnSpeed += position.frameTime * 0.01f;

        if (position.rightTurnSpeed > (position.frameTime * 0.15f)) {
            position.rightTurnSpeed = position.frameTime * 0.15f;
        }
    } else {
        position.rightTurnSpeed -= position.frameTime * 0.005f;

        if (position.rightTurnSpeed < 0.0f) {
            position.rightTurnSpeed = 0.0f;
        }
    }

    // Update the rotation using the turning speed.
    position.rotationY += position.rightTurnSpeed;
    if (position.rotationY > 360.0f) {
        position.rotationY -= 360.0f;
    }
}
