// =================
// compute-program.h
// =================

#ifndef COMPUTEPROGRAM_H
#define COMPUTEPROGRAM_H

#include "compute-system.h"

namespace compute
{
	class ComputeProgram {
	public:
		bool loadProgramFromSourceFile(ComputeSystem& cs, const std::string& fileName);

		cl::Program getProgram() {
			return _program;
		}

	private:
		cl::Program _program;
	};
}
#endif
