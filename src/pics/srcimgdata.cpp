// xxd -cols 16 -i image.bmp > image_data.h

#include "srcimgdata.hpp"

#ifndef VHLIBOPTIMAL_TEST_EMBEDDEDBMPID
#error "Please specify embedded bitmap ID"
#endif


#if VHLIBOPTIMAL_TEST_EMBEDDEDBMPID == 1
#include "example1.h"
#define EMBEDDED_EXAMPLE_DATA       example1_bmp
#define EMBEDDED_EXAMPLE_SIZE       example1_bmp_len

#elif VHLIBOPTIMAL_TEST_EMBEDDEDBMPID == 2
#include "example2.h"
#define EMBEDDED_EXAMPLE_DATA       example2_bmp
#define EMBEDDED_EXAMPLE_SIZE       example2_bmp_len

#elif VHLIBOPTIMAL_TEST_EMBEDDEDBMPID == 3
#include "example3.h"
#define EMBEDDED_EXAMPLE_DATA       example3_bmp
#define EMBEDDED_EXAMPLE_SIZE       example3_bmp_len

#elif VHLIBOPTIMAL_TEST_EMBEDDEDBMPID == 4
#include "example4.h"
#define EMBEDDED_EXAMPLE_DATA       example4_bmp
#define EMBEDDED_EXAMPLE_SIZE       example4_bmp_len

#elif VHLIBOPTIMAL_TEST_EMBEDDEDBMPID == 5
#include "example5.h"
#define EMBEDDED_EXAMPLE_DATA       example5_bmp
#define EMBEDDED_EXAMPLE_SIZE       example5_bmp_len

#elif VHLIBOPTIMAL_TEST_EMBEDDEDBMPID == 6
#include "example6.h"
#define EMBEDDED_EXAMPLE_DATA       example6_bmp
#define EMBEDDED_EXAMPLE_SIZE       example6_bmp_len

#elif VHLIBOPTIMAL_TEST_EMBEDDEDBMPID == 7
#include "example7.h"
#define EMBEDDED_EXAMPLE_DATA       example7_bmp
#define EMBEDDED_EXAMPLE_SIZE       example7_bmp_len

#else

#error "Invalid embedded bitmap ID"

#endif

const uint8_t *   embedded_bmp_data() { return EMBEDDED_EXAMPLE_DATA; }

const uint32_t    embedded_bmp_size() { return EMBEDDED_EXAMPLE_SIZE; }
