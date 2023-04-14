#pragma once 
#if defined(SYSTEM_WIN64)
#include "windows/platform_utils.h"
#elif defined(SYSTEM_MACOSX)
#elif defined(SYSTEM_LINUX)
#endif
#include <GL/glew.h>
#include <GLFW/glfw3.h>
