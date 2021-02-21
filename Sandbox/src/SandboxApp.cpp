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
		//ALT_INFO("ExampleLayer::Update");
		if (Alternate::Input::IsKeyPressed(ALT_KEY_LALT))
			ALT_TRACE("Tab");
	}

	void OnEvent(Alternate::Event& event) override
	{
		//ALT_TRACE("{0}", event);
	}
};

class Sandbox : public Alternate::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Alternate::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Alternate::Application* Alternate::CreateApplication()
{
	return new Sandbox();
}