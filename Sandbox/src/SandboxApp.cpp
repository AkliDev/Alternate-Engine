#include <Alternate.h>
#include <Alternate/Core/EntryPoint.h>

#include "Sandbox2D.h"

class Sandbox : public Alternate::Application
{
public:
	Sandbox()
		: Application("Sandbox")
	{
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Alternate::Application* Alternate::CreateApplication()
{
	return new Sandbox();
}