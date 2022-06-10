cmake_minimum_required(VERSION 3.21)
project(Project)

set(CMAKE_CXX_STANDARD 20)
set(FULL_PATH_TO_MYSQL_DIR ../Project/libraries/mysql/mysql-8.0.28-winx64)

#======================= INCLUSION OF MYSQL =======================#
include_directories(${FULL_PATH_TO_MYSQL_DIR}/include)
link_directories(${FULL_PATH_TO_MYSQL_DIR}/lib)
link_libraries(libmysql)

#======================= CREATING EXECUTABLE =======================#
add_executable(Project
        main.cpp
        DatabaseConnection.cpp
        DatabaseConnection.h
        menu.h
        Product.cpp
        Product.h
        User.cpp
        User.h
        Cart.cpp
        Cart.h)

#======================= LINKINg LIBRARIES =======================#
target_link_libraries(Project libmysql)
