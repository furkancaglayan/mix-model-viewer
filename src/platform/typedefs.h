#pragma once 
#if defined(SYSTEM_WIN64)
#include "windows/platform_utils.h"
#elif defined(SYSTEM_MACOSX)
#elif defined(SYSTEM_LINUX)
#endif
#include <GL/glew.h>
#include "mixAsset_folder.h"
#include "mixAsset_file.h"
#include "mixAsset_path.h"