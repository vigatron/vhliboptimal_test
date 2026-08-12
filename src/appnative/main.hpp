#pragma once

#include "vhplatform.hpp"
#include "version_vhplatform.h"

#include "vhliboptimal.hpp"
#include "version_vhliboptimal.h"

#include "version_vhlibrle7b.h"

#if VHLIB_PLATFORM_VERSION_HEX < 400
#error "Depends on vhlibplatform library"
#endif

#if VHLIB_OPTIMAL_VERSION_HEX < 800
#error "Depends on vhliboptimal library"
#endif

#if VHLIB_RLE7B_VERSION_HEX < 4
#error "Depends on vhlibrle7b library"
#endif
