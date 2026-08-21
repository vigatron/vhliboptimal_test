#include "timer/vhtimerstamp.hpp"

#ifdef VHPLATFORM_PC

void VHTimerStamp::start() {
    clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
}

void VHTimerStamp::stop() {
    clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
}

long long VHTimerStamp::result_us() {
    long nsec = end_time.tv_nsec - start_time.tv_nsec;
    long long elapsed = (end_time.tv_sec - start_time.tv_sec) * 1000000000LL + nsec;
    elapsed /= 1000LL;
    return elapsed;
}

long long VHTimerStamp::result_ms() {
    long nsec = end_time.tv_nsec - start_time.tv_nsec;
    long long elapsed = (end_time.tv_sec - start_time.tv_sec) * 1000000000LL + nsec;
    elapsed /= 1000000LL;
    return elapsed;
}

#endif

#ifdef VHPLATFORM_ESP32

void VHTimerStamp::start() {
    _start = esp_timer_get_time();
}

void VHTimerStamp::stop() {
    _stop = esp_timer_get_time();
}

uint32_t VHTimerStamp::result_us() {
    return _stop - _start;
}

uint32_t VHTimerStamp::result_ms() {
    return (_stop - _start) / 1000;
}

#endif


#ifdef VHPLATFORM_STM32

#include "main.h"

/**
 * 
 */
// void VHTimerStamp::init() {

//     #if defined(__CORTEX_M) && (__CORTEX_M == 7U)
//     // 1. Включаем тактирование отладочного блока DBGMCU напрямую через регистр
//     DBGMCU->CR |= DBGMCU_CR_DBG_SLEEP | DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_STANDBY;
//     #endif

//     // 1. Включаем TRC (Trace)
//     CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

//     // 2. Снимаем защиту записи в DWT (ОБЯЗАТЕЛЬНО для Cortex-M7 / F7 и H7)
//     #if defined(__CORTEX_M) && (__CORTEX_M == 7U)
//         #ifndef DWT_LAR_KEY
//         #define DWT_LAR_KEY 0xC5ACCE55U
//         #endif

//         DWT->LAR = DWT_LAR_KEY;
//     #endif

//     // 3. Обнуляем и запускаем счетчик
//     DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;
//     DWT->CYCCNT = 0;
//     DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
// }

/**
 * 
 */
void VHTimerStamp::init() {

    // 1. Включение отладки в режимах пониженного энергопотребления
    #if defined(STM32H7) || defined(STM32H750xx)
        // Для STM32H7 используем доменные регистры DBGMCU
        DBGMCU->CR |= DBGMCU_CR_DBG_SLEEPD1 | DBGMCU_CR_DBG_STOPD1 | DBGMCU_CR_DBG_STANDBYD1;
    #elif defined(__CORTEX_M) && (__CORTEX_M == 7U)
        // Для STM32F7 и других Cortex-M7
        DBGMCU->CR |= DBGMCU_CR_DBG_SLEEP | DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_STANDBY;
    #endif

    // 2. Включаем TRC (Trace)
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

    // 3. Разблокировка DWT (Lock Access Register)
    #if defined(__CORTEX_M) && (__CORTEX_M == 7U)
        #ifndef DWT_LAR_KEY
        #define DWT_LAR_KEY 0xC5ACCE55U
        #endif

        DWT->LAR = DWT_LAR_KEY;
    #endif

    // 4. Сброс и запуск счетчика циклов DWT CYCCNT
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/**
 * 
 */
void VHTimerStamp::start() {
    _start = DWT->CYCCNT;
}

/**
 * 
 */
void VHTimerStamp::stop() {
    _stop = DWT->CYCCNT;
}

/**
 * 
 */
uint32_t VHTimerStamp::result_ticks() {
    return _start <= _stop ? (_stop - _start) : ((UINT32_MAX - _start) + _stop);
}

/**
 * 
 */
uint32_t VHTimerStamp::result_us() {
    uint32_t timer_clks = result_ticks();
    unsigned int timer_us = timer_clks / (SystemCoreClock / 1000000.0f);
    return timer_us;
}

/**
 * 
 */
uint32_t VHTimerStamp::result_ms() {
    return result_us() / 1000;
}

#endif

