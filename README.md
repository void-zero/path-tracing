# Path tracer

A simple C++11 path tracer.

# Dependencies

This software depends on the following third party software to be compiled:

- **[glm](https://github.com/g-truc/glm)**: version 0.9.9.7 or later.
- **[assimp](https://github.com/assimp/assimp)**: 
```shell
$ sudo apt install libassimp-dev
```

# Compiling and Running

I've compiled and executed this software only in Linux (Ubuntu 14.04).
These are the steps needed in order to compile the program:

1. Install the dependencies (i.e. glm and assimp).
2. Download the source code together with the Makefile.
3. Open the Makefile with a text editor (e.g. vim, gedit, etc.).
4. Configure the variables CPPFLAGS and LDFLAGS in order to reflect your glm installations.
5. Save the Makefile.
6. Call 'make DEBUG=0' at the project root directory.
7. Done

To render the hardcoded scene, just issue the following command from the project root directory: 

    $ ./ptracer [number of samples]
    
The rendered scene will be in the folder renders, with the name "output.ppm".
