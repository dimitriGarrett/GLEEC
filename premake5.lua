outputdir = "%{cfg.buildcfg}"

workspace "GLEEC"
    location "bin"

    architecture "x64"

    language "C++"
    cppdialect "C++20"

    configurations
    {
        "Debug",
        "Release"
    }
 
    filter "configurations:Debug"
        defines { "GLEEC_DEBUG", "DEBUG", "_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "GLEEC_RELEASE", "NDEBUG" }
        optimize "On"

    filter {}

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin_int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
    }

    includedirs
    {
        "GLEEC",

        "deps/FREETYPE/include",
        "deps/GLFW/include",
        "deps/OPENAL/include",
        "deps/SNDFILE/include",
        "deps/STB/include",
        "deps/VULKAN/include",
    }

    filter "system:windows"
        libdirs
        {
            "deps/FREETYPE/lib",
            "deps/GLFW/lib",
            "deps/OPENAL/lib",
            "deps/SNDFILE/lib",
            "deps/VULKAN/lib",
        }

        links
        {
            "freetype",
            "glfw3dll",
            "OpenAL32",
            "sndfile",
            "shaderc_sharedd",
            "vulkan-1",
        }

    filter "system:Unix"
        links
        {
            "glfw",
            "openal",
            "sndfile",
        }

project "GLEEC"
    kind "SharedLib"

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "GLEEC_WINDOWS",
            "GLEEC_EXPORT"
        }

project "Testbed"
    kind "ConsoleApp"
        
    links { "GLEEC" }

    filter "system:windows"
 
    postbuildcommands
    {
        "{COPYFILE} " .. outputdir .. "/GLEEC/GLEEC.dll " .. outputdir .. "/%{prj.name}/GLEEC.dll",
        --"{TOUCH} dapexe.txt bin/" .. outputdir .. "/%{prj.name}",
        "{TOUCH} ../dapexe.txt",
        "{ECHO} bin/" .. outputdir .. "/%{prj.name}/%{prj.name}.exe > ../dapexe.txt",
        --"{ECHO} \"hello\"",
        "{COPYFILE} ../compile_commands/%{cfg.shortname}.json ../compile_commands.json",

        "glslang ../shaders/vert.vert -V -o ../shaders/vert.spv",
        "glslang ../shaders/frag.frag -V -o ../shaders/frag.spv",
    }
