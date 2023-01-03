//
// Created by kettl on 03/01/2023.
//

#ifndef UIGL_RUNTIME_H
#define UIGL_RUNTIME_H

#include "GLFW/glfw3.h"

class Runtime {
public:
    static uint64_t systemTimeSeconds() {
        return glfwGetTime();
    }

    static uint64_t systemTimeMillis() {
        return glfwGetTime() * 1000;
    }

    static uint64_t systemTimeMicros() {
        return glfwGetTime() * 1000000;
    }

    static uint64_t systemTimeNanos() {
        return glfwGetTime() * 1000000000;
    }
};


#endif //UIGL_RUNTIME_H
