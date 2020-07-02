# TSW Logger

Logging library, based on Baical P7.


## Requirements

Header-only:

- Boost::current_function.
- Boost::Exception.

Baical P7 will be loaded during build.


## Build

```
$ git clone --recurse-submodules -j8 https://github.com/artiomn/tsw-logger.git
$ ./build.sh
```


## Using

1. In CMakeLists.txt of your project:

```cmake
project(my-project)

add_subdirectory(tsw-logger)
add_executable("${PROJECT_NAME}")
target_link_libraries("${PROJECT_NAME}" tsw-logger)
```

2. In the code:

```cpp
LOG(tsw::LogLevel::Debug, "MESSAGE TO LOG!");
```
