#pragma once

#include "graphics/models/model.hpp"
#include "graphics/submodels/submodel.hpp"

#include <memory>

namespace Graphics
{
	class Bullet : public Model
	{
	public:
		Bullet();
		virtual ~Bullet() = default;

		virtual void updateShaders() override;
		virtual void render() const override;

	private:
		std::unique_ptr<Submodel> m_tracer{};

		void renderLights() const;
	};
}
