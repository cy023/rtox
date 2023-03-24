/**
 * @file test_00_uart.c
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
    printf("[test00]: uart ...\n");

    char c;
    while (1) {
        printf("Please input a character: \n");
        scanf("%c", &c);
        printf("Your input character is %c\n\n", c);
    }
    return 0;
}
