#include <Alternate.h>
#include <Alternate/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Alternate
{
	class AlternateEditor : public Application
	{
	public:
		AlternateEditor(const ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new EditorLayer());
		}

		~AlternateEditor()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "Alternate Editor";
		spec.CommandLineArgs = args;

		return new AlternateEditor(spec);
	}
}
