#ifndef POSITION_H
#define POSITION_H

#include <math.h>

struct Position {
    float frameTime;
    float rotationY;
    float leftTurnSpeed, rightTurnSpeed;
};

void InitializePosition(Position &position);

void TurnLeft(Position &position, bool keydown);
void TurnRight(Position &position, bool keydown);

#endif
