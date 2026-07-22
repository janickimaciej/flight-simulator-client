#pragma once

#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/submodels/submodel.hpp"

#include <memory>
#include <string>

namespace Graphics
{
	class Zeppelin : public Model
	{
	public:
		Zeppelin();
		virtual ~Zeppelin() = default;

		virtual void updateShaders() override;
		virtual void render() const override;

	private:
		std::unique_ptr<Submodel> m_body{};

		void renderSurfaces() const;
	};
}
