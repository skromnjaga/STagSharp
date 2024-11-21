# STagSharp - STag wrapper for .NET

This repository is a simple wrapper for Stag to use this library for marker detection in .NET.

> [!NOTE]
> For the original C++ source code of STag refer to: https://github.com/ManfredStoiber/stag.

## 📖 Usage
```c#
using OpenCvSharp;

using STagSharp;

// Load image with OpenCVSharp
Mat image = Cv2.ImRead("example.jpg");

// set HD library
int libraryHD = 21;

STagSharpDetector.DetectMarkers(image, libraryHD, out Point2f[][] corners, out int[] ids);
```