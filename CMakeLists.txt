project(cpp-timer)

include_directories(include)

add_library(libs OBJECT src/libs.cpp)
add_library(time OBJECT src/time.cpp)
add_library(timer OBJECT src/timer.cpp)
add_library(counter OBJECT src/counter.cpp)

add_executable(test src/test.cpp)
add_executable(test2 src/test2.cpp)

target_link_libraries(test timer libs time)
target_link_libraries(test2 counter libs time)
