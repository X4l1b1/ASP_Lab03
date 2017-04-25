#include "cfg.h"

    .extern AppStack_svr
    .extern AppStack_irq
	.extern main
	.global	start
	.global _init
	.global _fini

    /* Set stack pointer to end of AppStack and jump to main:
	 */
start:

  ldr sp, =(AppStack_svr + APPSTACKSIZE - 4)

  mrs r1,cpsr
  bic r1,r1,#0x1f
  orr r1,r1,#0x12
  msr cpsr_c,r1

  ldr sp, =(AppStack_irq + APPSTACKSIZE - 4)

  mrs r1,cpsr
  bic r1,r1,#0x1f
  orr r1,r1,#0x13
  msr cpsr_c,r1

  bl main
