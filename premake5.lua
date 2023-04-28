project "rk-integrator"
   language "C++"
   cppdialect "C++17"
   filter "system:macosx"
      buildoptions {"-Wall", "-Wextra", "-Wpedantic", "-Wconversion", "-Wno-unused-parameter"}
   filter{}

   pchheader "rk/pch.hpp"
   pchsource "src/pch.cpp"
   
   staticruntime "off"
   kind "StaticLib"

   targetdir("bin/" .. outputdir)
   objdir("build/" .. outputdir)

   files {"src/**.cpp", "include/**.hpp"}

   includedirs "../**/include"