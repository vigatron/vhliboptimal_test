// xxd -cols 16 -i image.bmp > image_data.h

#include "platform/platform.hpp"
#include "vhliboptimal.hpp"
#include "srcimgdata.hpp"

#include <cstdio>

#include "example1.h"
#include "example2.h"
#include "example3.h"
#include "example4.h"
#include "example5.h"
#include "example6.h"
#include "example7.h"

static constexpr uint32_t blocksize = 33 * 1024;
static uint8_t unpacked_bmp_area[blocksize] __attribute__((aligned(4)));

static VHRLE7b rle;


/**
 * 
 */
const uint8_t *   VHTestImagesArray::memblock_data(uint16_t imgid) {

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
const uint32_t VHTestImagesArray::memblock_size(uint16_t imgid) {

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
const uint32_t VHTestImagesArray::memblock_unpacked_size(uint16_t imgid) {

    return blocksize;
}


/**
 * 
 */
uint8_t * VHTestImagesArray::TempPtr() {
    return unpacked_bmp_area;
}

/**
 * 
 */
uint32_t VHTestImagesArray::TempMaxBufferSize() {
    return blocksize;
}

/**
 * 
 */
verr VHTestImagesArray::unpack(uint16_t imageid) {

    if(!(imageid >= GetFirstID() && imageid <= GetLastID()))
        return verror(1);

    const uint8_t             * prle        = memblock_data(imageid);
    const uint32_t              blocksz     = memblock_size(imageid);
    // const VHRLE7b::sthdr      * phdr        = (const VHRLE7b::sthdr *)prle;

    uint8_t *                   ptrdst      = TempPtr();
    uint32_t                    sizedst     = TempMaxBufferSize();

    verr retunpack = rle.unpack(prle, blocksz, ptrdst, sizedst);

    if(retunpack) {
        return verrmsg(201, "Can't unpack RLE memblock");
    }

    // printf("Image #%d unpack result status: %s \n", imgid, retunpack ? "FAILED" : "OK");

    return retunpack;
}

verr VHTestImagesArray::check_memblock(uint16_t blkid) {

    if(!(blkid >= GetFirstID() && blkid <= GetLastID()))
        return verror(1);

    const uint8_t             * prle        = VHTestImagesArray::memblock_data(blkid);
    const uint32_t              blocksz     = VHTestImagesArray::memblock_size(blkid);
    const VHRLE7b::sthdr      * phdr        = (const VHRLE7b::sthdr *)prle;

    verr testrle = rle.check(prle, blocksz);
    const char * strstat = testrle ? "ERROR" : "OK";

    printf("memblock #%d:  %5d bytes  CRC=%4X / Unpacked  %5d bytes CRC=%4X  status=%s\n",
        blkid,
        (int)blocksz,
        (int)phdr->crc32rle,
        (int)phdr->srcsize,
        (int)phdr->crc32src,
        strstat );

    return testrle;
}

/**
 * 
 */
verr VHTestImagesArray::CheckIntegrity() {

    verr r = vok;

    printf("\nChecking integrity:\n");

    for(uint16_t blkid = GetFirstID(); blkid <= GetLastID(); blkid++) {
        if(check_memblock(blkid)) r = verror(1);
    }

    return r;
}

/**
 * 
 */
verr VHTestImagesArray::CheckResolutions() {

    printf("\nTest image set:\n");

    for(uint16_t blkid = GetFirstID(); blkid <= GetLastID(); blkid++) {
        
        verr result = unpack(blkid);
        int width = 0;
        int height = 0;

        if(result == vok) {
            const uint8_t * pbmphdr = VHTestImagesArray::TempPtr() + sizeof(vhliboptimal::BMPFileHeader);
            const vhliboptimal::BMPInfoHeader * phdr = (vhliboptimal::BMPInfoHeader *)pbmphdr;
            width = phdr->width;
            height = phdr->height;
        }

        uint8_t sc = GetScaller(blkid);

        printf("BMP (1-bit) B&W Image #%d: %4d x %4d (Original %4d x %4d)\n",
            blkid, width, height, width * sc, height * sc);
    }

    return vok;
}
