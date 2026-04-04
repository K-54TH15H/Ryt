#include <ryt/core/renderer.hpp>

namespace RYT
{
    Renderer::Renderer(RenderMode mode) : mode(mode) {} 
    Renderer::~Renderer() {}

    void Renderer::Render(Camera& camera, const RaytracingContext* context) const
    {
	camera.Initialize();
	FrameBuffer frameBuffer(camera.imgW, camera.imgH);

	if(mode == RenderMode::CPU)
	    RenderCPU(camera, context, frameBuffer);
	else 
	    RenderGPU(camera, context, frameBuffer);

	frameBuffer.WriteToPPM(std::cout);
	std::clog << std::endl << "Render Complete" << std::endl;
    }

    void Renderer::SetMode(RenderMode mode)
    {
	this->mode = mode;
    }

    void Renderer::RenderCPU(const Camera& camera, const RaytracingContext* context, FrameBuffer& frameBuffer)
    {
	#pragma omp parallel for collapse(2) schedule(guided)
	for (int i = 0; i < camera.imgH; i++) {
	    for (int j = 0; j < camera.imgW; j++) {
		Color pixelColor(0, 0, 0);

		for (int sj = 0; sj < camera.sqrtSpp; sj++) {
		    for (int si = 0; si < camera.sqrtSpp; si++) {
			Ray r = camera.GetRay(j, i, si, sj);
			pixelColor += camera.RayColor(r, camera.maxDepth, context);
		    }
		}
		frameBuffer.WriteToBuffer(camera.pixelSamplesScale * pixelColor, i, j);
	    }
	}
    }

    void Renderer::RenderGPU(const Camera& cam, const RaytracingContext* context, FrameBuffer& fb)
    {
	// To Be Implemented
	std::cerr << "GPU Backend - To Be Implemented" << std::endl;	
    }
}
