/**
 * FILE: timer_toolbox.h
 *
 * @author Julien Baeriswyl                (julien.baeriswyl@heig-vd.ch)
 * @author Arthur Benjamin Simon Passuello (arthur.passuello@heig-vd.ch)
 * @since  2017-03-31
 */
#ifndef ASP_A_BAERISWYL_PASSUELLO_TIMER_TOOLBOX_H_
#define ASP_A_BAERISWYL_PASSUELLO_TIMER_TOOLBOX_H_

#include "stddefs.h"

#define TIMER_TICKS_PER_MS 32

typedef ulong Time;

extern void start_timer       (void);
extern void stop_timer        (void);
extern Time read_timer_value  (void);
extern void write_timer_value (Time val);
extern Time read_timer_mtime  (void);

#endif /* ASP_A_BAERISWYL_PASSUELLO_TIMER_TOOLBOX_H_ */
