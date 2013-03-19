cmake_minimum_required(VERSION 2.6)
project(HOMESYS)

find_package(GSOAP2)
#find_package(SQLITE3)

#set(CMAKE_CXX_COMPILER="distcc g++")
set(CMAKE_CXX_FLAGS "-g -Wall -std=gnu++0x")
#add_subdirectory(webservice)
#add_subdirectory(homesys)

set (BINARY build/homesys)

set (SOURCES 

#homesys:
homesys/homesys.cpp homesys/CSoapServer.cpp

#webservice:
webservice/soapC.cpp webservice/soaphomesysService.cpp 
)

add_executable(${BINARY} ${SOURCES})

target_link_libraries(${BINARY} ${GSOAP2_LIBRARY_RELEASE})
