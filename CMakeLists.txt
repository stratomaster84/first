cmake_minimum_required(VERSION 3.0.0)

project(_GAME_OF_LIFE)

# Find includes in corresponding build directories
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOMOC ON)
# Instruct CMake to run uic automatically when needed.
#set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# WARNINGS AS ERRORS
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

# ИСПОЛЬЗОВАНИЕ СТАНДАРТА 17
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
# ИЛИ ТАК :-)))
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lmysqlclient")

# This will find the Qt5 files. You will need a QT5_DIR env variable
#find_package(Qt5Widgets REQUIRED) # Equivalent of QT += widgets

set(SOURCES main.cpp)

#set(HEADERS ...)

# This will create you executable
add_executable(${PROJECT_NAME}  ${SOURCES} ${HEADERS})
# This will link necessary Qt5 libraries to your project
#target_link_libraries(${PROJECT_NAME}  Qt5::Widgets)
# ЕСЛИ НУЖЕН MySQL
#set(MYSQL_DIR D:/MAXSYS/MySQL)
#include_directories(${MYSQL_DIR}/include)
#link_directories(${MYSQL_DIR}/lib)
#link_directories(${MYSQL_DIR}/lib/opt)
#find_package(MySQL REQUIRED)
#target_link_libraries(${PROJECT_NAME} mysqlcliet)
