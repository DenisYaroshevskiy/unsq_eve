	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5               # -- Begin function _Z22inclusive_scan_inplacePsS_
.LCPI0_0:
	.short	0                       # 0x0
	.short	1                       # 0x1
	.short	2                       # 0x2
	.short	3                       # 0x3
	.short	4                       # 0x4
	.short	5                       # 0x5
	.short	6                       # 0x6
	.short	7                       # 0x7
	.short	8                       # 0x8
	.short	9                       # 0x9
	.short	10                      # 0xa
	.short	11                      # 0xb
	.short	12                      # 0xc
	.short	13                      # 0xd
	.short	14                      # 0xe
	.short	15                      # 0xf
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4
.LCPI0_1:
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2
.LCPI0_2:
	.long	6                       # 0x6
	.text
	.globl	_Z22inclusive_scan_inplacePsS_
	.p2align	4, 0x90
	.type	_Z22inclusive_scan_inplacePsS_,@function
_Z22inclusive_scan_inplacePsS_:         # @_Z22inclusive_scan_inplacePsS_
.L_Z22inclusive_scan_inplacePsS_$local:
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	push	r15
	push	r14
	push	rbx
	and	rsp, -32
	sub	rsp, 96
	.cfi_offset rbx, -40
	.cfi_offset r14, -32
	.cfi_offset r15, -24
	mov	r14, rsi
	mov	rbx, rdi
	and	rbx, -32
	mov	r15, rsi
	and	r15, -32
	and	edi, 31
	mov	rcx, rdi
	shr	rcx
	cmp	rbx, r15
	je	.LBB0_1
# %bb.2:
	lea	eax, [rcx - 1]
	vmovd	xmm0, eax
	vpbroadcastw	ymm0, xmm0
	vmovdqa	ymm1, ymmword ptr [rip + .LCPI0_0] # ymm1 = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
	vpcmpgtw	ymm0, ymm1, ymm0
	vpand	ymm0, ymm0, ymmword ptr [rbx]
	vpslldq	ymm1, ymm0, 2           # ymm1 = zero,zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11,12,13],zero,zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm0, ymm1, ymm0
	vpslldq	ymm1, ymm0, 4           # ymm1 = zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm0, ymm0, ymm1
	vpslldq	ymm1, ymm0, 8           # ymm1 = zero,zero,zero,zero,zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23]
	vpaddw	ymm0, ymm0, ymm1
	vpshufb	xmm1, xmm0, xmmword ptr [rip + .LCPI0_1] # xmm1 = xmm0[14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	vperm2i128	ymm1, ymm1, ymm1, 40 # ymm1 = zero,zero,ymm1[0,1]
	vpaddw	ymm0, ymm0, ymm1
	vmovdqa	ymmword ptr [rsp + 32], ymm0 # 32-byte Spill
	vmovdqa	ymmword ptr [rsp], ymm0
	lea	rax, [rbx + 2*rcx]
	lea	rsi, [rsp + 2*rcx]
	mov	edx, 32
	sub	rdx, rdi
	mov	rdi, rax
	vzeroupper
	call	memcpy
	vpshufhw	ymm0, ymmword ptr [rsp + 32], 239 # 32-byte Folded Reload
                                        # ymm0 = mem[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vpbroadcastd	ymm1, dword ptr [rip + .LCPI0_2] # ymm1 = [6,6,6,6,6,6,6,6]
	vpermd	ymm0, ymm1, ymm0
	add	rbx, 32
	cmp	rbx, r15
	je	.LBB0_5
# %bb.3:
	vmovdqa	xmm2, xmmword ptr [rip + .LCPI0_1] # xmm2 = [14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	.p2align	4, 0x90
.LBB0_4:                                # =>This Inner Loop Header: Depth=1
	vmovdqa	ymm3, ymmword ptr [rbx]
	vpslldq	ymm4, ymm3, 2           # ymm4 = zero,zero,ymm3[0,1,2,3,4,5,6,7,8,9,10,11,12,13],zero,zero,ymm3[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm3, ymm4, ymm3
	vpslldq	ymm4, ymm3, 4           # ymm4 = zero,zero,zero,zero,ymm3[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm3[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm3, ymm3, ymm4
	vpslldq	ymm4, ymm3, 8           # ymm4 = zero,zero,zero,zero,zero,zero,zero,zero,ymm3[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm3[16,17,18,19,20,21,22,23]
	vpaddw	ymm3, ymm3, ymm4
	vpshufb	xmm4, xmm3, xmm2
	vperm2i128	ymm4, ymm4, ymm4, 40 # ymm4 = zero,zero,ymm4[0,1]
	vpaddw	ymm0, ymm3, ymm0
	vpaddw	ymm0, ymm0, ymm4
	vmovdqa	ymmword ptr [rbx], ymm0
	vpshufhw	ymm0, ymm0, 239 # ymm0 = ymm0[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vpermd	ymm0, ymm1, ymm0
	add	rbx, 32
	cmp	r15, rbx
	jne	.LBB0_4
.LBB0_5:
	cmp	r15, r14
	je	.LBB0_8
# %bb.6:
	xor	ecx, ecx
	jmp	.LBB0_7
.LBB0_1:
	vpxor	xmm0, xmm0, xmm0
.LBB0_7:
	mov	rax, r15
	sub	rax, r14
	add	rax, 32
	sar	rax
	lea	edx, [rcx - 1]
	vmovd	xmm1, edx
	vpbroadcastw	ymm1, xmm1
	mov	edx, 16
	sub	edx, eax
	vmovd	xmm2, edx
	vpbroadcastw	ymm2, xmm2
	vmovdqa	ymm3, ymmword ptr [rip + .LCPI0_0] # ymm3 = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
	vpcmpgtw	ymm1, ymm3, ymm1
	vpcmpgtw	ymm2, ymm2, ymm3
	vpand	ymm1, ymm1, ymm2
	vpand	ymm1, ymm1, ymmword ptr [r15]
	vpslldq	ymm2, ymm1, 2           # ymm2 = zero,zero,ymm1[0,1,2,3,4,5,6,7,8,9,10,11,12,13],zero,zero,ymm1[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm1, ymm2, ymm1
	vpslldq	ymm2, ymm1, 4           # ymm2 = zero,zero,zero,zero,ymm1[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm1[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm1, ymm1, ymm2
	vpslldq	ymm2, ymm1, 8           # ymm2 = zero,zero,zero,zero,zero,zero,zero,zero,ymm1[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm1[16,17,18,19,20,21,22,23]
	vpaddw	ymm1, ymm1, ymm2
	vpshufb	xmm2, xmm1, xmmword ptr [rip + .LCPI0_1] # xmm2 = xmm1[14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	vperm2i128	ymm2, ymm2, ymm2, 40 # ymm2 = zero,zero,ymm2[0,1]
	vpaddw	ymm0, ymm1, ymm0
	vpaddw	ymm0, ymm0, ymm2
	vmovdqa	ymmword ptr [rsp], ymm0
	add	rax, rcx
	lea	rdi, [r15 + 2*rcx]
	lea	rsi, [rsp + 2*rcx]
	add	rax, rax
	mov	edx, 32
	sub	rdx, rax
	vzeroupper
	call	memcpy
.LBB0_8:
	lea	rsp, [rbp - 24]
	pop	rbx
	pop	r14
	pop	r15
	pop	rbp
	.cfi_def_cfa rsp, 8
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z22inclusive_scan_inplacePsS_, .Lfunc_end0-_Z22inclusive_scan_inplacePsS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
