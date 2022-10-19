include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

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

group "Dependencies"
	include "vendor/premake"
	include "Alternate/vendor/Box2D"
	include "Alternate/vendor/Glad"
	include	"Alternate/vendor/imgui"
	include "Alternate/vendor/yaml-cpp"
group ""

include "Alternate"
include "Sandbox"
include "Alternate-Editor"
