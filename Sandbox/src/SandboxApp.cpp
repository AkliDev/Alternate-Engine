#include <Alternate.h>
#include <Alternate/Core/EntryPoint.h>

#include "Sandbox2D.h"

namespace Alternate
{
	class AlternateEditor : public Application
	{
	public:
		AlternateEditor(const ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new Sandbox2D());
		}

		~AlternateEditor()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "Sandbox";
		spec.CommandLineArgs = args;

		return new AlternateEditor(spec);
	}
}
