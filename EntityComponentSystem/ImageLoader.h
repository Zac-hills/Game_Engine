#ifndef __IMAGE_LOADER_H__
#define __IMAGE_LOADER_H__
#include "SOIL.h"
#define IMAGE_LOADER ImageLoader::getLoader()

class ImageLoader
{
private:
	ImageLoader();
	~ImageLoader();
public:
	static ImageLoader &getLoader();
	unsigned int loadImage(const char *filePath);
	void takeScreenShot();
};

#endif