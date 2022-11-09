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

set(CMAKE_CXX_COMPILER "g++")

include_directories(include)
include_directories(SDL/include)
include_directories(SDL_mixer/include)

add_library(libs_obj OBJECT src/libs.cpp)
add_library(time_obj OBJECT src/time.cpp)
add_library(timer_obj OBJECT src/timer.cpp)
add_library(counter_obj OBJECT src/counter.cpp)
add_library(alarm_obj OBJECT src/alarm.cpp)
add_library(timecache_obj OBJECT src/timecache.cpp)
add_library(log_obj OBJECT src/log.cpp)

add_executable(timer src/main/timer.cpp)
add_executable(counter src/main/counter.cpp)

target_link_libraries(time_obj libs_obj)
target_link_libraries(alarm_obj SDL2::SDL2 SDL2_mixer)
target_link_libraries(timer timer_obj time_obj alarm_obj timecache_obj log_obj)
target_link_libraries(counter counter_obj time_obj alarm_obj timecache_obj log_obj)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/timer
	PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ WORLD_EXECUTE WORLD_WRITE WORLD_READ
       	DESTINATION bin)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/counter
	PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ WORLD_EXECUTE WORLD_WRITE WORLD_READ
       	DESTINATION bin)

