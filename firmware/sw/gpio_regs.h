#ifndef GPIO_REGS_H
#define GPIO_REGS_H

#include <stdint.h>
#include "base_addr.h"

#define     GPIO_DATA_REG           0x00000000
#define     GPIO_DIR_REG            0x00000004

#if APB_GPIO_BASE_ADDR_0 != INVALID_ADDR
    #define GPIO_BASE_ADDR APB_GPIO_BASE_ADDR_0
#else
    #define GPIO_BASE_ADDR AHB_GPIO_BASE_ADDR_0
#endif

#endif

#define reg_gpio_data (*(volatile uint32_t*) (GPIO_BASE_ADDR + GPIO_DATA_REG))
#define reg_gpio_dir (*(volatile uint32_t*) (GPIO_BASE_ADDR + GPIO_DIR_REG))