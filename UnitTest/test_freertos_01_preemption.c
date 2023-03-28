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

void usart_putc(char data)
{
    UART_Write(UART0, (uint8_t *) &data, 1);
}

void usart_puts(char *string)
{
    for (; *string != '\0'; string++) {
        usart_putc(*string);
    }
}

/*-----------------------------------------------------------*/

void task1()
{
    while (1) {
        usart_puts("Here is task1\r\n");
        // taskYIELD();
        // vTaskDelay(MILLI_SECOND_TICK * 100);
    }
}

void task2()
{
    while (1) {
        usart_puts("Here is task2\r\n");
        // taskYIELD();
        // vTaskDelay(MILLI_SECOND_TICK * 100);
    }
}

/*-----------------------------------------------------------*/

int main(void)
{
    system_init();

    BaseType_t res;

    res = xTaskCreate(task1, "task1", 256, NULL, tskIDLE_PRIORITY + 1, NULL);
    configASSERT(res == pdPASS);
    res = xTaskCreate(task2, "task2", 256, NULL, tskIDLE_PRIORITY + 1, NULL);
    configASSERT(res == pdPASS);

    printf("FreeRTOS is starting ...\n");

    /* Start the scheduler. */
    vTaskStartScheduler();

    for (;;)
        ;
}
