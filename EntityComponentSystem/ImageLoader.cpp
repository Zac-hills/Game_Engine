#include "glew.h"
#include "ImageLoader.h"
#include <iostream>
#include "BufferManager.h"

ImageLoader::ImageLoader(){}

ImageLoader::~ImageLoader(){}

ImageLoader &ImageLoader::getLoader()
{
	static ImageLoader ONLY_ONE;
	return ONLY_ONE;
}

unsigned int ImageLoader::loadImage(const char *filePath)
{
	unsigned int cache = BUFFER_MANAGER.checkIfExists(filePath);
	if (cache == 0)
	{
		unsigned int image_index = 0;
			image_index = SOIL_load_OGL_texture(filePath,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | 
			SOIL_FLAG_INVERT_Y |
			SOIL_FLAG_NTSC_SAFE_RGB);


		if (image_index == 0)
		{
			printf("SOIL loading error: '%s'\n", SOIL_last_result());
			return 0;
		}
		BUFFER_MANAGER.addBuffer(filePath, cache);
		return image_index;
	}
	else
	{
		return cache;
	}
}

void ImageLoader::takeScreenShot()
{
	unsigned int imagesave = SOIL_save_screenshot("awesomenessity.bmp",
		SOIL_SAVE_TYPE_BMP,
		0, 0, 1920, 1080);
}