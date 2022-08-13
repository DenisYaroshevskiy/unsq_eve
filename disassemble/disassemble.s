	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z7memcmp_PKvS0_m               # -- Begin function _Z7memcmp_PKvS0_m
	.p2align	4, 0x90
	.type	_Z7memcmp_PKvS0_m,@function
_Z7memcmp_PKvS0_m:                      # @_Z7memcmp_PKvS0_m
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	push	r15
	push	r14
	push	r13
	push	r12
	push	rbx
	and	rsp, -32
	sub	rsp, 128
	.cfi_offset rbx, -56
	.cfi_offset r12, -48
	.cfi_offset r13, -40
	.cfi_offset r14, -32
	.cfi_offset r15, -24
	mov	r9, rsi
	test	rdx, rdx
	je	.LBB0_4
# %bb.1:
	lea	r13, [rdi + rdx]
	mov	rbx, rdi
	and	rbx, -32
	mov	qword ptr [rsp + 24], rdi       # 8-byte Spill
	mov	r12d, edi
	and	r12d, 31
	mov	r14, r13
	and	r14, -32
	cmp	rbx, r14
	mov	qword ptr [rsp + 16], rdx       # 8-byte Spill
	je	.LBB0_22
# %bb.2:
	vmovaps	ymm0, ymmword ptr [rbx]
	vmovaps	ymmword ptr [rsp + 32], ymm0    # 32-byte Spill
	lea	rdi, [rsp + r12]
	add	rdi, 64
	mov	edx, 32
	sub	rdx, r12
	mov	r15, r9
	mov	rsi, r9
	vzeroupper
	call	memcpy@PLT
	vmovdqa	ymm0, ymmword ptr [rsp + 32]    # 32-byte Reload
	vpcmpeqb	ymm0, ymm0, ymmword ptr [rsp + 64]
	vpmovmskb	eax, ymm0
	not	eax
	shrx	eax, eax, r12d
	shlx	eax, eax, r12d
	test	eax, eax
	je	.LBB0_5
# %bb.3:
	bsf	eax, eax
	add	rbx, rax
	mov	r13, rbx
	mov	r9, r15
.LBB0_28:
	mov	rdx, qword ptr [rsp + 16]       # 8-byte Reload
	jmp	.LBB0_29
.LBB0_4:
	mov	r13, rdi
	sub	r13, rdi
	xor	eax, eax
	cmp	r13, rdx
	jne	.LBB0_30
	jmp	.LBB0_31
.LBB0_5:
	add	rbx, 32
	cmp	rbx, r14
	mov	r9, r15
	je	.LBB0_20
# %bb.6:
	mov	rax, r9
	sub	rax, r12
	add	rax, 32
	vpcmpeqd	ymm0, ymm0, ymm0
	jmp	.LBB0_8
.LBB0_7:                                #   in Loop: Header=BB0_8 Depth=1
	mov	rax, rcx
	cmp	rbx, r14
	je	.LBB0_20
.LBB0_8:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_17 Depth 2
	vmovdqa	ymm1, ymmword ptr [rbx]
	vmovdqu	ymm2, ymmword ptr [rax]
	vpsubb	ymm3, ymm1, ymm2
	vptest	ymm3, ymm3
	jne	.LBB0_32
# %bb.9:                                #   in Loop: Header=BB0_8 Depth=1
	lea	rcx, [rbx + 32]
	cmp	rcx, r14
	je	.LBB0_20
# %bb.10:                               #   in Loop: Header=BB0_8 Depth=1
	vmovdqa	ymm1, ymmword ptr [rcx]
	vmovdqu	ymm2, ymmword ptr [rax + 32]
	vpsubb	ymm3, ymm1, ymm2
	vptest	ymm3, ymm3
	jne	.LBB0_27
# %bb.11:                               #   in Loop: Header=BB0_8 Depth=1
	lea	rcx, [rbx + 64]
	cmp	rcx, r14
	je	.LBB0_20
# %bb.12:                               #   in Loop: Header=BB0_8 Depth=1
	vmovdqa	ymm1, ymmword ptr [rcx]
	vmovdqu	ymm2, ymmword ptr [rax + 64]
	vpsubb	ymm3, ymm1, ymm2
	vptest	ymm3, ymm3
	jne	.LBB0_27
# %bb.13:                               #   in Loop: Header=BB0_8 Depth=1
	lea	rcx, [rbx + 96]
	cmp	rcx, r14
	je	.LBB0_20
# %bb.14:                               #   in Loop: Header=BB0_8 Depth=1
	vmovdqa	ymm1, ymmword ptr [rcx]
	vmovdqu	ymm2, ymmword ptr [rax + 96]
	vpsubb	ymm3, ymm1, ymm2
	vptest	ymm3, ymm3
	jne	.LBB0_27
# %bb.15:                               #   in Loop: Header=BB0_8 Depth=1
	sub	rbx, -128
	lea	rcx, [rax + 128]
	mov	rsi, r14
	sub	rsi, rbx
	lea	rdi, [rsi + 127]
	cmp	rdi, 255
	jb	.LBB0_7
# %bb.16:                               #   in Loop: Header=BB0_8 Depth=1
	mov	rdx, rcx
	test	rsi, rsi
	cmovns	rdi, rsi
	mov	rsi, rdi
	sar	rsi, 7
	and	rdi, -128
	lea	r8, [rbx + rdi]
	lea	rcx, [rax + rdi]
	add	rcx, 128
	.p2align	4, 0x90
.LBB0_17:                               #   Parent Loop BB0_8 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovdqa	ymm1, ymmword ptr [rbx]
	vmovdqa	ymm4, ymmword ptr [rbx + 32]
	vmovdqa	ymm5, ymmword ptr [rbx + 64]
	vmovdqa	ymm8, ymmword ptr [rbx + 96]
	vmovdqu	ymm2, ymmword ptr [rdx]
	vmovdqu	ymm6, ymmword ptr [rdx + 64]
	vmovdqu	ymm9, ymmword ptr [rdx + 96]
	vpcmpeqb	ymm3, ymm1, ymm2
	vpcmpeqb	ymm4, ymm4, ymmword ptr [rdx + 32]
	vpxor	ymm4, ymm4, ymm0
	vpcmpeqb	ymm7, ymm5, ymm6
	vpcmpeqb	ymm10, ymm8, ymm9
	vpand	ymm11, ymm7, ymm3
	vpand	ymm11, ymm11, ymm10
	vpxor	ymm11, ymm11, ymm0
	vpor	ymm11, ymm11, ymm4
	vpmovmskb	eax, ymm11
	test	eax, eax
	jne	.LBB0_24
# %bb.18:                               #   in Loop: Header=BB0_17 Depth=2
	add	rsi, -1
	sub	rbx, -128
	sub	rdx, -128
	test	rsi, rsi
	jne	.LBB0_17
# %bb.19:                               #   in Loop: Header=BB0_8 Depth=1
	mov	rbx, r8
	jmp	.LBB0_7
.LBB0_20:
	cmp	r13, r14
	je	.LBB0_28
# %bb.21:
	xor	r12d, r12d
	mov	rdx, qword ptr [rsp + 16]       # 8-byte Reload
.LBB0_22:
	lea	rsi, [r9 + rdx]
	mov	eax, r13d
	and	eax, 31
	sub	rsi, rax
	mov	rbx, r14
	sub	rbx, r13
	vmovaps	ymm0, ymmword ptr [r14]
	vmovaps	ymmword ptr [rsp + 32], ymm0    # 32-byte Spill
	lea	rdi, [rsp + r12]
	add	rdi, 64
	add	rsi, r12
	lea	rax, [rbx + r12]
	add	rax, 32
	add	rbx, 32
	mov	edx, 32
	sub	rdx, rax
	mov	r15, r9
	vzeroupper
	call	memcpy@PLT
	mov	r9, r15
	vmovdqa	ymm0, ymmword ptr [rsp + 32]    # 32-byte Reload
	vpcmpeqb	ymm0, ymm0, ymmword ptr [rsp + 64]
	add	rbx, 32
	neg	rbx
	mov	rax, -1
	shlx	rax, rax, rbx
	not	eax
	vpmovmskb	ecx, ymm0
	not	ecx
	shrx	eax, eax, r12d
	shlx	eax, eax, r12d
	and	eax, ecx
	mov	rdx, qword ptr [rsp + 16]       # 8-byte Reload
	je	.LBB0_29
# %bb.23:
	bsf	eax, eax
	add	r14, rax
	mov	r13, r14
.LBB0_29:
	mov	rdi, qword ptr [rsp + 24]       # 8-byte Reload
	sub	r13, rdi
	xor	eax, eax
	cmp	r13, rdx
	je	.LBB0_31
.LBB0_30:
	movzx	eax, byte ptr [rdi + r13]
	movzx	ecx, byte ptr [r9 + r13]
	sub	eax, ecx
.LBB0_31:
	lea	rsp, [rbp - 40]
	pop	rbx
	pop	r12
	pop	r13
	pop	r14
	pop	r15
	pop	rbp
	.cfi_def_cfa rsp, 8
	vzeroupper
	ret
.LBB0_24:
	.cfi_def_cfa rbp, 16
	vpsubb	ymm0, ymm8, ymm9
	vpmovmskb	eax, ymm10
	not	eax
	bsf	ecx, eax
	xor	eax, eax
	xor	edx, edx
	vptest	ymm0, ymm0
	sete	dl
	cmove	ecx, eax
	shl	rdx, 5
	add	rdx, 96
	vpsubb	ymm0, ymm5, ymm6
	vpmovmskb	esi, ymm7
	not	esi
	bsf	esi, esi
	vptest	ymm0, ymm0
	cmove	esi, ecx
	mov	ecx, 64
	cmove	rcx, rdx
	vpmovmskb	edx, ymm4
	bsf	edx, edx
	cmove	edx, esi
	mov	esi, 32
	cmove	rsi, rcx
	vpsubb	ymm0, ymm1, ymm2
	vpmovmskb	ecx, ymm3
	not	ecx
	bsf	ecx, ecx
	vptest	ymm0, ymm0
	cmove	ecx, edx
	cmove	rax, rsi
	add	rcx, rax
	add	rbx, rcx
.LBB0_25:
	mov	r13, rbx
	jmp	.LBB0_28
.LBB0_27:
	vpcmpeqb	ymm0, ymm1, ymm2
	vpmovmskb	eax, ymm0
	not	eax
	bsf	eax, eax
	add	rcx, rax
	mov	r13, rcx
	jmp	.LBB0_28
.LBB0_32:
	vpcmpeqb	ymm0, ymm1, ymm2
	vpmovmskb	eax, ymm0
	not	eax
	bsf	eax, eax
	add	rbx, rax
	jmp	.LBB0_25
.Lfunc_end0:
	.size	_Z7memcmp_PKvS0_m, .Lfunc_end0-_Z7memcmp_PKvS0_m
	.cfi_endproc
                                        # -- End function
	.type	_ZN3eve4fmodE,@object           # @_ZN3eve4fmodE
	.bss
	.globl	_ZN3eve4fmodE
_ZN3eve4fmodE:
	.zero	1
	.size	_ZN3eve4fmodE, 1

	.section	".linker-options","e",@llvm_linker_options
	.ident	"Ubuntu clang version 14.0.6-++20220622053133+f28c006a5895-1~exp1~20220622173215.107"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
