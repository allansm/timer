project(cpp-timer)

find_package(SDL2)
find_library(SDL2_MIXER NAMES SDL2_mixer)

if((NOT SDL2_FOUND) OR (NOT SDL2_MIXER))
	execute_process(COMMAND git submodule update --init --recursive)
endif()

if(NOT SDL2_FOUND)
	add_subdirectory(SDL)
else()
	message("-- SDL2 FOUND")
endif()

if(NOT SDL2_MIXER)
	add_subdirectory(SDL_mixer)
else()
	message("-- SDL2_MIXER FOUND")
endif()

include_directories(include)
include_directories(SDL/include)
include_directories(SDL_mixer/include)

add_library(libs OBJECT src/libs.cpp)
add_library(time OBJECT src/time.cpp)
add_library(timer OBJECT src/timer.cpp)
add_library(counter OBJECT src/counter.cpp)
add_library(alarm OBJECT src/alarm.cpp)
add_library(timecache OBJECT src/timecache.cpp)

add_executable(test src/test.cpp)
add_executable(test2 src/test2.cpp)

target_link_libraries(time libs)
target_link_libraries(alarm SDL2::SDL2 SDL2_mixer)
target_link_libraries(test timer time alarm)
target_link_libraries(test2 counter time alarm timecache)
