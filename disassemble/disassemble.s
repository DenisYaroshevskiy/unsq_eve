	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5               # -- Begin function _Z29inclusive_scan_overlap_storesPiS_
.LCPI0_0:
	.long	0                       # 0x0
	.long	1                       # 0x1
	.long	2                       # 0x2
	.long	3                       # 0x3
	.long	4                       # 0x4
	.long	5                       # 0x5
	.long	6                       # 0x6
	.long	7                       # 0x7
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2
.LCPI0_1:
	.long	7                       # 0x7
	.text
	.globl	_Z29inclusive_scan_overlap_storesPiS_
	.p2align	4, 0x90
	.type	_Z29inclusive_scan_overlap_storesPiS_,@function
_Z29inclusive_scan_overlap_storesPiS_:  # @_Z29inclusive_scan_overlap_storesPiS_
.L_Z29inclusive_scan_overlap_storesPiS_$local:
	.cfi_startproc
# %bb.0:
	mov	rax, rsi
	sub	rax, rdi
	cmp	rax, 31
	jg	.LBB0_3
# %bb.1:
	lea	rax, [rdi + 4096]
	and	rax, -4096
	sub	rax, rdi
	cmp	rax, 31
	jg	.LBB0_2
# %bb.10:
	lea	rax, [rsi - 32]
	sub	rdi, rax
	shr	rdi, 2
	dec	edi
	vmovd	xmm0, edi
	vpbroadcastd	ymm0, xmm0
	vmovdqa	ymm1, ymmword ptr [rip + .LCPI0_0] # ymm1 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm0, ymm1, ymm0
	vpand	ymm1, ymm0, ymmword ptr [rsi - 32]
	vpslldq	ymm2, ymm1, 4           # ymm2 = zero,zero,zero,zero,ymm1[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm1[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddd	ymm1, ymm2, ymm1
	vpslldq	ymm2, ymm1, 8           # ymm2 = zero,zero,zero,zero,zero,zero,zero,zero,ymm1[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm1[16,17,18,19,20,21,22,23]
	vpaddd	ymm1, ymm1, ymm2
	vpshufd	xmm2, xmm1, 255         # xmm2 = xmm1[3,3,3,3]
	vperm2i128	ymm2, ymm2, ymm2, 40 # ymm2 = zero,zero,ymm2[0,1]
	vpaddd	ymm1, ymm1, ymm2
	vpmaskmovd	ymmword ptr [rsi - 32], ymm0, ymm1
	vzeroupper
	ret
.LBB0_3:
	vmovdqu	ymm2, ymmword ptr [rdi]
	vpxor	xmm0, xmm0, xmm0
	cmp	rax, 65
	jl	.LBB0_4
# %bb.5:
	lea	r9, [rdi + 32]
	mov	rax, r9
	and	rax, -32
	mov	rdx, rsi
	and	rdx, -32
	lea	r8, [rdx - 32]
	vmovdqa	ymm1, ymmword ptr [rax]
	shr	r9d, 2
	and	r9d, 7
	mov	ecx, 8
	sub	ecx, r9d
	vmovd	xmm0, ecx
	vpbroadcastd	ymm0, xmm0
	vpcmpgtd	ymm3, ymm0, ymmword ptr [rip + .LCPI0_0]
	vpand	ymm0, ymm2, ymm3
	vpslldq	ymm2, ymm0, 4           # ymm2 = zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddd	ymm0, ymm2, ymm0
	vpslldq	ymm2, ymm0, 8           # ymm2 = zero,zero,zero,zero,zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23]
	vpaddd	ymm0, ymm0, ymm2
	vpshufd	xmm2, xmm0, 255         # xmm2 = xmm0[3,3,3,3]
	vperm2i128	ymm2, ymm2, ymm2, 40 # ymm2 = zero,zero,ymm2[0,1]
	vpaddd	ymm4, ymm0, ymm2
	vpbroadcastd	ymm2, dword ptr [rip + .LCPI0_1] # ymm2 = [7,7,7,7,7,7,7,7]
	vpermd	ymm0, ymm2, ymm4
	vpmaskmovd	ymmword ptr [rdi], ymm3, ymm4
	cmp	r8, rax
	je	.LBB0_9
# %bb.6:
	add	rax, 32
	.p2align	4, 0x90
.LBB0_7:                                # =>This Inner Loop Header: Depth=1
	vpslldq	ymm3, ymm1, 4           # ymm3 = zero,zero,zero,zero,ymm1[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm1[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddd	ymm1, ymm3, ymm1
	vpslldq	ymm3, ymm1, 8           # ymm3 = zero,zero,zero,zero,zero,zero,zero,zero,ymm1[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm1[16,17,18,19,20,21,22,23]
	vpaddd	ymm1, ymm1, ymm3
	vpshufd	xmm3, xmm1, 255         # xmm3 = xmm1[3,3,3,3]
	vperm2i128	ymm3, ymm3, ymm3, 40 # ymm3 = zero,zero,ymm3[0,1]
	vpaddd	ymm0, ymm1, ymm0
	vpaddd	ymm1, ymm0, ymm3
	vpermd	ymm0, ymm2, ymm1
	vmovdqa	ymmword ptr [rax - 32], ymm1
	vmovdqa	ymm1, ymmword ptr [rax]
	add	rax, 32
	cmp	rdx, rax
	jne	.LBB0_7
# %bb.8:
	mov	rax, r8
	jmp	.LBB0_9
.LBB0_2:
	mov	rax, rdi
	sub	rax, rsi
	add	rax, 32
	shr	rax, 2
	mov	ecx, 8
	sub	ecx, eax
	vmovd	xmm0, ecx
	vpbroadcastd	ymm0, xmm0
	vpcmpgtd	ymm0, ymm0, ymmword ptr [rip + .LCPI0_0]
	vpand	ymm1, ymm0, ymmword ptr [rdi]
	vpslldq	ymm2, ymm1, 4           # ymm2 = zero,zero,zero,zero,ymm1[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm1[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddd	ymm1, ymm2, ymm1
	vpslldq	ymm2, ymm1, 8           # ymm2 = zero,zero,zero,zero,zero,zero,zero,zero,ymm1[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm1[16,17,18,19,20,21,22,23]
	vpaddd	ymm1, ymm1, ymm2
	vpshufd	xmm2, xmm1, 255         # xmm2 = xmm1[3,3,3,3]
	vperm2i128	ymm2, ymm2, ymm2, 40 # ymm2 = zero,zero,ymm2[0,1]
	vpaddd	ymm1, ymm1, ymm2
	vpmaskmovd	ymmword ptr [rdi], ymm0, ymm1
	vzeroupper
	ret
.LBB0_4:
	vmovdqa	ymm1, ymm2
	mov	rax, rdi
.LBB0_9:
	lea	rcx, [rsi - 32]
	mov	rdx, rax
	sub	rdx, rcx
	add	rdx, 32
	shr	rdx, 2
	mov	ecx, 8
	sub	ecx, edx
	vmovd	xmm2, ecx
	vpbroadcastd	ymm2, xmm2
	vpcmpgtd	ymm2, ymm2, ymmword ptr [rip + .LCPI0_0]
	vmovdqu	ymm3, ymmword ptr [rsi - 32]
	vpand	ymm1, ymm1, ymm2
	vpslldq	ymm4, ymm1, 4           # ymm4 = zero,zero,zero,zero,ymm1[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm1[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddd	ymm1, ymm4, ymm1
	vpslldq	ymm4, ymm1, 8           # ymm4 = zero,zero,zero,zero,zero,zero,zero,zero,ymm1[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm1[16,17,18,19,20,21,22,23]
	vpaddd	ymm1, ymm1, ymm4
	vpshufd	xmm4, xmm1, 255         # xmm4 = xmm1[3,3,3,3]
	vperm2i128	ymm4, ymm4, ymm4, 40 # ymm4 = zero,zero,ymm4[0,1]
	vpaddd	ymm0, ymm1, ymm0
	vpaddd	ymm0, ymm0, ymm4
	vpbroadcastd	ymm1, dword ptr [rip + .LCPI0_1] # ymm1 = [7,7,7,7,7,7,7,7]
	vpermd	ymm1, ymm1, ymm0
	vpmaskmovd	ymmword ptr [rax], ymm2, ymm0
	vpslldq	ymm0, ymm3, 4           # ymm0 = zero,zero,zero,zero,ymm3[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm3[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddd	ymm0, ymm0, ymm3
	vpslldq	ymm2, ymm0, 8           # ymm2 = zero,zero,zero,zero,zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23]
	vpaddd	ymm0, ymm0, ymm2
	vpshufd	xmm2, xmm0, 255         # xmm2 = xmm0[3,3,3,3]
	vperm2i128	ymm2, ymm2, ymm2, 40 # ymm2 = zero,zero,ymm2[0,1]
	vpaddd	ymm0, ymm0, ymm2
	vpaddd	ymm0, ymm0, ymm1
	vmovdqu	ymmword ptr [rsi - 32], ymm0
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z29inclusive_scan_overlap_storesPiS_, .Lfunc_end0-_Z29inclusive_scan_overlap_storesPiS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
