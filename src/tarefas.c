#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

osThreadId_t thread1_id, thread2_id;

typedef struct leds 
{
  uint8_t led_id;
  uint8_t led_time;
}leds ;

void thread1(void *arg){
  uint8_t state = 0;
  struct leds *led_activated;
  led_activated = arg;
  if (led_activated->led_id == 1)
    while(1){
      state ^= LED1;
      LEDWrite(LED1, state);
      osDelay(led_activated->led_time);
    } // while
  else
    while(1){
      state ^= LED2;
      LEDWrite(LED2, state);
      osDelay(led_activated->led_time);
    } // while
    
} // thread1


void main(void){
  LEDInit(LED2 | LED1); 
  osKernelInitialize();

  struct leds led01;
  struct leds led02;
  
  led01.led_id =1;
  led01.led_time = 100;
  
  led02.led_id =2;
  led02.led_time = 200;
  
  thread1_id = osThreadNew(thread1, &led01, NULL);
  thread1_id = osThreadNew(thread1, &led02, NULL);


  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main
