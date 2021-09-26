	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE # -- Begin function _Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE
	.p2align	4, 0x90
	.type	_Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE,@function
_Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE: # @_Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE
	.cfi_startproc
# %bb.0:
	push	r15
	.cfi_def_cfa_offset 16
	push	r14
	.cfi_def_cfa_offset 24
	push	r13
	.cfi_def_cfa_offset 32
	push	r12
	.cfi_def_cfa_offset 40
	push	rbx
	.cfi_def_cfa_offset 48
	sub	rsp, 48
	.cfi_def_cfa_offset 96
	.cfi_offset rbx, -48
	.cfi_offset r12, -40
	.cfi_offset r13, -32
	.cfi_offset r14, -24
	.cfi_offset r15, -16
	mov	rax, qword ptr [rdi]
	mov	r14, qword ptr [rdi + 8]
	cmp	rax, r14
	je	.LBB0_36
# %bb.1:
	mov	rbx, rax
	and	rbx, -16
	mov	r12, r14
	and	r12, -16
	shr	eax, 2
	and	eax, 3
	cmp	rbx, r12
	je	.LBB0_2
# %bb.3:
	movdqa	xmm0, xmmword ptr [rbx]
	pxor	xmm1, xmm1
	pcmpeqd	xmm1, xmm0
	movmskps	r13d, xmm1
	xor	r13d, 15
	mov	edx, r13d
	mov	ecx, eax
	shr	edx, cl
	shl	edx, cl
	and	edx, 7
	mov	ecx, 3
	jmp	qword ptr [8*rdx + .LJTI0_0]
.LBB0_4:
	pshufd	xmm0, xmm0, 3                   # xmm0 = xmm0[3,0,0,0]
	xor	ecx, ecx
	jmp	.LBB0_12
.LBB0_2:
	mov	rsi, rbx
	jmp	.LBB0_26
.LBB0_5:
	pshufd	xmm0, xmm0, 12                  # xmm0 = xmm0[0,3,0,0]
	mov	ecx, 1
	jmp	.LBB0_12
.LBB0_6:
	pshufd	xmm0, xmm0, 13                  # xmm0 = xmm0[1,3,0,0]
	mov	ecx, 1
	jmp	.LBB0_12
.LBB0_7:
	pshufd	xmm0, xmm0, 52                  # xmm0 = xmm0[0,1,3,0]
	jmp	.LBB0_11
.LBB0_8:
	pshufd	xmm0, xmm0, 14                  # xmm0 = xmm0[2,3,0,0]
	mov	ecx, 1
	jmp	.LBB0_12
.LBB0_9:
	pshufd	xmm0, xmm0, 56                  # xmm0 = xmm0[0,2,3,0]
	jmp	.LBB0_11
.LBB0_10:
	pshufd	xmm0, xmm0, 57                  # xmm0 = xmm0[1,2,3,0]
.LBB0_11:
	mov	ecx, 2
.LBB0_12:
	shr	r13d, 3
	add	r13, rcx
	lea	rdx, [4*r13]
	lea	r15, [rbx + 4*rax]
	movdqa	xmmword ptr [rsp], xmm0
	mov	rsi, rsp
	mov	rdi, r15
	call	memcpy@PLT
	lea	rsi, [r15 + 4*r13]
	add	rbx, 16
	cmp	rbx, r12
	je	.LBB0_24
# %bb.13:
	pxor	xmm0, xmm0
	jmp	.LBB0_14
.LBB0_21:                               #   in Loop: Header=BB0_14 Depth=1
	pshufd	xmm1, xmm1, 57                  # xmm1 = xmm1[1,2,3,0]
.LBB0_22:                               #   in Loop: Header=BB0_14 Depth=1
	mov	ecx, 2
.LBB0_23:                               #   in Loop: Header=BB0_14 Depth=1
	shr	eax, 3
	add	rax, rcx
	movdqu	xmmword ptr [rsi], xmm1
	lea	rsi, [rsi + 4*rax]
	add	rbx, 16
	cmp	rbx, r12
	je	.LBB0_24
.LBB0_14:                               # =>This Inner Loop Header: Depth=1
	movdqa	xmm1, xmmword ptr [rbx]
	movdqa	xmm2, xmm1
	pcmpeqd	xmm2, xmm0
	movmskps	eax, xmm2
	xor	eax, 15
	mov	edx, eax
	and	edx, 7
	mov	ecx, 3
	jmp	qword ptr [8*rdx + .LJTI0_1]
.LBB0_15:                               #   in Loop: Header=BB0_14 Depth=1
	pshufd	xmm1, xmm1, 3                   # xmm1 = xmm1[3,0,0,0]
	xor	ecx, ecx
	jmp	.LBB0_23
.LBB0_16:                               #   in Loop: Header=BB0_14 Depth=1
	pshufd	xmm1, xmm1, 12                  # xmm1 = xmm1[0,3,0,0]
	mov	ecx, 1
	jmp	.LBB0_23
.LBB0_17:                               #   in Loop: Header=BB0_14 Depth=1
	pshufd	xmm1, xmm1, 13                  # xmm1 = xmm1[1,3,0,0]
	mov	ecx, 1
	jmp	.LBB0_23
.LBB0_18:                               #   in Loop: Header=BB0_14 Depth=1
	pshufd	xmm1, xmm1, 52                  # xmm1 = xmm1[0,1,3,0]
	jmp	.LBB0_22
.LBB0_19:                               #   in Loop: Header=BB0_14 Depth=1
	pshufd	xmm1, xmm1, 14                  # xmm1 = xmm1[2,3,0,0]
	mov	ecx, 1
	jmp	.LBB0_23
.LBB0_20:                               #   in Loop: Header=BB0_14 Depth=1
	pshufd	xmm1, xmm1, 56                  # xmm1 = xmm1[0,2,3,0]
	jmp	.LBB0_22
.LBB0_24:
	cmp	r14, r12
	je	.LBB0_36
# %bb.25:
	xor	eax, eax
.LBB0_26:
	mov	edx, r12d
	sub	edx, r14d
	add	edx, 16
	shr	edx, 2
	movdqa	xmm0, xmmword ptr [r12]
	pxor	xmm1, xmm1
	pcmpeqd	xmm1, xmm0
	mov	cl, 4
	sub	cl, dl
	mov	rdx, -1
	shl	rdx, cl
	not	edx
	mov	ecx, eax
	shr	edx, cl
	movmskps	edi, xmm1
	shl	edx, cl
	xor	edi, 15
	and	edx, edi
	mov	edi, edx
	and	edi, 7
	mov	ecx, 3
	jmp	qword ptr [8*rdi + .LJTI0_2]
.LBB0_27:
	pshufd	xmm0, xmm0, 3                   # xmm0 = xmm0[3,0,0,0]
	xor	ecx, ecx
	jmp	.LBB0_35
.LBB0_28:
	pshufd	xmm0, xmm0, 12                  # xmm0 = xmm0[0,3,0,0]
	mov	ecx, 1
	jmp	.LBB0_35
.LBB0_29:
	pshufd	xmm0, xmm0, 13                  # xmm0 = xmm0[1,3,0,0]
	mov	ecx, 1
	jmp	.LBB0_35
.LBB0_30:
	pshufd	xmm0, xmm0, 52                  # xmm0 = xmm0[0,1,3,0]
	jmp	.LBB0_34
.LBB0_31:
	pshufd	xmm0, xmm0, 14                  # xmm0 = xmm0[2,3,0,0]
	mov	ecx, 1
	jmp	.LBB0_35
.LBB0_32:
	pshufd	xmm0, xmm0, 56                  # xmm0 = xmm0[0,2,3,0]
	jmp	.LBB0_34
.LBB0_33:
	pshufd	xmm0, xmm0, 57                  # xmm0 = xmm0[1,2,3,0]
.LBB0_34:
	mov	ecx, 2
.LBB0_35:
	shr	edx, 3
	add	rdx, rcx
	shl	rdx, 2
	lea	rdi, [rsi + 4*rax]
	movdqa	xmmword ptr [rsp], xmm0
	mov	rsi, rsp
	call	memcpy@PLT
.LBB0_36:
	add	rsp, 48
	.cfi_def_cfa_offset 48
	pop	rbx
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_def_cfa_offset 8
	ret
.Lfunc_end0:
	.size	_Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE, .Lfunc_end0-_Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE
	.cfi_endproc
	.section	.rodata,"a",@progbits
	.p2align	3
.LJTI0_0:
	.quad	.LBB0_4
	.quad	.LBB0_5
	.quad	.LBB0_6
	.quad	.LBB0_7
	.quad	.LBB0_8
	.quad	.LBB0_9
	.quad	.LBB0_10
	.quad	.LBB0_12
.LJTI0_1:
	.quad	.LBB0_15
	.quad	.LBB0_16
	.quad	.LBB0_17
	.quad	.LBB0_18
	.quad	.LBB0_19
	.quad	.LBB0_20
	.quad	.LBB0_21
	.quad	.LBB0_23
.LJTI0_2:
	.quad	.LBB0_27
	.quad	.LBB0_28
	.quad	.LBB0_29
	.quad	.LBB0_30
	.quad	.LBB0_31
	.quad	.LBB0_32
	.quad	.LBB0_33
	.quad	.LBB0_35
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 14.0.0 (https://github.com/llvm/llvm-project.git 15e9575fb5988a66aa6e57a55818b54b575dd795)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
