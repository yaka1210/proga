cmake_minimum_required(VERSION 3.16)

project(lab2 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Test)

add_executable(lab2
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    kursvalut.h kursvalut.cpp
    cryptokurs.h cryptokurs.cpp
    regularkurs.h regularkurs.cpp
    filemanager.h filemanager.cpp
    model.h model.cpp
)

target_link_libraries(lab2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

add_executable(tests
    test_model.cpp
    model.cpp
    kursvalut.cpp
    cryptokurs.cpp
    regularkurs.cpp
    filemanager.cpp
)
target_link_libraries(tests PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Test
)

enable_testing()
add_test(NAME tests COMMAND tests)
