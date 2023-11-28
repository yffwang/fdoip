#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::shared_ptr<int> p1 = std::make_shared<int>(0);
constexpr int N = 10000;
std::vector<std::shared_ptr<int>> sp_arr1(N);
std::vector<std::shared_ptr<int>> sp_arr2(N);

void increment_count(std::vector<std::shared_ptr<int>>& sp_arr) {
    for (int i = 0; i < N; i++) {
        sp_arr[i] = p1;
    }
}

void testcase1_sharedptr_usecount_concurrency() {
    std::thread t1(increment_count, std::ref(sp_arr1));
    std::thread t2(increment_count, std::ref(sp_arr2));
    t1.join();
    t2.join();

    std::cout << __FUNCTION__ << std::endl << "Expected result is 20001, Real result is " << p1.use_count() << std::endl;
}

std::shared_ptr<int> p2 = std::make_shared<int>(0);
void modify_memory() {
    for (int i = 0; i < 10000; i++) {
        (*p2)++;
    }
}

void testcase2_sharedptr_modify_concurrency() {
    std::thread t1(modify_memory);
    std::thread t2(modify_memory);
    t1.join();
    t2.join();

    std::cout << __FUNCTION__ << std::endl << "Expected result is 20000, Real result is " << (*p2) << std::endl;
}

std::shared_ptr<int> p3 = std::make_shared<int>(1);
std::mutex m3;
void testcase3_sharedptr_modifyptr_concurrency() {
    auto modify_self = [&p3]() {
        std::lock_guard<std::mutex> lock(m3);
        for (int i = 0; i < 10000; i++) {
            p3 = std::make_shared<int>(1);
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; i++) {
        threads.emplace_back(modify_self);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << __FUNCTION__ << std::endl << "Expected result is 1, Real result is " << (*p3) << std::endl;
}

int main() {
    testcase1_sharedptr_usecount_concurrency();

    testcase2_sharedptr_modify_concurrency();

    testcase3_sharedptr_modifyptr_concurrency();

    return 0;
}


