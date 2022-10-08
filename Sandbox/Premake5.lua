project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Alternate/vendor/spdlog/include",
		"%{wks.location}/Alternate/src",
		"%{wks.location}/Alternate/vendor",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
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
