#pragma once

#include "graphics/assetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/models/model.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <string>

namespace Graphics
{
	class Hills : public Model
	{
	public:
		Hills(AssetManager<ProceduralMeshName, const Mesh>& proceduralMeshManager,
			AssetManager<std::string, const Texture>& textureManager);
		virtual void updateShaders() override;
		virtual void render() const override;
		virtual ~Hills() = default;

	private:
		Submodel m_ground;

		void renderSurfaces() const;
	};
}
