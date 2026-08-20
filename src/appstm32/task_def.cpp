#include "main.h"
#include "cmsis_os.h"
#include "usb_device.h"

#include "classes/led.hpp"


extern USBD_HandleTypeDef hUsbDeviceFS;


/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
void StartDefaultTask(void *argument)
{

    VHSYSLED::Init();
    VHSYSLED::Off();

    /* Infinite loop */
    for(;;)
    {

        // First part
        VHSYSLED::On();     osDelay(250);
        VHSYSLED::Off();    osDelay(250);
        VHSYSLED::On();     osDelay(250);
        VHSYSLED::Off();    osDelay(250);

        if (hUsbDeviceFS.dev_state == USBD_STATE_CONFIGURED) {

            for(int i=0; i<5; i++) {
                VHSYSLED::On();     osDelay( 20);
                VHSYSLED::Off();    osDelay( 80);
            }
            

        } else {
            VHSYSLED::On();     osDelay( 20);
            VHSYSLED::Off();    osDelay(480);
            VHSYSLED::On();     osDelay( 20);
            VHSYSLED::Off();    osDelay(480);
        }

    }

}
