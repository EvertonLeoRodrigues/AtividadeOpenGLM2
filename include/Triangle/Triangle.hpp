#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <cstddef>
#include <glad/glad.h>

class Triangle {
private:
    GLuint VAO;
    GLuint VBO;
    GLuint vertexCount;

public:
    Triangle()
        : VAO(0)
        , VBO(0)
        , vertexCount(0)
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
    }

    ~Triangle()
    {
        // Clean up
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void createTriangle(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
    {
        GLfloat vertices[] = {
            x0, y0, 0.0f,
            x1, y1, 0.0f,
            x2, y2, 0.0f
        };

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        GLint currentSize = 0;
        glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &currentSize);

        glBufferData(GL_ARRAY_BUFFER, currentSize + sizeof(vertices), NULL, GL_DYNAMIC_DRAW);
        if (currentSize > 0) {
            void* data = glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);
            glUnmapBuffer(GL_ARRAY_BUFFER);
        }

        glBufferSubData(GL_ARRAY_BUFFER, currentSize, sizeof(vertices), vertices);

        glVertexAttribPointer(0, 3, GL_FLOAT, 3 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);

        vertexCount += 3;

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    GLuint getVAO() const
    {
        return VAO;
    }

    GLuint getVertexCount() const
    {
        return vertexCount;
    }
};

#endif // TRIENGLE_H
