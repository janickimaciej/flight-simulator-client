#include "app/commandLineArgs.hpp"

#include "app/commandLineArg.hpp"

#include <cstddef>

namespace
{
	bool isValidIPAddress(const std::string& address);
}

namespace App
{
	bool CommandLineArgs::parse(int argc, char** argv, CommandLineArgs& args)
	{
		if (argc < 2)
		{
			return false;
		}

		int gameModeIndex = std::stoi(argv[toSizeT(CommandLineArg::gameMode)]);
		if (gameModeIndex < 0 || gameModeIndex > 1)
		{
			return false;
		}
		args.gameMode = static_cast<GameMode>(gameModeIndex);

		if (!((args.gameMode == GameMode::multiplayer && argc == multiplayerArgCount) ||
			(args.gameMode == GameMode::singleplayer && argc == singleplayerArgCount)))
		{
			return false;
		}

		int controllerTypeIndex =
			std::stoi(argv[toSizeT(CommandLineArg::controllerType)]);
		if (controllerTypeIndex < 0 || controllerTypeIndex >= controllerTypeCount)
		{
			return false;
		}
		args.controllerType = static_cast<ControllerType>(controllerTypeIndex);

		int airplaneTypeIndex = std::stoi(argv[toSizeT(CommandLineArg::airplaneType)]);
		if (airplaneTypeIndex < 0 || airplaneTypeIndex >= Common::airplaneTypeCount)
		{
			return false;
		}
		args.airplaneType = static_cast<Common::AirplaneType>(airplaneTypeIndex);

		int mapIndex = std::stoi(argv[toSizeT(CommandLineArg::map)]);
		if (mapIndex < 0 || mapIndex >= Common::mapCount)
		{
			return false;
		}
		args.map = static_cast<Common::MapName>(mapIndex);

		if (args.gameMode == GameMode::singleplayer)
		{
			return true;
		}

		args.serverIPAddress = argv[toSizeT(CommandLineArg::serverIPAddress)];
		if (!isValidIPAddress(args.serverIPAddress))
		{
			return false;
		}

		static constexpr int minPortValue = 0;
		static constexpr int maxPortValue = 1 << 16;

		args.serverNetworkThreadPort =
			std::stoi(argv[toSizeT(CommandLineArg::serverNetworkThreadPort)]);
		if (args.serverNetworkThreadPort < minPortValue ||
			args.serverNetworkThreadPort >= maxPortValue)
		{
			return false;
		}

		args.serverPhysicsThreadPort =
			std::stoi(argv[toSizeT(CommandLineArg::serverPhysicsThreadPort)]);
		if (args.serverPhysicsThreadPort < minPortValue ||
			args.serverPhysicsThreadPort >= maxPortValue)
		{
			return false;
		}

		args.clientNetworkThreadPort =
			std::stoi(argv[toSizeT(CommandLineArg::clientNetworkThreadPort)]);
		if (args.clientNetworkThreadPort < minPortValue ||
			args.clientNetworkThreadPort >= maxPortValue)
		{
			return false;
		}

		args.clientPhysicsThreadPort =
			std::stoi(argv[toSizeT(CommandLineArg::clientPhysicsThreadPort)]);
		if (args.clientPhysicsThreadPort < minPortValue ||
			args.clientPhysicsThreadPort >= maxPortValue)
		{
			return false;
		}

		return true;
	}
}

namespace
{
	bool isValidIPAddress(const std::string& address)
	{
		int fieldIndex = 0;
		std::string field{};
		for (std::size_t i = 0; i <= address.size(); ++i)
		{
			if (i == address.size() || address[i] == '.')
			{
				if (field.empty()) return false;

				int fieldInt = std::stoi(field);
				static constexpr int maxFieldValue = 255;
				if (fieldInt > maxFieldValue) return false;

				field.clear();
				++fieldIndex;
			}
			else if (address[i] >= '0' && address[i] <= '9')
			{
				field.push_back(address[i]);
			}
			else
			{
				return false;
			}
		}

		return fieldIndex == 4;
	}
}
