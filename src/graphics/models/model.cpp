#include "graphics/models/model.hpp"

namespace Graphics
{
	glm::mat4 Model::getModelMatrix() const
	{
		return getMatrix();
	}

	glm::vec3 Model::getPos() const
	{
		return getState().pos;
	}

	void Model::scale(float scaleRatio)
	{
		Transformable::scale(scaleRatio);
	}
}
