#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

osThreadId_t thread1_id;
osThreadId_t thread2_id;
osThreadId_t thread3_id;
osThreadId_t thread4_id;

typedef struct leds 
{
  uint8_t led_id;
  uint32_t led_time;
}leds ;

void thread1(void *arg){
  uint8_t state = 0;
  struct leds *led_activated;
  led_activated = arg;
  uint8_t led = led_activated->led_id;
  while(1)
  {
    state ^= led;
    LEDWrite(led, state);
    osDelay(led_activated->led_time);
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
  
  led03.led_id =4;
  led03.led_time = 300;
  
  led04.led_id =8;
  led04.led_time = 400;
  
  thread1_id = osThreadNew(thread1, &led01, NULL);
  thread2_id = osThreadNew(thread1, &led02, NULL);
  thread3_id = osThreadNew(thread1, &led03, NULL);
  thread4_id = osThreadNew(thread1, &led04, NULL);

  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main
