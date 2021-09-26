include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Alternate"
	architecture "x86_64"
	startproject "Alternate-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["Glad"] =		"%{wks.location}/Alternate/vendor/Glad/include"
IncludeDir["ImGui"] =		"%{wks.location}/Alternate/vendor/imgui"
IncludeDir["glm"] =			"%{wks.location}/Alternate/vendor/glm"
IncludeDir["stb_image"] =	"%{wks.location}/Alternate/vendor/stb_image"
IncludeDir["entt"] =		"%{wks.location}/Alternate/vendor/entt/include"
IncludeDir["yaml_cpp"] =	"%{wks.location}/Alternate/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] =	"%{wks.location}/Alternate/vendor/ImGuizmo/include"

group "Dependencies"
	include "vendor/premake"
	include "Alternate/vendor/Glad"
	include	"Alternate/vendor/imgui"
	include "Alternate/vendor/yaml-cpp"
group ""

include "Alternate"
include "Sandbox"
include "Alternate-Editor"
