//
// Created by kettl on 03/01/2023.
//

#ifndef UIGL_MUTEXOBJECT_H
#define UIGL_MUTEXOBJECT_H

#include <mutex>

typedef std::recursive_mutex mutex;

template<class T>
class MutexObject {
private:
    mutable T* m_ref;
    mutable mutex* m_mutex;

public:
    explicit MutexObject(T* ref) {
        m_ref = ref;
        m_mutex = new std::recursive_mutex();
    }
public:
    T* acquire() {
        lock();
        return m_ref;
    }

    T* getRef() {
        return m_ref;
    }

    void free() {
        m_mutex->unlock();
    }

    void lock() {
        m_mutex->lock();
    }
};

#endif //UIGL_MUTEXOBJECT_H
