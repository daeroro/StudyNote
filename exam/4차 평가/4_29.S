		.data
fmt:	.asciz "this is test %d\n"
		.text
		.globl main

print: 	stmfd sp!, {lr}
	
		ldr r0, =fmt
		bl printf

		ldmfd sp!, {lr}
		mov pc, lr
	  

main: stmfd sp!, {lr}

	  mov r1, #4
	  bl print

	  mov r0, #0
	  ldmfd sp!, {lr}
	  mov pc, lr
