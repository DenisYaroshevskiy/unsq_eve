	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5               # -- Begin function _Z19transform_unalignedPiS_
.LCPI0_0:
	.long	0                       # 0x0
	.long	1                       # 0x1
	.long	2                       # 0x2
	.long	3                       # 0x3
	.long	4                       # 0x4
	.long	5                       # 0x5
	.long	6                       # 0x6
	.long	7                       # 0x7
	.text
	.globl	_Z19transform_unalignedPiS_
	.p2align	4, 0x90
	.type	_Z19transform_unalignedPiS_,@function
_Z19transform_unalignedPiS_:            # @_Z19transform_unalignedPiS_
.L_Z19transform_unalignedPiS_$local:
	.cfi_startproc
# %bb.0:
	mov	rax, rsi
	sub	rax, rdi
	cmp	rax, 32
	jge	.LBB0_1
.LBB0_12:
	mov	rax, rdi
	sub	rax, rsi
	je	.LBB0_15
# %bb.13:
	lea	rcx, [rdi + 4096]
	and	rcx, -4096
	sub	rcx, rdi
	cmp	rcx, 31
	jg	.LBB0_14
# %bb.16:
	lea	rax, [rsi - 32]
	sub	rdi, rax
	shr	rdi, 2
	vmovdqu	ymm0, ymmword ptr [rsi - 32]
	vpaddd	ymm0, ymm0, ymm0
	dec	edi
	vmovd	xmm1, edi
	vpbroadcastd	ymm1, xmm1
	vmovdqa	ymm2, ymmword ptr [rip + .LCPI0_0] # ymm2 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm1, ymm2, ymm1
	vpmaskmovd	ymmword ptr [rsi - 32], ymm1, ymm0
	vzeroupper
	ret
.LBB0_1:
	mov	rcx, rdi
	jmp	.LBB0_2
	.p2align	4, 0x90
.LBB0_10:                               #   in Loop: Header=BB0_2 Depth=1
	mov	r8, rsi
	sub	r8, rdi
.LBB0_11:                               #   in Loop: Header=BB0_2 Depth=1
	mov	rcx, rdi
	cmp	r8, 32
	jl	.LBB0_12
.LBB0_2:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_9 Depth 2
	vmovdqu	ymm0, ymmword ptr [rcx]
	vpaddd	ymm0, ymm0, ymm0
	vmovdqu	ymmword ptr [rcx], ymm0
	lea	rdi, [rcx + 32]
	mov	rax, rsi
	sub	rax, rdi
	cmp	rax, 32
	jl	.LBB0_12
# %bb.3:                                #   in Loop: Header=BB0_2 Depth=1
	vmovdqu	ymm0, ymmword ptr [rcx + 32]
	vpaddd	ymm0, ymm0, ymm0
	vmovdqu	ymmword ptr [rcx + 32], ymm0
	lea	rdi, [rcx + 64]
	mov	rax, rsi
	sub	rax, rdi
	cmp	rax, 32
	jl	.LBB0_12
# %bb.4:                                #   in Loop: Header=BB0_2 Depth=1
	vmovdqu	ymm0, ymmword ptr [rcx + 64]
	vpaddd	ymm0, ymm0, ymm0
	vmovdqu	ymmword ptr [rcx + 64], ymm0
	lea	rdi, [rcx + 96]
	mov	rax, rsi
	sub	rax, rdi
	cmp	rax, 32
	jl	.LBB0_12
# %bb.5:                                #   in Loop: Header=BB0_2 Depth=1
	vmovdqu	ymm0, ymmword ptr [rcx + 96]
	vpaddd	ymm0, ymm0, ymm0
	vmovdqu	ymmword ptr [rcx + 96], ymm0
	lea	rdi, [rcx + 128]
	mov	r8, rsi
	sub	r8, rdi
	mov	rdx, r8
	sar	rdx, 2
	lea	rax, [rdx + 31]
	cmp	rax, 63
	jb	.LBB0_11
# %bb.6:                                #   in Loop: Header=BB0_2 Depth=1
	test	rdx, rdx
	cmovns	rax, rdx
	sar	rax, 5
	test	al, 1
	je	.LBB0_8
# %bb.7:                                #   in Loop: Header=BB0_2 Depth=1
	vmovdqu	ymm0, ymmword ptr [rcx + 128]
	vmovdqu	ymm1, ymmword ptr [rcx + 160]
	vmovdqu	ymm2, ymmword ptr [rcx + 192]
	vmovdqu	ymm3, ymmword ptr [rcx + 224]
	vpaddd	ymm0, ymm0, ymm0
	vpaddd	ymm1, ymm1, ymm1
	vpaddd	ymm2, ymm2, ymm2
	vpaddd	ymm3, ymm3, ymm3
	vmovdqu	ymmword ptr [rcx + 128], ymm0
	vmovdqu	ymmword ptr [rcx + 160], ymm1
	vmovdqu	ymmword ptr [rcx + 192], ymm2
	vmovdqu	ymmword ptr [rcx + 224], ymm3
	add	rcx, 256
	dec	rax
	mov	rdi, rcx
.LBB0_8:                                #   in Loop: Header=BB0_2 Depth=1
	and	r8, -128
	cmp	r8, 128
	je	.LBB0_10
	.p2align	4, 0x90
.LBB0_9:                                #   Parent Loop BB0_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovdqu	ymm0, ymmword ptr [rdi]
	vmovdqu	ymm1, ymmword ptr [rdi + 32]
	vmovdqu	ymm2, ymmword ptr [rdi + 64]
	vmovdqu	ymm3, ymmword ptr [rdi + 96]
	vpaddd	ymm0, ymm0, ymm0
	vpaddd	ymm1, ymm1, ymm1
	vpaddd	ymm2, ymm2, ymm2
	vpaddd	ymm3, ymm3, ymm3
	vmovdqu	ymmword ptr [rdi], ymm0
	vmovdqu	ymmword ptr [rdi + 32], ymm1
	vmovdqu	ymmword ptr [rdi + 64], ymm2
	vmovdqu	ymmword ptr [rdi + 96], ymm3
	vmovdqu	ymm0, ymmword ptr [rdi + 128]
	vmovdqu	ymm1, ymmword ptr [rdi + 160]
	vmovdqu	ymm2, ymmword ptr [rdi + 192]
	vmovdqu	ymm3, ymmword ptr [rdi + 224]
	vpaddd	ymm0, ymm0, ymm0
	vpaddd	ymm1, ymm1, ymm1
	vpaddd	ymm2, ymm2, ymm2
	vpaddd	ymm3, ymm3, ymm3
	vmovdqu	ymmword ptr [rdi + 128], ymm0
	vmovdqu	ymmword ptr [rdi + 160], ymm1
	vmovdqu	ymmword ptr [rdi + 192], ymm2
	vmovdqu	ymmword ptr [rdi + 224], ymm3
	add	rdi, 256
	add	rax, -2
	jne	.LBB0_9
	jmp	.LBB0_10
.LBB0_14:
	add	rax, 32
	shr	rax, 2
	vmovdqu	ymm0, ymmword ptr [rdi]
	vpaddd	ymm0, ymm0, ymm0
	mov	ecx, 8
	sub	ecx, eax
	vmovd	xmm1, ecx
	vpbroadcastd	ymm1, xmm1
	vpcmpgtd	ymm1, ymm1, ymmword ptr [rip + .LCPI0_0]
	vpmaskmovd	ymmword ptr [rdi], ymm1, ymm0
.LBB0_15:
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z19transform_unalignedPiS_, .Lfunc_end0-_Z19transform_unalignedPiS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
