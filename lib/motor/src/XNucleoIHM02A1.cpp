/**
 ******************************************************************************
 * @file    XNucleoIHM02A1.cpp
 * @author  AST / Software Platforms and Cloud
 * @version V1.0
 * @date    November 3rd, 2015
 * @brief   Implementation file for the X_NUCLEO_IHM02A1 expansion board.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */


/* Generated with STM32CubeTOO -----------------------------------------------*/


/* Includes ------------------------------------------------------------------*/

/* ACTION 1 ------------------------------------------------------------------*
 * Include here platform specific header files.                               *
 *----------------------------------------------------------------------------*/
#include "ch.h"
#include "hal.h"
/* ACTION 2 ------------------------------------------------------------------*
 * Include here expansion board specific header files.                        *
 *----------------------------------------------------------------------------*/
#include "XNucleoIHM02A1.h"


/* Variables -----------------------------------------------------------------*/

/* Number of expansion boards. */
uint8_t XNucleoIHM02A1::number_of_boards = 0;


/* Methods -------------------------------------------------------------------*/

/**
 * @brief Constructor.
 * @param init_0        pointer to the initialization structure of the first motor.
 * @param init_1        pointer to the initialization structure of the second motor.
 * @param flag_irq      pin name of the FLAG pin of the component.
 * @param busy_irq      pin name of the BUSY pin of the component.
 * @param standby_reset pin name of the STBY\RST pin of the component.
 * @param ssel          pin name of the SSEL pin of the SPI device to be used for communication.
 * @param spi           SPI device to be used for communication.
 */
XNucleoIHM02A1::XNucleoIHM02A1(L6470_init_t *init_0, L6470_init_t *init_1, ioline_t flag_irq, ioline_t  busy_irq, ioline_t standby_reset, ioline_t ssel) 
{
    // Les pins ssel et standby_reset sont initialis??
    // comme il faut:
    
    // OLD CODE 
    // pinMode(standby_reset, OUTPUT);
    // pinMode(ssel, OUTPUT);
    // digitalWrite(ssel, HIGH);

    //NEW
    palSetLineMode(standby_reset, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(ssel, PAL_MODE_OUTPUT_PUSHPULL);
    palWriteLine(ssel, PAL_HIGH);


    // Initialisation de l'instance SPI
    // OLD
    //dev_spi->begin();
    //NEW : Nothing 


    /* Instantiating the components. */
    l6470_0 = new  L6470(flag_irq, busy_irq, standby_reset, ssel);
    l6470_1 = new L6470(flag_irq, busy_irq, standby_reset, ssel);
    components[0] = l6470_0;
    components[1] = l6470_1;

    /* Initializing the components. */
    init_components[0] = init_0;
    init_components[1] = init_1;
    if (!init()) {
        /*Do nothing*/
    }
}


/**
 * @brief Initializing the X_NUCLEO_IHM02A1 board.
 * @retval true if initialization is successful, false otherwise.
 */
bool XNucleoIHM02A1::init(void)
{
    /* Initializing the components. */
   
    /* Disable the L6470. */
    // OLD
    // digitalWrite(standby_reset, 0);
    // NEW
    palWriteLine(standby_reset, PAL_LOW);

    /* Wait for at least t_STBY,min */
    // OLD delay(1);
    chThdSleepMilliseconds(1);

    /* Enable the L6470. */
    palWriteLine(standby_reset, PAL_HIGH);

    /* Wait for at least t_logicwu */
    // OLD delay(1);
     chThdSleepMilliseconds(1);

    return (init_L6470_0() && init_L6470_1());
}


/**
 * @brief  Initialize the L6470 component.
 * @retval true if initialization is successful, false otherwise.
 */
bool XNucleoIHM02A1::init_L6470_0(void)
{
    /* Initialization. */
    if (l6470_0->init((void *) init_components[0]) != COMPONENT_OK) {
        return false;
    }

    return true;
}

/**
 * @brief  Initialize the L6470 component.
 * @retval true if initialization is successful, false otherwise.
 */
bool XNucleoIHM02A1::init_L6470_1(void)
{
    /* Initialization. */
    if (l6470_1->init((void *) init_components[1]) != COMPONENT_OK) {
        return false;
    }

    return true;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/ 
