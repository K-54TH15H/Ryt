#ifndef RYTIMAGE_HPP
#define RYTIMAGE_HPP

#include <device_types.h>
#include <string>

namespace RYT {
class Image {
public:
  // Constructors
  Image();
  Image(const char *fileName);

  // Destructors
  ~Image();

  bool Load(const std::string &fileName);
  __host__ __device__ int Width() const;
  __host__ __device__ int Height() const;
  bool HasFloatData() const;
  bool HasBinaryData() const;
  __host__ __device__ const unsigned char *PixelData(int x, int y) const;

  const int bytesPerPixel = 3;
  float *fdata = nullptr;
  unsigned char *bdata = nullptr;
  int imageWidth = 0;
  int imageHeight = 0;
  int bytesPerScanline = 0;

private:
  __host__ __device__ int Clamp(int x, int low, int high) const;
  unsigned char FloatToByte(float value) const;
  void ConvertToBytes();
};
} // namespace RYT
#endif
