#pragma once

#include "Alternate/Core/UUID.h"
#include "Alternate/Core/Timestep.h"
#include "Alternate/Renderer/EditorCamera.h"

#include "entt.hpp"

class b2World;

namespace Alternate
{	
	class Entity;
	class Scene
	{
	public:
		static Ref<Scene> Copy(Ref<Scene> other);

		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();	
		void OnSimulationStart();
		void OnSimulationStop();

		void OnEditorUpdate(Timestep ts, EditorCamera& camera);
		void OnSimulationUpdate(Timestep ts, EditorCamera& camera);
		void OnRuntimeUpdate(Timestep ts);
			
		void DuplicateEntity(Entity entity);

		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetPrimaryCameraEntity();

		template<typename... Components>
		auto GetAllEntitiesWith()
		{
			return m_Registry.view<Components...>();
		}
	private:
		void OnPhysics2DStart();
		void OnPhysics2DStop();
		void RenderScene(EditorCamera& camera);

		template<typename T>
		void OnComponentAdded(Entity entity, T& component);	
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		b2World* m_PhysicsWorld2D = nullptr;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}
