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
        std::cout << "Step 4." << std::endl;
        std::lock_guard<std::mutex> lock(this->getMutex());
        // Perform operations on the resource
        std::cout << "Performing operations on the resource." << std::endl;
    }
};

int main() {
    Resource resource;

    // {
    //     std::lock_guard<std::mutex> lock(resource.getMutex());
    // }
    // resource.doSomething();

    // std::thread t([&resource]() {
    //     std::cout << "Entering thread." << std::endl;
    //     std::lock_guard<std::mutex> lock(resource.getMutex());
    // });
    // t.join();

    return 0;
}
