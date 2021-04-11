#include <Alternate.h>
#include <Alternate/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Alternate
{
	class AlternateEditor : public Application
	{
	public:
		AlternateEditor()
			: Application("Alternate Editor")
		{
			PushLayer(new EditorLayer());
		}

		~AlternateEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new AlternateEditor();
	}
}