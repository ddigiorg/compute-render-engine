// =========
// helpers.h
// =========

#ifndef HELPERS_H
#define HELPERS_H

#include "compute-system.h"

#include <iostream>

namespace compute
{
	cl::Buffer createBuffer1D(ComputeSystem &cs, size_t size)
	{
		cl_int err;

		cl::Buffer buffer = cl::Buffer(cs.getContext(), CL_MEM_READ_WRITE, size, &err);

		if (err)
			std::cerr << "error creating CL buffer" << std::endl;
		else
			return buffer;
	}

	cl::BufferGL createBuffer1DGL(ComputeSystem &cs, cl_int glId)
	{
		cl_int err;

		cl::BufferGL buffer = cl::BufferGL(cs.getContext(), CL_MEM_READ_WRITE, glId, &err);

		if (err)
			std::cerr << "error creating CL buffer from GL buffer" << std::endl;
		else
			return buffer;
	}


	// createDoubleBuffer2D(cs, vld._size, CL_RG, CL_FLOAT)
	cl::Image2D createBuffer2D(ComputeSystem &cs, cl_int2 size, cl_channel_order channelOrder, cl_channel_type channelType)
	{
		return cl::Image2D(cs.getContext(), CL_MEM_READ_WRITE, cl::ImageFormat(channelOrder, channelType), size.x, size.y);
	}

	cl::ImageGL createBuffer2DGL(ComputeSystem &cs, cl_int glId)
	{
		cl_int err;

		cl::ImageGL buffer = cl::ImageGL(cs.getContext(), CL_MEM_READ_WRITE, GL_TEXTURE_2D, 0, glId, &err);

		if (err)
			std::cerr << "error creating CL buffer from GL buffer" << std::endl;
		else
			return buffer;
	}

	// createDoubleBuffer3D(cs, vld._size, CL_RG, CL_FLOAT)
	cl::Image3D createBuffer3D(ComputeSystem &cs, cl_int3 size, cl_channel_order channelOrder, cl_channel_type channelType)
	{
		return cl::Image3D(cs.getContext(), CL_MEM_READ_WRITE, cl::ImageFormat(channelOrder, channelType), size.x, size.y, size.z);
	}



	void writeBuffer1D(ComputeSystem &cs, cl::Buffer& buffer, size_t size, const void *ptr)
	{
		cs.getQueue().enqueueWriteBuffer(buffer, CL_TRUE, 0, size, ptr);
		cs.getQueue().finish();
	}
}

#endif
