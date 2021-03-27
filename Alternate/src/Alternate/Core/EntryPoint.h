#pragma once

#ifdef ALT_PLATFORM_WINDOWS

extern Alternate::Application* Alternate::CreateApplication();
int main(int argc, char** argv)
{
	Alternate::Log::Init();

	ALT_PROFILE_BEGIN_SESSION("Startup", "AlternateProfile-Startup.json");
	auto app = Alternate::CreateApplication();
	ALT_PROFILE_END_SESSION();

	ALT_PROFILE_BEGIN_SESSION("Runtime", "AlternateProfile-Runtime.json");
	app->Run();
	ALT_PROFILE_END_SESSION();

	ALT_PROFILE_BEGIN_SESSION("Shutdown", "AlternateProfile-Shutdown.json");
	delete app;
	ALT_PROFILE_END_SESSION();
}
#endif