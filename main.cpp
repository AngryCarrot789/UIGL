#include <iostream>
#include <GLFW/glfw3.h>
#include "TimeTrigger.h"
#include "app/App.h"

#define YOUR_MOOOOO 23

void update() {
    std::cout << "Update!" << std::endl;
}

void render() {
    std::cout << "Render!" << std::endl;
}

int main() {
    std::cout << YOUR_MOOOOO << "Hello, World!" << std::endl;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    TimeTrigger updateTrigger = TimeTrigger::fromSeconds(1);
    TimeTrigger renderTrigger = TimeTrigger::fromSeconds(2);

    App* app = App::get();

    while (!glfwWindowShouldClose(window)) {
        if (updateTrigger.getAndStepIf()) {
            update();
        }

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        if (renderTrigger.getAndStepIf()) {
            render();
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        // Wait for events to arrive
        glfwWaitEvents();
    }

    glfwTerminate();
    return 0;
}
