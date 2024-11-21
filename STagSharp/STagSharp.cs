using System.Diagnostics.Contracts;
using System.Runtime.InteropServices;

using OpenCvSharp;

namespace STagSharp;


public class STagSharpDetector()
{
    public static void DetectMarkers(Mat image, int dictionaryHD, out Point2f[][] corners, out int[] ids)
    {
        if (image is null)
        {
            throw new ArgumentNullException();
        }

        detectMarkersFromSharp(image.CvPtr, dictionaryHD, out int markersFoundedCount, out ids, out int cornersFoundedCount, out float[] cornersArray);

        corners = new Point2f[markersFoundedCount][];

        for (int i = 0; i < markersFoundedCount; i++)
        {
            corners[i] = new Point2f[4];

            for (int j = 0; j < corners[i].Length; j++)
            {
                corners[i][j] = new Point2f(cornersArray[i * 4 * 2 + j * 2], cornersArray[i * 4 * 2 + j * 2 + 1]);
            }
        }

        GC.KeepAlive(image);
    }

    [Pure, DllImport("StagSharpExtern.dll", CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]
    public static extern void detectMarkersFromSharp(
        IntPtr image,
        int dictionaryHD,
        out int markersFoundedCount,
        [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 2)] out int[] ids,
        out int cornersFoundedCount,
        [MarshalAs(UnmanagedType.LPArray, SizeParamIndex = 4)] out float[] corner);
}