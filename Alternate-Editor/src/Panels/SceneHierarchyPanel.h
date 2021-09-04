#pragma once
#include "Alternate/Core/Base.h"
#include "Alternate/Core/Log.h"
#include "Alternate/Scene/Scene.h"
#include "Alternate/Scene/Entity.h"
namespace Alternate
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContex(const Ref<Scene>& context);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}