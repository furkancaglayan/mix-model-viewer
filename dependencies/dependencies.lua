
filter { "system:windows" }
    postbuildcommands { "copy ..\\..\\dependencies\\glew\\bin\\%{cfg.buildcfg}\\glew32.dll ..\\..\\bin\\%{cfg.buildcfg}\\glew32.dll" }

filter {}