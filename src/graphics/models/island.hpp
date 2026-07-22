#pragma once

#include "graphics/meshes/mesh.hpp"
#include "graphics/meshes/proceduralMeshName.hpp"
#include "graphics/models/model.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	class Island : public Model
	{
	public:
		Island();
		virtual ~Island() = default;

		virtual void updateShaders() override;
		virtual void render() const override;

	private:
		std::unique_ptr<Submodel> m_ground{};

		void renderSurfaces() const;
	};
}
