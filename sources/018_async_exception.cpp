/* 异常处理
 *
 * 使用std::async()尝试运行的起来的后台线程或者使用std::future<>.get()运行的线程中发生了异常该如何处理？
 *
 * 好消息是：没有什么特别事情会发生。对future调用get()也能处理异常。事实上当get()被调用，且后台操作已经(或)
 * 随后由于异常而终止，该异常不会在此线程内被处理，而是会再次被传播出去。因此，预处理后台操作所生的异常，你只
 * 需要谐同get()做出“以同步方式调用该操作”所做的相同动作即可。
 */

#include <iostream>
#include <future>
#include <exception>

struct my_exception : public std::exception
{
    const char * what () const throw ()
    {
        return "C++ Exception";
    }
};

void task_exception()
{
    throw my_exception();
}



int main()
{
    std::future<void> result_future = std::async(task_exception);

    try {
        result_future.get();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return EXIT_FAILURE;
}