#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <ryt/graphics/color.hpp>

namespace RYT
{
    class FrameBuffer
    {
	private:
	    // The Main Buffer
	    Color* buffer;
	    
	    // Properties of the buffer
	    size_t imgW;
	    size_t imgH;
	    size_t size;

	public:
	    // Constructors
	    FrameBuffer(const int imgW, const int imgH);

	    // Destructor
	    ~FrameBuffer();

	    // Write to buffer
	    void WriteToBuffer(Color color, const int i, const int j);

	    // Write to output stream in ppm format
	    void WriteToPPM(std::ostream& outputStream);
    };
}
#endif
