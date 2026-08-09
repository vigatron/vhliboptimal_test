// xxd -cols 16 -i image.bmp > image_data.h

#include "srcimgdata.hpp"

#if VHLIBOPTIMAL_TEST_EMBEDDEDBMPID == 0

#include "example1.h"

#define EMBEDDED_EXAMPLE_DATA       example1_bmp
#define EMBEDDED_EXAMPLE_SIZE       example1_bmp_len

#else

#error "Invalid embedded bitmap ID"
// #include "example2.h"
// #include "example3.h"
// #include "example4.h"
// #include "example5.h"
// #include "example6.h"
// #include "example7.h"

#endif

uint8_t *   embedded_bmp_data() { return EMBEDDED_EXAMPLE_DATA; }

uint32_t    embedded_bmp_size() { return EMBEDDED_EXAMPLE_SIZE; }
