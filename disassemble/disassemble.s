	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5                               # -- Begin function _Z14inclusive_scanPiS_
.LCPI0_0:
	.long	0                               # 0x0
	.long	1                               # 0x1
	.long	2                               # 0x2
	.long	3                               # 0x3
	.long	4                               # 0x4
	.long	5                               # 0x5
	.long	6                               # 0x6
	.long	7                               # 0x7
.LCPI0_2:
	.long	1                               # 0x1
	.long	2                               # 0x2
	.long	3                               # 0x3
	.long	4                               # 0x4
	.long	5                               # 0x5
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	8                               # 0x8
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2
.LCPI0_1:
	.long	7                               # 0x7
	.text
	.globl	_Z14inclusive_scanPiS_
	.p2align	4, 0x90
	.type	_Z14inclusive_scanPiS_,@function
_Z14inclusive_scanPiS_:                 # @_Z14inclusive_scanPiS_
	.cfi_startproc
# %bb.0:
	cmp	rdi, rsi
	je	.LBB0_8
# %bb.1:
	mov	rcx, rdi
	and	rcx, -32
	mov	rax, rsi
	and	rax, -32
	shr	edi, 2
	and	edi, 7
	cmp	rcx, rax
	je	.LBB0_2
# %bb.3:
	vmovdqa	ymm0, ymmword ptr [rcx]
	vmovd	xmm1, edi
	vpbroadcastd	ymm2, xmm1
	vpcmpgtd	ymm1, ymm2, ymmword ptr [rip + .LCPI0_0]
	vpxor	xmm3, xmm3, xmm3
	vpblendvb	ymm0, ymm0, ymm3, ymm1
	vpslldq	ymm1, ymm0, 4                   # ymm1 = zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddd	ymm0, ymm1, ymm0
	vpslldq	ymm1, ymm0, 8                   # ymm1 = zero,zero,zero,zero,zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23]
	vpaddd	ymm0, ymm0, ymm1
	vpshufd	xmm1, xmm0, 255                 # xmm1 = xmm0[3,3,3,3]
	vperm2i128	ymm1, ymm1, ymm1, 40    # ymm1 = zero,zero,ymm1[0,1]
	vpaddd	ymm3, ymm0, ymm1
	vpbroadcastd	ymm1, dword ptr [rip + .LCPI0_1] # ymm1 = [7,7,7,7,7,7,7,7]
	vpermd	ymm0, ymm1, ymm3
	vmovdqa	ymm4, ymmword ptr [rip + .LCPI0_2] # ymm4 = [1,2,3,4,5,6,7,8]
	vpcmpgtd	ymm2, ymm4, ymm2
	vpmaskmovd	ymmword ptr [rcx], ymm2, ymm3
	add	rcx, 32
	cmp	rcx, rax
	je	.LBB0_6
	.p2align	4, 0x90
.LBB0_4:                                # =>This Inner Loop Header: Depth=1
	vmovdqa	ymm2, ymmword ptr [rcx]
	vpslldq	ymm3, ymm2, 4                   # ymm3 = zero,zero,zero,zero,ymm2[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm2[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddd	ymm2, ymm3, ymm2
	vpslldq	ymm3, ymm2, 8                   # ymm3 = zero,zero,zero,zero,zero,zero,zero,zero,ymm2[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm2[16,17,18,19,20,21,22,23]
	vpaddd	ymm2, ymm2, ymm3
	vpshufd	xmm3, xmm2, 255                 # xmm3 = xmm2[3,3,3,3]
	vperm2i128	ymm3, ymm3, ymm3, 40    # ymm3 = zero,zero,ymm3[0,1]
	vpaddd	ymm0, ymm2, ymm0
	vpaddd	ymm2, ymm0, ymm3
	vpermd	ymm0, ymm1, ymm2
	vmovdqa	ymmword ptr [rcx], ymm2
	add	rcx, 32
	cmp	rcx, rax
	jne	.LBB0_4
.LBB0_6:
	xor	edi, edi
	cmp	rax, rsi
	jne	.LBB0_7
.LBB0_8:
	vzeroupper
	ret
.LBB0_2:
	vpxor	xmm0, xmm0, xmm0
.LBB0_7:
	mov	rcx, rax
	sub	rcx, rsi
	add	rcx, 32
	shr	rcx, 2
	vmovd	xmm1, edi
	vpbroadcastd	ymm1, xmm1
	vmovdqa	ymm2, ymmword ptr [rip + .LCPI0_0] # ymm2 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm3, ymm1, ymm2
	mov	edx, 8
	sub	edx, ecx
	vmovd	xmm4, edx
	vpbroadcastd	ymm4, xmm4
	vpcmpgtd	ymm2, ymm4, ymm2
	vpandn	ymm3, ymm3, ymm2
	vpxor	xmm4, xmm4, xmm4
	vpblendvb	ymm3, ymm4, ymmword ptr [rax], ymm3
	vpslldq	ymm4, ymm3, 4                   # ymm4 = zero,zero,zero,zero,ymm3[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm3[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddd	ymm3, ymm4, ymm3
	vpslldq	ymm4, ymm3, 8                   # ymm4 = zero,zero,zero,zero,zero,zero,zero,zero,ymm3[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm3[16,17,18,19,20,21,22,23]
	vpaddd	ymm3, ymm3, ymm4
	vpshufd	xmm4, xmm3, 255                 # xmm4 = xmm3[3,3,3,3]
	vperm2i128	ymm4, ymm4, ymm4, 40    # ymm4 = zero,zero,ymm4[0,1]
	vpaddd	ymm0, ymm3, ymm0
	vpaddd	ymm0, ymm0, ymm4
	vmovdqa	ymm3, ymmword ptr [rip + .LCPI0_2] # ymm3 = [1,2,3,4,5,6,7,8]
	vpcmpgtd	ymm1, ymm3, ymm1
	vpand	ymm1, ymm1, ymm2
	vpmaskmovd	ymmword ptr [rax], ymm1, ymm0
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z14inclusive_scanPiS_, .Lfunc_end0-_Z14inclusive_scanPiS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 13.0.0 (https://github.com/llvm/llvm-project.git e3251f2ec44bd65f440d215517f135c39f22d1b9)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
