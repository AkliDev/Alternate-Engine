#include "altpch.h"
#include "Entity.h"

namespace Alternate
{
	Entity::Entity(entt::entity handle, Scene* scene)
		:m_EntityHandle(handle), m_Scene(scene)
	{

	}
}