workspace "RTS3D_RETAKE"
    configurations { "Debug", "Release" }
    startproject "RTS3D"
    architecture "x64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "RTS3D/Vendor/GLFW"
    include "RTS3D/Vendor/GLAD"
    include "RTS3D/Vendor/glm"
    include "RTS3D/Vendor/imgui"
group ""

project "RTS3D"
    location "RTS3D"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    files {
        "%{prj.name}/Resource/**",
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
    }

    includedirs {
        "%{prj.name}/Source",
        "%{prj.name}/Vendor/GLFW/include",
        "%{prj.name}/Vendor/GLAD/include",
        "%{prj.name}/Vendor/glm",
        "%{prj.name}/Vendor/imgui",
    }

    links {
        "GLFW",
        "GLAD",
        "glm",
	    "ImGui",
    }

    defines {}

    filter "configurations:Debug"
        defines { "_DEBUG" }
        symbols "on"

    filter "configurations:Release"
        defines { "_NDEBUG" }
        optimize "on"

    filter "system:windows"
        system "windows"
        systemversion "latest"
        architecture "x64"

        links {
            "opengl32"
        }

        defines {
            "_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE",
        }

    filter "system:linux"
        system "linux"
        architecture "ARM"

        links {
            "dl",
            "pthread",
            "X11",
            "EGL",
            "GLESv2",
            "Xrandr",
            "Xcursor",
        }
        
        defines {
            "_PLATFORM_RASPBERRY",
            "GLFW_INCLUDE_ES31",
        }
