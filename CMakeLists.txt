project(JobShopScheduling)
cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++14 -o3")

FIND_PACKAGE(Boost 1.40 COMPONENTS program_options REQUIRED)

include_directories(includes includes/Constructives includes/LocalSearches includes/Metaheuristics)

file(GLOB_RECURSE SRC src/*.cpp)

ADD_EXECUTABLE(app ${SRC} includes/GraphUtils/CriticalPath.hpp src/GraphUtils/BellmanFord.cpp includes/GraphUtils/BellmanFord.hpp)

TARGET_LINK_LIBRARIES(app LINK_PUBLIC ${Boost_LIBRARIES})

INSTALL(TARGETS app DESTINATION bin)