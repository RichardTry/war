#include "camera.h"

Transform camera;

bool cursor = true;

bool moveForward = false, moveBack = false, moveLeft = false, moveRight = false, moveUp = false, moveDown = false;
int prev_mouse_x = 0.0, prev_mouse_y = 0.0;

glm::mat4 model, view, projection;
float camRotSpeed = 0.01;
float camMoveSpeed = 0.01;

void MoveCamera()
{
    if (moveForward) {
        camera.position.x += -sin(camera.rotation.y) * camMoveSpeed;
        camera.position.z += -cos(camera.rotation.y) * camMoveSpeed;
    }
    if (moveBack) {
        camera.position.x += sin(camera.rotation.y) * camMoveSpeed;
        camera.position.z += cos(camera.rotation.y) * camMoveSpeed;
    }
    if (moveLeft) {
        camera.position.x += -cos(camera.rotation.y) * camMoveSpeed;
        camera.position.z += sin(camera.rotation.y) * camMoveSpeed;
    }
    if (moveRight) {
        camera.position.x += cos(camera.rotation.y) * camMoveSpeed;
        camera.position.z += -sin(camera.rotation.y) * camMoveSpeed;
    }
    if (moveUp) {
        camera.position.y += camMoveSpeed;
    }
    if (moveDown) {
        camera.position.y -= camMoveSpeed;
    }

    view = glm::rotate(view, camera.rotation.x, glm::vec3(-1.0f, 0.0f, 0.0f));
    view = glm::rotate(view, camera.rotation.y, glm::vec3(0.0f, -1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(-camera.position.x, -camera.position.y, -camera.position.z));
}
