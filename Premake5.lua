workspace "Alternate"
	architecture "x64"
	startproject "Alternate-Editor"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["Glad"] = "Alternate/vendor/Glad/include"
IncludeDir["ImGui"] = "Alternate/vendor/imgui"
IncludeDir["glm"] = "Alternate/vendor/glm"
IncludeDir["stb_image"] = "Alternate/vendor/stb_image"
IncludeDir["entt"] = "Alternate/vendor/entt/include"
IncludeDir["yaml_cpp"] = "Alternate/vendor/yaml-cpp/include"

group "Dependencies"
	include "Alternate/vendor/Glad"
	include	"Alternate/vendor/imgui"
	include "Alternate/vendor/yaml-cpp"
group ""

project "Alternate"
	location "Alternate"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "altpch.h"
	pchsource "Alternate/src/altpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/vendor/SDL2/include",	
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}"
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
		"yaml-cpp"
		--"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ALT_PLATFORM_WINDOWS",
			"ALT_BUILD_DLL"
		}

		postbuildcommands
		{
			"{COPY} ../%{prj.name}/vendor/SDL2/lib/x64/SDL2.dll  \"../bin/" .. outputdir .. "/Sandbox/\"",
			"{COPY} ../%{prj.name}/vendor/SDL2/lib/x64/SDL2.dll  \"../bin/" .. outputdir .. "/Alternate-Editor/\"",
		}

	filter "configurations:Debug"
		defines "ALT_DEBUG"
		runtime "Debug"
		symbols "on" 

	filter "configurations:Release"
		defines "ALT_RELEASE"
		runtime "Release"
		optimize "on" 

	filter "configurations:Dist"
		defines "ALT_DIST"
		runtime "Release"
		optimize "on" 	

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Alternate/src",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Alternate"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ALT_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "ALT_DEBUG"
		runtime "Debug"
		symbols "on" 

	filter "configurations:Release"
		defines "ALT_RELEASE"
		runtime "Release"
		optimize "on" 

	filter "configurations:Dist"
		defines "ALT_DIST"
		runtime "Release"
		optimize "on" 

project "Alternate-Editor"
	location "Alternate-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Alternate/src",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
	}

	links
	{
		"Alternate"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ALT_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "ALT_DEBUG"
		runtime "Debug"
		symbols "on" 

	filter "configurations:Release"
		defines "ALT_RELEASE"
		runtime "Release"
		optimize "on" 

	filter "configurations:Dist"
		defines "ALT_DIST"
		runtime "Release"
		optimize "on" 