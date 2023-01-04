//
// Created by kettl on 04/01/2023.
//

#ifndef UIGL_DISPATCHEROPERATION_H
#define UIGL_DISPATCHEROPERATION_H

#include "DispatcherGlobals.h"

class Dispatcher;

enum Status {
    PENDING = 0b000001,
    ABORTED = 0b000010,
    COMPLETED = 0b000100,
    COMPLETED_SUCCESS = 0b001100,
    COMPLETED_FAILED = 0b010100,
    EXECUTING = 0b100000
};

class DispatcherOperation {
private:
    Dispatcher* m_dispatcher;
    DispatcherPriority m_priority;
    Action m_callback;
    Status m_state;
    bool m_is_aborted;

public:
    DispatcherOperation(Dispatcher* pDispatcher, DispatcherPriority pPriority, Action pCallback) {
        this->m_dispatcher = pDispatcher;
        this->m_priority = pPriority;
        this->m_callback = pCallback;
        m_state = Status::PENDING;
    }

    void invoke() {
        m_state = Status::EXECUTING;
        try {
            m_callback();
            m_state = m_is_aborted ? ABORTED : COMPLETED_SUCCESS;
        }
        catch (std::exception& ex) {
            m_state = COMPLETED_FAILED;
            throw;
        }
    }

    void reset() {
        m_state = PENDING;
        m_is_aborted = false;
    }

    Dispatcher* getDispatcher() const {
        return m_dispatcher;
    }

    DispatcherPriority getPriority() const {
        return m_priority;
    }

    Action getMCb() const {
        return m_callback;
    }
};

typedef std::vector<DispatcherOperation*> OpPtrList;

#endif //UIGL_DISPATCHEROPERATION_H
