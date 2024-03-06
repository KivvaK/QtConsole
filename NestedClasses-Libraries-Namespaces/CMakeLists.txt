cmake_minimum_required(VERSION 3.14)

project(NestedClasses-Libraries-Namespaces LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(NestedClasses-Libraries-Namespaces
  main.cpp
  list.h
  matrix.h
  matrix.cpp
)
target_link_libraries(NestedClasses-Libraries-Namespaces Qt${QT_VERSION_MAJOR}::Core)

install(TARGETS NestedClasses-Libraries-Namespaces
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
