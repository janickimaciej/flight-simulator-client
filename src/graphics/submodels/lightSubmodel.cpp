#include "graphics/submodels/lightSubmodel.hpp"

#include "graphics/shaderPrograms.hpp"

namespace Graphics
{
	LightSubmodel::LightSubmodel(const Light& light, const std::shared_ptr<const Mesh>& mesh,
		const Material& material, const std::shared_ptr<const Texture>& texture) :
		Submodel{*ShaderPrograms::light, mesh, material, texture},
		m_light{light}
	{ }

	LightSubmodel::LightSubmodel(const Light& light, const LightSubmodel& lightSubmodel) :
		Submodel{lightSubmodel},
		m_light{light}
	{ }

	glm::mat4 LightSubmodel::getSubmodelMatrix() const
	{
		return m_light.getState().matrix() * getMatrix();
	}
}
