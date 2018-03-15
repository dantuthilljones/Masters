# Dan's Master's Project

This project comes in two forms: standalone and paraview plug in.

## Standalone
The standlone program can take Peano data files (both metadata and individual files) and either convert them to the VTK format or sample the data on to a single regular grid in the peano file format.

### Setup

#### Dependancies
Note: the versions listed below are what I used but others should work.

* Boost Header-Only Library v1.45.0
* CMake v3.3
* VTK v8.01
* A C++ compiler

#### Installation
1. Download this git repository on to your computer
2. Open the terminal in the Standalone folder
3. Create a folder called "bin" `mkdir bin`
4. Move in to this new folder `cd bin`
5. Generate the project via cmake `ccmake ../src`
6. In the CMake interface, press `c` to configure the project. This will probably fail because your dependancies will have different location to mine. You will need to correct the values of "Boost\_INCLUDE\_DIR" and "VTK\_DIR". If they don't appear in the interface, try pressing `t` which opens advanced options.
7. Select the generate option once it is available in the CMake interface by pressing `g`
8. Build the project via make `make`. This should create "PeanoStandalone" in the bin folder.

### Usage
The metadata files which I have been given to test with contained a few bugs which may or may not be fixed. My program assumes that all files contain the correct information and will break if it encounters something unexpected. Before you run the standalone program on a metadata file I suggest you open it in your favourite text editor and check the contents. I found that the first dataset pointed to a file with number 1 however the first file actually was number 0. Additionally the metadata file pointed to a number of extra files at the end of the list.

##### Converting
To convert a peano file to VTK, use the convert command like so `./PeanoStandalone convert INPUT_FILE OUTPUT_FOLDER`

For example, if I wanted to convert all the files linked together by the metadatafile `/home/dan/Documents/Masters/ExampleFiles/FromPhysics2/ConservedWriter-Peano-Cartesian-cells-ascii.peano-patch-file` output them in to the folder `/home/dan/Documents/Masters/ExampleFiles/standalonetest` I would run the command `./PeanoStandalone convert /home/dan/Documents/Masters/ExampleFiles/FromPhysics2/ConservedWriter-Peano-Cartesian-cells-ascii.peano-patch-file /home/dan/Documents/Masters/ExampleFiles/standalonetest`

##### Subsampling
When given a metadata file, the subsampling method will subsample each dataset on to a single peano patch and modify the metadata file to include those new files. The paraview plugin adds an interface to select which resolution to load when viewing the patch files.
To subsample a peano file, use the subsample command like so `./PeanoStandalone subsample INPUT_FILE X_SIZE Y_SIZE Z_SIZE`

For example the command `./PeanoStandalone subsample /home/dan/Documents/Masters/ExampleFiles/FromPhysics2/ConservedWriter-Peano-Cartesian-cells-ascii.peano-patch-file 10 10 10` will subample each patch file on to a new patch with a resolution of 10 by 10 by 10.


####

## Paraview Plugin
The second is a plugin for the scientific viewing software Paraview. This adds the standalone program's functionality to paraview, allowing you to load pre-computed subsampled data or subsampling it on the fly.

### Installation
The installation for the paraview plug in is much more long-winded than for the subsampler because it requires you to compile your own version of paraview. A guide for this can be found here https://www.paraview.org/Wiki/ParaView:Build_And_Install

I encountered a lot of problems compiling paraview myself and I've listed the solutions to the ones I can remember off the top of my head below

* `This application failed to start because it could not find or load the Qt platform plugin...`
Set the environment variable QT_PLUGIN_PATH to your QT plugins folder. For me the command is `export QT_PLUGIN_PATH=/home/dan/Qt/5.9.2/gcc_64/plugins`.
*  `libprotobuf FATAL ... protobuf/vtkprotobuf/src/google/protobuf/stubs/common.cc:62 ... something something version 2.6.0 something 2.3.0 ...` 
This is caused by the file `libqgtk3.so` which is found in your QT installation at `Qt/5.9.2/gcc_64/plugins/platformthemes/`. You should move this file somewhere else, but don't delete it because you won't be able to compile plugins without it. The repository contains a script I use paraview.sh. This script moves the file from the folder, opens paraview then moves it back after 5 seconds. You may want to modify it yourself to work on your environment.

#### Dependancies
Note: the versions listed below are what I used but others should work.

* Paraview installed via source (has its own dependancies not listed here)
* Boost Header-Only Library v1.45.0
* CMake v3.3
* A C++ compiler

#### Installation
1. Download this git repository on to your computer
2. Open the terminal in the Plugin folder
3. Create a folder called "bin" `mkdir bin`
4. Move in to this new folder `cd bin`
5. Set the environment variable "QT_PLUGIN_PATH" to the qt plugin location. For me this location is "/home/dan/Qt/5.9.2/gcc_64/plugins" and so the command is `export QT_PLUGIN_PATH=/home/dan/Qt/5.9.2/gcc_64/plugins`
6. If you moved the libqgtk3.so file so that paraview will open, you will need to put it back in the platformthemes folder now
7. Generate the project via cmake `ccmake ../src`
8. The build should fail because of something to do with Qt5. To solve this set "Qt5_DIR" in the cmake interface to the location of "Qt5Config.cmake". For me this is in "/home/dan/Qt/5.9.2/gcc_64/lib/cmake/Qt5"
9. In the CMake interface, press `c` to configure the project. This will probably fail because of more dependancies. You will need to correct the values of "Boost\_INCLUDE\_DIR" and "ParaView\_DIR". If they don't appear in the interface, try pressing `t` which opens advanced options.
10. Select the generate option once it is available in the CMake interface by pressing `g`
11. Build the project via make `make`. This should create "vtkPeanoReader.so" in the bin folder.
12. If the libqgtk3.so file is in the platformthemes folder, you will have to remove it so that paraview can run. The repository contains a script I use paraview.sh. This script moves the file from the folder, opens paraview then moves it back after 5 seconds. You may want to modify it yourself to work on your environment.
13. Open your compiled version of paraview
14. Add the plugin via Tools > Manage Plugin > Load New and selecting the file vtkPeanoReader.so
