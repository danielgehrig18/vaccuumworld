cmake_minimum_required(VERSION 2.8.3)
project(vacuumworld)

add_definitions(-std=c++11)
# To enable assertions when compiled in release mode.
add_definitions(-DROS_ASSERT_ENABLED)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

include_directories(include)

# Libraries without dependencies on other internal libs
add_library(sensor src/sensor.cpp)

add_library(actuator src/actuator.cpp)

add_library(model src/model.cpp)

add_library(state src/state.cpp)

add_library(visualizer src/visualizer.cpp)


# Libs with only one internal dependency
add_library(motor src/motor.cpp)
target_link_libraries(motor actuator)

add_library(sucker src/sucker.cpp)
target_link_libraries(sucker actuator)

add_library(dirt_sensor src/dirt_sensor.cpp)
target_link_libraries(dirt_sensor sensor)

add_library(proximity_sensor src/proximity_sensor.cpp)
target_link_libraries(proximity_sensor sensor)

add_library(direction_sensor src/direction_sensor.cpp)
target_link_libraries(direction_sensor sensor)

add_library(location_sensor src/location_sensor.cpp)
target_link_libraries(location_sensor sensor)

add_library(path_searcher src/path_searcher.cpp)
target_link_libraries(path_searcher state)


# Libs with multiple internal dependencies (+ problem.cpp)
add_library(strategy src/strategy.cpp)
target_link_libraries(strategy model path_searcher)

add_library(agent src/agent.cpp)
target_link_libraries(agent dirt_sensor proximity_sensor direction_sensor location_sensor motor sucker strategy visualizer)

add_library(environment src/environment.cpp)
target_link_libraries(environment agent dirt_sensor proximity_sensor motor sucker model visualizer)

add_library(problem src/problem.cpp)
target_link_libraries(problem environment)

add_library(simulation src/simulation.cpp)
target_link_libraries(simulation environment problem visualizer)

add_executable(vacuum_world src/main.cpp)
target_link_libraries(vacuum_world simulation visualizer)
