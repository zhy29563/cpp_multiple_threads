一般而言， `std::async()`是一个辅助函数，用来在分离线程中启动某个`可调用对象`(如果可能的话)。因此，如果低层平台支持多线程，你可以让`可调用对象`并
发运转；如果低层平台不支持，也没有任何损失。

然而，`async()`的真是行为复杂得多，且高度取决于启动策略，后者可作为第一实参。基于这个因素，以下便以应用程序开发者的角度描述`async()`的三个标准调用
形式。

1. std::future<> async(std::launch::async, _callable func, args...)
   - 尝试启动`func`并给予实参`args`，形成一个异步任务
   - 如果以上办不到，就抛出`std::system_error`异常，带着差错码`std::errc::resource_unavailable_try_again`
   - 被启动的线程保证在程序结束前完成，除非中途失败
   - 以下情况会结束线程（完成工作）：
     - 对返回的`future`调用`get()`或`wait()`
     - 如果最后一个执行`返回之future所代表的shared state`的object被销毁
   - 这意味着对`async()`的调用会造成停滞直到`func`完成——如果`async()`的返回值未被使用的话
2. std::future<> async(std::launch::async, _callable func, args...)
   - 传递`func`并夹带实参`args`，形成一个推迟任务。当对返回的`future`调用`wait()`或`get()`，那个推迟任务即被`同步调用`
   - 如果既没有调用`get()`亦没有调用`wait()`，那个推迟任务绝不会启动
3. std::future<> async( _callable func, args...)
   - 相当于调用`async()`并携带`std::launch::async|std::launch::deferred`组合而成的启动策略。系统会根据当前形势选择其中一个启动策略。也就是说，如果`立即启动`策略行不通的话，会造成`func`被`推迟调用`
   - 也就是说，如果`async()`可以为`func`启动一个新线程，就那么做，否则`func`就会被推迟，直到对返回的`future`调用`get()`或`wait()`
   - 这个调用的唯一保证是，一旦我们对返回的`future`调用`get()`或`wait()`，`func`就一定会被调用且完成
   - 如果没有对返回的`future`调用`get()`或`wait()`，`func`有可能永不被调用
   - 注意，如果无法异步调用`func`，本形式的`async()`不会抛出`std::system_error`异常