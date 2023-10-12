// example1.cpp

#include <iostream>
#include <mutex>
#include <thread>

class Resource {
private:
    std::mutex mtx_;

public:
    std::mutex& getMutex() {
        return mtx_;
    }

    void doSomething() {
        std::lock_guard<std::mutex> lock(mtx_);
        // Perform operations on the resource
        std::cout << "Performing operations on the resource." << std::endl;
    }
};

int main() {
    Resource resource;

    std::lock_guard<std::mutex> lock(resource.getMutex());
    resource.doSomething();

    return 0;
}