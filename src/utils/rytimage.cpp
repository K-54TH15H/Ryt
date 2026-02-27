#include <iostream>
#include <ryt/utils/rytimage.hpp>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG

#include <stb/stb_image.h>

namespace RYT {
// Constructors
Image::Image() {};
Image::Image(const char *cFileName) {
  std::string sFileName = std::string(cFileName);
  char *imageDir = getenv("RYTImages");

  if (imageDir && Load(std::string(imageDir) + "/" + sFileName))
    return;
  if (Load(sFileName))
    return;

  // Error: Couldn't find/load image file
  std::cerr << "[ERROR]: Could not find/load image file - " << sFileName << "."
            << std::endl;
}

Image::~Image() {
  delete[] bdata;
  STBI_FREE(fdata);
}

bool Image::Load(const std::string &sFileName) {
  int bpp = bytesPerPixel;
  fdata = stbi_loadf(sFileName.c_str(), &imageWidth, &imageHeight, &bpp,
                     bytesPerPixel);
  if (fdata == nullptr)
    return false;

  bytesPerScanline = imageWidth * bytesPerPixel;

  ConvertToBytes();
  return true;
}

int Image::Width() const { return (fdata == nullptr) ? 0 : imageWidth; }

int Image::Height() const { return (fdata == nullptr) ? 0 : imageHeight; }

const unsigned char *Image::PixelData(int x, int y) const {
  static unsigned char magenta[] = {255, 0, 255};
  if (bdata == nullptr)
    return magenta;

  x = Clamp(x, 0, imageWidth);
  y = Clamp(y, 0, imageHeight);

  return bdata + y * bytesPerScanline + x * bytesPerPixel;
}

int Image::Clamp(int x, int low, int high) const {
  if (x < low)
    return low;
  if (x < high)
    return x;
  return high - 1;
}

unsigned char Image::FloatToByte(float value) const {
  if (value < 0.0)
    return 0;
  if (value >= 1.0)
    return 255;

  return (unsigned char)(256 * value);
}

void Image::ConvertToBytes() {
  int totalBytes = imageWidth * imageHeight * bytesPerPixel;
  bdata = new unsigned char[totalBytes];

  unsigned char *bptr = bdata;
  float *fptr = fdata;

  for (int i = 0; i < totalBytes; i++, fptr++, bptr++) {
    *bptr = FloatToByte(*fptr);
  }
}
} // namespace RYT
