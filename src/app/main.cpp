#include "app/commandLineArgs.hpp"
#include "app/exitCode.hpp"
#include "app/exitSignal.hpp"
#include "app/threads/renderingThread.hpp"

int main(int argc, char** argv)
{
	using namespace App;

	CommandLineArgs args{};
	if (!CommandLineArgs::parse(argc, argv, args))
	{
		return toInt(ExitCode::badArgs);
	}

	ExitSignal exitSignal{};
	RenderingThread renderingThread{exitSignal};
	renderingThread.start(args);

	return toInt(exitSignal.getExitCode());
}
