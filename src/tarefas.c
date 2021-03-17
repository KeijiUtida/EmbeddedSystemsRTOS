#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

osThreadId_t thread1_id, thread2_id;

void thread1(void *arg){
  uint8_t state = 0;
  if (arg == NULL)
    while(1){
      state ^= LED1;
      LEDWrite(LED1, state);
      osDelay(100);
    } // while
  else
    while(1){
      state ^= LED2;
      LEDWrite(LED2, state);
      osDelay(100);
    } // while
    
} // thread1


void main(void){
  LEDInit(LED2 | LED1); 
  osKernelInitialize();
  uint32_t led02[1];
  
  thread1_id = osThreadNew(thread1, NULL, NULL);
  thread1_id = osThreadNew(thread1, &led02, NULL);


  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main
