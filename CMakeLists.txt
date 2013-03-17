cmake_minimum_required(VERSION 2.6)
project(HOMESYS)

#There are lots of scripts with cmake
#for finding external libraries. 
#see /usr/local/share/cmake-2.6/Modules/Find*.cmake for more examples
#find_package(GSOAP2)
#find_package(SQLITE3)

set(CMAKE_CXX_FLAGS "-g -Wall")
#add_subdirectory(webservice)

add_executable(build/server server.cpp)
#target_link_libraries(build/server ${GSOAP2_LIBRARY_RELEASE})
