project "ImGui"
	kind "StaticLib"
	language "C++"
	staticruntime "On"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
        "**.h",
        "**.cpp",
		"backends/imgui_impl_glfw.cpp",
		"backends/imgui_impl_opengl3.cpp",
	}

    includedirs {
		"",
        "%{wks.location}/RTS3D/vendor/GLFW/include",
        "%{wks.location}/RTS3D/vendor/GLAD/include",
    }

    links {
        "GLFW",
        "GLAD",
    }
	
	filter "system:windows"
		systemversion "latest"

		defines  { 
			"_CRT_SECURE_NO_WARNINGS",
            "IMGUI_IMPL_OPENGL_LOADER_GLAD",
		}

	filter "configurations:debug"
		symbols "On"
				
	filter "configurations:release"
		optimize "On"
