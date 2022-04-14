#include <iostream>
#include <thread>
#include <future>
#include <chrono>

int main()
{
    std::cout << "parent thread: start" << std::endl;
    std::cout << "parent thread: id is " << std::this_thread::get_id() << std::endl;

    // 通过输出可以看到，在该语句执行之后，可调用对象未开始执行。在调用wait()之后，可调用对象才开始执行，且可调动对象运行在调用线程上，即同步调用
    std::future<void> result_future = std::async(std::launch::deferred, [](){
        std::cout << "child thread: start" << std::endl;
        std::cout << "child thread: id is " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << "child thread: end" << std::endl;
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "parent thread: run other task" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    result_future.wait();

    std::cout << "parent thread: end" << std::endl;
    return EXIT_SUCCESS;
}
