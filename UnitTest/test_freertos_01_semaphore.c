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
SemaphoreHandle_t usart_semaphore;

/*-----------------------------------------------------------*/

void usart_putc(char data)
{
    UART_Write(UART0, (uint8_t *) &data, 1);
}

void usart_puts(char *string)
{
    xSemaphoreTake(usart_semaphore, portMAX_DELAY);

    for (; *string != '\0'; string++) {
        usart_putc(*string);
    }

    xSemaphoreGive(usart_semaphore);
}

/*-----------------------------------------------------------*/

void task1()
{
    while (1) {
        usart_puts("Here is task1\r\n");
        // vTaskDelay(MILLI_SECOND_TICK * 1000);
    }
}

void task2()
{
    while (1) {
        usart_puts("Here is task2\r\n");
        // vTaskDelay(MILLI_SECOND_TICK * 1000);
    }
}

/*-----------------------------------------------------------*/

int main(void)
{
    system_init();

    usart_semaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(usart_semaphore);

    xTaskCreate(task1, "task1", 256, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(task2, "task2", 256, NULL, tskIDLE_PRIORITY + 1, NULL);

    printf("FreeRTOS is starting ...\n");

    /* Start the scheduler. */
    vTaskStartScheduler();

    for (;;)
        ;
}
