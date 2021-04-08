#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
//#include <SFML/OpenGL.hpp>
#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <math.h>
#include <unordered_set>

#include "window.h"
#include "transform.h"
#include "vao.h"
#include "obj-loader/objloader.h"
#include "program.h"
#include "content.h"
#include "world.h"

using namespace std;

bool cursor = true;

bool moveForward = false, moveBack = false, moveLeft = false, moveRight = false, moveUp = false, moveDown = false;
int prev_mouse_x = 0.0;
int prev_mouse_y = 0.0;

glm::mat4 model, view, projection;
Transform camera;
float camRotSpeed = 0.01;
float camMoveSpeed = 0.01;

GLuint vertexVBO;

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

/*
void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    projection = glm::perspective(glm::radians(90.0f), (float)width / height, 0.1f, 100.0f);
}
*/

int main()
{
    InitWindow();

    // InitWorld() here?
    srand(time(0));

    gladLoadGL();

    projection = glm::perspective(glm::radians(90.0f), (float)window.getSize().x / window.getSize().y, 0.1f, 1000.0f);
    view = glm::mat4(1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    Program prog;
    prog.AddShader("test.frag", GL_FRAGMENT_SHADER);
    prog.AddShader("test.vert", GL_VERTEX_SHADER);
    prog.Use(projection * view);

    VAO vao;
    vao.AddVBO({
    {-2, -2+5, 0},
    {2+5, -2+5, 0},
    {2, 2+5, 0},
    {-2, 2+15, 0}
    });
    vao.AddVBO({
    {1,0,0},
    {0,1,0},
    {0,0,1},
    {1,0,1}
    });
    vao.AddEBO({
    0, 1, 2,
    0, 2, 3
    });

    Content content;
    content.initContent("sdsd");
    camera.position.z += 30;
    camera.position.x += 16;
    camera.position.y += 5;

    bool running = true;
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized){
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }
            else if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::W){
                    moveForward = true;
                }
                else if (event.key.code == sf::Keyboard::S){
                    moveBack = true;
                }
                else if (event.key.code == sf::Keyboard::A){
                    moveLeft = true;
                }
                else if (event.key.code == sf::Keyboard::D){
                    moveRight = true;
                }
                else if (event.key.code == sf::Keyboard::Space){
                    moveUp = true;
                }
                else if (event.key.code == sf::Keyboard::LShift){
                    moveDown = true;
                }
                else if (event.key.code == sf::Keyboard::Escape){
                    if (cursor){
                        cursor = false;
                        window.setMouseCursorVisible(false);
                    }
                    else {
                        cursor = true;
                        window.setMouseCursorVisible(true);
                    }
                }
            }
            else if (event.type == sf::Event::KeyReleased){
                if (event.key.code == sf::Keyboard::W){
                    moveForward = false;
                }
                else if (event.key.code == sf::Keyboard::S){
                    moveBack = false;
                }
                else if (event.key.code == sf::Keyboard::A){
                    moveLeft = false;
                }
                else if (event.key.code == sf::Keyboard::D){
                    moveRight = false;
                }
                else if (event.key.code == sf::Keyboard::Space){
                    moveUp = false;
                }
                else if (event.key.code == sf::Keyboard::LShift){
                    moveDown = false;
                }
            }
            else if (event.type == sf::Event::MouseMoved){
                if (!cursor){
                    camera.rotation.y -= (event.mouseMove.x - prev_mouse_x) * camRotSpeed;
                    camera.rotation.x -= (event.mouseMove.y - prev_mouse_y) * camRotSpeed;
                    if (camera.rotation.x > M_PI / 2)
                        camera.rotation.x = M_PI / 2;
                    if (camera.rotation.x < -M_PI / 2)
                        camera.rotation.x = -M_PI / 2;
                    prev_mouse_x = event.mouseMove.x;
                    prev_mouse_y = event.mouseMove.y;
                }
            }
        }

        if (!cursor) {
            prev_mouse_x = window.getSize().x / 2;
            prev_mouse_y = window.getSize().y / 2;
            sf::Mouse::setPosition(sf::Vector2i(prev_mouse_x,prev_mouse_y), window);
        }

        /* Render here */
        glClearColor(0.6,0.8,1,0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = glm::mat4(1.0);
        MoveCamera();

        model = glm::mat4(1.0);
        prog.Use(projection * view);
        DrawWorld(&camera);
        glUseProgram(0);

        //window.display();
        window.display();
    }

    return 0;
}
