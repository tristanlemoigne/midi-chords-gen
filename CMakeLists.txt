# Create project
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# Add project name
project(main)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Build the rtmidi library
add_subdirectory(libs/rtmidi)


# include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/libs/rtmidi)
# include_directories(${PROJECT_SOURCE_DIR}/include ${RTMIDI_INCLUDE_DIRS})

set(SOURCES 
    ${PROJECT_SOURCE_DIR}/src/main.cpp 
    ${PROJECT_SOURCE_DIR}/src/player.cpp 
    ${PROJECT_SOURCE_DIR}/src/phrase.cpp 
    ${PROJECT_SOURCE_DIR}/src/range.cpp 
    # ${PROJECT_SOURCE_DIR}/include/intervals.hpp 
    # ${PROJECT_SOURCE_DIR}/include/json.hpp 
    # ${PROJECT_SOURCE_DIR}/include/phrase.hpp 
    # ${PROJECT_SOURCE_DIR}/include/player.hpp 
    # ${PROJECT_SOURCE_DIR}/include/range.hpp 
    # ${PROJECT_SOURCE_DIR}/include/notes.hpp 
)

# file(GLOB all_SRCS
#     "${PROJECT_SOURCE_DIR}/src/*.cpp"
#     # "${PROJECT_SOURCE_DIR}/include/*.hpp"
# )


# Add executable
add_executable(main ${SOURCES})
# add_executable(main 
#     src/main.cpp
#     src/phrase.cpp 
#     src/player.cpp 
#     src/range.cpp 
#     src/test.cpp 
#     include/intervals.hpp 
#     include/json.hpp 
#     include/notes.hpp 
#     include/phrase.hpp 
#     include/player.hpp 
#     include/range.hpp 
#     include/test.hpp 
# )
# add_executable(test src/main.cpp)
# add_executable(main ${all_SRCS})


# target_include_directories(test PRIVATE
#                           "${PROJECT_BINARY_DIR}"
#                           "${PROJECT_SOURCE_DIR}/libs/rtmidi"
#                           "${PROJECT_SOURCE_DIR}/libs/nlohmann"
#                           "${PROJECT_SOURCE_DIR}/include"
#                           )

# target_include_directories(test PRIVATE ${PROJECT_SOURCE_DIR}/include)

# target_link_directories(main PUBLIC ${CMAKE_SOURCE_DIR}/libs/rtmidi)
target_link_libraries(main PRIVATE rtmidi)

# Take care to select proper CmakeLists.txt configuration for cmake