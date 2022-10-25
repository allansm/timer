project(cpp-timer)

include_directories(include)

add_library(timer OBJECT src/timer.cpp)

add_executable(test src/test.cpp)

target_link_libraries(test timer)
