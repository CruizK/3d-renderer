# graphics-project

## How to run
1. Make Build Directory in root folder (`mkdir build && cd build`)
2. Run `cmake ../`
3. If on windows, will create a VS project called Sandbox you can build and run (Make sure to set Sandbox as startup project)
4. If on linux, will create a makefile, just run `make -j` and run with `./Sandbox`

## Things that need to be done
- [X] Perspective Camera
- [ ] Some sort of Input system
- [ ] Framebuffer and probably a library integration to output an image from the current render state
- [ ] Material System
- [ ] 3D Model Loading
- [ ] 2D Texture Loading for Materials
- [ ] Lighting System
