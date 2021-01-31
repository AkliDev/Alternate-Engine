#include <Alternate.h>

class Sandbox : public Alternate::Application
{
public:
	Sandbox()
	{
	
	}

	~Sandbox()
	{

	}
};

Alternate::Application* Alternate::CreateApplication()
{
	return new Sandbox();
}