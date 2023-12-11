cmake_minimum_required(VERSION 3.27)
project("Combat-game-management")

set(CMAKE_CXX_STANDARD 20)

# Add the source files to the project
add_executable(${PROJECT_NAME}
    main.cpp
    Player/Player.cpp
    Player/Player.h
)

# Include the directory containing main.cpp
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# You can also set the output directory for the executable if you want.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
