#pragma once

#ifdef ALT_PLATFORM_WINDOWS

extern Alternate::Application* Alternate::CreateApplication();
int main(int argc, char** argv)
{
	Alternate::Log::Init();
	ALT_CORE_WARN("Initialized Log!");
	ALT_INFO("Initialized Log!");
	auto app = Alternate::CreateApplication();
	app->Run();
	delete app;
}
#endif