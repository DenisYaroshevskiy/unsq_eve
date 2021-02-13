	.arch armv8-a
	.file	"disassemble.cc"
	.text
	.align	2
	.p2align 4,,11
	.global	_Z11call_strlenPKc
	.type	_Z11call_strlenPKc, %function
_Z11call_strlenPKc:
.LFB9755:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	and	x2, x0, -16
	mov	w4, 0
	ldr	q1, [x2]
	cmeq	v1.16b, v1.16b, #0
	cmeq	v0.4s, v1.4s, #0
	not	v0.16b, v0.16b
#APP
// 8975 "/usr/lib/gcc-cross/aarch64-linux-gnu/10/include/arm_neon.h" 1
	xtn v0.4h,v0.4s
// 0 "" 2
#NO_APP
	umaxp	v0.2s, v0.2s, v0.2s
	umov	w1, v0.s[0]
	cbz	w1, .L2
	ushr	v1.8h, v1.8h, 4
	sub	x1, x0, x2
#APP
// 8999 "/usr/lib/gcc-cross/aarch64-linux-gnu/10/include/arm_neon.h" 1
	xtn v1.8b,v1.8h
// 0 "" 2
#NO_APP
	lsl	x1, x1, 2
	cmp	x1, 64
	beq	.L2
	fmov	x6, d1
	mov	x5, 1
	lsl	x1, x5, x1
	neg	x1, x1
	ands	x1, x1, x6
	beq	.L2
	rbit	x1, x1
	mov	w4, w5
	clz	x1, x1
	lsr	x3, x1, 2
.L2:
	cbnz	w4, .L4
	.p2align 3,,7
.L14:
	ldr	q1, [x2, 16]!
	cmeq	v1.16b, v1.16b, #0
	cmeq	v0.4s, v1.4s, #0
	not	v0.16b, v0.16b
#APP
// 8975 "/usr/lib/gcc-cross/aarch64-linux-gnu/10/include/arm_neon.h" 1
	xtn v0.4h,v0.4s
// 0 "" 2
#NO_APP
	umaxp	v0.2s, v0.2s, v0.2s
	umov	w1, v0.s[0]
	cbz	w1, .L14
	ushr	v1.8h, v1.8h, 4
#APP
// 8999 "/usr/lib/gcc-cross/aarch64-linux-gnu/10/include/arm_neon.h" 1
	xtn v0.8b,v1.8h
// 0 "" 2
#NO_APP
	umov	x1, v0.d[0]
	cmp	x1, 0
	rbit	x1, x1
	clz	x1, x1
	lsr	x1, x1, 2
	csel	x3, x1, x3, ne
.L4:
	add	x2, x2, x3
	sub	x0, x2, x0
	ret
	.cfi_endproc
.LFE9755:
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
