workspace "RTS3D_RETAKE"
    configurations { "Debug", "Release" }
    startproject "RTS3D"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "RTS3D/vendor/GLFW"
    include "RTS3D/vendor/GLAD"
    include "RTS3D/vendor/glm"
    include "RTS3D/vendor/imgui"
    include "RTS3D/vendor/stb"
group ""

project "RTS3D"
    location "RTS3D"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    files {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
    }

    includedirs {
        "%{prj.name}/source",
        "%{prj.name}/vendor/GLFW/include",
        "%{prj.name}/vendor/GLAD/include",
        "%{prj.name}/vendor/glm",
        "%{prj.name}/vendor/imgui",
	    "%{prj.name}/vendor/stb",
    }

    links {
        "GLFW",
        "GLAD",
        "glm",
	    "ImGui",
	    "stb",
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
        architecture "x86_64"

        links {
            "opengl32"
        }

        defines { "_PLATFORM_WINDOWS" }

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
