#pragma once

#include <cstdint>
#include "vhlibrle7b.hpp"

class VHTestImagesArray {

    public:

        static int               GetFirstID() { return 1; }
        static int               GetLastID () { return 7; }

        static const uint8_t *   memblock_data(uint16_t imgid);
        static const uint32_t    memblock_size(uint16_t imgid);
        static const uint32_t    memblock_unpacked_size(uint16_t imgid);

        static uint8_t         * TempPtr();
        static uint32_t          TempMaxBufferSize();

        static verr              CheckIntegrity();
        static verr              CheckResolutions();

        static verr              unpack(uint16_t blkid);

    private:

        static verr             check_memblock(uint16_t id);
};
