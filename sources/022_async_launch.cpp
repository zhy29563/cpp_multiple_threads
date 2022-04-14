#include <iostream>
#include <thread>
#include <future>
#include <chrono>

int main()
{
    std::cout << "parent thread: start" << std::endl;
    std::cout << "parent thread: id is " << std::this_thread::get_id() << std::endl;

    // 默认启动策略
    // std::launch::async|std::launch::deferred
    // 由系统选择其中一个
    std::future<void> result_future = std::async([](){
        std::cout << "child thread: start" << std::endl;
        std::cout << "child thread: id is " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "child thread: end" << std::endl;
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "parent thread: run other task" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 确保可调用对象，一定会被执行
    result_future.wait();

    std::cout << "parent thread: end" << std::endl;
    return EXIT_SUCCESS;
}
