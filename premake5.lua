workspace "Integrated Game Streaming Architecture"
architecture "x64"

configurations
{
    "Debug",
    "Release"
}



outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"



-- Middleware Static-Library Project --
project "Middleware"
    location "Middleware"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "GSA_PLATFORM_WINDOWS"
        }

        buildoptions
        {
            "/Zc:preprocessor"
        }

    filter "configurations:Debug"
        defines 
        {
            "GSA_BUILD_DEBUG"
        }

    filter "configurations:Release"
        defines 
        {
            "GSA_BUILD_RELEASE"
        }

        optimize "On"



-- Client Console-Application Project --
project "Client"
    location "Client"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Middleware/src"
    }

    links 
    {
        "Middleware",
        "opengl32.lib",
        "user32.lib",
        "gdi32.lib",
        "shell32.lib",
        "vcruntime.lib",
        "msvcrt.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "GSA_PLATFORM_WINDOWS"
        }

        buildoptions
        {
            "/Zc:preprocessor"
        }

    filter "configurations:Debug"
        defines 
        {
            "GSA_BUILD_DEBUG"
        }

    filter "configurations:Release"
        defines 
        {
            "GSA_BUILD_RELEASE"
        }

        optimize "On"



-- Server Console-Application Project --
project "Server"
    location "Server"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Middleware/src"
    }

    links 
    {
        "Middleware",
        "opengl32.lib",
        "user32.lib",
        "gdi32.lib",
        "shell32.lib",
        "vcruntime.lib",
        "msvcrt.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines 
        {
            "GSA_PLATFORM_WINDOWS"
        }

        buildoptions
        {
            "/Zc:preprocessor"
        }

    filter "configurations:Debug"
        defines 
        {
            "GSA_BUILD_DEBUG"
        }

    filter "configurations:Release"
        defines 
        {
            "GSA_BUILD_RELEASE"
        }

        optimize "On"



-- Clean Function --
newaction {
    trigger     = "clean",
    description = "Delete all intermediate build files, output files, and generated project files",
    execute     = function ()
       print("Removing intermediate build files, output files, and generated project files from the current directory...")

       os.rmdir("./.bin")
       os.rmdir("./.bin-int")

       os.remove("./Integrated Game Streaming Architecture.sln")
       os.remove("./Makefile")

       os.remove("./Middleware/Middleware.vcxproj")
       os.remove("./Middleware/Middleware.vcxproj.user")
       os.remove("./Middleware/Makefile")

       os.remove("./Client/Client.vcxproj")
       os.remove("./Client/Client.vcxproj.user")
       os.remove("./Client/Makefile")

       os.remove("./Server/Server.vcxproj")
       os.remove("./Server/Server.vcxproj.user")
       os.remove("./Server/Makefile")

       print("Directory should be clean.")
    end
 }