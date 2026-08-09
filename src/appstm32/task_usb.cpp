#include "main.h"
#include "cmsis_os.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

#include "classes/cmdlinebuff.hpp"

#include "platform/platform.hpp"
#include "sysinfo/sysinfo.hpp"


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
void StartUSBTask(void *argument) {

    /* init code for USB_DEVICE */
    MX_USB_DEVICE_Init();

    osDelay(1500);

    VHSYSInfo::SysInfo();

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
