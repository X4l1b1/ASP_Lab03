/**
 * FILE: gpio_toolbox.c
 * 
 * @author Julien Baeriswyl                (julien.baeriswyl@heig-vd.ch)
 * @author Arthur Benjamin Simon Passuello (arthur.passuello@heig-vd.ch)
 * @since  2017-03-07
 */
#include "gpio_toolbox.h"

#include "gpio.h"
#include "students_tools.h"

#include "timer_toolbox.h"

static GPIOBus module_list[] =
{
    GPIO_MOD1_BASE_ADD,
    GPIO_MOD2_BASE_ADD,
    GPIO_MOD3_BASE_ADD,
    GPIO_MOD4_BASE_ADD,
    GPIO_MOD5_BASE_ADD,
    GPIO_MOD6_BASE_ADD,
};

#define GPIO_TB_MOD_REG(module, offset) (volatile GPIOBus*)(module_list[module - 1] + offset)

void SetOutput (GPIOModule module, GPIOBus bitmask)
{
    /* DONE in step 2 */
    *GPIO_TB_MOD_REG(module, OMAP_GPIO_SETDATAOUT) |= bitmask;
}

void ClearOutput (GPIOModule module, GPIOBus bitmask)
{
    /* DONE in step 2 */
    *GPIO_TB_MOD_REG(module, OMAP_GPIO_CLEARDATAOUT) |= bitmask;
}

GPIOSignal ReadInput (GPIOModule module, GPIOBus bitmask)
{
    /* DONE in step 2 */
    return *GPIO_TB_MOD_REG(module, OMAP_GPIO_DATAIN) & bitmask ? 1 : 0;
}

void ToggleOutput (GPIOModule module, GPIOBus bitmask)
{
    /* DONE in step 2 */
    *GPIO_TB_MOD_REG(module, OMAP_GPIO_DATAOUT) ^= bitmask;
}

void UnmaskIRQ (GPIOModule module, GPIOBus bitmask)
{
    /* DONE in step 3 */
    *GPIO_TB_MOD_REG(module, OMAP_GPIO_IRQENABLE1) &= ~bitmask;
}

void MaskIRQ (GPIOModule module, GPIOBus bitmask)
{
    /* DONE in step 3 */
    *GPIO_TB_MOD_REG(module, OMAP_GPIO_IRQENABLE1) |= bitmask;
}

#undef GPIO_TB_MOD_REG
