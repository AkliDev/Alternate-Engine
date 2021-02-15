workspace "Alternate"
	architecture "x64"

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

include "Alternate/vendor/Glad"
include	"Alternate/vendor/imgui"

project "Alternate"
	location "Alternate"
	kind "SharedLib"
	language "C++"

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
	staticruntime "on"
	systemversion "latest"

	defines
	{
		"ALT_PLATFORM_WINDOWS",
		"ALT_BUILD_DLL",
		"ALT_ENABLE_ASSERTS"
	}

	postbuildcommands
	{
		"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox",
		--"{COPY} %{prj.name}/vendor/SDL2/lib/x64/SDL2.dll ../bin/" .. outputdir .. "/Sandbox"
	}

	filter "configurations:Debug"
		defines "ALT_DEBUG"
		buildoptions "/MDd"
		symbols "On" 

	filter "configurations:Release"
		defines "ALT_RELEASE"
		buildoptions "/MD"
		optimize "On" 

	filter "configurations:Dist"
		defines "ALT_DIST"
		buildoptions "/MD"
		optimize "On" 	

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"ALT_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "ALT_DEBUG"
		buildoptions "/MDd"
		symbols "On" 

	filter "configurations:Release"
		defines "ALT_RELEASE"
		buildoptions "/MD"
		optimize "On" 

	filter "configurations:Dist"
		defines "ALT_DIST"
		buildoptions "/MD"
		optimize "On" 