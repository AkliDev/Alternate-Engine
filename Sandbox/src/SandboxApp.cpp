#include <Alternate.h>

class ExampleLayer : public Alternate::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		ALT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Alternate::Event& event) override
	{
		ALT_TRACE("{0}", event);
	}
};

class Sandbox : public Alternate::Application
{
public:
	Sandbox()
	{
		PushOverlay(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Alternate::Application* Alternate::CreateApplication()
{
	return new Sandbox();
}