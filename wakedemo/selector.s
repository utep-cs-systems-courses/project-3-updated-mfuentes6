	.arch msp430g2553
	.p2align 1,0
	.text

	.extern redrawScreen
	.extern clearScreen
jt:
	.word default
	.word option1
	.word option2
	.word option3

	.global new_screen
	.global new_color
new_color:
	mov.b 0xf800, r12 		;color blue
	call #clearScreen
	jmp end
new_screen:
	cmp #4, &redrawScreen
	jhs default

	mov &redrawScreen, r13
	add r13, r13			; add to itself to get the offset
	mov jt(r13), r0		;jumps to jt[redrawScreen]


	;; switch table options

option3:
	mov #1, &redrawScreen
	jmp end

option2:
	add #1, &redrawScreen
	jmp end

	
option1:
	add #1, &redrawScreen
	jmp end

default:
	mov #1, &redrawScreen
end:
	pop r0
