	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5               # -- Begin function _Z14inclusive_scanPsS_
.LCPI0_0:
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
	.short	16                      # 0x10
.LCPI0_3:
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
	.globl	_Z14inclusive_scanPsS_
	.p2align	4, 0x90
	.type	_Z14inclusive_scanPsS_,@function
_Z14inclusive_scanPsS_:                 # @_Z14inclusive_scanPsS_
.L_Z14inclusive_scanPsS_$local:
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
	sub	rsp, 160
	.cfi_offset rbx, -40
	.cfi_offset r14, -32
	.cfi_offset r15, -24
	mov	r14, rsi
	mov	rax, rsi
	sub	rax, rdi
	cmp	rax, 31
	jg	.LBB0_4
# %bb.1:
	lea	rax, [rdi + 4096]
	and	rax, -4096
	sub	rax, rdi
	cmp	rax, 31
	jg	.LBB0_3
# %bb.2:
	lea	rax, [r14 - 32]
	mov	rcx, rdi
	sub	rcx, rax
	lea	rsi, [rsp + rcx]
	mov	edx, 32
	sub	rdx, rcx
	mov	eax, ecx
	shr	eax
	dec	eax
	vmovd	xmm0, eax
	vpbroadcastw	ymm0, xmm0
	vmovdqa	ymm1, ymmword ptr [rip + .LCPI0_3] # ymm1 = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
	vpcmpgtw	ymm0, ymm1, ymm0
	vpand	ymm0, ymm0, ymmword ptr [r14 - 32]
	vpslldq	ymm1, ymm0, 2           # ymm1 = zero,zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11,12,13],zero,zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm0, ymm1, ymm0
	vpslldq	ymm1, ymm0, 4           # ymm1 = zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm0, ymm0, ymm1
	vpslldq	ymm1, ymm0, 8           # ymm1 = zero,zero,zero,zero,zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23]
	vpaddw	ymm0, ymm0, ymm1
	vpshufb	xmm1, xmm0, xmmword ptr [rip + .LCPI0_1] # xmm1 = xmm0[14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	vperm2i128	ymm1, ymm1, ymm1, 40 # ymm1 = zero,zero,ymm1[0,1]
	vpaddw	ymm0, ymm0, ymm1
	vmovdqa	ymmword ptr [rsp], ymm0
	vzeroupper
	call	memcpy
	jmp	.LBB0_16
.LBB0_4:
	vmovdqu	ymm0, ymmword ptr [rdi]
	vpxor	xmm5, xmm5, xmm5
	cmp	rax, 65
	jl	.LBB0_5
# %bb.6:
	lea	rax, [rdi + 32]
	mov	rbx, rax
	and	rbx, -32
	mov	r15, r14
	and	r15, -32
	add	r15, -32
	vmovaps	ymm1, ymmword ptr [rbx]
	vmovaps	ymmword ptr [rsp + 32], ymm1 # 32-byte Spill
	and	eax, 31
	mov	edx, 32
	sub	rdx, rax
                                        # kill: def $eax killed $eax killed $rax
	shr	eax
	mov	ecx, 16
	sub	ecx, eax
	vmovd	xmm1, ecx
	vpbroadcastw	ymm1, xmm1
	vmovdqa	ymm2, ymmword ptr [rip + .LCPI0_0] # ymm2 = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]
	vpsubusw	ymm1, ymm2, ymm1
	vpxor	xmm2, xmm2, xmm2
	vpcmpeqw	ymm1, ymm1, ymm2
	vpand	ymm0, ymm0, ymm1
	vpslldq	ymm1, ymm0, 2           # ymm1 = zero,zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11,12,13],zero,zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm0, ymm1, ymm0
	vpslldq	ymm1, ymm0, 4           # ymm1 = zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm0, ymm0, ymm1
	vpslldq	ymm1, ymm0, 8           # ymm1 = zero,zero,zero,zero,zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23]
	vpaddw	ymm0, ymm0, ymm1
	vpshufb	xmm1, xmm0, xmmword ptr [rip + .LCPI0_1] # xmm1 = xmm0[14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	vperm2i128	ymm1, ymm1, ymm1, 40 # ymm1 = zero,zero,ymm1[0,1]
	vpaddw	ymm0, ymm0, ymm1
	vpshufhw	ymm1, ymm0, 239 # ymm1 = ymm0[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vpbroadcastd	ymm2, dword ptr [rip + .LCPI0_2] # ymm2 = [6,6,6,6,6,6,6,6]
	vmovdqa	ymmword ptr [rsp + 96], ymm2 # 32-byte Spill
	vpermd	ymm1, ymm2, ymm1
	vmovdqa	ymmword ptr [rsp + 64], ymm1 # 32-byte Spill
	vmovdqa	ymmword ptr [rsp], ymm0
	mov	rsi, rsp
	vzeroupper
	call	memcpy
	cmp	r15, rbx
	je	.LBB0_7
# %bb.8:
	vmovdqa	xmm0, xmmword ptr [rip + .LCPI0_1] # xmm0 = [14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	vmovdqa	xmm1, xmmword ptr [rip + .LCPI0_1] # xmm1 = [14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	vmovdqa	ymm5, ymmword ptr [rsp + 64] # 32-byte Reload
	vmovdqa	ymm6, ymmword ptr [rsp + 96] # 32-byte Reload
	vmovdqa	ymm3, ymmword ptr [rsp + 32] # 32-byte Reload
	jmp	.LBB0_9
	.p2align	4, 0x90
.LBB0_13:                               #   in Loop: Header=BB0_9 Depth=1
	vmovdqa	ymm3, ymmword ptr [rbx]
	cmp	rbx, r15
	je	.LBB0_14
.LBB0_9:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_12 Depth 2
	vpslldq	ymm2, ymm3, 2           # ymm2 = zero,zero,ymm3[0,1,2,3,4,5,6,7,8,9,10,11,12,13],zero,zero,ymm3[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm2, ymm2, ymm3
	vpslldq	ymm3, ymm2, 4           # ymm3 = zero,zero,zero,zero,ymm2[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm2[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm2, ymm2, ymm3
	vpslldq	ymm3, ymm2, 8           # ymm3 = zero,zero,zero,zero,zero,zero,zero,zero,ymm2[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm2[16,17,18,19,20,21,22,23]
	vpaddw	ymm2, ymm2, ymm3
	vpshufb	xmm3, xmm2, xmm0
	vperm2i128	ymm3, ymm3, ymm3, 40 # ymm3 = zero,zero,ymm3[0,1]
	vpaddw	ymm2, ymm2, ymm5
	vpaddw	ymm2, ymm2, ymm3
	vpshufhw	ymm3, ymm2, 239 # ymm3 = ymm2[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vpermd	ymm5, ymm6, ymm3
	vmovdqa	ymmword ptr [rbx], ymm2
	lea	rax, [rbx + 32]
	vmovdqa	ymm3, ymmword ptr [rbx + 32]
	cmp	rax, r15
	je	.LBB0_14
# %bb.10:                               #   in Loop: Header=BB0_9 Depth=1
	vpslldq	ymm2, ymm3, 2           # ymm2 = zero,zero,ymm3[0,1,2,3,4,5,6,7,8,9,10,11,12,13],zero,zero,ymm3[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm2, ymm2, ymm3
	vpslldq	ymm3, ymm2, 4           # ymm3 = zero,zero,zero,zero,ymm2[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm2[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm2, ymm2, ymm3
	vpslldq	ymm3, ymm2, 8           # ymm3 = zero,zero,zero,zero,zero,zero,zero,zero,ymm2[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm2[16,17,18,19,20,21,22,23]
	vpaddw	ymm2, ymm2, ymm3
	vpshufb	xmm3, xmm2, xmm0
	vperm2i128	ymm3, ymm3, ymm3, 40 # ymm3 = zero,zero,ymm3[0,1]
	vpaddw	ymm2, ymm5, ymm2
	vpaddw	ymm2, ymm2, ymm3
	vpshufhw	ymm3, ymm2, 239 # ymm3 = ymm2[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vmovdqa	ymmword ptr [rbx + 32], ymm2
	vpermd	ymm5, ymm6, ymm3
	add	rbx, 64
	mov	rcx, r15
	sub	rcx, rbx
	sar	rcx
	lea	rax, [rcx + 31]
	cmp	rax, 63
	jb	.LBB0_13
# %bb.11:                               #   in Loop: Header=BB0_9 Depth=1
	test	rcx, rcx
	cmovns	rax, rcx
	sar	rax, 5
	.p2align	4, 0x90
.LBB0_12:                               #   Parent Loop BB0_9 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovdqa	ymm2, ymmword ptr [rbx]
	vmovdqa	ymm3, ymmword ptr [rbx + 32]
	vpslldq	ymm4, ymm2, 2           # ymm4 = zero,zero,ymm2[0,1,2,3,4,5,6,7,8,9,10,11,12,13],zero,zero,ymm2[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm2, ymm4, ymm2
	vpslldq	ymm4, ymm2, 4           # ymm4 = zero,zero,zero,zero,ymm2[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm2[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm2, ymm2, ymm4
	vpslldq	ymm4, ymm2, 8           # ymm4 = zero,zero,zero,zero,zero,zero,zero,zero,ymm2[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm2[16,17,18,19,20,21,22,23]
	vpaddw	ymm2, ymm2, ymm4
	vpshufb	xmm4, xmm2, xmm1
	vperm2i128	ymm4, ymm4, ymm4, 40 # ymm4 = zero,zero,ymm4[0,1]
	vpaddw	ymm2, ymm2, ymm5
	vpaddw	ymm2, ymm2, ymm4
	vpshufhw	ymm4, ymm2, 239 # ymm4 = ymm2[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vpermd	ymm4, ymm6, ymm4
	vmovdqa	ymmword ptr [rbx], ymm2
	vpslldq	ymm2, ymm3, 2           # ymm2 = zero,zero,ymm3[0,1,2,3,4,5,6,7,8,9,10,11,12,13],zero,zero,ymm3[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm2, ymm2, ymm3
	vpslldq	ymm3, ymm2, 4           # ymm3 = zero,zero,zero,zero,ymm2[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm2[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm2, ymm2, ymm3
	vpslldq	ymm3, ymm2, 8           # ymm3 = zero,zero,zero,zero,zero,zero,zero,zero,ymm2[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm2[16,17,18,19,20,21,22,23]
	vpaddw	ymm2, ymm2, ymm3
	vpshufb	xmm3, xmm2, xmm1
	vperm2i128	ymm3, ymm3, ymm3, 40 # ymm3 = zero,zero,ymm3[0,1]
	vpaddw	ymm2, ymm2, ymm3
	vpaddw	ymm2, ymm4, ymm2
	vpshufhw	ymm3, ymm2, 239 # ymm3 = ymm2[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vpermd	ymm5, ymm6, ymm3
	vmovdqa	ymmword ptr [rbx + 32], ymm2
	add	rbx, 64
	dec	rax
	jne	.LBB0_12
	jmp	.LBB0_13
.LBB0_3:
	mov	rdx, rdi
	sub	rdx, r14
	lea	eax, [rdx + 32]
	shr	eax
	mov	ecx, 16
	sub	ecx, eax
	vmovd	xmm0, ecx
	vpbroadcastw	ymm0, xmm0
	vpcmpgtw	ymm0, ymm0, ymmword ptr [rip + .LCPI0_3]
	vpand	ymm0, ymm0, ymmword ptr [rdi]
	vpslldq	ymm1, ymm0, 2           # ymm1 = zero,zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11,12,13],zero,zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm0, ymm1, ymm0
	vpslldq	ymm1, ymm0, 4           # ymm1 = zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm0, ymm0, ymm1
	vpslldq	ymm1, ymm0, 8           # ymm1 = zero,zero,zero,zero,zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23]
	vpaddw	ymm0, ymm0, ymm1
	vpshufb	xmm1, xmm0, xmmword ptr [rip + .LCPI0_1] # xmm1 = xmm0[14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	vperm2i128	ymm1, ymm1, ymm1, 40 # ymm1 = zero,zero,ymm1[0,1]
	vpaddw	ymm0, ymm0, ymm1
	vmovdqa	ymmword ptr [rsp], ymm0
	neg	rdx
	mov	rsi, rsp
	vzeroupper
	call	memcpy
	jmp	.LBB0_16
.LBB0_5:
	vmovdqa	ymm3, ymm0
	mov	rbx, rdi
	jmp	.LBB0_15
.LBB0_14:
	mov	rbx, r15
	jmp	.LBB0_15
.LBB0_7:
	vmovdqa	ymm5, ymmword ptr [rsp + 64] # 32-byte Reload
	vmovdqa	ymm3, ymmword ptr [rsp + 32] # 32-byte Reload
.LBB0_15:
	lea	rax, [r14 - 32]
	vmovups	ymm0, ymmword ptr [r14 - 32]
	vmovaps	ymmword ptr [rsp + 64], ymm0 # 32-byte Spill
	mov	rdx, rbx
	sub	rdx, rax
	lea	eax, [rdx + 32]
	shr	eax
	mov	ecx, 16
	sub	ecx, eax
	vmovd	xmm0, ecx
	vpbroadcastw	ymm0, xmm0
	vpcmpgtw	ymm0, ymm0, ymmword ptr [rip + .LCPI0_3]
	vpand	ymm0, ymm3, ymm0
	vpslldq	ymm1, ymm0, 2           # ymm1 = zero,zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11,12,13],zero,zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm0, ymm1, ymm0
	vpslldq	ymm1, ymm0, 4           # ymm1 = zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm0, ymm0, ymm1
	vpslldq	ymm1, ymm0, 8           # ymm1 = zero,zero,zero,zero,zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23]
	vpaddw	ymm0, ymm0, ymm1
	vpshufb	xmm1, xmm0, xmmword ptr [rip + .LCPI0_1] # xmm1 = xmm0[14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	vperm2i128	ymm1, ymm1, ymm1, 40 # ymm1 = zero,zero,ymm1[0,1]
	vpaddw	ymm0, ymm0, ymm5
	vpaddw	ymm0, ymm0, ymm1
	vpshufhw	ymm1, ymm0, 239 # ymm1 = ymm0[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vpbroadcastd	ymm2, dword ptr [rip + .LCPI0_2] # ymm2 = [6,6,6,6,6,6,6,6]
	vpermd	ymm1, ymm2, ymm1
	vmovdqa	ymmword ptr [rsp + 32], ymm1 # 32-byte Spill
	vmovdqa	ymmword ptr [rsp], ymm0
	neg	rdx
	mov	rsi, rsp
	mov	rdi, rbx
	vzeroupper
	call	memcpy
	vmovdqa	ymm1, ymmword ptr [rsp + 64] # 32-byte Reload
	vpslldq	ymm0, ymm1, 2           # ymm0 = zero,zero,ymm1[0,1,2,3,4,5,6,7,8,9,10,11,12,13],zero,zero,ymm1[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm0, ymm0, ymm1
	vpslldq	ymm1, ymm0, 4           # ymm1 = zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm0, ymm0, ymm1
	vpslldq	ymm1, ymm0, 8           # ymm1 = zero,zero,zero,zero,zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23]
	vpaddw	ymm0, ymm0, ymm1
	vpshufb	xmm1, xmm0, xmmword ptr [rip + .LCPI0_1] # xmm1 = xmm0[14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	vperm2i128	ymm1, ymm1, ymm1, 40 # ymm1 = zero,zero,ymm1[0,1]
	vpaddw	ymm0, ymm0, ymm1
	vpaddw	ymm0, ymm0, ymmword ptr [rsp + 32] # 32-byte Folded Reload
	vmovdqu	ymmword ptr [r14 - 32], ymm0
.LBB0_16:
	lea	rsp, [rbp - 24]
	pop	rbx
	pop	r14
	pop	r15
	pop	rbp
	.cfi_def_cfa rsp, 8
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z14inclusive_scanPsS_, .Lfunc_end0-_Z14inclusive_scanPsS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
