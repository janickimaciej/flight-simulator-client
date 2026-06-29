#pragma once

#include "app/controllerType.hpp"
#include "app/gameMode.hpp"
#include "common/airplaneTypeName.hpp"
#include "common/mapName.hpp"

#include <string>

namespace App
{
	struct CommandLineArgs
	{
		GameMode gameMode{};
		ControllerType controllerType{};
		Common::AirplaneTypeName airplaneTypeName{};
		Common::MapName mapName{};
		std::string serverIPAddress{};
		int serverNetworkThreadPort{};
		int serverPhysicsThreadPort{};
		int clientNetworkThreadPort{};
		int clientPhysicsThreadPort{};

		static bool parse(int argc, char** argv, CommandLineArgs& args);
	};
}
