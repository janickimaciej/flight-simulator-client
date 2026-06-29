#pragma once

#include <cstddef>

namespace App
{
	inline constexpr int multiplayerArgCount = 10;
	inline constexpr int singleplayerArgCount = 5;

	enum class CommandLineArg
	{
		programName,
		gameMode,
		controllerType,
		airplaneType,
		map,
		serverIPAddress,
		serverNetworkThreadPort,
		serverPhysicsThreadPort,
		clientNetworkThreadPort,
		clientPhysicsThreadPort
	};

	std::size_t toSizeT(CommandLineArg commandLineArg);
}
