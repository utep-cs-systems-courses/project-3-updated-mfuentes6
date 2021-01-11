	.arch msp430g2553
	.p2align 1,0
	.text

	.extern redrawScreen
jt:
	.word default
	.word option1
	.word option2
	.word option3

	.global new_screen
new_screen:
	cmp #4, &redrawScreen
	jhs default

	mov &redrawScreen, r12
	add r12, r12		; add to itself to get the offset
	mov jt(r12), r0		;jumps to jt[redrawScreen]


	;; switch table options

option3:
	add #1, &redrawScreen
	jmp end

option2:
	add #1, &redrawScreen
	jmp end

	
option1:
	add #1, &redrawScreen
	jmp end

default:
	mov #0, &redrawScreen
end:
	pop r0
