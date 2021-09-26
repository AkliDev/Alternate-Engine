project "Alternate"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "altpch.h"
	pchsource "src/altpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{		
		"src",
		"vendor/spdlog/include",
		"vendor/SDL2/include",	
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}"
	}

	libdirs 
	{
		"vendor/SDL2/lib/x64"
	}

	links
	{
		"SDL2.lib",
		"Glad",
		"ImGui",
		"yaml-cpp"
		--"opengl32.lib"
	}

	filter "files:vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }

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