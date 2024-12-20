workspace "Strike"
    architecture "x64"
    startproject "StrikeThrough"

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
IncludeDir["GLFW"] = "Strike/vendor/GLFW/include"
IncludeDir["Glad"] = "Strike/vendor/Glad/include"
IncludeDir["ImGui"] = "Strike/vendor/imgui"
IncludeDir["glm"] = "Strike/vendor/glm"
IncludeDir["stb_image"] = "Strike/vendor/stb_image"

group "Dependencies"
    include "Strike/vendor/GLFW"
    include "Strike/vendor/Glad"
    include "Strike/vendor/imgui"
group ""

project "Strike"
    location "Strike"
    kind "StaticLib"
    language "C++"        
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "strkpch.h"
    pchsource "Strike/src/strkpch.cpp"

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
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "STRK_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "STRK_DEBUG"
        runtime "Debug"
        symbols "on"
            
    filter "configurations:Release"
        defines "STRK_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "STRK_DIST"
        runtime "Release"
        optimize "on"


    
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"        
    cppdialect "C++20"
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
        "Strike/vendor/spdlog/include",
        "Strike/src",
        "Strike/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Strike"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "STRK_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "STRK_DEBUG"
        runtime "Debug"
        symbols "on"
            
    filter "configurations:Release"
        defines "STRK_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "STRK_DIST"
        runtime "Release"
        optimize "on"
        
        
        
project "StrikeThrough"
    location "StrikeThrough"
    kind "ConsoleApp"
    language "C++"        
    cppdialect "C++20"
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
        "Strike/vendor/spdlog/include",
        "Strike/src",
        "Strike/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Strike"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "STRK_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "STRK_DEBUG"
        runtime "Debug"
        symbols "on"
            
    filter "configurations:Release"
        defines "STRK_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "STRK_DIST"
        runtime "Release"
        optimize "on"
