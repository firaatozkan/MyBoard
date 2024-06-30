cmake_minimum_required(VERSION 3.5.0)
project(ToyKanban VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)

find_package(Qt5 COMPONENTS Core Widgets Sql)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(
    ToyKanban
    ./src/Main.cpp
    ./src/KanbanBoard.cpp
    ./src/TaskRepository.cpp
    ./src/TaskMovingDialog.cpp
    ./src/TaskAdditionDialog.cpp
    
    ./include/KanbanBoard.hpp
    ./include/TaskRepository.hpp
    ./include/TaskMovingDialog.hpp
    ./include/TaskAdditionDialog.hpp
)

target_include_directories(
    ToyKanban
    PRIVATE
    ./include
)

target_link_libraries(
    ToyKanban
    PUBLIC
    Qt5::Core
    Qt5::Widgets
    Qt5::Sql
)

# Desired db path
add_compile_definitions(DB_PATH_ENV="${PROJECT_SOURCE_DIR}/Tasks.db")