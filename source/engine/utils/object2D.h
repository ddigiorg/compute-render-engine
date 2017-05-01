// ==========
// object2D.h
// ==========

#include "engine/utils/utils.h"
#include "engine/render/texture2D.h"
#include "engine/render/image-mesh.h"
#include "engine/compute/helpers.h"
#include "engine/compute/compute-system.h"

namespace utils
{
	class Object2D
	{
	public:
		Object2D();

		Object2D(compute::ComputeSystem& cs, utils::Vec2ui32 textureSize, float meshScale, unsigned int id)
			: _glTexture2D(id), _glImageMesh(id)
		{
			_textureSize = textureSize;
			_meshSize.x = static_cast<unsigned int>(textureSize.x * meshScale);
			_meshSize.y = static_cast<unsigned int>(textureSize.y * meshScale);

			setPosition(0, 0);

			_glTexture2D.nullRGBA32F(_textureSize.x, _textureSize.y);

			setImageGL(cs);
		}

	cl::ImageGL getImageGL()
	{
		return _clImageGL;
	}

	void setPosition(unsigned int x, unsigned int y)
	{
		_glImageMesh.update(x, y, _meshSize.x, _meshSize.y);
	}

	void setTextureData(std::vector<utils::Vec4f> data)
	{
		_glTexture2D.updateRGBA32F(_textureSize.x, _textureSize.y, data);
	}

	void setImageGL(compute::ComputeSystem& cs)
	{
		_clImageGL = compute::createBuffer2DGL(cs, _glTexture2D.getID());
	}

	void render()
	{
		_glTexture2D.bind();
		_glImageMesh.draw();
	}

	private:
		utils::Vec2ui32 _textureSize;
		utils::Vec2ui32 _meshSize;

		render::Texture2D _glTexture2D;
		render::ImageMesh _glImageMesh;
		cl::ImageGL _clImageGL;
	};
}
