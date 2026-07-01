#include "graphics/cameras/trackingCamera.hpp"

#include "graphics/cameras/perspectiveCamera.hpp"
#include "graphics/models/model.hpp"

#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Graphics
{
	TrackingCamera::TrackingCamera(float fovRad, float nearPlane, float farPlane,
		const Model& model) :
		PerspectiveCamera{fovRad, nearPlane, farPlane},
		m_model{model}
	{ }

	void TrackingCamera::use(float aspectRatio)
	{
		aimAtModel();
		Camera::use(aspectRatio);
	}

	void TrackingCamera::aimAtModel()
	{
		Common::State state = getState();
		glm::vec3 modelPos = m_model.getPos();
		state.setOrientation(glm::normalize(state.pos - modelPos));
		setState(state);
	}
}
