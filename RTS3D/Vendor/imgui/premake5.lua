project "ImGui"
	kind "StaticLib"
	language "C++"
	staticruntime "On"
	
	files {
        "**.h",
        "**.cpp",
	}

    includedirs {
		"",
        "%{wks.location}/RTS3D/Vendor/GLFW/include",
        "%{wks.location}/RTS3D/Vendor/GLAD/include",
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
