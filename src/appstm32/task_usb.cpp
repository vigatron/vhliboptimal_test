#include "main.h"
#include "cmsis_os.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

#include "classes/cmdlinebuff.hpp"

#include "platform/platform.hpp"
#include "sysinfo/sysinfo.hpp"
#include "testcontainer/testcontainer.hpp"


extern USBD_HandleTypeDef hUsbDeviceFS;

extern VHCommandLineBuffer cmdLine;

extern TestLibraryContainer testContainer;

void SendText(const char * txt);
void SendTextLine(const char * txt);

void execcmd();

#ifdef ITCM_TEST_ENABLED

extern uint32_t _sitcm_load;
extern uint32_t _sitcm;
extern uint32_t _eitcm;

/**
 * 
 */
void ITCMRAMTest() {

    printf("_sitcm_load=%p _sitcm=%p _eitcm=%p\n",
        &_sitcm_load, &_sitcm, &_eitcm);

    uint8_t *flash_src = (uint8_t *)&_sitcm_load;
    uint8_t *itcm_dst  = (uint8_t *)&_sitcm;
    int bsize = 64;

    printf("\nFLASH Region @ %p\n", flash_src);

    for(int i=0; i < bsize; i++) {
        if(!(i%16)) { printf("\n %4X: ", i); }
        printf("%.2X ", flash_src[i]);
    }

    printf("\n\n");

    printf("\nITCMRAM Region @ %p\n", itcm_dst);
    for(int i=0; i < bsize; i++) {
        if(!(i%16)) { printf("\n %4X: ", i); }
        printf("%.2X ", itcm_dst[i]);
    }

    printf("\n\n");
}

#endif

/**
 * 
 */
void StartUSBTask(void *argument) {

    /* init code for USB_DEVICE */
    MX_USB_DEVICE_Init();

    osDelay(1500);

    if(testContainer.Init()) {
        verrmsg(2, "VHLIBOptimalSetup() failed");
        while(1) { osDelay(1); }
    }

    // ITCMRAMTest();

    static constexpr char strWelcome []  = "Welcome!";
    printf("\n%s\n\n", strWelcome);

    for(;;) {

        printf(">"); fflush(stdout);

        while(!cmdLine.avail()) {
            osDelay(1);
        }

        execcmd();

    }
}
