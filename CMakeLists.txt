# 指定最低的CMAKE版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14 FATAL_ERROR)

# 创建项目
PROJECT(cpp_multiple_threads LANGUAGES CXX)

# 指定CPLUSPLUS标准
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_C_STANDARD 11)
SET(CMAKE_C_STANDARD_REQUIRED ON)

#######################################################################################################################
# 多线程高级接口（async）
#######################################################################################################################
# 启动无参无返回值的可调用对象
ADD_EXECUTABLE(001_async_start_global_function sources/001_async_start_global_function.cpp)
ADD_EXECUTABLE(002_async_start_member_function sources/002_async_start_member_function.cpp)
ADD_EXECUTABLE(003_async_start_function_object sources/003_async_start_function_object.cpp)
ADD_EXECUTABLE(004_async_start_lambda_expression sources/004_async_start_lambda_expression.cpp)

# 启动有参无返回值的可调用对象
ADD_EXECUTABLE(005_async_start_global_function sources/005_async_start_global_function.cpp)
ADD_EXECUTABLE(006_async_start_member_function sources/006_async_start_member_function.cpp)
ADD_EXECUTABLE(007_async_start_function_object sources/007_async_start_function_object.cpp)
ADD_EXECUTABLE(008_async_start_lambda_expression sources/008_async_start_lambda_expression.cpp)

# 启动无参有返回值的可调用对象
ADD_EXECUTABLE(009_async_start_global_function sources/009_async_start_global_function.cpp)
ADD_EXECUTABLE(010_async_start_member_function sources/010_async_start_member_function.cpp)
ADD_EXECUTABLE(011_async_start_function_object sources/011_async_start_function_object.cpp)
ADD_EXECUTABLE(012_async_start_lambda_expression sources/012_async_start_lambda_expression.cpp)