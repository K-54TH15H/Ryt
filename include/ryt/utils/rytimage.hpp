#ifndef RYTIMAGE_HPP
#define RYTIMAGE_HPP

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG

#include <stb/stb_image.h>
#include <string>

class RytImage
{
    public:
	// Constructors
	RytImage();
	RytImage(const char* fileName);
	
	// Destructors
	~RytImage();

	bool Load(const std::string& fileName);
	int Width() const;
	int Height() const;

    private:
	const int bytesPerPixel = 3;
	float* fdata = nullptr;
	unsigned char* bdata = nullptr;
	int imageWidth = 0;
	int imageHeight = 0;
	int bytesPerScanline = 0;

	int Clamp(int x, int low, int high);
	unsigned char floatToByte(float value);
	void convertToBytes();
};

#endif
