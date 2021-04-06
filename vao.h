#ifndef VAO_H
#define VAO_H

#include <vector>
#include "glm/glm.hpp"
#include <glad/glad.h>

class VAO
{
    private:
        GLuint vao;
        std::vector<GLuint> vbos;
        GLuint ebo = 0;
        size_t ebo_len;

    public:
        VAO();
        ~VAO();

        void Bind();
        void AddVBO(const std::vector<glm::vec3>& data);
        void AddEBO(const std::vector<unsigned>& data);
        void Clear();

        void Draw();
};

#endif // VAO_H
