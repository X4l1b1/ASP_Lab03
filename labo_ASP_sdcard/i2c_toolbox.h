/*
 * i2c_toolbox.h
 *
 *  Created on: 24 oct. 2012
 *      Author: redsuser
 */

#ifndef I2C_TOOLBOX_H_
#define I2C_TOOLBOX_H_

extern void i2c1_init();
extern int i2c1_write_byte(ushort slave_add, ushort reg_add ,ushort value);

#endif /* I2C_TOOLBOX_H_ */
