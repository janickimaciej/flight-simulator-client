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

	void Model::setScale(float scaleRatio)
	{
		Transformable::setScale(scaleRatio);
	}
}
