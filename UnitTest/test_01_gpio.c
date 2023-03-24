/**
 * @file test_01_gpio.c
 * @author cy023
 * @date 2023.03.20
 * @brief
 *
 */

#include <stdio.h>
#include "NuMicro.h"
#include "system.h"

int main()
{
    system_init();
    printf("System Boot.\n");
    printf("[test01]: gpio ...\n");

    while (1) {
        PH4 ^= 1;
        PH5 ^= 1;
        system_delay_ms(1000);
    }
    return 0;
}
