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

    targetdir("bin/%{cfg.buildcfg}")

    files
    {
        "../../../engine/**.h",
        "../../../engine/**.cpp",
    }
    
    libdirs { "libs", "../../../lib" }
    libdirs { "libs", "../../../lib/entt/include" }
    libdirs { "libs", "../../../lib/spdlog/include" }
    libdirs { "libs", "../../../lib/stb"}
    libdirs { "libs", "../../../lib/glm"}
    libdirs { "libs", "../../../lib/glad/include"}
    libdirs { "libs", "../../../lib/imgui"}
    libdirs {"libs", "../../../../../../../Library/Frameworks/SDL2.framework" }
    
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



