/*
 * init.h
 *
 *  Created on: 22 mars 2012
 *  Author: Evangelina Lolivier-Exler
 *  Basic functions of initialization of the REPTAR board
 */
 
/**
 * FILE: init.h
 * 
 * @author Julien Baeriswyl                (julien.baeriswyl@heig-vd.ch)
 * @author Arthur Benjamin Simon Passuello (arthur.passuello@heig-vd.ch)
 * @since  2017-03-07
 */
#ifndef INIT_H_
#define INIT_H_

extern void GPIO_init      (void);
extern void lcd_init       (void);
extern void interrupt_init (void);
extern void timer_init     (void);

#endif /* INIT_H_ */
