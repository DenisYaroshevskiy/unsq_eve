	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5               # -- Begin function _Z22inclusive_scan_inplacePiS_
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
	.globl	_Z22inclusive_scan_inplacePiS_
	.p2align	4, 0x90
	.type	_Z22inclusive_scan_inplacePiS_,@function
_Z22inclusive_scan_inplacePiS_:         # @_Z22inclusive_scan_inplacePiS_
.L_Z22inclusive_scan_inplacePiS_$local:
	.cfi_startproc
# %bb.0:
	mov	rcx, rdi
	and	rcx, -32
	mov	rax, rsi
	and	rax, -32
	shr	edi, 2
	and	edi, 7
	dec	edi
	cmp	rcx, rax
	je	.LBB0_1
# %bb.2:
	vmovd	xmm0, edi
	vpbroadcastd	ymm0, xmm0
	vmovdqa	ymm1, ymmword ptr [rip + .LCPI0_0] # ymm1 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm0, ymm1, ymm0
	vpand	ymm1, ymm0, ymmword ptr [rcx]
	vpslldq	ymm2, ymm1, 4           # ymm2 = zero,zero,zero,zero,ymm1[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm1[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddd	ymm1, ymm2, ymm1
	vpslldq	ymm2, ymm1, 8           # ymm2 = zero,zero,zero,zero,zero,zero,zero,zero,ymm1[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm1[16,17,18,19,20,21,22,23]
	vpaddd	ymm1, ymm1, ymm2
	vpshufd	xmm2, xmm1, 255         # xmm2 = xmm1[3,3,3,3]
	vperm2i128	ymm2, ymm2, ymm2, 40 # ymm2 = zero,zero,ymm2[0,1]
	vpaddd	ymm2, ymm1, ymm2
	vpmaskmovd	ymmword ptr [rcx], ymm0, ymm2
	vpbroadcastd	ymm1, dword ptr [rip + .LCPI0_1] # ymm1 = [7,7,7,7,7,7,7,7]
	vpermd	ymm0, ymm1, ymm2
	add	rcx, 32
	cmp	rcx, rax
	je	.LBB0_4
	.p2align	4, 0x90
.LBB0_3:                                # =>This Inner Loop Header: Depth=1
	vmovdqa	ymm2, ymmword ptr [rcx]
	vpslldq	ymm3, ymm2, 4           # ymm3 = zero,zero,zero,zero,ymm2[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm2[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddd	ymm2, ymm3, ymm2
	vpslldq	ymm3, ymm2, 8           # ymm3 = zero,zero,zero,zero,zero,zero,zero,zero,ymm2[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm2[16,17,18,19,20,21,22,23]
	vpaddd	ymm2, ymm2, ymm3
	vpshufd	xmm3, xmm2, 255         # xmm3 = xmm2[3,3,3,3]
	vperm2i128	ymm3, ymm3, ymm3, 40 # ymm3 = zero,zero,ymm3[0,1]
	vpaddd	ymm0, ymm2, ymm0
	vpaddd	ymm0, ymm0, ymm3
	vmovdqa	ymmword ptr [rcx], ymm0
	vpermd	ymm0, ymm1, ymm0
	add	rcx, 32
	cmp	rax, rcx
	jne	.LBB0_3
.LBB0_4:
	mov	edi, -1
	cmp	rax, rsi
	jne	.LBB0_5
# %bb.6:
	vzeroupper
	ret
.LBB0_1:
	vpxor	xmm0, xmm0, xmm0
.LBB0_5:
	mov	rcx, rax
	sub	rcx, rsi
	add	rcx, 32
	shr	rcx, 2
	vmovd	xmm1, edi
	vpbroadcastd	ymm1, xmm1
	mov	edx, 8
	sub	edx, ecx
	vmovd	xmm2, edx
	vpbroadcastd	ymm2, xmm2
	vmovdqa	ymm3, ymmword ptr [rip + .LCPI0_0] # ymm3 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm1, ymm3, ymm1
	vpcmpgtd	ymm2, ymm2, ymm3
	vpand	ymm1, ymm1, ymm2
	vpand	ymm2, ymm1, ymmword ptr [rax]
	vpslldq	ymm3, ymm2, 4           # ymm3 = zero,zero,zero,zero,ymm2[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm2[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddd	ymm2, ymm3, ymm2
	vpslldq	ymm3, ymm2, 8           # ymm3 = zero,zero,zero,zero,zero,zero,zero,zero,ymm2[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm2[16,17,18,19,20,21,22,23]
	vpaddd	ymm2, ymm2, ymm3
	vpshufd	xmm3, xmm2, 255         # xmm3 = xmm2[3,3,3,3]
	vperm2i128	ymm3, ymm3, ymm3, 40 # ymm3 = zero,zero,ymm3[0,1]
	vpaddd	ymm0, ymm2, ymm0
	vpaddd	ymm0, ymm0, ymm3
	vpmaskmovd	ymmword ptr [rax], ymm1, ymm0
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z22inclusive_scan_inplacePiS_, .Lfunc_end0-_Z22inclusive_scan_inplacePiS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
