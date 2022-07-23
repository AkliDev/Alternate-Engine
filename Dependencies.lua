
-- Alternate Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/Alternate/vendor/stb_image"
IncludeDir["yaml_cpp"] = "%{wks.location}/Alternate/vendor/yaml-cpp/include"
IncludeDir["Box2D"] = "%{wks.location}/Alternate/vendor/Box2D/include"
IncludeDir["GLFW"] = "%{wks.location}/Alternate/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Alternate/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Alternate/vendor/ImGui"
IncludeDir["ImGuizmo"] = "%{wks.location}/Alternate/vendor/ImGuizmo"
IncludeDir["glm"] = "%{wks.location}/Alternate/vendor/glm"
IncludeDir["entt"] = "%{wks.location}/Alternate/vendor/entt/include"
IncludeDir["shaderc"] = "%{wks.location}/Alternate/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/Alternate/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"
