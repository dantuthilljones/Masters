cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project (PeanoVTKProject)


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

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})

    add_executable(PeanoVTK
        PeanoPatch.cpp
        PeanoPatchData.cpp
        PeanoPatchReader.cpp
        PeanoVariable.cpp
        PeanoVTK.cpp
        PeanoConverter.cpp)

    target_link_libraries(PeanoVTK
        ${VTK_LIBRARIES})
else(Boost_FOUND)
    message(FATAL_ERROR "Could not find the boost libraries! :(")
endif()
