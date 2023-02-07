project "stb"
	kind "StaticLib"
	language "C++"
	staticruntime "On"

	files {
		"stb/stb_image.h",
	}
	includedirs { "" }
	
	filter "system:windows"
		systemversion "latest"

		defines 
		{ 
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:debug"
		symbols "On"
				
	filter "configurations:release"
		optimize "On"