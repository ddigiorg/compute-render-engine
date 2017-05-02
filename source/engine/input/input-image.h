// =============
// input-image.h
// =============

#ifndef INPUTIMAGE_H
#define INPUTIMAGE_H

#include "../utils/utils.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>

#include <vector>

namespace input
{
	class InputImage
	{
	public:
		InputImage();
		InputImage(std::string& fileName);
		~InputImage();

		std::vector<utils::Vec4f> getPixels();
		void printInfo();

		unsigned int getWidth()
		{
			return _imageWidth;
		}

		unsigned int getHeight()
		{
			return _imageHeight;
		}

	private:
		cv::Mat _image;

		std::string _fileName;

		int _imageWidth;
		int _imageHeight;
	};
}

#endif
