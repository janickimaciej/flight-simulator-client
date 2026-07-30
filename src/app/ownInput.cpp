#include "app/ownInput.hpp"

namespace App
{
	void OwnInput::setOwnInput(const Physics::PlayerInput& ownInput)
	{
		std::scoped_lock lock{m_mutex};

		m_ownInput = ownInput;
	}

	Physics::PlayerInput OwnInput::getOwnInput() const
	{
		std::scoped_lock lock{m_mutex};

		Physics::PlayerInput ownInput = m_ownInput;

		return ownInput;
	}
}
