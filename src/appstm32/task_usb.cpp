#include "main.h"
#include "cmsis_os.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

#include "classes/cmdlinebuff.hpp"


extern USBD_HandleTypeDef hUsbDeviceFS;

VHCommandLineBuffer cmdLine;

static constexpr char strWelcome        []  = "Welcome";

static constexpr char strlineInfo       []  = "Processing System Info ...";
static constexpr char strlineExec       []  = "Starting test ...";
static constexpr char strlineMem        []  = "MEM@XXXX";

static constexpr char strlineUnknown    []  = "? Unknown command";
static constexpr char strlinePrompt     []  = ">";
static constexpr char strnl             []  = {0x0D, 0x0A, 0x00};


bool flagPacketAvail = false;

/**
 * 
 */
void SendText(const char * txt) {

    while(hUsbDeviceFS.dev_state != USBD_STATE_CONFIGURED) {
        osDelay(1);
    }

    USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
    while(hcdc->TxState != 0) {
        osDelay(1); 
    }

    size_t slen = strlen(txt);
    CDC_Transmit_FS((uint8_t *)txt, slen);
}

/**
 * 
 */
void SendTextLine(const char * txt) {

    SendText(txt);
    SendText(strnl);
}

/**
 * 
 */
void execcmd() {

    SendText(strnl);

    // 
    if(cmdLine.iscmd(VHCommandLineBuffer::cmdi))        { 
        SendTextLine(strlineInfo);
    } else if(cmdLine.iscmd(VHCommandLineBuffer::cmde)) {
        SendTextLine(strlineExec);
    } else if(cmdLine.iscmd(VHCommandLineBuffer::cmdm)) {
        SendTextLine(strlineMem);
    } else if(!cmdLine.data()[0]) {
        // Empty line
    } else {
        SendTextLine(strlineUnknown);
    }

    cmdLine.reset();
    SendText(strlinePrompt);

}

/**
 * 
 */
extern "C" void BRIDGE_CDC_Receive_FS(uint8_t* Buf, uint32_t *Len) {

    for(uint32_t i=0; i < *Len; i++ ) {
        
        cmdLine.add(Buf[i]);
        if(cmdLine.avail()) {
            flagPacketAvail = true;
        } else {
            CDC_Transmit_FS(Buf + i, 1);
        }
    }

}

/**
 * 
 */
void StartUSBTask(void *argument) {

    /* init code for USB_DEVICE */
    MX_USB_DEVICE_Init();

    osDelay(1500);

    SendText(strWelcome);
    SendText(strnl);
    SendText(strlinePrompt);

    for(;;) {

        osDelay(1);

        if (hUsbDeviceFS.dev_state != USBD_STATE_CONFIGURED) 
            continue;

        if(flagPacketAvail) {
            execcmd();
            flagPacketAvail = false;
        }

    }
}
