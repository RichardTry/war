cmake_minimum_required(VERSION 3.25)
project(war)

# The COMPONENTS part checks that OGRE was built the way we need it
# The CONFIG flag makes sure we get OGRE instead of OGRE-next
find_package(OGRE REQUIRED COMPONENTS Bites CONFIG)
link_directories(${CMAKE_BINARY_DIR}/lua)

SET(SOURCES
    camera.cpp
    chunk.cpp
    content.cpp
    game.cpp
    main.cpp
    object.cpp
    tile_content.cpp
    unit.cpp
    window.cpp
    world.cpp
    )
 
# add the source files as usual
add_executable(war ${SOURCES})
 
# this also sets the includes and pulls third party dependencies
target_link_libraries(war OgreBites lua53)