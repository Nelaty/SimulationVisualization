# SimulationVisualization
This project visualizes various physic simulations.

## 1. Building

**Visual Studio 2017**

**1st step**</br>
Before building the application, the physics engine (Rumble3D) and the scene graph (EyeCandy3D) need to build. To do that, navigate to the specific submodule and build them by using the included visual studio solution.

**2nd step**</br>
To build the application, open the visual studio solution, select the desired platform and configuration and press <kbd>F7</kbd>.

## 2. Installation

**Visual Studio 2017**

This project is dependent on following repositories:
* Rumble3D -> Physics library
* EyeCandy3D -> Scenegraph and Input

Nuget packages:
* glm
* glfw
* glew.v140
* freetype

Additional include directories:
* *Rumble3D/Rumble3D/include*
* *EyeCandy3D/EyeCandy3D/include*
* *EyeCandy3D/External/include*

Additional dependencies:
* Rumble3D.lib
* EyeCandy3D.lib
* opengl32.lib
* agui.lib

## 3. Documentation

**Doxygen note:**

1. To generate you're own documentation with doxygen, you need to have "Dot" installed (included in the graphviz package). Otherwise collaboration graphs will not be generated!
1. Navigate to ./Docs/ and execute the command: "doxygen Doxyfile"
