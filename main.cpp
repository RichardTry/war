#include <iostream>

#include "window.h"
#include "transform.h"
#include "camera.h"
#include "obj-loader/objloader.h"
#include "content.h"
#include "world.h"

#include "game.h"

// int main() {
//     try
//     {
//     	Game app;
//         app.initApp();
//         app.getRoot()->startRendering();
//         app.closeApp();
//     }
//     catch (const std::exception& e)
//     {
//         std::cerr << "Error occurred during execution: " << e.what() << '\n';
//         return 1;
//     }

//     return 0;
// }

using namespace std;

int main()
{
    try {
        Game app;
        app.initApp();

        // InitWorld() here?
        srand(time(0));

        Content content;
        content.initContent("test_save");

    // InitWorld();

    bool running = true;
    // while (running)
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed){
    //             // end the program
    //             running = false;
    //         }
    //         else if (event.type == sf::Event::Resized){
    //             // adjust the viewport when the window is resized
    //             glViewport(0, 0, event.size.width, event.size.height);
    //             projection = glm::perspective(glm::radians(90.0f), (float)event.size.width / event.size.height, 0.1f, 1000.0f);
    //             window_center = sf::Vector2i(window.getSize() / 2u);
    //         }
    //         else if (event.type == sf::Event::KeyPressed){
    //             if (event.key.code == sf::Keyboard::W){
    //                 moveForward = true;
    //             }
    //             else if (event.key.code == sf::Keyboard::S){
    //                 moveBack = true;
    //             }
    //             else if (event.key.code == sf::Keyboard::A){
    //                 moveLeft = true;
    //             }
    //             else if (event.key.code == sf::Keyboard::D){
    //                 moveRight = true;
    //             }
    //             else if (event.key.code == sf::Keyboard::Space){
    //                 moveUp = true;
    //             }
    //             else if (event.key.code == sf::Keyboard::LShift){
    //                 moveDown = true;
    //             }
    //             else if (event.key.code == sf::Keyboard::Escape){
    //                 if (cursor){
    //                     cursor = false;
    //                     window.setMouseCursorVisible(false);
    //                     sf::Mouse::setPosition(window_center, window); // For keeping camera angle after returning from ESC mode
    //                 }
    //                 else {
    //                     cursor = true;
    //                     window.setMouseCursorVisible(true);
    //                 }
    //             }
    //         }
    //         else if (event.type == sf::Event::KeyReleased){
    //             if (event.key.code == sf::Keyboard::W){
    //                 moveForward = false;
    //             }
    //             else if (event.key.code == sf::Keyboard::S){
    //                 moveBack = false;
    //             }
    //             else if (event.key.code == sf::Keyboard::A){
    //                 moveLeft = false;
    //             }
    //             else if (event.key.code == sf::Keyboard::D){
    //                 moveRight = false;
    //             }
    //             else if (event.key.code == sf::Keyboard::Space){
    //                 moveUp = false;
    //             }
    //             else if (event.key.code == sf::Keyboard::LShift){
    //                 moveDown = false;
    //             }
    //         }
    //     }

    //     /* Render here */
    //     glClearColor(0.6,0.8,1,0.0);

    //     // MoveCamera();
    // }
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (const std::exception& e) {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}