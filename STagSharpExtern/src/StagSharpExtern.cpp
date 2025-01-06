#include "StagSharpExtern.h"

#include <Stag.h>
#ifdef _DEBUG
#pragma comment (lib, "libs/staglibd.lib")
#else
#pragma comment (lib, "libs/staglib.lib")
#endif


#include <combaseapi.h>

namespace stagsharp {

	void __stdcall detectMarkersFromSharp(const cv::Mat& image,
		int libraryHD,
		int* markers_founded_count,
		int** output_ids,
		int* output_flatten_coords_count,
		float** output_coords_flatten) {

		auto corners = std::vector<std::vector<cv::Point2f>>();
		auto ids = std::vector<int>();

		stag::detectMarkers(image, libraryHD, corners, ids);

		*markers_founded_count = ids.size();
		auto output_ids_size = (*markers_founded_count) * sizeof(int);
		*output_ids = static_cast<int*>(CoTaskMemAlloc(output_ids_size));
		memcpy(*output_ids, ids.data(), output_ids_size);

		auto corners_flatten = std::vector<cv::Point2f>();
		for (auto&& v : corners) {
			corners_flatten.insert(corners_flatten.end(), v.begin(), v.end());
		}

		*output_flatten_coords_count = corners.size() * 4 * 2;
		auto output_corners_size = (*output_flatten_coords_count) * sizeof(float);
		*output_coords_flatten = static_cast<float*>(CoTaskMemAlloc(output_corners_size));
		memcpy(*output_coords_flatten, corners_flatten.data(), output_corners_size);
	}
}