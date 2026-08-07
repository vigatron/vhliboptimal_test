#pragma once

#include "vhplatform.hpp"
#include "version_vhplatform.h"

#include "vhliboptimal.hpp"
#include "version_vhliboptimal.h"

#if VHLIB_PLATFORM_VERSION_MAJOR != 0 || VHLIB_PLATFORM_VERSION_MINOR != 4
#error "Depends on vhlibplatform library"
#endif

#if VHLIB_OPTIMAL_VERSION_MAJOR !=0 || VHLIB_OPTIMAL_VERSION_MINOR != 8
#error "Depends on vhliboptimal library"
#endif
