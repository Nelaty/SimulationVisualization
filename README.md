# SimulationVisualization
This project visualizes various physic simulations.

## 1. Building

This project depends on following repositories:
* Rumble3D -> Physics library
* EyeCandy3D -> Scenegraph and Input

**Dependencies**

* Rumble3D
* EyeCandy3D
* glm
* glfw
* GLEW
* GL
* GLU
* X11
* Xrandr
* Xinerama
* Xi
* Xxf86vm
* Xcursor
* pthread
* dl
* freetype

**Include directories**

* *Rumble3D/Rumble3D/include*
* *EyeCandy3D/EyeCandy3D/include*
* *EyeCandy3D/External/include*

**Building**

Before the simulation project can be built, the EyeCandy3D scenegraph 
and the Rumble3D physics engine need to be built (see instructions in respective repositories).

1. Navigate to the project root directory
2. Create cmake files 
    ```
    mkdir build
    cd build
    cmake ..
    ```
3. Build project
    1. Linux: `make`
    2. Windows: `cmake --build .`

## 2. Documentation

**Doxygen note:**

1. To generate you're own documentation with doxygen, you need to have "Dot" installed (included in the graphviz package). Otherwise collaboration graphs will not be generated!
2. Navigate to ./Docs/ and execute the command: "doxygen Doxyfile"
