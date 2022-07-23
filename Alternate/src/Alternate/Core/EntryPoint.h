#pragma once
#include "Alternate/Core/Application.h"

#ifdef ALT_PLATFORM_WINDOWS

extern Alternate::Application* Alternate::CreateApplication(ApplicationCommandLineArgs args);
int main(int argc, char** argv)
{
	Alternate::Log::Init();

	ALT_PROFILE_BEGIN_SESSION("Startup", "AlternateProfile-Startup.json");
	auto app = Alternate::CreateApplication({ argc, argv });
	ALT_PROFILE_END_SESSION();

	ALT_PROFILE_BEGIN_SESSION("Runtime", "AlternateProfile-Runtime.json");
	app->Run();
	ALT_PROFILE_END_SESSION();

	ALT_PROFILE_BEGIN_SESSION("Shutdown", "AlternateProfile-Shutdown.json");
	delete app;
	ALT_PROFILE_END_SESSION();
}
#endif
