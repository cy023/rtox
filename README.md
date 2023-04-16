# rtox

## Description:
RTOX is an IoT development platform that uses the NUM487KM_DEVB board as its base. The project includes the FreeRTOS operating system and a driver for the SPI NOR Flash (w25q128jv) on which LittleFS is ported. The project also uses uLog for logging purposes and Ethernet for networking. The lightweight TCP/IP stack lwIP is ported, and Segger SystemView RTT is integrated for visualizing the RTOS behavior.

## Dependencies:
- NUM487KM_DEVB board
- FreeRTOS
- SPI NOR Flash (w25q128jv) driver
- LittleFS
- Ethernet PHY (DP83848)
- lwIP
- uLog
- Segger SystemView RTT

## Reference
- [NUM487KM_DEVB](https://github.com/cy023/NUM487KM_DEVB)
- [FreeRTOS-Kernel](https://github.com/FreeRTOS/FreeRTOS-Kernel)
- [W25Q128JV_HAL](https://github.com/cy023/W25Q128JV_HAL)
- [LittleFS](https://github.com/littlefs-project/littlefs)
- [lwIP](https://git.savannah.nongnu.org/cgit/lwip.git)
- [uLog](https://github.com/rdpoor/ulog)
- [SEGGER SystemView](https://www.segger.com/products/development-tools/systemview/)
