project(JobShopScheduling)
cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++14 -o3")

FIND_PACKAGE(PkgConfig)
FIND_PACKAGE(Boost 1.40 COMPONENTS program_options REQUIRED)

include_directories(includes
        includes/Constructives
        includes/LocalSearches
        includes/Metaheuristics
        includes/GraphUtils)
include_directories(src
        src/Constructives
        src/LocalSearches
        src/Metaheuristics
        src/GraphUtils)

file(GLOB_RECURSE SRC src/*.cpp)
file(GLOB_RECURSE INCLUDES includes/*.hpp)

add_library(core ${SRC} ${INCLUDES})
TARGET_LINK_LIBRARIES(core ${Boost_LIBRARIES})

ADD_EXECUTABLE(app src/main.cpp)

enable_testing()
    include_directories(includes)
    add_executable(tests test/maintest.cpp)
    target_link_libraries(tests LINK_PUBLIC ${Boost_LIBRATIES} core)

TARGET_LINK_LIBRARIES(app LINK_PUBLIC ${Boost_LIBRARIES} core)

#INSTALL(TARGETS app DESTINATION bin)