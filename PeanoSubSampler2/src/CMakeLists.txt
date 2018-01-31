cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project (PeanoSubSampler)

if (${CMAKE_EXTRA_GENERATOR} MATCHES "Eclipse CDT4")
	add_definitions (-DCMAKE_CXX_COMPILER_ARG1=-std=c++11)
	add_definitions (-DCMAKE_ECLIPSE_GENERATE_SOURCE_PROJECT=TRUE)
endif (${CMAKE_EXTRA_GENERATOR} MATCHES "Eclipse CDT4")

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "/home/dan/Documents/boost_1_65_1")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "/home/dan/Documents/boost_1_65_1/libs")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0)


find_package(VTK REQUIRED)
vtk_module_config(VTK
  vtkCommonCore
  vtkFiltersSources
  vtkFiltersSources
  vtkInteractionStyle
  vtkRendering${VTK_RENDERING_BACKEND}

  vtkIOLegacy
  vtkIOXML
  vtkIOGeometry
)
include(${VTK_USE_FILE})


find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()


if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    add_executable(PeanoSubSampler
        PeanoPatch.cpp
        PeanoPatchData.cpp
        PeanoReader.cpp
        PeanoMetaFile.cpp
        PeanoVariable.cpp
        PeanoVTK.cpp
        PeanoDataSet.cpp
        PeanoConverter.cpp)

    target_link_libraries(PeanoSubSampler
        ${VTK_LIBRARIES})
else(Boost_FOUND)
    message(FATAL_ERROR "Could not find the boost libraries! :(")
endif()
