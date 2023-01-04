//
// Created by kettl on 04/01/2023.
//

#ifndef UIGL_WINDOW_H
#define UIGL_WINDOW_H

#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow* m_handle;
public:
    Window(GLFWwindow* window) {
        m_handle = window;
    }

public:
    void show() {
        glfwShowWindow(m_handle);
    }

    void makeContextCurrent() {
        glfwMakeContextCurrent(m_handle);
    }

    void swapBuffers() {
        glfwSwapBuffers(m_handle);
    }
};

#endif //UIGL_WINDOW_H
