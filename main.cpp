#include <iostream>
#include <GLFW/glfw3.h>
#include <thread>
#include "TimeTrigger.h"
#include "app/App.h"

#include "MutexObject.h"

#define YOUR_MOOOOO 23

void update() {
    std::cout << "Update!" << std::endl;
}

void render() {
    std::cout << "Render!" << std::endl;
}

class Counter {
private:
    int m_counter;
public:
    Counter() {
        m_counter = 0;
    }

    void increment() {
        m_counter++;
    }

    int getValue() {
        return m_counter;
    }
};

MutexObject<Counter> m_counter = MutexObject<Counter>(new Counter());

void thread_main1() {
    for (int i = 0; i < 10000; ++i) {
        m_counter.acquire()->increment();
        m_counter.free();
        std::this_thread::yield();
    }
}

void thread_main2() {
    for (int i = 0; i < 10000; ++i) {
        m_counter.acquire()->increment();
        m_counter.free();
    }
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

    App* app = App::get();

    app->m_window = new Window(window);

    std::thread thread1 = std::thread(thread_main1);
    std::thread thread2 = std::thread(thread_main2);

    thread1.join();
    thread2.join();


    app->m_window->makeContextCurrent();
    app->m_window->show();

    std::cout << "Counter = " << m_counter.acquire()->getValue() << std::endl;

    try {
        do {
            app->tick();
            if (app->isInShutdownMode() || glfwWindowShouldClose(window)) {
                std::cout << "Shutting down!" << glfwWindowShouldClose(window) <<  std::endl;
                break;
            }

            if (app->isRenderDirty()) {
                if (app->isFullRenderDirty()) {
                    /* Render here */
                    glClear(GL_COLOR_BUFFER_BIT);
                }

                /* Swap front and back buffers */
                app->m_window->swapBuffers();
            }

            // Wait for events to arrive
            glfwWaitEvents();
        } while (true);
    }
    catch (std::exception& e) {
        std::cout << "Error in main app: " << e.what() << std::endl;
    }

    glfwTerminate();
    return 0;
}
