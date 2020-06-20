	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5               # -- Begin function _Z9transformPiS_
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
	.globl	_Z9transformPiS_
	.p2align	4, 0x90
	.type	_Z9transformPiS_,@function
_Z9transformPiS_:                       # @_Z9transformPiS_
.L_Z9transformPiS_$local:
	.cfi_startproc
# %bb.0:
	mov	rcx, rdi
	and	rcx, -32
	mov	r8, rsi
	and	r8, -32
	shr	edi, 2
	and	edi, 7
	cmp	rcx, r8
	je	.LBB0_15
# %bb.1:
	vmovdqa	ymm0, ymmword ptr [rcx]
	vpaddd	ymm0, ymm0, ymm0
	dec	edi
	vmovd	xmm1, edi
	vpbroadcastd	ymm1, xmm1
	vmovdqa	ymm2, ymmword ptr [rip + .LCPI0_0] # ymm2 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm1, ymm2, ymm1
	vpmaskmovd	ymmword ptr [rcx], ymm1, ymm0
	add	rcx, 32
	jmp	.LBB0_2
	.p2align	4, 0x90
.LBB0_12:                               #   in Loop: Header=BB0_2 Depth=1
	mov	rcx, rdi
.LBB0_2:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_11 Depth 2
	cmp	rcx, r8
	je	.LBB0_13
# %bb.3:                                #   in Loop: Header=BB0_2 Depth=1
	vmovdqa	ymm0, ymmword ptr [rcx]
	vpaddd	ymm0, ymm0, ymm0
	vmovdqa	ymmword ptr [rcx], ymm0
	lea	rax, [rcx + 32]
	cmp	rax, r8
	je	.LBB0_13
# %bb.4:                                #   in Loop: Header=BB0_2 Depth=1
	vmovdqa	ymm0, ymmword ptr [rcx + 32]
	vpaddd	ymm0, ymm0, ymm0
	vmovdqa	ymmword ptr [rcx + 32], ymm0
	lea	rax, [rcx + 64]
	cmp	rax, r8
	je	.LBB0_13
# %bb.5:                                #   in Loop: Header=BB0_2 Depth=1
	vmovdqa	ymm0, ymmword ptr [rcx + 64]
	vpaddd	ymm0, ymm0, ymm0
	vmovdqa	ymmword ptr [rcx + 64], ymm0
	lea	rax, [rcx + 96]
	cmp	rax, r8
	je	.LBB0_13
# %bb.6:                                #   in Loop: Header=BB0_2 Depth=1
	vmovdqa	ymm0, ymmword ptr [rcx + 96]
	vpaddd	ymm0, ymm0, ymm0
	vmovdqa	ymmword ptr [rcx + 96], ymm0
	lea	rdi, [rcx + 128]
	mov	r9, r8
	sub	r9, rdi
	mov	rax, r9
	sar	rax, 2
	lea	rdx, [rax + 31]
	cmp	rdx, 63
	jb	.LBB0_12
# %bb.7:                                #   in Loop: Header=BB0_2 Depth=1
	test	rax, rax
	cmovns	rdx, rax
	sar	rdx, 5
	test	dl, 1
	jne	.LBB0_9
# %bb.8:                                #   in Loop: Header=BB0_2 Depth=1
                                        # implicit-def: $rcx
	and	r9, -128
	cmp	r9, 128
	je	.LBB0_2
	jmp	.LBB0_11
	.p2align	4, 0x90
.LBB0_9:                                #   in Loop: Header=BB0_2 Depth=1
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
	je	.LBB0_2
	.p2align	4, 0x90
.LBB0_11:                               #   Parent Loop BB0_2 Depth=1
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
	jne	.LBB0_11
	jmp	.LBB0_12
.LBB0_13:
	cmp	r8, rsi
	je	.LBB0_16
# %bb.14:
	xor	edi, edi
.LBB0_15:
	mov	rax, r8
	sub	rax, rsi
	add	rax, 32
	shr	rax, 2
	vmovdqa	ymm0, ymmword ptr [r8]
	vpaddd	ymm0, ymm0, ymm0
	dec	edi
	vmovd	xmm1, edi
	vpbroadcastd	ymm1, xmm1
	mov	ecx, 8
	sub	ecx, eax
	vmovd	xmm2, ecx
	vpbroadcastd	ymm2, xmm2
	vmovdqa	ymm3, ymmword ptr [rip + .LCPI0_0] # ymm3 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm1, ymm3, ymm1
	vpcmpgtd	ymm2, ymm2, ymm3
	vpand	ymm1, ymm1, ymm2
	vpmaskmovd	ymmword ptr [r8], ymm1, ymm0
.LBB0_16:
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z9transformPiS_, .Lfunc_end0-_Z9transformPiS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
