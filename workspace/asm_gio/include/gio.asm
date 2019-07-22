	.text
	.arm

	;global은 ccs에서 사용하는 문법
	.global _gio_a5_on_
	.asmfunc

_gio_a5_on_off_
	; for gioREG setting
	ldr r4, gio_reg
	mov r6, #0x1
	str r6, [r4]
	mov r6, #0xFF
	str r6, [r4, #0x14]
	str r6, [r4, #0x8]

	; for gioPORTA setting
	ldr r5, gio_a
	; 0b 0010 0000
	mov r6, #0x20
	mov r9, #0x00
	str r6, [r5]
	str r6, [r5, #0x1c]
	mov r7, #0
	mov r8, #30000

l_on:	str r6, [r5, #0x8]

	add r7, r7, #1
	cmp r8, r7

	bne l_on

	mov r7, #0

l_off:	str r9, [r5, #0x8]
	add r7, r7, #1
	cmp r8, r7
	bne l_off

	mov r7, #0
	beq l_on

	bx lr

gio_reg .word 	0xFFF7BC00
gio_a	.word	0xFFF7BC34

	.endasmfunc

	.global _print_cpsr_
	.asmfunc

_print_cpsr_
    mrs r0, cpsr
    bx lr

    .endasmfunc

	.global _print_spsr_
	.asmfunc

_print_spsr_
    mrs r0, spsr
    bx lr

    .endasmfunc
