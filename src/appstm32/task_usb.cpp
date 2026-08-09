#include "main.h"
#include "cmsis_os.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

#include "classes/cmdlinebuff.hpp"

#include "version_vhliboptimal.h"
#include "platform/platform.hpp"


// --- Двухэтапный макрос для превращения любого токена в строку ---
#define STRINGIFY_NX(a)         #a
#define STRINGIFY(a)            STRINGIFY_NX(a)

#define BUILD_TARGET_STR        STRINGIFY(BUILD_TARGET_NAME)

static constexpr char strWelcome        []  = "Welcome!";

extern USBD_HandleTypeDef hUsbDeviceFS;

extern VHCommandLineBuffer cmdLine;

void SendText(const char * txt);
void SendTextLine(const char * txt);

void execcmd();

//
verr VHLIBOptimalSetup();


/**
 * 
 */
static void SysInfo() {

    printf("\r\n\n");
    printf("-------------------------------------------------\n");
    printf("Application  : VHLIBOptimal_test\n");
    printf("Platform     : %s\n", BUILD_TARGET_STR);
    printf("VHLIBOptimal : v%d.%d.%d\n",
        VHLIB_OPTIMAL_VERSION_MAJOR,
        VHLIB_OPTIMAL_VERSION_MINOR,
        VHLIB_OPTIMAL_VERSION_PATCH);
    printf("-------------------------------------------------\n");

}

/**
 * 
 */
void StartUSBTask(void *argument) {

    /* init code for USB_DEVICE */
    MX_USB_DEVICE_Init();

    osDelay(1500);

    SysInfo();

    if(VHLIBOptimalSetup()) {
        verrmsg(103, "VHLIBOptimalSetup() failed!");
        while(1) { osDelay(1); }
    }

    printf("\n%s\n\n", strWelcome);

    for(;;) {

        printf(">"); fflush(stdout);

        while(!cmdLine.avail()) {
            osDelay(1);
        }

        execcmd();

    }
}
