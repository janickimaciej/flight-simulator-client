#pragma once

#include "graphics/models/model.hpp"
#include "graphics/submodels/submodel.hpp"

#include <memory>

namespace Graphics
{
	class IslandLand : public Model
	{
	public:
		IslandLand();
		virtual ~IslandLand() = default;

		virtual void updateShaders() override;
		virtual void render() const override;

	private:
		std::unique_ptr<Submodel> m_surface{};
	};
}
