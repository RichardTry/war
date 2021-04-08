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
#include "camera.h"
#include "vao.h"
#include "obj-loader/objloader.h"
#include "program.h"
#include "content.h"
#include "world.h"

using namespace std;

GLuint vertexVBO;

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
    model = glm::mat4(1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    if (!sf::Shader::isAvailable())
    {
        cout << "shaders are not available..." << endl;
    }
    sf::Shader shader;
    if (!shader.loadFromFile("test.vert", "test.frag"))
    {
        cout << "shader files not found..." << endl;
    }

    Program prog;
    prog.AddShader("test.frag", GL_FRAGMENT_SHADER);
    prog.AddShader("test.vert", GL_VERTEX_SHADER);

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
                        sf::Mouse::setPosition(window_center, window); // For keeping camera angle after returning from ESC mode
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
            /*
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
                    cout << "EVENT!" << endl;
                }
            }
            */
        }

        /*
        if (!cursor) {
            prev_mouse_x = window.getSize().x / 2;
            prev_mouse_y = window.getSize().y / 2;
            //sf::Mouse::setPosition(sf::Vector2i(prev_mouse_x,prev_mouse_y), window);
        }
        */

        /* Render here */
        glClearColor(0.6,0.8,1,0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        view = glm::mat4(1.0);
        MoveCamera();

        model = glm::mat4(1.0);
        //sf::Shader::bind(&shader);
        prog.Use(projection * view);
        //shader.setUniform("mvp", sf::Glsl::Mat4(glm::value_ptr(projection * view)));
        DrawWorld(&camera);
        //sf::Shader::bind(NULL);
        window.display();
    }

    return 0;
}
