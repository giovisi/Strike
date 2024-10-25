workspace "Strike"
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
IncludeDir["GLFW"] = "Strike/vendor/GLFW/include"
IncludeDir["Glad"] = "Strike/vendor/Glad/include"
IncludeDir["ImGui"] = "Strike/vendor/imgui"
IncludeDir["glm"] = "Strike/vendor/glm"

include "Strike/vendor/GLFW"
include "Strike/vendor/Glad"
include "Strike/vendor/imgui"
--include "Strike/vendor/glm"

project "Strike"
    location "Strike"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "strkpch.h"
    pchsource "Strike/src/strkpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib",
        "dwmapi.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "STRK_PLATFORM_WINDOWS",
            "STRK_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "STRK_DEBUG"
        staticruntime "Off"
        runtime "Debug"
        symbols "On"
            
    filter "configurations:Release"
        defines "STRK_RELEASE"
        staticruntime "Off"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "STRK_DIST"
        staticruntime "Off"
        runtime "Release"
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
        "Strike/vendor/spdlog/include",
        "Strike/src",
        "Strike/vendor",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Strike"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "STRK_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "STRK_DEBUG"
        staticruntime "Off"
        runtime "Debug"
        symbols "On"
            
    filter "configurations:Release"
        defines "STRK_RELEASE"
        staticruntime "Off"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "STRK_DIST"
        staticruntime "Off"
        runtime "Release"
        optimize "On"