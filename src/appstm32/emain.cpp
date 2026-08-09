#include "main.h"
#include "cmsis_os.h"

#include "classes/led.hpp"

osThreadId_t defaultTaskHandle;
osThreadId_t usbTaskHandle;


const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

const osThreadAttr_t usbTask_attributes = {
  .name = "usbTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

// Tasks references
void StartDefaultTask(void *argument);
void StartUSBTask(void *argument);


// Board related
void VHBoardInit();


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    VHBoardInit();

    /* Init scheduler */
    osKernelInitialize();

    /* Create the thread(s) */
    defaultTaskHandle   = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);
    usbTaskHandle       = osThreadNew(StartUSBTask, NULL, &usbTask_attributes);

    /* Start scheduler */
    osKernelStart();

    /* We should never get here as control is now taken by the scheduler */

    /* Infinite loop */
    while (1) { }
}

// Функция задержки, устойчивая к оптимизации компилятора
void Soft_Delay(volatile uint32_t count)
{
    while (count--)
    {
        __NOP(); // Вставка ассемблерной инструкции "No Operation"
    }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {

        for(int i=0;i<5;i++) {
            Soft_Delay(1000000); VHSYSLED::On();
            Soft_Delay(1000000); VHSYSLED::Off();
        }
        
        Soft_Delay(9000000);

    }
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    #error "USE_FULL_ASSERT defined"
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
