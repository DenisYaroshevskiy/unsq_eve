	.arch armv8-a
	.file	"disassemble.cc"
	.text
	.align	2
	.p2align 4,,11
	.global	_Z11call_strlenPKc
	.type	_Z11call_strlenPKc, %function
_Z11call_strlenPKc:
.LFB9756:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	and	x2, x0, -16
	mov	w4, 0
	ldr	q0, [x2]
	cmeq	v0.16b, v0.16b, #0
	umaxv	s1, v0.4s
	umov	w3, v1.s[0]
	cbz	w3, .L2
	ushr	v0.8h, v0.8h, 4
	sub	x3, x0, x2
#APP
// 8999 "/usr/lib/gcc-cross/aarch64-linux-gnu/10/include/arm_neon.h" 1
	xtn v0.8b,v0.8h
// 0 "" 2
#NO_APP
	lsl	x3, x3, 2
	cmp	x3, 64
	beq	.L2
	fmov	x6, d0
	mov	x5, 1
	lsl	x3, x5, x3
	neg	x3, x3
	ands	x3, x3, x6
	beq	.L2
	rbit	x1, x3
	mov	w4, w5
	clz	x1, x1
	lsr	x1, x1, 2
.L2:
	cbnz	w4, .L17
	sub	sp, sp, #16
	.cfi_def_cfa_offset 16
	.p2align 3,,7
.L15:
	ldr	q0, [x2, 16]!
	cmeq	v0.16b, v0.16b, #0
	umaxv	s1, v0.4s
	umov	w1, v1.s[0]
	cbz	w1, .L15
	ushr	v0.8h, v0.8h, 4
#APP
// 8999 "/usr/lib/gcc-cross/aarch64-linux-gnu/10/include/arm_neon.h" 1
	xtn v0.8b,v0.8h
// 0 "" 2
#NO_APP
	umov	x1, v0.d[0]
	ldr	x3, [sp]
	add	sp, sp, 16
	.cfi_def_cfa_offset 0
	cmp	x1, 0
	rbit	x1, x1
	clz	x1, x1
	lsr	x1, x1, 2
	csel	x1, x1, x3, ne
	add	x1, x2, x1
	sub	x0, x1, x0
	ret
	.p2align 2,,3
.L17:
	add	x1, x2, x1
	sub	x0, x1, x0
	ret
	.cfi_endproc
.LFE9756:
	.size	_Z11call_strlenPKc, .-_Z11call_strlenPKc
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align	3
	.type	DW.ref.__gxx_personality_v0, %object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.xword	__gxx_personality_v0
	.ident	"GCC: (Ubuntu 10.2.0-5ubuntu1~20.04) 10.2.0"
	.section	.note.GNU-stack,"",@progbits