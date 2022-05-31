workspace "Man520_SDL"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

outputdir = "{%cgf.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "sdl2_gameframework"
    location "sdl2_gameframework"
    kind "ConsoleApp"
    language "c++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/include/**.h"
        "%{prj.name}/sr/**.cpp"
    }

    filter "system:macOS"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "lastest"

    filter "configurations:Debug"
        symbols "On"
     
    filter "configurations:Release"
        optimize "On"

    filter "configurations:Distribution"
        optimize "On"



