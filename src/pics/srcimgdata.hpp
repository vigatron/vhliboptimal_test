#pragma once

#include <cstdint>


class VHTestImagesArray {

    public:

        static const uint8_t *   embedded_bmp_data(uint16_t imgid);
        static const uint32_t    embedded_bmp_size(uint16_t imgid);

        static uint8_t         * TempPicPtr();
        static uint32_t          TempPicMaxBufferSize();

    private:

};
