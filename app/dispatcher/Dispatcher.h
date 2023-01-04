//
// Created by kettl on 03/01/2023.
//

#ifndef UIGL_DISPATCHER_H
#define UIGL_DISPATCHER_H

#include <vector>
#include <mutex>
#include <thread>

#include "../../MutexObject.h"
#include "DispatcherOperation.h"
#include "DispatcherGlobals.h"

class Dispatcher;

class Dispatcher {
private:
    std::thread::id m_owner_thread_id;

    MutexObject<OpPtrList>* items[8]{};

    Dispatcher() {
        m_owner_thread_id = std::this_thread::get_id();
        for (int i = 0; i < 8; i++) {
            items[i] = new MutexObject<OpPtrList>(new OpPtrList());
        }
    }

public:
    void invoke(Action callback) {
        invoke(callback, DispatcherPriority::APP_PRE_TICK);
    }

    void invoke(Action callback, DispatcherPriority priority) {
        DispatcherOperation* operation = new DispatcherOperation(this, priority, callback);
        if (priority == DispatcherPriority::APP_PRE_TICK && isOwnerThread()) {
            operation->invoke();
            delete (operation);
        }
        else {
            invoke(operation);
        }
    }

    void invoke(DispatcherOperation* operation) {
        MutexObject<OpPtrList>* mutex = items[operation->getPriority()];
        mutex->acquire()->push_back(operation);
        mutex->free();
    }

    void process(DispatcherPriority priority) {
        MutexObject<OpPtrList>* mutex = items[priority];
        processList(mutex->acquire());
        mutex->free();
    }

    bool isOwnerThread() {
        return std::this_thread::get_id() == m_owner_thread_id;
    }

private:
    void processList(OpPtrList* list) {
        for (DispatcherOperation* item : *list) {
            processOperation(item);
        }
        list->clear();
    }

    void processOperation(DispatcherOperation* operation) {
        try {
            operation->invoke();
            delete operation;
        }
        catch (std::exception& ex) {
            delete operation;
            throw;
        }
    }
public:
    static Dispatcher* get() {
        return gInstance != nullptr ? gInstance : (gInstance = new Dispatcher());
    }

private:
    static Dispatcher* gInstance;
};


#endif //UIGL_DISPATCHER_H
