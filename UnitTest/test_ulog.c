#include <stdio.h>
#include "NuMicro.h"
#include "system.h"
#include "ulog.h"

int main()
{
    int num = 23;

    system_init();
    printf("System Boot.\n");
    printf("[test]: uLog ...\n\n");

    ULOG_INIT();

    // log messages with a severity of "ALWAYS" or higher to the console.
    // The user must supply a method for console_logger.
    ULOG_SUBSCRIBE(console_logger, ULOG_ALWAYS_LEVEL);

    ULOG_ASSERT("num = %d", num);
    ULOG_ERROR("num = %d", num);
    ULOG_WARN("num = %d", num);
    ULOG_INFO("num = %d", num);
    ULOG_DEBUG("num = %d", num);
    ULOG_VERBOSE("num = %d", num);

    printf("\nNormal printf, num = %d\n", num);

    // remove a logger
    ULOG_UNSUBSCRIBE(console_logger);

    return 0;
}
