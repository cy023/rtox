/*
 * FreeRTOS Kernel V10.0.0
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software. If you wish to use our
 * Amazon FreeRTOS name, please do so in a fair use way that does not cause
 * confusion.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

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

void task1()
{
    while (1) {
        PH4 ^= 1;
        vTaskDelay(MILLI_SECOND_TICK * 3000);
    }
}

void task2()
{
    while (1) {
        PH5 ^= 1;
        vTaskDelay(MILLI_SECOND_TICK * 1000);
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
/*-----------------------------------------------------------*/

// void vApplicationMallocFailedHook(void)
// {
//     /* vApplicationMallocFailedHook() will only be called if
//     configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a
//     hook function that will get called if a call to pvPortMalloc() fails.
//     pvPortMalloc() is called internally by the kernel whenever a task, queue,
//     timer or semaphore is created.  It is also called by various parts of the
//     demo application.  If heap_1.c or heap_2.c are used, then the size of the
//     heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
//     FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
//     to query the size of free heap space that remains (although it does not
//     provide information on how the remaining heap might be fragmented). */
//     taskDISABLE_INTERRUPTS();
//     for (;;)
//         ;
// }
/*-----------------------------------------------------------*/

// void vApplicationIdleHook(void)
// {
//     /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is
//     set to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the
//     idle task.  It is essential that code added to this hook function never
//     attempts to block in any way (for example, call xQueueReceive() with a
//     block time specified, or call vTaskDelay()).  If the application makes
//     use of the vTaskDelete() API function (as this demo application does)
//     then it is also important that vApplicationIdleHook() is permitted to
//     return to its calling function, because it is the responsibility of the
//     idle task to clean up memory allocated by the kernel to any task that has
//     since been deleted. */
// }
/*-----------------------------------------------------------*/

// void vApplicationStackOverflowHook(xTaskHandle pxTask, signed char
// *pcTaskName)
// {
//     (void) pcTaskName;
//     (void) pxTask;

//     /* Run time stack overflow checking is performed if
//     configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
//     function is called if a stack overflow is detected. */
//     taskDISABLE_INTERRUPTS();
//     for (;;)
//         ;
// }
/*-----------------------------------------------------------*/

// void vApplicationTickHook(void)
// {
//     /* This function will be called by each tick interrupt if
//     configUSE_TICK_HOOK is set to 1 in FreeRTOSConfig.h.  User code can be
//     added here, but the tick hook is called from an interrupt context, so
//     code must not attempt to block, and only the interrupt safe FreeRTOS API
//     functions can be used (those that end in FromISR()).  */

// #if (mainCREATE_SIMPLE_BLINKY_DEMO_ONLY == 0)
//     {
//         /* In this case the tick hook is used as part of the queue set test.
//         */
//         // FIXME
//         // vQueueSetAccessQueueSetFromISR();
//     }
// #endif /* mainCREATE_SIMPLE_BLINKY_DEMO_ONLY */
// }
