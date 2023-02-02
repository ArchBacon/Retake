project "stb"
	kind "StaticLib"
	language "C++"
	staticruntime "On"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"stb.cpp",
		"stb_image.h",
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