-- premake5.lua
workspace "ImLuaGui"
    location "build"
    configurations { "Debug", "Release" }

project "ImLuaGui"
    location "build"
    kind "ConsoleApp"
    language "C++"
    architecture ("x86_64")
    targetdir "build/%{cfg.buildcfg}"
    debugdir "%{prj.location}/.."
    cppdialect "C++17"

    files {
        "src/**.h",
        "src/**.cpp",
        "imgui/imgui.h",
        "imgui/imgui.cpp",
        "imgui/imgui_draw.cpp",
        "imgui/imgui_tables.cpp",
        "imgui/imgui_widgets.cpp",
        "imgui/backends/imgui_impl_dx11.cpp",
        "imgui/backends/imgui_impl_win32.cpp"
    }

    includedirs {
        "imgui",
        "imgui/backends",
        "lua/include",
        "sol",
    }

    libdirs {
        "lua",
        "$(DXSDK_DIR)/Lib/x86"
    }
    links {
        "lua54.lib",
        "d3d11.lib",
        "d3dcompiler.lib",
        "dxgi.lib"
    }

    postbuildcommands {
        "{COPYFILE} %[lua/*.lib] %[%{!cfg.targetdir}]",
        "{COPYFILE} %[lua/*.dll] %[%{!cfg.targetdir}]",
    }
    
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"