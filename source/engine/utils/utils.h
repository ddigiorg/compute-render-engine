// =======
// utils.h
// =======

#ifndef _UTILS_H_
#define _UTILS_H_

#include <cstdint>

namespace utils
{
	typedef struct Vec2i32
	{
		int x, y;

		Vec2i32(){};

		Vec2i32(
			int32_t initX,
			int32_t initY)
		{
			x = initX;
			y = initY;
		}
	} Vec2i32;

	typedef struct Vec2ui32
	{
		int x, y;

		Vec2ui32(){};

		Vec2ui32(
			uint32_t initX,
			uint32_t initY)
		{
			x = initX;
			y = initY;
		}
	} Vec2ui32;

	typedef struct Vec4ui8
	{
		unsigned char x, y, z, w;

		Vec4ui8(){};

		Vec4ui8(
			uint8_t initX,
			uint8_t initY,
			uint8_t initZ,
			uint8_t initW)
		{
			x = initX;
			y = initY;
			z = initX;
			w = initW;
		}
	} Vec4ui8;

	typedef struct Vec2f
	{
		float x, y;

		Vec2f(){};

		Vec2f(
			float initX,
			float initY)
		 {
			x = initX;
			y = initY;
		}
	} Vec2f;

	typedef struct Vec4f
	{
		float x, y, z, w;

		Vec4f(){};

		Vec4f(
			float initX,
			float initY,
			float initZ,
			float initW)
		{
			x = initX;
			y = initY;
			z = initZ;
			w = initW;
		}
	} Vec4f;
}
#endif
