	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5               # -- Begin function _Z24transform_overlap_storesPiS_
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
	.globl	_Z24transform_overlap_storesPiS_
	.p2align	4, 0x90
	.type	_Z24transform_overlap_storesPiS_,@function
_Z24transform_overlap_storesPiS_:       # @_Z24transform_overlap_storesPiS_
.L_Z24transform_overlap_storesPiS_$local:
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
# %bb.20:
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
.LBB0_3:
	vmovdqu	ymm0, ymmword ptr [rdi]
	cmp	rax, 65
	jl	.LBB0_19
# %bb.4:
	lea	rcx, [rdi + 32]
	and	rcx, -32
	mov	r8, rsi
	and	r8, -32
	add	r8, -32
	vmovdqa	ymm1, ymmword ptr [rcx]
	vpaddd	ymm0, ymm0, ymm0
	vmovdqu	ymmword ptr [rdi], ymm0
	cmp	r8, rcx
	jne	.LBB0_6
# %bb.5:
	vmovdqa	ymm0, ymm1
	mov	rdi, rcx
	jmp	.LBB0_19
	.p2align	4, 0x90
.LBB0_15:                               #   in Loop: Header=BB0_6 Depth=1
	mov	rcx, rdi
.LBB0_16:                               #   in Loop: Header=BB0_6 Depth=1
	vmovdqa	ymm1, ymmword ptr [rcx]
	cmp	rcx, r8
	je	.LBB0_17
.LBB0_6:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_14 Depth 2
	vpaddd	ymm0, ymm1, ymm1
	vmovdqa	ymmword ptr [rcx], ymm0
	lea	rax, [rcx + 32]
	vmovdqa	ymm0, ymmword ptr [rcx + 32]
	cmp	rax, r8
	je	.LBB0_18
# %bb.7:                                #   in Loop: Header=BB0_6 Depth=1
	vpaddd	ymm0, ymm0, ymm0
	vmovdqa	ymmword ptr [rcx + 32], ymm0
	lea	rax, [rcx + 64]
	vmovdqa	ymm0, ymmword ptr [rcx + 64]
	cmp	rax, r8
	je	.LBB0_18
# %bb.8:                                #   in Loop: Header=BB0_6 Depth=1
	vpaddd	ymm0, ymm0, ymm0
	vmovdqa	ymmword ptr [rcx + 64], ymm0
	lea	rax, [rcx + 96]
	vmovdqa	ymm0, ymmword ptr [rcx + 96]
	cmp	rax, r8
	je	.LBB0_18
# %bb.9:                                #   in Loop: Header=BB0_6 Depth=1
	vpaddd	ymm0, ymm0, ymm0
	vmovdqa	ymmword ptr [rcx + 96], ymm0
	lea	rdi, [rcx + 128]
	mov	r9, r8
	sub	r9, rdi
	mov	rax, r9
	sar	rax, 2
	lea	rdx, [rax + 31]
	cmp	rdx, 63
	jb	.LBB0_15
# %bb.10:                               #   in Loop: Header=BB0_6 Depth=1
	test	rax, rax
	cmovns	rdx, rax
	sar	rdx, 5
	test	dl, 1
	jne	.LBB0_12
# %bb.11:                               #   in Loop: Header=BB0_6 Depth=1
                                        # implicit-def: $rcx
	and	r9, -128
	cmp	r9, 128
	jne	.LBB0_14
	jmp	.LBB0_16
	.p2align	4, 0x90
.LBB0_12:                               #   in Loop: Header=BB0_6 Depth=1
	vmovdqa	ymm0, ymmword ptr [rcx + 128]
	vmovdqa	ymm1, ymmword ptr [rcx + 160]
	vmovdqa	ymm2, ymmword ptr [rcx + 192]
	vmovdqa	ymm3, ymmword ptr [rcx + 224]
	vpaddd	ymm0, ymm0, ymm0
	vpaddd	ymm1, ymm1, ymm1
	vpaddd	ymm2, ymm2, ymm2
	vpaddd	ymm3, ymm3, ymm3
	vmovdqa	ymmword ptr [rcx + 128], ymm0
	vmovdqa	ymmword ptr [rcx + 160], ymm1
	vmovdqa	ymmword ptr [rcx + 192], ymm2
	vmovdqa	ymmword ptr [rcx + 224], ymm3
	add	rcx, 256
	dec	rdx
	mov	rdi, rcx
	and	r9, -128
	cmp	r9, 128
	je	.LBB0_16
	.p2align	4, 0x90
.LBB0_14:                               #   Parent Loop BB0_6 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovdqa	ymm0, ymmword ptr [rdi]
	vmovdqa	ymm1, ymmword ptr [rdi + 32]
	vmovdqa	ymm2, ymmword ptr [rdi + 64]
	vmovdqa	ymm3, ymmword ptr [rdi + 96]
	vpaddd	ymm0, ymm0, ymm0
	vpaddd	ymm1, ymm1, ymm1
	vpaddd	ymm2, ymm2, ymm2
	vpaddd	ymm3, ymm3, ymm3
	vmovdqa	ymmword ptr [rdi], ymm0
	vmovdqa	ymmword ptr [rdi + 32], ymm1
	vmovdqa	ymmword ptr [rdi + 64], ymm2
	vmovdqa	ymmword ptr [rdi + 96], ymm3
	vmovdqa	ymm0, ymmword ptr [rdi + 128]
	vmovdqa	ymm1, ymmword ptr [rdi + 160]
	vmovdqa	ymm2, ymmword ptr [rdi + 192]
	vmovdqa	ymm3, ymmword ptr [rdi + 224]
	vpaddd	ymm0, ymm0, ymm0
	vpaddd	ymm1, ymm1, ymm1
	vpaddd	ymm2, ymm2, ymm2
	vpaddd	ymm3, ymm3, ymm3
	vmovdqa	ymmword ptr [rdi + 128], ymm0
	vmovdqa	ymmword ptr [rdi + 160], ymm1
	vmovdqa	ymmword ptr [rdi + 192], ymm2
	vmovdqa	ymmword ptr [rdi + 224], ymm3
	add	rdi, 256
	add	rdx, -2
	jne	.LBB0_14
	jmp	.LBB0_15
.LBB0_2:
	vmovdqu	ymm0, ymmword ptr [rdi]
	mov	rax, rdi
	sub	rax, rsi
	add	rax, 32
	shr	rax, 2
	vpaddd	ymm0, ymm0, ymm0
	mov	ecx, 8
	sub	ecx, eax
	vmovd	xmm1, ecx
	vpbroadcastd	ymm1, xmm1
	vpcmpgtd	ymm1, ymm1, ymmword ptr [rip + .LCPI0_0]
	vpmaskmovd	ymmword ptr [rdi], ymm1, ymm0
	vzeroupper
	ret
.LBB0_17:
	vmovdqa	ymm0, ymm1
.LBB0_18:
	mov	rdi, r8
.LBB0_19:
	vmovdqu	ymm1, ymmword ptr [rsi - 32]
	vpaddd	ymm0, ymm0, ymm0
	vmovdqu	ymmword ptr [rdi], ymm0
	vpaddd	ymm0, ymm1, ymm1
	vmovdqu	ymmword ptr [rsi - 32], ymm0
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z24transform_overlap_storesPiS_, .Lfunc_end0-_Z24transform_overlap_storesPiS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
