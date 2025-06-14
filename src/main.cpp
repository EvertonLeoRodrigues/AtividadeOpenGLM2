#include "shaderClass/shaderClass.hpp"
#include <GLFW/glfw3.h>
#include <Triangle/Triangle.hpp>
#include <cmath>
#include <fstream>
#include <glad/glad.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const GLint WIDTH = 800, HEIGHT = 600;

Triangle triangle;
std::vector<glm::vec2> clicks;

// Funções
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

int main()
{
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Triangle Creator", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Configura Callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    Shader myShader = Shader("shaders/vertex.glsl", "shaders/fragment.glsl");

    while (!glfwWindowShouldClose) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        myShader.use();
        glBindVertexArray(triangle.getVAO());
        glDrawArrays(GL_TRIANGLES, 0, triangle.getVertexCount());
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        // Converte para coordenadas normalizadas do OpenGL (-1, 1)
        float x = (2.0f * xpos) / WIDTH - 1.0f;
        float y = 1.0f - (2.0f * ypos) / HEIGHT;
        clicks.push_back(glm::vec2(x, y));
        if (clicks.size() == 3) {
            triangle.createTriangle(clicks[0].x, clicks[0].x, clicks[1].x, clicks[1].y, clicks[2].x, clicks[2].y);
            clicks.clear();
        }
    }
}
