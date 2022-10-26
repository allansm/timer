project(cpp-timer)

include_directories(include)

add_library(timer OBJECT src/timer.cpp)

add_executable(test src/test.cpp)
add_executable(test2 src/test2.cpp)

target_link_libraries(test timer)
