	.arch armv8-a
	.file	"disassemble.cc"
	.text
	.align	2
	.p2align 4,,11
	.global	_Z7memcmp_PKvS0_m
	.type	_Z7memcmp_PKvS0_m, %function
_Z7memcmp_PKvS0_m:
.LFB14232:
	.cfi_startproc
	stp	x29, x30, [sp, -128]!
	.cfi_def_cfa_offset 128
	.cfi_offset 29, -128
	.cfi_offset 30, -120
	adrp	x3, :got:__stack_chk_guard
	ldr	x3, [x3, :got_lo12:__stack_chk_guard]
	mov	x29, sp
	stp	x19, x20, [sp, 16]
	.cfi_offset 19, -112
	.cfi_offset 20, -104
	mov	x19, x0
	stp	x21, x22, [sp, 32]
	.cfi_offset 21, -96
	.cfi_offset 22, -88
	add	x21, x19, x2
	ldr	x0, [x3]
	str	x0, [sp, 120]
	mov	x0, 0
	cmp	x19, x21
	beq	.L32
	stp	x23, x24, [sp, 48]
	.cfi_offset 24, -72
	.cfi_offset 23, -80
	and	x24, x21, -16
	sub	x0, x24, x21
	and	x23, x19, -16
	stp	x25, x26, [sp, 64]
	.cfi_offset 26, -56
	.cfi_offset 25, -64
	mov	x20, x1
	and	x22, x19, 15
	add	x25, x0, x2
	cmp	x24, x23
	beq	.L3
	ldr	q1, [x23]
	add	x26, sp, 96
	add	x0, x26, x22
	mov	x2, 16
	sub	x2, x2, x22
	str	q1, [sp, 80]
	bl	memcpy
	ldp	q1, q0, [sp, 80]
	cmeq	v0.16b, v0.16b, v1.16b
	not	v0.16b, v0.16b
	umaxv	s1, v0.4s
	fmov	w0, s1
	cbnz	w0, .L61
.L4:
	add	x1, x23, 16
	cmp	x24, x1
	beq	.L6
	sub	x2, x23, x19
	add	x2, x2, 16
	add	x2, x20, x2
.L7:
	ldr	q1, [x1]
	ldr	q0, [x2]
	cmeq	v0.16b, v0.16b, v1.16b
	not	v0.16b, v0.16b
	umaxv	s1, v0.4s
	fmov	w0, s1
	cbnz	w0, .L62
	add	x3, x1, 16
	cmp	x24, x3
	beq	.L6
	ldr	q1, [x1, 16]
	ldr	q0, [x2, 16]
	cmeq	v0.16b, v0.16b, v1.16b
	not	v0.16b, v0.16b
	umaxv	s1, v0.4s
	fmov	w0, s1
	cbnz	w0, .L17
	add	x3, x1, 32
	cmp	x24, x3
	beq	.L6
	ldr	q1, [x1, 32]
	ldr	q0, [x2, 32]
	cmeq	v0.16b, v0.16b, v1.16b
	not	v0.16b, v0.16b
	umaxv	s1, v0.4s
	fmov	w0, s1
	cbnz	w0, .L17
	add	x3, x1, 48
	cmp	x24, x3
	beq	.L6
	ldr	q1, [x1, 48]
	ldr	q0, [x2, 48]
	cmeq	v0.16b, v0.16b, v1.16b
	not	v0.16b, v0.16b
	umaxv	s1, v0.4s
	fmov	w0, s1
	cbnz	w0, .L17
	add	x1, x1, 64
	mov	x5, 64
	sub	x4, x24, x1
	add	x0, x2, x5
	mov	x3, x1
	sdiv	x4, x4, x5
.L18:
	mov	x2, x0
	mov	x1, x3
	cbz	x4, .L23
	ldp	q0, q2, [x0]
	ldp	q1, q4, [x3]
	ldp	q6, q5, [x3, 32]
	ldr	q3, [x0, 32]
	cmeq	v1.16b, v0.16b, v1.16b
	cmeq	v2.16b, v2.16b, v4.16b
	ldr	q0, [x0, 48]
	cmeq	v3.16b, v3.16b, v6.16b
	and	v4.16b, v1.16b, v2.16b
	cmeq	v0.16b, v0.16b, v5.16b
	and	v4.16b, v4.16b, v3.16b
	and	v4.16b, v4.16b, v0.16b
	not	v4.16b, v4.16b
	umaxv	s4, v4.4s
	fmov	w1, s4
	cbz	w1, .L63
	not	v0.16b, v0.16b
	umaxv	s4, v0.4s
	fmov	w0, s4
	cbz	w0, .L34
	shrn	v0.8b, v0.8h, 4
	mov	x1, 3
	fmov	x0, d0
	rbit	x0, x0
	clz	x0, x0
	asr	x0, x0, 2
.L19:
	not	v0.16b, v3.16b
	umaxv	s3, v0.4s
	fmov	w2, s3
	cbz	w2, .L20
	shrn	v0.8b, v0.8h, 4
	mov	x1, 2
	fmov	x0, d0
	rbit	x0, x0
	clz	x0, x0
	asr	x0, x0, 2
.L20:
	not	v0.16b, v2.16b
	umaxv	s2, v0.4s
	fmov	w2, s2
	cbz	w2, .L21
	shrn	v0.8b, v0.8h, 4
	mov	x1, 1
	fmov	x0, d0
	rbit	x0, x0
	clz	x0, x0
	asr	x0, x0, 2
.L21:
	not	v0.16b, v1.16b
	umaxv	s1, v0.4s
	fmov	w2, s1
	cbz	w2, .L22
	shrn	v0.8b, v0.8h, 4
	mov	x1, 0
	fmov	x0, d0
	rbit	x0, x0
	clz	x0, x0
	asr	x0, x0, 2
.L22:
	add	x1, x0, x1, lsl 4
	add	x0, x3, x1
	sub	x19, x0, x19
	add	x20, x20, x19
	b	.L29
	.p2align 2,,3
.L3:
	add	x1, x22, x25
	add	x0, sp, 96
	add	x1, x20, x1
	add	x0, x0, x22
.L11:
	mov	x2, x24
	ldr	q1, [x2], 16
	sub	x2, x21, x2
	str	q1, [sp, 80]
	add	x23, x2, 16
	sub	x2, x23, x22
	bl	memcpy
	ldp	q1, q0, [sp, 80]
	cmeq	v0.16b, v0.16b, v1.16b
	not	v0.16b, v0.16b
	umaxv	s1, v0.4s
	fmov	w0, s1
	cbz	w0, .L59
	shrn	v0.8b, v0.8h, 4
	lsl	x3, x22, 2
	lsl	x2, x23, 2
	cmp	x22, 16
	beq	.L59
	mov	x1, -1
	mov	x0, x1
	lsl	x1, x1, x3
	cmp	x23, 16
	lsl	x0, x0, x2
	fmov	x2, d0
	bic	x0, x1, x0
	and	x0, x0, x2
	and	x1, x1, x2
	csel	x0, x0, x1, ne
	cbz	x0, .L59
	rbit	x0, x0
	clz	x0, x0
	add	x0, x24, x0, lsr 2
	sub	x19, x0, x19
	add	x20, x20, x19
.L29:
	cmp	x21, x0
	beq	.L59
	ldp	x23, x24, [sp, 48]
	.cfi_restore 24
	.cfi_restore 23
	ldp	x25, x26, [sp, 64]
	.cfi_restore 26
	.cfi_restore 25
	ldrb	w0, [x0]
	ldrb	w1, [x20]
	sub	w0, w0, w1
.L1:
	adrp	x1, :got:__stack_chk_guard
	ldr	x1, [x1, :got_lo12:__stack_chk_guard]
	ldr	x3, [sp, 120]
	ldr	x2, [x1]
	subs	x3, x3, x2
	mov	x2, 0
	bne	.L64
	ldp	x19, x20, [sp, 16]
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 128
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 21
	.cfi_restore 22
	.cfi_restore 19
	.cfi_restore 20
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L59:
	.cfi_def_cfa_offset 128
	.cfi_offset 19, -112
	.cfi_offset 20, -104
	.cfi_offset 21, -96
	.cfi_offset 22, -88
	.cfi_offset 23, -80
	.cfi_offset 24, -72
	.cfi_offset 25, -64
	.cfi_offset 26, -56
	.cfi_offset 29, -128
	.cfi_offset 30, -120
	ldp	x23, x24, [sp, 48]
	.cfi_restore 24
	.cfi_restore 23
	ldp	x25, x26, [sp, 64]
	.cfi_restore 26
	.cfi_restore 25
.L32:
	mov	w0, 0
	b	.L1
	.p2align 2,,3
.L61:
	.cfi_offset 23, -80
	.cfi_offset 24, -72
	.cfi_offset 25, -64
	.cfi_offset 26, -56
	shrn	v0.8b, v0.8h, 4
	lsl	x22, x22, 2
	mov	x3, -1
	lsl	x3, x3, x22
	fmov	x0, d0
	ands	x3, x3, x0
	beq	.L4
	rbit	x3, x3
	clz	x3, x3
	add	x0, x23, x3, lsr 2
	sub	x19, x0, x19
	add	x20, x20, x19
	b	.L29
.L23:
	cmp	x24, x1
	bne	.L7
	.p2align 3,,7
.L6:
	tst	x21, 15
	beq	.L59
	add	x1, x20, x25
	mov	x0, x26
	mov	x22, 0
	b	.L11
	.p2align 2,,3
.L62:
	shrn	v0.8b, v0.8h, 4
	fmov	x0, d0
	rbit	x0, x0
	clz	x0, x0
	add	x0, x1, x0, lsr 2
	sub	x19, x0, x19
	add	x20, x20, x19
	b	.L29
	.p2align 2,,3
.L17:
	shrn	v0.8b, v0.8h, 4
	fmov	x0, d0
	rbit	x0, x0
	clz	x0, x0
	add	x0, x3, x0, lsr 2
	sub	x19, x0, x19
	add	x20, x20, x19
	b	.L29
.L64:
	.cfi_restore 23
	.cfi_restore 24
	.cfi_restore 25
	.cfi_restore 26
	stp	x23, x24, [sp, 48]
	.cfi_offset 24, -72
	.cfi_offset 23, -80
	stp	x25, x26, [sp, 64]
	.cfi_offset 26, -56
	.cfi_offset 25, -64
	bl	__stack_chk_fail
.L34:
	mov	x0, 0
	mov	x1, 4
	b	.L19
.L63:
	add	x3, x3, 64
	add	x0, x0, 64
	sub	x4, x4, #1
	b	.L18
	.cfi_endproc
.LFE14232:
	.size	_Z7memcmp_PKvS0_m, .-_Z7memcmp_PKvS0_m
	.global	_ZN3eve4fmodE
	.bss
	.align	3
	.type	_ZN3eve4fmodE, %object
	.size	_ZN3eve4fmodE, 1
_ZN3eve4fmodE:
	.zero	1
	.ident	"GCC: (Ubuntu 12-20220222-1ubuntu1) 12.0.1 20220222 (experimental) [master r12-7325-g2f59f067610]"
	.section	.note.GNU-stack,"",@progbits
