#ifndef STAG_STAGSHARP_H
#define STAG_STAGSHARP_H

#include "opencv2/opencv.hpp"

namespace stagsharp {

	extern "C"
	{
		/**
		 * Detects markers in given image. Maximum possible error correction for the given libraryHD is used.
		 * @param inImage OpenCV Matrix of input image.
		 * @param libraryHD The library HD that is used. Possible values are [11,&nbsp;13,&nbsp;15,&nbsp;17,&nbsp;19,&nbsp;21,&nbsp;23].
		 * @param output_corners The vector where the corners of detected markers are written into.
		 * @param output_ids The vector where the ids of detected markers are written into.
		 */
		__declspec(dllexport) void __stdcall detectMarkersFromSharp(
			const cv::Mat& image,
			int libraryHD,
			int* markers_founded_count,
			int** output_ids,
			int* output_flatten_coords_count,
			float** output_coords_flatten);
	}
}

#endif //STAG_STAGSHARP_H