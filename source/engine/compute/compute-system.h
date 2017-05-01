// ================
// compute-system.h
// ================

#ifndef COMPUTESYSTEM_H
#define COMPUTESYSTEM_H

#define __CL_ENABLE_EXCEPTIONS

#include <CL/cl.hpp>

namespace compute
{
	class ComputeSystem
	{
	public:
		enum DeviceType {_cpu, _gpu, _all, _none};

		bool init(DeviceType type); //createFromGLContext = false);
		void printCLInfo();

		cl::Platform getPlatform()
		{
			return _platform;
		}

		cl::Device getDevice()
		{
			return _device;
		}

		cl::Context getContext()
		{
			return _context;
		}

		cl::CommandQueue getQueue()
		{
			return _queue;
		}

	private:
		cl::Platform _platform;
		cl::Device _device;
		cl::Context _context;
		cl::CommandQueue _queue;
	};
}

#endif
