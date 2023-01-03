//
// Created by kettl on 03/01/2023.
//

#include "TimeTrigger.h"

TimeTrigger::TimeTrigger(double interval) {
    mInterval = interval;
    mLastTick = 0;
}

TimeTrigger TimeTrigger::fromSeconds(double seconds) {
    return TimeTrigger(seconds);
}
