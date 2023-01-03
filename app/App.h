//
// Created by kettl on 03/01/2023.
//

#ifndef UIGL_APP_H
#define UIGL_APP_H

#include <cstdint>

class App {
private:
    uint64_t mInitTime;

    explicit App(uint64_t time) {
        mInitTime = time;
    }
public:
    static App* get() {
        return gApp != nullptr ? gApp : (gApp = new App());
    }

private:
    static App* gApp;
};


#endif //UIGL_APP_H
