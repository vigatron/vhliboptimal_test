#include "benchmark.hpp"

#include "main.h"

/**
 * 
 */
void VHTimeStamp::Init() {

    // 1. Включаем TRC (Trace)
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    // 2. Снимаем защиту записи в DWT (ОБЯЗАТЕЛЬНО для Cortex-M7 / F7 и H7)
    #if defined(__CORTEX_M) && (__CORTEX_M == 7U)
        DWT->LAR = 0xC5ACCE15; 
    #endif

    // 3. Обнуляем и запускаем счетчик
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    
}

/**
 * 
 */
void VHTimeStamp::Start() {
    start = DWT->CYCCNT;
}

/**
 * 
 */
void VHTimeStamp::Stop() {
    stop = DWT->CYCCNT;
}

/**
 * 
 */
uint32_t VHTimeStamp::ResultTick() {
    return start < stop ? (stop - start) : ((UINT32_MAX - start) + stop);
}
