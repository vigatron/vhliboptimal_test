#pragma once

#include <cstdint>
#include "vhlibrle7b.hpp"

class VHTestImagesArray
{

public:
    static int GetFirstID() { return 1; }
    static int GetLastID() { return 7; }

    static const uint8_t *memblock_data(uint16_t imgid);
    static uint32_t memblock_size(uint16_t imgid);

    static verr CheckIntegrity();

    static verr unpack(uint16_t blkid, uint8_t * dstptr, uint16_t dstszmax);

    static uint16_t minRequiredBufferSize() { return 33 * 1024; }

    static uint8_t GetScaller(uint16_t imgid)
    {

        switch (imgid)
        {
        case 1:
            return 8;
        case 2:
            return 8;
        case 3:
            return 4;
        case 4:
            return 4;
        case 5:
            return 2;
        case 6:
            return 2;
        case 7:
            return 4;
        }
        return 0;
    }

    static verr check_memblock(uint16_t id);
    
private:



};
