project "glm"
	kind "StaticLib"
	language "C++"
	staticruntime "On"

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