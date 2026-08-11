// xxd -cols 16 -i image.bmp > image_data.h

#include "srcimgdata.hpp"

#include "example1.h"
#include "example2.h"
#include "example3.h"
#include "example4.h"
#include "example5.h"
#include "example6.h"
#include "example7.h"

static constexpr uint32_t blocksize = 33 * 1024;
static uint8_t unpacked_bmp_area[blocksize] __attribute__((aligned(4)));


/**
 * 
 */
const uint8_t *   VHTestImagesArray::embedded_bmp_data(uint16_t imgid) {

    switch(imgid) {
        case 1: return example1_vhrle; break;
        case 2: return example2_vhrle; break;
        case 3: return example3_vhrle; break;
        case 4: return example4_vhrle; break;
        case 5: return example5_vhrle; break;
        case 6: return example6_vhrle; break;
        case 7: return example7_vhrle; break;
        default: { }
    }

    return example1_vhrle;
}

/**
 * 
 */
const uint32_t VHTestImagesArray::embedded_bmp_size(uint16_t imgid) {

    switch(imgid) {
        case 1: return example1_vhrle_len; break;
        case 2: return example2_vhrle_len; break;
        case 3: return example3_vhrle_len; break;
        case 4: return example4_vhrle_len; break;
        case 5: return example5_vhrle_len; break;
        case 6: return example6_vhrle_len; break;
        case 7: return example7_vhrle_len; break;
        default: { }
    }

    return example1_vhrle_len;
}

/**
 * 
 */
uint8_t * VHTestImagesArray::TempPicPtr() {
    return unpacked_bmp_area;
}

/**
 * 
 */
uint32_t VHTestImagesArray::TempPicMaxBufferSize() {
    return blocksize;
}
