#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

osThreadId_t thread1_id;

typedef struct leds 
{
  uint8_t led_id;
  uint8_t led_time;
}leds ;

void thread1(void *arg){
  uint8_t state = 0;
  struct leds *led_activated;
  led_activated = arg;
  uint8_t led_id = led_activated->led_id;
  switch (led_id)
  {
      case 1: 
        while(1)
        {
          state ^= LED1;
          LEDWrite(LED1, state);
          osDelay(led_activated->led_time);
        } 
      break;
      case 2: 
        while(1)
        {
          state ^= LED2;
          LEDWrite(LED2, state);
          osDelay(led_activated->led_time);
        }
      break;
      case 3: 
        while(1)
        {
          state ^= LED3;
          LEDWrite(LED3, state);
          osDelay(led_activated->led_time);
        }
      break;
      case 4: 
        while(1)
        {
          state ^= LED4;
          LEDWrite(LED4, state);
          osDelay(led_activated->led_time);
       }
       break;
  }    
} // thread1


void main(void){
  LEDInit(LED2 | LED1 | LED3 | LED4); 
  osKernelInitialize();

  struct leds led01, led02, led03, led04;
  
  led01.led_id =1;
  led01.led_time = 100;
  
  led02.led_id =2;
  led02.led_time = 200;
  
  led03.led_id =3;
  led03.led_time = 300;
  
  led04.led_id =4;
  led04.led_time = 400;
  
  thread1_id = osThreadNew(thread1, &led01, NULL);
  thread1_id = osThreadNew(thread1, &led02, NULL);
  thread1_id = osThreadNew(thread1, &led03, NULL);
  thread1_id = osThreadNew(thread1, &led04, NULL);


  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main
