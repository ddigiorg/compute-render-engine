# Windows Visual Studio Installtion
Verified:
- Visual Studio 2017
- OpenCL via CUDA Version 8.0.44
- opencv-3.2.0-vc14
- Glew-2.0.0-win32   (note: has x64 in it)
- SFML-2.4.2-windows-vc14-64-bit

## Instructions
- Install Visual Studio Community (download)
  - Universal Windows Platform development
  - Desktop development with C++

- Install OpenCL for Nvidia via CUDA (download)
  - Verify OpenCL.dll is in system32 folder

- Install OpenCV (download)
  - Extract opencv folder to C:\ directory

- Install Glew binaries (32 bit) (download)
  - Extract glew folder to C:\ directory

- Install SFML (32 bit) (download)
  - Extract SFML folder to C:\ directory

- Create new Visual C++ Empty Project (e.g. CRE)

- In the VS “Solution Explorer” add relevant header, source and resource files

- Edit Project Properties:
  - For “Configuration” select “All Configurations”
  - For “Platform” select “x64”
  - Include: In “C/C++ > General > Additional Include Directories” 
    - Source Directory of compute-render-engine: D:\code\CRE\CRE\source
    - OpenCL: C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v8.0\include
    - OpenCV: C:\opencv\build\include
    - Glew: C:\glew-2.0.0\include
    - SFML: C:\SFML-2.4.2\include
  - Linking: In “Linker > General > Additional Library Directories” 
    - OpenCL: C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v8.0\lib\x64
    - OpenCV: C:\opencv\build\x64\vc14\lib
    - Glew: C:\glew-2.0.0\lib\Release\x64
    - SFML: C:\SFML-2.4.2\lib
  - Linking: In “Linker > Input > Additional Dependencies”
    - OpenCL.lib
    - opencv_world320.lib
    - Opengl32.lib
    - glu32.lib
    - Glew32.lib
    - sfml-system.lib
    - sfml-window.lib
    - sfml-graphics.lib

- For “Solution Configuration” select “Release”.  Then “Build > Build Solution”.

- Copy compute-render-engine’s source and resource folders  into project’s release directory (e.g. D:\code\CRE\x64\Release)

- Copy .dll files into project’s release directory (e.g. D:\code\CRE\x64\Release)
  - Glew32.dll
  - sfml-system-2.dll
  - sfml-window-2.dll
  - sfml-graphics-2.dll
  - opencv_world320.dll
  - opencv_ffmpeg320_64.dll

- Run the .exe in project’s release directory (e.g. D:\code\CRE\x64\Release)
