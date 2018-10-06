#include "ImageLoader.h"

ImageLoader::ImageLoader(int type, std::string location)
{
	this->type = type;
	this->location = location;
	try
	{
		D3DXGetImageInfoFromFile(this->location.c_str(), &this->imgInfo);
	}
	catch(exception e)
	{
		MessageBox(NULL, "Load image failed", "Failed", MB_OK);
	}

	this->width = this->imgInfo.Width;
	this->height = this->imgInfo.Height;
}


ImageLoader::~ImageLoader()
{
}

D3DXIMAGE_INFO ImageLoader::GetImgInfo()
{
	return imgInfo;
}

std::string ImageLoader::GetImgPath()
{
	return location;
}
