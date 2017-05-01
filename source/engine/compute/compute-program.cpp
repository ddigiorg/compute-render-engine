// ===================
// compute-program.cpp
// ===================

// TODO: Clean up error checking

#include "compute-program.h"

#include <fstream>
#include <iostream>

using namespace compute;

bool ComputeProgram::loadProgramFromSourceFile(ComputeSystem& cs, const std::string& fileName)
{
	std::ifstream sourceFile(fileName);

	if (!sourceFile.is_open())
	{
		std::cout << "[cp] Could not open file: " << fileName << std::endl;
		return false;
	}

	std::string sourceCode(
		std::istreambuf_iterator<char>(sourceFile),
		(std::istreambuf_iterator<char>()));

	cl::Program::Sources source(1, std::make_pair(sourceCode.c_str(), sourceCode.length() + 1));

	_program = cl::Program(cs.getContext(), source);

	sourceFile.close();

	try
	{
		_program.build(); //devices
	}
	catch (cl::Error er)
	{
		std::cerr << "ERROR: " <<  er.what() << ": " << er.err() << std::endl;
	}

	//printf("done building program\n");
	//std::cout 
	//	<< "[cp] Build Status: " 
	//	<< _program.getBuildInfo<CL_PROGRAM_BUILD_STATUS>(cs.getDevice()) 
	//	<< std::endl;
	//std::cout << "Build Options:\t" << program.getBuildInfo<CL_PROGRAM_BUILD_OPTIONS>(devices[0]) << std::endl;
	//std::cout << "Build Log:\t " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(devices[0]) << std::endl;
}
