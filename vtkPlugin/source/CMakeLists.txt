cmake_minimum_required(VERSION 3.6)

set(QT_PLUGIN_PATH "/home/dan/Qt/5.9.2/gcc_64/plugins")

FIND_PACKAGE(ParaView REQUIRED)
INCLUDE(${PARAVIEW_USE_FILE})

ADD_PARAVIEW_PLUGIN(
  PeanoReader                 #<--Name for the plugin
 "1.0"                      #<--Version string
  SERVER_MANAGER_XML vtkPeanoReader.xml  #<-- server manager xml
  SERVER_MANAGER_SOURCES vtkPeanoReader.cpp #<-- source files for the new classes
  REQUIRED_ON_SERVER
)
