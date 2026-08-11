#pragma once

#include "graphics/models/model.hpp"
#include "graphics/submodels/submodel.hpp"

#include <memory>

namespace Graphics
{
	class Sea : public Model
	{
	public:
		Sea();
		virtual ~Sea() = default;

		virtual void updateShaders() override;
		virtual void render() const override;

	private:
		std::unique_ptr<Submodel> m_surface{};
	};
}
