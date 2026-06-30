#pragma once

#include "graphics/assetManager.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/submodels/submodel.hpp"

#include <string>

namespace Graphics
{
	class Zeppelin : public Model
	{
	public:
		Zeppelin(AssetManager<std::string, const Mesh>& fileMeshManager);
		virtual void updateShaders() override;
		virtual void render() const override;
		virtual ~Zeppelin() = default;

	private:
		Submodel m_body;

		void renderSurfaces() const;
	};
}
