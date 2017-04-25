/**
 * FILE: students_defs.h
 * 
 * @author Julien Baeriswyl                (julien.baeriswyl@heig-vd.ch)
 * @author Arthur Benjamin Simon Passuello (arthur.passuello@heig-vd.ch)
 * @since  2017-04-04
 */
#ifndef ASP_A_BAERISWYL_PASSUELLO_DEFS_H_
#define ASP_A_BAERISWYL_PASSUELLO_DEFS_H_

#include "stddefs.h"

// define types
typedef enum {false, true} bool;

// alignment optimisation
#define ALIGN (sizeof(size_t))

#define ONES  ((size_t)-1/UCHAR_MAX)
#define HIGHS (ONES * (UCHAR_MAX/2+1))
#define HASZERO(x) (((x)-ONES) & ~(x) & HIGHS)

#endif /* ASP_A_BAERISWYL_PASSUELLO_DEFS_H_ */
