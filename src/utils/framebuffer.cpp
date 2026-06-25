#include "ryt/graphics/color.hpp"
#include <ryt/utils/framebuffer.hpp>

namespace RYT {
// Constructor
FrameBuffer::FrameBuffer(const int imgW, const int imgH) {
  this->size = imgW * imgH;

  buffer = new Color[this->size];

  this->imgW = imgW;
  this->imgH = imgH;
}

// Destructor
FrameBuffer::~FrameBuffer() { delete[] buffer; }

// Write to buffer
void FrameBuffer::WriteToBuffer(Color color, const int i, const int j) {
  buffer[(i * imgW) + j] = color;
}

// Write to output stream in ppm format
void FrameBuffer::WriteToPPM(std::ostream &os) {
  // PPM init line
  os << "P3" << std::endl
     << imgW << ' ' << imgH << std::endl
     << 255 << std::endl;

  for (int i = 0; i < imgH; i++) {
    for (int j = 0; j < imgW; j++) {
      WriteColor(os, buffer[(i * imgW) + j]);
    }
    os << std::endl;
  }
}

size_t FrameBuffer::GetSize() const { return this->size; }
size_t FrameBuffer::GetWidth() const { return this->imgW; }
size_t FrameBuffer::GetHeight() const { return this->imgH; }
Color **FrameBuffer::GetBufferAddress() { return &(this->buffer); }
} // namespace RYT
