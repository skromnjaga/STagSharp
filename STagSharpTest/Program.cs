using OpenCvSharp;
using OpenCvSharp.Aruco;

using STagSharp;

namespace STagSharpTest;


public class Program
{
    static void Main(string[] args)
    {
        // Load image with OpenCVSharp
        Mat image = Cv2.ImRead("example.jpg");

        // set HD library
        int libraryHD = 21;

        // Detect markers thru unmanaged STag library
        STagSharpDetector.DetectMarkers(image, libraryHD, out Point2f[][] corners, out int[] ids);

        // Draw detected markers 
        CvAruco.DrawDetectedMarkers(image, corners, ids);

        // Display markers on image
        Cv2.NamedWindow("img", WindowFlags.Normal);
        Cv2.ResizeWindow("img", 800, 600);

        Cv2.ImShow("img", image);
        Cv2.WaitKey();
    }
}
