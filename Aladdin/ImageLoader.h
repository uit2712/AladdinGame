#pragma once
#include <iostream>
#include <d3dx9.h>
#include "GameObjectTypes.h"
#include "ImagePaths.h"

using namespace std;
class ImageLoader
{
protected:
	int width;
	int height;
	std::string location;
	int type;
	D3DXIMAGE_INFO imgInfo;
public:
	ImageLoader(int type, std::string location);
	~ImageLoader();

	D3DXIMAGE_INFO GetImgInfo();
	std::string GetImgPath();
};

