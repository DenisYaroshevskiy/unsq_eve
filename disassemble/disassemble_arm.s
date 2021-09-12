	.arch armv8-a
	.file	"disassemble.cc"
	.text
	.align	2
	.p2align 4,,11
	.global	_Z14inclusive_scanPiS_
	.type	_Z14inclusive_scanPiS_, %function
_Z14inclusive_scanPiS_:
.LFB11321:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	stp	x29, x30, [sp, -96]!
	.cfi_def_cfa_offset 96
	.cfi_offset 29, -96
	.cfi_offset 30, -88
	adrp	x2, :got:__stack_chk_guard
	mov	x29, sp
	ldr	x2, [x2, #:got_lo12:__stack_chk_guard]
	stp	x21, x22, [sp, 32]
	.cfi_offset 21, -64
	.cfi_offset 22, -56
	mov	x21, x1
	ldr	x1, [x2]
	str	x1, [sp, 88]
	mov	x1, 0
	cmp	x0, x21
	bne	.L14
.L1:
	adrp	x0, :got:__stack_chk_guard
	ldr	x0, [x0, #:got_lo12:__stack_chk_guard]
	ldr	x1, [sp, 88]
	ldr	x2, [x0]
	subs	x1, x1, x2
	mov	x2, 0
	bne	.L15
	ldp	x21, x22, [sp, 32]
	ldp	x29, x30, [sp], 96
	.cfi_remember_state
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 21
	.cfi_restore 22
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L14:
	.cfi_restore_state
	and	x2, x0, -16
	stp	x19, x20, [sp, 16]
	.cfi_offset 20, -72
	.cfi_offset 19, -80
	and	x20, x21, -16
	ubfx	x4, x0, 2, 2
	and	x3, x0, 15
	fmov	s0, w4
	cmp	x20, x2
	bne	.L4
	add	x1, sp, 64
	add	x0, x20, x3
	movi	v2.4s, 0
	add	x1, x1, x3
.L5:
	ldr	q4, [x20], 16
	adrp	x3, .LC0
	dup	v0.4s, v0.s[0]
	mov	x2, 4
	ldr	q5, [x3, #:lo12:.LC0]
	sub	x20, x20, x21
	movi	v1.4s, 0
	sub	x20, x2, x20, asr 2
	cmge	v3.4s, v5.4s, v0.4s
	sub	x2, x20, x4
	dup	v0.4s, w20
	lsl	x2, x2, 2
	cmgt	v0.4s, v0.4s, v5.4s
	and	v0.16b, v3.16b, v0.16b
	and	v3.16b, v4.16b, v0.16b
	ext	v0.16b, v1.16b, v3.16b, #12
	add	v0.4s, v0.4s, v3.4s
	ext	v1.16b, v1.16b, v0.16b, #8
	add	v1.4s, v1.4s, v0.4s
	add	v2.4s, v1.4s, v2.4s
	str	q2, [sp, 64]
	bl	memcpy
	ldp	x19, x20, [sp, 16]
	.cfi_remember_state
	.cfi_restore 20
	.cfi_restore 19
	b	.L1
	.p2align 2,,3
.L4:
	.cfi_restore_state
	adrp	x1, .LC0
	dup	v0.4s, w4
	mov	x19, x2
	mov	x2, 4
	ldr	q2, [x1, #:lo12:.LC0]
	sub	x2, x2, x4
	ldr	q1, [x19], 16
	add	x22, sp, 64
	cmge	v0.4s, v2.4s, v0.4s
	lsl	x2, x2, 2
	movi	v3.4s, 0
	add	x1, x22, x3
	and	v1.16b, v1.16b, v0.16b
	ext	v0.16b, v3.16b, v1.16b, #12
	add	v1.4s, v0.4s, v1.4s
	ext	v0.16b, v3.16b, v1.16b, #8
	add	v0.4s, v0.4s, v1.4s
	dup	v2.4s, v0.s[3]
	stp	q2, q0, [sp, 48]
	bl	memcpy
	cmp	x20, x19
	ldr	q2, [sp, 48]
	beq	.L6
	movi	v3.4s, 0
	mov	x0, x19
	.p2align 3,,7
.L7:
	ldr	q1, [x0]
	ext	v0.16b, v3.16b, v1.16b, #12
	add	v1.4s, v0.4s, v1.4s
	ext	v0.16b, v3.16b, v1.16b, #8
	add	v0.4s, v0.4s, v1.4s
	add	v0.4s, v0.4s, v2.4s
	dup	v2.4s, v0.s[3]
	str	q0, [x0], 16
	cmp	x20, x0
	bne	.L7
.L6:
	cmp	x21, x20
	beq	.L12
	mov	x1, x22
	mov	x0, x20
	fmov	s0, wzr
	mov	x4, 0
	b	.L5
	.p2align 2,,3
.L12:
	ldp	x19, x20, [sp, 16]
	.cfi_restore 20
	.cfi_restore 19
	b	.L1
.L15:
	stp	x19, x20, [sp, 16]
	.cfi_offset 20, -72
	.cfi_offset 19, -80
	bl	__stack_chk_fail
	.cfi_endproc
.LFE11321:
	.size	_Z14inclusive_scanPiS_, .-_Z14inclusive_scanPiS_
	.section	.rodata.cst16,"aM",@progbits,16
	.align	4
.LC0:
	.word	0
	.word	1
	.word	2
	.word	3
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align	3
	.type	DW.ref.__gxx_personality_v0, %object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.xword	__gxx_personality_v0
	.ident	"GCC: (Ubuntu 10.3.0-1ubuntu1~20.04) 10.3.0"
	.section	.note.GNU-stack,"",@progbits
