include_directories(${HOMESYS_SOURCE_DIR}/homesys)
link_directories(${HOMESYS_SOURCE_DIR}/homesys)

set (SOURCES homesys.cpp CSoapServer.cpp)
add_executable(../build/homesys ${SOURCES})
message("homesys:")
message(${SOURCES})