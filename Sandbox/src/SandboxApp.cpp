#include <Alternate.h>
#include <Alternate/Core/EntryPoint.h>

#include "Sandbox2D.h"

namespace Alternate
{
	class AlternateEditor : public Application
	{
	public:
		AlternateEditor(ApplicationCommandLineArgs args)
			: Application("Sandbox2D", args)
		{
			PushLayer(new Sandbox2D());
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
