#pragma once

#include "graphics/models/model.hpp"
#include "graphics/submodels/submodel.hpp"

#include <memory>

namespace Graphics
{
	class IslandShore : public Model
	{
	public:
		IslandShore();
		virtual ~IslandShore() = default;

		virtual void updateShaders() override;
		virtual void render() const override;

	private:
		std::unique_ptr<Submodel> m_surface{};
	};
}
