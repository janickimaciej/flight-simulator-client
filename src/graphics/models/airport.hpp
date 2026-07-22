#pragma once

#include "graphics/lights/pointLight.hpp"
#include "graphics/lights/spotLight.hpp"
#include "graphics/meshes/mesh.hpp"
#include "graphics/models/model.hpp"
#include "graphics/submodels/lightSubmodel.hpp"
#include "graphics/submodels/submodel.hpp"
#include "graphics/texture.hpp"

#include <memory>
#include <string>
#include <vector>

namespace Graphics
{
	class Airport : public Model
	{
	public:
		Airport();
		virtual ~Airport() = default;

		virtual void updateShaders() override;
		virtual void render() const override;

	private:
		std::unique_ptr<Submodel> m_ground{};
		std::unique_ptr<Submodel> m_runway{};
		std::unique_ptr<Submodel> m_apron{};
		std::unique_ptr<Submodel> m_tower{};
		std::vector<Submodel> m_hangarExteriors{};
		std::vector<Submodel> m_hangarInteriors{};
		std::vector<Submodel> m_lightBodies{};
		std::vector<std::unique_ptr<SpotLight>> m_lights{};
		std::vector<LightSubmodel> m_lightSubmodels{};

		void renderSurfaces() const;
		void renderLights() const;
	};
}
