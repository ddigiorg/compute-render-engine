# Compute Render Engine

Compute Render Engine (CRE) uses OpenCL and OpenGL interoperability to provide shared data buffers for computation and visualization.  Its purpose is to provide a framework for users who wish to see dynamically changing data on a parallel device (like a gpu) without the added cost of seperate computation and visualization stages.  Additionally, CRE uses SFML for OpenGL window context creation and OpenCV for inputting video files.  CRE works on Linux and Windows.

## Demos

### Particles

https://www.youtube.com/watch?v=jjvSq6iag0k

The particles demo creates an OpenGL vertex buffer object (VBO) of particle positions which gets shared with an OpenCL kernel.  The OpenCL kernel uses Neutonian physics equations to calculate the position and velocity of each particle relative to a point gravity provided by a mouse click.  OpenGL handles the color VBO.  The demo shows 4 million particles at ~60fps on the GeForce GTX 750 Ti graphics card.  The highest number of particles the  GeForce GTX 750 Ti can handle before dipping under 60fps is 8 million particles.  The demos was also run on a GeForce GTX 1070 with a limit of 27 million particles before dipping under 60fps.</p>

Engine Capabilities:

- 8 million particles at ~60 FPS on a GeForce GTX 750 Ti GPU
- 27 million particles at ~60 FPS on a GeForce GTX 1070 GPU

### Retina

https://www.youtube.com/watch?v=MzjDUMFdF1E

The retina demo creates two OpenGL 2D texture objects shared with an OpenCL kernel: one texture for video pixel data and the other for edge detection data.  Pixel data of the input video is read via OpenCV and copied to the OpenGL/CL texture object.  The OpenCL kernel then uses the center-surround response pattern of retinal ganglion cells to provide edge detection.  Pixels are made monochromatic before retinal processing, therefore the algorithm only considers light-dark contrast and not the color contrast of opponent-color theory.

- Red is high ganglion cell response (center pixel is light, surround pixels are dark)
- Green is low ganglion cell response (center pixel is dark, surround pixels are light)
- Black is steady-state response (center pixel is light, surround pixels are light OR center pixel is dark, surround pixels are dark)

## Future Improvements
- OSX support
- Moveable OpenGL view camera
- 3D demo
- Add color opponent theory to retina demo
