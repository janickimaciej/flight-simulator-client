#pragma once

namespace App
{
	enum class ExitCode
	{
		ok,
		badArgs,
		failedToConnect,
		connectionLost
	};

	int toInt(ExitCode exitCode);
}
