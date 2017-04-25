/* ----------------------------------------------------------------------
  Institut ReDS - HEIG-VD Yverdon-les-Bains
 ------------------------------------------------------------------------

 Date   : 17/09/2008
 Modified: 24/05/2012 REPTAR board adaptation
 Description : LCD toolbox
 -----------------------------------------------------------------------
*/

/**
 * FILE: timer_toolbox.c
 *
 * @author Julien Baeriswyl                (julien.baeriswyl@heig-vd.ch)
 * @author Arthur Benjamin Simon Passuello (arthur.passuello@heig-vd.ch)
 * @since  2017-03-31
 */
#include "timer_toolbox.h"
#include "timer.h"
#include "bits.h"

void start_timer (void)
{
    /* DONE in step 4 */
    GPT1_REG(TCLR) |= BIT0;
}

void stop_timer (void)
{
    /* DONE in step 4 */
    GPT1_REG(TCLR) &= ~BIT0;
}

Time read_timer_value (void)
{
    /* DONE in step 4 */
    return GPT1_REG(TCRR);
}

void write_timer_value (Time val)
{
    /* DONE in step 4 */
    GPT1_REG(TCRR) = val;
}

Time read_timer_mtime (void)
{
    return read_timer_value() / TIMER_TICKS_PER_MS;
}
