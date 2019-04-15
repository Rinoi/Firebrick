.arm
.text
.global main
main:
	mov r0, #0x4000000
	mov r1, #0x03 //// Use video mode 3 (in BG2, a 16bpp bitmap in VRAM)
	strb r1, [r0], #1
	mov r1, #0x04 // Enable BG2 (BG0 = 1, BG1 = 2, BG2 = 4, ...)
	strb r1, [r0]



set:
	/*init*/
	mov r4, #0x6000000 //addr GB2
	mov r5, #240 // WITH
	mov r6, #160 // HEIGHT

	/* get the wifth pas */
	mov r0, #0x1F
	lsl r0, #8
	mov r1, #240
	swi 0x60000
	mov r7, r0
	/*end*/
forY:
	mov r5, #240 // WITH
forX:
getC:
	mul r0, r7, r5
	lsr r0, #8

	mov r1, #0x0A
	mov r2, #0x10

	add r0, r1, lsl#5
	add r0, r2, lsl#10
endC:
	strh r0, [r4], #2
	subs r5, r5, #1
	bne forX
	subs r6, r6, #1
	bne forY
infin:
	swi 0x50000
	b infin
