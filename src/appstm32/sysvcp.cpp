#include "main.h"
#include "cmsis_os.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

#include "classes/cmdlinebuff.hpp"


extern USBD_HandleTypeDef hUsbDeviceFS;

extern VHCommandLineBuffer cmdLine;


static constexpr char strnl [] = { 0x0A, 0x0D, 0x00};


/**
 * Redirect printf to USBs
 */
extern "C" int _write(int file, char *ptr, int len) {

    while(hUsbDeviceFS.dev_state != USBD_STATE_CONFIGURED) { osDelay(1); }

    USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
    while(hcdc->TxState != 0) {
        osDelay(1); 
    }

    CDC_Transmit_FS((uint8_t *)ptr, len);
    return len;
}

/**
 * 
 */
void SendText(const char * txt) {

    while(hUsbDeviceFS.dev_state != USBD_STATE_CONFIGURED) { osDelay(1); }

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
uint32_t verrmsg(int x, const char * txt) {
    printf("verrmsg: %s code=%d\n", txt, x);
    return x;
}


/**
 * 
 */
extern "C" void BRIDGE_CDC_Receive_FS(uint8_t* Buf, uint32_t *Len) {

    for(uint32_t i=0; i < *Len; i++ ) {
        cmdLine.add(Buf[i]);
        if(*(Buf+i) != 0x0D)
            CDC_Transmit_FS(Buf + i, 1);
    }

}

