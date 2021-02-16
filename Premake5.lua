workspace "Alternate"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["Glad"] = "Alternate/vendor/Glad/include"
IncludeDir["ImGui"] = "Alternate/vendor/imgui"

group "Dependencies"
	include "Alternate/vendor/Glad"
	include	"Alternate/vendor/imgui"
group ""

project "Alternate"
	location "Alternate"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "altpch.h"
	pchsource "Alternate/src/altpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/SDL2/include",	
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	libdirs 
	{
		"%{prj.name}/vendor/SDL2/lib/x64"
	}

	links
	{
		"SDL2.lib",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	cppdialect "C++17"
	systemversion "latest"

	defines
	{
		"ALT_PLATFORM_WINDOWS",
		"ALT_BUILD_DLL"
	}

	postbuildcommands
	{
		"{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"",
		"{COPY} ../%{prj.name}/vendor/SDL2/lib/x64/SDL2.dll  \"../bin/" .. outputdir .. "/Sandbox/\"",
	}

	filter "configurations:Debug"
		defines "ALT_DEBUG"
		runtime "Debug"
		symbols "On" 

	filter "configurations:Release"
		defines "ALT_RELEASE"
		runtime "Release"
		optimize "On" 

	filter "configurations:Dist"
		defines "ALT_DIST"
		runtime "Release"
		optimize "On" 	

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Alternate/vendor/spdlog/include",
		"Alternate/src"
	}

	links
	{
		"Alternate"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"ALT_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "ALT_DEBUG"
		runtime "Debug"
		symbols "On" 

	filter "configurations:Release"
		defines "ALT_RELEASE"
		runtime "Release"
		optimize "On" 

	filter "configurations:Dist"
		defines "ALT_DIST"
		runtime "Release"
		optimize "On" 