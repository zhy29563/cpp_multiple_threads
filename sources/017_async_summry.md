# 1. 关于 std::async() 与 std::future<>的一些说明

C++ 11 标准库中提供的 std::async() 与 std::future<> 使得开启异步任务变得简单，其中：

- std::async()

  该接口让一个可调用对象(callable object) `若是可能的话`在后台运行，成为一个独立线程

- std::future<>

  允许你等待线程结束并获取其结果（一个返回值，或者也许是一个异常）



# 2. async  与 future 的配对试用

```c++
int main()
{
    int i = 200;
    std::future<int> result_future = std::async([=]()->int{
        ...
        return 100;
    });
    
    ...

    int result = result_future.get();
    
    ...
}
```

上面的代码块中，**async()** `尝试`将其所获得的可调用对象`立刻异步`启动于`一个分离线程`内。因此，在`概念上`可调用对象被启动了，且不会造成`main()`的停滞。

`std::async`的返回值必须是`std::future`对象有以下两个原因：

- 它允许你获取`可调用对象`的返回结果，这个结果也许是一个返回值，也许是一个异常。此外，在返回事件上，该结果可能立刻返回，也可能在将来（等待一段事件后）返回。如果`可调用对象`是一个无返回值的类型，则返回`std::future<void>`
- 它的存在，确保`可调用对象`一定会被调用。注意先前所说**async()** `尝试`启动`可调用对象`。如果尝试启动未成功，则需要使用`std::future`才能强迫其启动。

随着`get()`被调用，以下三件事情之一会发生：

1. 如果`可调用对象`被`async()`启动于一个`分离线程中`并且`已结束`，会立刻获得结果
2. 如果`可调用对象`被`启动但尚未结束`，`get()`会引发停滞待`可调用对象`结束后获取结果
3. 如果`可调用对象`尚未启动，会被`强迫启动`如果一个`同步调用`；`get()`会引发停滞直至产生结果

这样的行为很重要，因为这确保了在`单线程环境`中，或是当`async()无法启动新线程`时，程序仍能有效运作

因此 std::future<int> result1(std::async(func1)); 与 result1.get() 的组合允许你以某种方式优化程序：

1. 如果可能，当`父线程`的下一个语句被处理时，`可调用对象`被`并行运行`
2. 如果`无法并行运行`，那么`可调用对象`会在`get()被调用时`被以同步的方式调用。这就意味着无论如何都能保证至少在`get()执行后`一定会调用`可调用对象`——不是异步就是同步

> **注意**
>
> 如果没调用`get()`就不保证`可调用对象`一定会被调用。如前面所述，如果`async()`无法立刻启动它所收到的函数，就会`推迟`调用，使得当程序**调用get()或wait()意欲明确索求目标函数的结果**才被调用。如果没有那样一个明确请求，即使父线程终止，`可调用对象`也不会执行。
