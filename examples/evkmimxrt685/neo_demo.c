/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "sct_neopixel.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define NEOPIXEL_TYPE       0
#define NEOPIXEL_NUMBER     40
#define NEOPIXEL_CH         9

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile uint32_t g_systickCounter;

/*******************************************************************************
 * Code
 ******************************************************************************/
void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t pixelData[NEOPIXEL_NUMBER];
    uint32_t i;
    uint32_t color;

    /* Init board hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Initialize NeoPixel Interface */
    sctpix_init(NEOPIXEL_TYPE);
    sctpix_addCh(NEOPIXEL_CH, pixelData, NEOPIXEL_NUMBER);
    for (i=0; i<NEOPIXEL_NUMBER; i++){
        pixelData[i]=0x080001;
    }
    sctpix_show();

    PRINTF("SCT NeoPixel Demo\r\n");

    /* Set systick reload value to generate 1ms interrupt */
    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        while (1)
        {
        }
    }

    i = 0;
    while (1)
    {
        SysTick_DelayTicks(50U);
        color = i/NEOPIXEL_NUMBER;
        color = (1&color) + ((2&color)<<16) + ((4&color)<<8);
        pixelData[i % NEOPIXEL_NUMBER] = 0;
        pixelData[(i+1) % NEOPIXEL_NUMBER] = color;
        pixelData[(i+2) % NEOPIXEL_NUMBER] = color <<1;
        pixelData[(i+3) % NEOPIXEL_NUMBER] = color <<2;
        pixelData[(i+4) % NEOPIXEL_NUMBER] = color <<3;
        pixelData[(i+5) % NEOPIXEL_NUMBER] = color <<4;
        pixelData[(i+6) % NEOPIXEL_NUMBER] = color <<2;
        pixelData[(i+7) % NEOPIXEL_NUMBER] = color ;
        sctpix_show();
        i +=1;
    }
}
