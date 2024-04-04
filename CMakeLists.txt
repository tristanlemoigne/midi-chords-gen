# Create project
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# Add project name
project(main)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# In Debug, copy librairies file (dll) next tot the executable to run properly
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Build the rtmidi library
add_subdirectory(libs/rtmidi)
add_subdirectory(libs/nlohmann_json)

# Add folders for include files 
include_directories(
    ${PROJECT_SOURCE_DIR}/include 
)

# Copy data.json to build directory
file(COPY ${PROJECT_SOURCE_DIR}/src/data.json DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# Add sources files to project
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Add executable
add_executable(main ${SOURCES})

# Indique à Cmake où chercher les en-têtes des librairies
# target_include_directories(main PRIVATE ${PROJECT_SOURCE_DIR}/libs/nlohmann)
target_link_libraries(main PRIVATE rtmidi)
target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)