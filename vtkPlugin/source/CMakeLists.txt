cmake_minimum_required(VERSION 3.6)

set(QT_PLUGIN_PATH "/home/dan/Qt/5.9.2/gcc_64/plugins")

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()


SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/home/dan/Documents/boost_1_65_1")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/home/dan/Documents/boost_1_65_1/libs")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else(Boost_FOUND)
    message(FATAL_ERROR "Could not find the boost libraries! :(")
endif()


FIND_PACKAGE(ParaView REQUIRED)
INCLUDE(${PARAVIEW_USE_FILE})

ADD_PARAVIEW_PLUGIN(
  PeanoReader                 #<--Name for the plugin
 "1.0"                      #<--Version string
  SERVER_MANAGER_XML vtkPeanoReader.xml  #<-- server manager xml
  SERVER_MANAGER_SOURCES vtkPeanoReader.cpp #<-- main source file
  SOURCES PeanoPatch.cpp PeanoPatchData.cpp PeanoReader.cpp PeanoMetaReader.cpp PeanoVariable.cpp PeanoConverter.cpp #<-- source files for the new classes
  REQUIRED_ON_SERVER
)
