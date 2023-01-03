//
// Created by kettl on 03/01/2023.
//

#ifndef UIGL_TIMETRIGGER_H
#define UIGL_TIMETRIGGER_H

#include "GLFW/glfw3.h"

class TimeTrigger {
private:
    double mLastTick;
    double mInterval;
public:
    explicit TimeTrigger(double interval);

    static TimeTrigger fromSeconds(double seconds);

    static TimeTrigger fromMillis(double millis) {
        return TimeTrigger(1000.0 / millis);
    }

    static TimeTrigger fromTps(double ticksPerSecond) {
        return TimeTrigger(1.0 / ticksPerSecond);
    }

    void step() {
        mLastTick = glfwGetTime();
    }

    double getDiff() {
        return glfwGetTime() - mLastTick;
    }

    bool canStep() {
        return getDiff() > mInterval;
    }

    bool getAndStepIf() {
        if (canStep()) {
            step();
            return true;
        }
        return false;
    }
};


#endif //UIGL_TIMETRIGGER_H
