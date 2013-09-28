cmake_minimum_required(VERSION 2.6)
project(HOMESYS)

find_package(GSOAP2)
find_package(SQLITE3)

set(CMAKE_CXX_COMPILER="distcc g++")
set(CMAKE_CXX_FLAGS "-g -Wall -std=gnu++0x")
#add_subdirectory(webservice)
#add_subdirectory(homesys)

set (BINARY build/homesys)

set (SOURCES 

#homesys:
homesys/homesys.cpp 
homesys/CSoapServer.cpp
raspberry/CGPIOClass.cpp
homesys/CDevice.cpp
homesys/CDeviceManager.cpp
homesys/COperation.cpp
homesys/CActionTranslator.cpp
homesys/CTimer.cpp
homesys/CActionsChain.cpp
        
#can232:
can232/CCan232.cpp
        
#tools:
tools/CBuffer.cpp 
tools/CCanBuffer.cpp
tools/CSerCom.cpp 
tools/CTimeOut.cpp
tools/CTools.cpp
tools/CConfiguration.cpp
tools/CDevicesConfig.cpp
tools/CDatabase.cpp
tools/CLog.cpp
tools/CBlob.cpp
tools/CParamsConverter.cpp

#can_devices:
can_devices/CCanSimpleSwitchActor.cpp
can_devices/CCanSimpleSwitchSensor.cpp
can_devices/CCanRGBActor.cpp
        

#webservice:
webservice/soapC.cpp webservice/soaphomesysService.cpp 
)

add_executable(${BINARY} ${SOURCES})

target_link_libraries(${BINARY} ${GSOAP2_LIBRARY_RELEASE} ${SQLITE3_LIBRARY_RELEASE})
