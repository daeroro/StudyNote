		.data
fmt:	.asciz "result = %f\n"

		.text
		.globl main

integ:	push {fp, lr}
		add fp, sp, #4
		sub sp, sp, #32

fcons:	.float 1.0
		.float 2.0
		.float 0.001
		.float 3.0
		.float 7.0
		
		vldr.32 s1, fcons
		vldr.32 s2, fcons+4
		vldr.32 s3, fcons+8
		vldr.32 s4, fcons+12
		vldr.32 s5, fcons+16
	
		mov r4, #0
		mov r5, #1000	

iloop:	vmul.f32 s6, s1, s1
		vmul.f32 s6, s6, s4

		vmul.f32 s7, s5, s1
		vadd.f32 s6, s6, s7
		vmul.f32 s6, s6, s3

		vadd.f32 s8, s8, s6		

		vadd.f32 s1, s1, s3

		add r4, r4, #1
		cmp r5, r4
		bne iloop

		vcvt.f64.f32 d16, s8
		vmov r2, r3, d16

		ldr r0, =fmt
		bl printf

ifin:	sub sp, fp, #4
		pop {fp, pc}


main: 	push {fp, lr}
		add fp, sp, #4
		sub sp, sp, #32

		bl integ

		mov r0, #0
		sub sp, fp, #4
		pop {fp, pc}
