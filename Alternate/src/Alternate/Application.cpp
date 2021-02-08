#include "altpch.h"
#include "Application.h"

#include "Alternate/Events/ApplicationEvent.h"
#include "Alternate/Log.h"
namespace Alternate
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent event(1200, 720);
		ALT_TRACE(event);
		while (true);
	}
}
