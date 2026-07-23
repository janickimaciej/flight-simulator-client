#pragma once

#include "common/transformable.hpp"

#include <glm/glm.hpp>

namespace Graphics
{
	class Model : public Common::Transformable
	{
	public:
		virtual ~Model() = default;

		virtual void updateShaders() = 0;
		virtual void render() const = 0;
		glm::mat4 getModelMatrix() const;
		glm::vec3 getPos() const;
		virtual void scale(float scaleRatio) override; // locally
	};
}
