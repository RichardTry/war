#ifndef CAMERA_H
#define CAMERA_H

#include "transform.h"
//#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

extern Transform camera;

extern bool cursor;

extern bool moveForward, moveBack, moveLeft, moveRight, moveUp, moveDown;
extern int prev_mouse_x, prev_mouse_y;

extern glm::mat4 model, view, projection;
extern float camRotSpeed;
extern float camMoveSpeed;

void MoveCamera();

#endif // CAMERA_H
