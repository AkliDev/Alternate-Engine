#include "altpch.h"
#include "SceneSerializer.h"

#include <fstream>
#include <yaml-cpp/yaml.h>

namespace Alternate
{

	SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
		:m_Scene(scene)
	{

	}

	void SceneSerializer::Serialize(const std::string& filepath)
	{

	}

	void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{
		ALT_CORE_ASSERT(false, "not implemented");
	}

	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		return false;
	}

	bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
	{
		ALT_CORE_ASSERT(false, "not implemented");
		return false;
	}
}