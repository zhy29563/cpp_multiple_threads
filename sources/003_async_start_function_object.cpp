#include <iostream>
#include <thread>
#include <future>
#include <chrono>

class A
{
public:
    void operator()()
    {
        std::cout << "child thread: start" << std::endl;
        std::cout << "child thread: id is " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "child thread: end" << std::endl;
    }
};

int main()
{
    std::cout << "parent thread: start" << std::endl;
    std::cout << "parent thread: id is " << std::this_thread::get_id() << std::endl;

    A a;
    std::future<void> result_future = std::async(a);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "parent thread: run other task" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    result_future.wait();

    std::cout << "parent thread: end" << std::endl;
    return EXIT_SUCCESS;
}
