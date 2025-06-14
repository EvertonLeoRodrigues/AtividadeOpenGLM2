#include "shaderClass/shaderClass.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <fstream>
#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

using namespace std;

const GLint WIDTH = 800, HEIGHT = 600;

void kay_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Protótipo da função de callback de teclado
GLuint setupGeometry();
GLuint createTriangle(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);

int main()
{

    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

GLuint createTriangle(GLfloat x0, GLfloat y0, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
}

GLuint setupGeometry()
{
    GLfloat vertices[] = {
        -0.5, -0.5, 0.0, // v0
        0.5, -0.5, 0.0, // v1
        0.0, 0.5, 0.0, // v2
    };

    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    return VAO;
}
