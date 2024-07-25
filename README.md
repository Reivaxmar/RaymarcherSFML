# Raymarcher with SFML
The other day I was looking in some of my old projects and I saw an idea that I had to make a Raymarcher, so that's what I've done. The rendering is still a bit weird, but it works. Keep in mind that this is a work-in-progress project.

## How to compile
This is a CMake project. Run the setup.sh if you're on a Unix-based system or setup.bat if you're on windows (mingw).
After that, run the generated Makefile.
In case that you want to do it manually, here's a guide:
```bash
#!/bin/bash
mkdir build # To create the build directory
cd build # And go in it
cmake -G "Type" .. # Change "Type" for whatever else you want to generate the project for
```

## Features
Currently, its pretty basic. The only thing that it has is a good class based structure and a basic renderer for circles with plain colors.