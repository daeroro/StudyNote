		.data
		
		.text
		.globl main

get_node:	stmfd sp!, {lr}

			mov r0, #12
			bl malloc

			ldmfd sp!, {lr}
			mov pc, lr

insert:	push {fp, lr}
		add fp, sp, #4

#insert할 데이터 옮기기
		mov r4, r1		
		
#12바이트 동적 할당
		bl get_node

#할당 된 주소를 stack에 옮기기
		mov r5, r0
		str r5, [fp, #4]
#동적 할당 된 공간에 데이터 옮기고 좌/우 주소 들어갈 공간 0으로 초기화
		str r4, [r5, #0]
		mov r3, #0
		str r3, [r5, #4]
		str r3, [r5, #8]

		pop {fp, pc}

main:	push {fp, lr}
		add fp, sp, #4
		sub sp, sp, #8

#스택에 저장된 시작 주소 기억
		sub r9, fp, #8

		mov r1, #0
		str r1, [fp, #-8]

		mov r1, #3
		bl ensert 

		mov r0, #0
		pop {fp, pc}
