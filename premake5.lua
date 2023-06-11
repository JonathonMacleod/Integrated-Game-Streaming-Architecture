workspace "Integrated Game Streaming Architecture"
architecture "x64"

configurations
{
    "Debug",
    "Release"
}



outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"



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

    links 
    {
        "opengl32.lib",
        "user32.lib",
        "gdi32.lib",
        "shell32.lib",
        "vcruntime.lib",
        "msvcrt.lib"
    }

    includedirs
    {
        "libs/spdlog-v1-11-0/include"
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
        libdirs {
            "libs/spdlog-v1-11-0/libs/Debug"
        }

        defines 
        {
            "GSA_BUILD_DEBUG"
        }

    filter "configurations:Release"
        libdirs {
            "libs/spdlog-v1-11-0/libs/Release"
        }

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