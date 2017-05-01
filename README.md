# Compute Render Engine

Compute Render Engine (CRE) uses OpenCL and OpenGL interoperability to provide shared data buffers for computation and visualization.  Its purpose is to provide a framework for users who wish to see dynamically changing data on a parallel device (like a gpu) without the added cost of seperate computation and visualization stages.  Additionally, CRE uses SFML for OpenGL window context creation and OpenCV for inputting video files.

## Demos
- Particles: https://www.youtube.com/watch?v=jjvSq6iag0k
- Retina: https://www.youtube.com/watch?v=MzjDUMFdF1E

## Tested Software
- OpenGL version 4.5.0 NVIDIA 375.10
- OpenCL version 2.1 (using C++ wrappers)
- OpenCV version 3.2
- SFML version 2.4.2

## Tested Hardware
- GeForce GTX 750 Ti GPU
- GeForce GTX 1070 GPU
