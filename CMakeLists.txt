cmake_minimum_required(VERSION 3.10)
project(TerminalGame)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Add all your source files here
set(SOURCES
    Source.cpp
    MainCharacter.cpp
    Enemy.cpp
    Grotte.cpp
    Goblin.cpp
    Ape.cpp
    Dragon.cpp
    Hest.cpp
    Snake.cpp
    Unicorn.cpp
    EnemyFactory.cpp
    Weapons.cpp
    DatabaseManager.cpp
    GameManager.cpp
)
find_package(Qt5Sql REQUIRED)

# Create the executable
add_executable(TerminalGame ${SOURCES})

target_link_libraries(TerminalGame Qt5::Core Qt5::Sql)