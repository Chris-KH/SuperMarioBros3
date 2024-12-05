#pragma once
#include <memory>
#include <stdexcept>

using namespace std;

template <class T>
class Singleton {
public:
    static T& getInstance() {
        if (!instance) {
            instance.reset(new T());
        }
        return *instance;
    }

    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() {} // Private constructor to prevent instantiation
    ~Singleton() {}
    static unique_ptr<T> instance; // Use smart pointer for automatic memory management
};

// Initialize the static member
template <class T>
unique_ptr<T> Singleton<T>::instance = nullptr;