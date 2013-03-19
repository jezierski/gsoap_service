include_directories(${HOMESYS_SOURCE_DIR}/webservice)
link_directories(${HOMESYS_SOURCE_DIR}/webservice)

#find_package(GSOAP2)

set (SOURCES soapC.cpp soaphomesysService.cpp)
#target_link_libraries(${HOMESYS_BINARY_DIR}/build/homesys ${GSOAP2_LIBRARY_RELEASE})
message("webser:")
message(${SOURCES})
add_executable(../build/homesys ${SOURCES})