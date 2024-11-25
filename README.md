# STagSharp - STag wrapper for .NET

This repository is a simple wrapper for Stag to use this library for marker detection in .NET.

> [!NOTE]
> For the original C++ source code of STag refer to: https://github.com/ManfredStoiber/stag.

## Description

Due to problems with the implementation of CMake projects containing mixed C# and C++ projects, STagSharp is implemented as a solution for MS Visual Studio. Solution supports debugging of mixed unmanaged C++ and managed C# code. STagSharp contains three projects: STagSharpExtern, STagSharp and STagSharpTest: 
   - STagSharpExtern is a C++ wrapper over the original STag library for compilation into DLL and connection via DllImport from .NET. The [OpenCVSharp](https://github.com/shimat/opencvsharp) library was used to pass the image for processing from .NET to STag in OpenCV Mat format. Unfortunately it was not possible to pass Point2f[][] through it, so STagSharpExtern converts the detected corners of markers into a float array.
   - STagSharp is a C# wrapper over STagSharpExtern.  It uses [OpenCVSharp](https://github.com/shimat/opencvsharp) to pass the image to unmanaged C++ code. The returned float array from STagSharpExtern is converted to Point2f[][] for compatibility with the standard ArUco marker detection function from OpenCV.
   - STagSharpTest is a minimal console application for testing STagSharp and STagSharpExtern. It loads the image “example.jpg”, performs STag marker detection and displays the result in the OpenCV window.

Additionally, the solution folder contains the "STagGitBuild" folder with the "CMakeLists.txt" file. This file automatically clones the original STag repository and builds it. Cloning and building is run as a pre-build action for the STagSharpExtern project.  The CMake file also copies the stag.h file and the output file staglib(d).lib to the STagSharpExtern project folder.

To run STagSharpTest, additional .dll files (jpeg62.dll, ..., opencv_core4d.dll, ..., zlibd1.dll) are copied from the STagSharpExtern output folder into the pre-build action for the STagSharpTest project.

> [!NOTE]
> To use STagSharp.dll separately from the solution, all necessary dynamic DLLs (StagSharpExtern.dll, jpeg62.dll, ..., opencv_core4d.dll, ..., zlibd1.dll) need to be copied.

## Getting Started
1. Install Prerequisites

    - [CMake >= 3.16](https://cmake.org/getting-started/) (optional)
    On Windows: https://cmake.org/download/
    CMake is used to clone and build the original STag repository, and copy the necessary files for the STagSharpExtern project. These actions can be done manually or with other software tools. But the STagSharp solution will require modifications to run.

    - [vcpkg](https://vcpkg.io/) (optional)
    On Windows: can be installed with vcpkg or manualy
    Vcpkg is used to automatically retrieve the OpenCV library to build the original STag repository. Installation can be done manually or with other software tools. But the STagSharp solution will require modifications to run.

    - [OpenCV 4](https://opencv.org/get-started/) for C++
    On Windows: can be installed with vcpkg or manualy

2. Clone this repository
   
    `git clone https://github.com/skromnjaga/STagSharp`

3. Build the project

    Open STagSharp solution in Visual Studio and build all targets.
    
4. Run the example
    Run STagSharpTest project from solution


## Usage
```c#
using OpenCvSharp;

using STagSharp;

// Load image with OpenCVSharp
Mat image = Cv2.ImRead("example.jpg");

// set HD library
int libraryHD = 21;

STagSharpDetector.DetectMarkers(image, libraryHD, out Point2f[][] corners, out int[] ids);
```