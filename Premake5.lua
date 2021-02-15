workspace "Alternate"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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
		"%{prj.name}/vendor/SDL2/include"	
	}

	libdirs 
	{
		"%{prj.name}/vendor/SDL2/lib/x64"
	}

	links
	{
		"SDL2.lib",
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
		symbols "On" 

	filter "configurations:Release"
		defines "ALT_RELEASE"
		optimize "On" 

	filter "configurations:Dist"
		defines "ALT_DIST"
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
		symbols "On" 

	filter "configurations:Release"
		defines "ALT_RELEASE"
		optimize "On" 

	filter "configurations:Dist"
		defines "ALT_DIST"
		optimize "On" 