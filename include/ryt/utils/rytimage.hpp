#ifndef RYTIMAGE_HPP
#define RYTIMAGE_HPP

#include <string>

namespace RYT
{
class Image
{
    public:
	// Constructors
	Image();
	Image(const char* fileName);
	
	// Destructors
	~Image();

	bool Load(const std::string& fileName);
	int Width() const;
	int Height() const;
	const unsigned char* PixelData(int x, int y) const;

    private:
	const int bytesPerPixel = 3;
	float* fdata = nullptr;
	unsigned char* bdata = nullptr;
	int imageWidth = 0;
	int imageHeight = 0;
	int bytesPerScanline = 0;

	int Clamp(int x, int low, int high) const;
	unsigned char FloatToByte(float value) const;
	void ConvertToBytes();
};
}
#endif
