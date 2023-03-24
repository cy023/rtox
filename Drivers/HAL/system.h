/**
 * @file system.h
 * @author cy023
 * @date 2023.03.20
 * @brief
 */


#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

#define PLL_CLOCK      192000000
#define SPI_FLASH_PORT SPI2

/*******************************************************************************
 * Public Function
 ******************************************************************************/
/**
 * @brief System initialization.
 *
 *  - system_gpio_init()
 *  - system_clock_init()
 *  - system_uart_init()
 *  - system_spi_init()
 */
void system_init(void);

/**
 * @brief System deinitialization.
 *
 *  - system_gpio_deinit()
 *  - system_clock_deinit()
 *  - system_uart_deinit()
 *  - system_spi_deinit()
 */
void system_deinit(void);

/**
 * @brief Delay by polling.
 * @param uint32_t ms   delay times in millisecond.
 */
void system_delay_ms(uint32_t ms);

#endif /* SYSTEM_H */
