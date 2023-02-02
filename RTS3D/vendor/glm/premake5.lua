project "glm"
	kind "StaticLib"
	language "C++"
	staticruntime "On"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"glm/**.cpp",
		"glm/**.hpp",
		"glm/**.inl"
	}
	
	includedirs
	{
		"",
	}
	
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