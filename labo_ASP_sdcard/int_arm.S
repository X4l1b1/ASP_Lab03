.global isr
.extern isr_handler

isr:
	stmfd	R13!, {r0-r12, LR}

	bl		isr_handler

	ldmfd	sp!, {r0-r12, LR}
	subs	pc, lr, #4
