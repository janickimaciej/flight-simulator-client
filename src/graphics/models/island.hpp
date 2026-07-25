#pragma once

#include "graphics/models/model.hpp"
#include "graphics/submodels/submodel.hpp"

#include <memory>

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
