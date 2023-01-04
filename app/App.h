//
// Created by kettl on 03/01/2023.
//

#ifndef UIGL_APP_H
#define UIGL_APP_H

#include <cstdint>
#include "../Runtime.h"
#include "dispatcher/Dispatcher.h"
#include "Window.h"

class App {
public:
    Window* m_window;

private:
    uint64_t mInitMillis;

    bool mShutdownNextTick = false;
    bool mRenderDirty = true;
    bool mFullRenderRequired = true;

    explicit App(uint64_t initTime) {
        mInitMillis = initTime;
    }

public:
    static void wake() {
        glfwPostEmptyEvent();
    }

    void tick() {
        Dispatcher::get()->process(DispatcherPriority::APP_PRE_TICK);
    }

    bool isInShutdownMode() const {
        return mShutdownNextTick;
    }

    bool isRenderDirty() const {
        return mRenderDirty;
    }

    bool isFullRenderDirty() {
        if (!mFullRenderRequired)
            return false;
        mFullRenderRequired = false;
        return true;
    }

public:
    static App* get() {
        return gApp != nullptr ? gApp : (gApp = new App(Runtime::systemTimeMillis()));
    }

private:
    static App* gApp;
};


#endif //UIGL_APP_H
