#pragma once

#include <cstdint>

class VHTimeStamp {

    public:

        static void Init();
        void Start();
        void Stop();
        uint32_t ResultTick();

    private:
        uint32_t start;
        uint32_t stop;
};