#ifndef PROGRAM_H
#define PROGRAM_H

#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Program
{
    private:
        GLuint prog;

    public:
        Program();
        ~Program();

        void AddShader(char* filename, GLuint type);
        void Use(glm::mat4 viewprojection);
};

#endif // PROGRAM_H
