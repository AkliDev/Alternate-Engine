#include <Alternate.h>
#include <Alternate/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Alternate
{
	class AlternateEditor : public Application
	{
	public:
		AlternateEditor(ApplicationCommandLineArgs args)
			: Application("Alternate Editor", args)
		{
			PushLayer(new EditorLayer());
		}

		~AlternateEditor()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new AlternateEditor(args);
	}
}
