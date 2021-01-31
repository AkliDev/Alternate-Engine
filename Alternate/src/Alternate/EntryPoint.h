#pragma once

#ifdef ALT_PLATFORM_WINDOWS

extern Alternate::Application* Alternate::CreateApplication();
int main(int argc, char** argv)
{
	printf("Alternate Engine\n");
	auto app = Alternate::CreateApplication();
	app->Run();
	delete app;
}
#endif