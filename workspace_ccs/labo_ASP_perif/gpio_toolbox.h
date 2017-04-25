/*
 * gpio_toolbox.h
 *
 *  Created on: 22 mars 2012
 *  Author: Evangelina Lolivier-Exler
 *  prototypes for GPIO access
 */

/**
 * FILE: gpio_toolbox.h
 * 
 * @author Julien Baeriswyl                (julien.baeriswyl@heig-vd.ch)
 * @author Arthur Benjamin Simon Passuello (arthur.passuello@heig-vd.ch)
 * @since  2017-03-07
 */

#ifndef GPIO_TOOLBOX_H_
#define GPIO_TOOLBOX_H_

#include "stddefs.h"
#include "students_tools.h"

/* Type definition to treat GPIO  */
typedef ulong GPIOBus;
typedef uchar GPIOPin;
typedef uchar GPIOSignal;
typedef uchar GPIOModule;

struct GPIODetect
{
    GPIOModule module;
    GPIOPin    pin;
    GPIOSignal now,
               past;
};

/* Macro to manipulate GPIO event detector */
#define GPIO_DETECT_INIT(m,p) (struct GPIODetect){.module = (m), .pin = (p), .now = ReadInput((m), BIT(p)), .past = 0}
#define GPIO_DETECT_SAVE(obj) ((obj).past = (obj).now, (obj).now = ReadInput((obj).module, BIT((obj).pin)))
#define GPIO_DETECT_SAME(obj) ((obj).past) == (obj).now)
#define GPIO_DETECT_RISE(obj) ((obj).past  <  (obj).now)
#define GPIO_DETECT_FALL(obj) ((obj).past  >  (obj).now)

/* Read / Write to GPIO */
extern void       SetOutput    (GPIOModule module, GPIOBus bitmask);
extern void       ClearOutput  (GPIOModule module, GPIOBus bitmask);
extern GPIOSignal ReadInput    (GPIOModule module, GPIOBus bitmask);
extern void       ToggleOutput (GPIOModule module, GPIOBus bitmask);
extern void       UnmaskIRQ    (GPIOModule module, GPIOBus bitmask);
extern void       MaskIRQ      (GPIOModule module, GPIOBus bitmask);

#endif /* GPIO_TOOLBOX_H_ */
