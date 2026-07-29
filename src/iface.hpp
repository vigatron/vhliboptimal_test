#pragma once

#include "vhplatform.hpp"

void IFACE_OPTIMAL_GetLinePixels(
    void *userData,
    uint8_t *dstptr,
    uint16_t bytescnt,
    uint16_t srcid,
    uint16_t srcx,
    uint16_t srcy
);

void IFACE_OPTIMAL_Border(
    void *userData,
    uint8_t cmd,
    uint8_t dirh, 
    uint8_t dirv,
    uint16_t cellx,
    uint16_t celly, 
    uint16_t imgx,
    uint16_t imgy
);

void IFACE_OPTIMAL_Content(
    void *userData,
    uint32_t cell1,
    uint32_t cell2,
    uint8_t dir
);

void IFACE_OPTIMAL_Benchmark(
    void *userData,
    int cmd,
    int param
);
