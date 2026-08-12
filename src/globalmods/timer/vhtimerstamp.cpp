#include "vhtimerstamp.hpp"



#ifdef VHPLATFORM_PC

VHTimerStamp::VHTimerStamp() {

}

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



#ifdef VHPLATFORM_STM32

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


#endif

