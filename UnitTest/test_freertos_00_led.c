#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "timers.h"

/* Hardware and starter kit includes. */
#include "NuMicro.h"
#include "system.h"

#define MILLI_SECOND_TICK (configTICK_RATE_HZ / 1000)

/*-----------------------------------------------------------*/

void task1()
{
    while (1) {
        PH4 ^= 1;
        vTaskDelay(MILLI_SECOND_TICK * 2000);
    }
}

void task2()
{
    while (1) {
        PH5 ^= 1;
        vTaskDelay(MILLI_SECOND_TICK * 3000);
    }
}

/*-----------------------------------------------------------*/

int main(void)
{
    system_init();

    xTaskCreate(task1, "task1", 256, NULL, tskIDLE_PRIORITY + 2, NULL);
    xTaskCreate(task2, "task2", 256, NULL, tskIDLE_PRIORITY + 1, NULL);

    printf("FreeRTOS is starting ...\n");

    /* Start the scheduler. */
    vTaskStartScheduler();

    for (;;)
        ;
}
