@==============================================================================@
@ ASP-A Lab   : 2 - Peripherals
@ File        : int_arm.S
@ Author      : Baeriswyl Julien, Passuello Arthur
@ Date        : 2017-03-14
@ Description : Step 3 - interrupt routine
@==============================================================================@

.text
.extern isr_handler
.global isr

@@
@ Interrupt service routine
@
@ \param  <none>
@ \return <nothing>
@
isr:
    @ DONE in step 3
    stmfd sp!, {r0-r12, lr}

    bl isr_handler

    ldmfd sp!, {r0-r12, lr}
    subs  pc,  lr,   #4

