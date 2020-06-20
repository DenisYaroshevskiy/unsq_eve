	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5               # -- Begin function _Z6reducePiS_
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
	.globl	_Z6reducePiS_
	.p2align	4, 0x90
	.type	_Z6reducePiS_,@function
_Z6reducePiS_:                          # @_Z6reducePiS_
.L_Z6reducePiS_$local:
	.cfi_startproc
# %bb.0:
	mov	rcx, rdi
	and	rcx, -32
	mov	r8, rsi
	and	r8, -32
	shr	edi, 2
	and	edi, 7
	dec	edi
	cmp	rcx, r8
	je	.LBB0_1
# %bb.2:
	vmovd	xmm0, edi
	vpbroadcastd	ymm0, xmm0
	vmovdqa	ymm1, ymmword ptr [rip + .LCPI0_0] # ymm1 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm0, ymm1, ymm0
	vpand	ymm0, ymm0, ymmword ptr [rcx]
	add	rcx, 32
	vpxor	xmm1, xmm1, xmm1
	vpxor	xmm2, xmm2, xmm2
	vpxor	xmm3, xmm3, xmm3
	jmp	.LBB0_3
	.p2align	4, 0x90
.LBB0_15:                               #   in Loop: Header=BB0_3 Depth=1
	shl	r10, 7
	add	rcx, r10
.LBB0_3:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_11 Depth 2
                                        #     Child Loop BB0_14 Depth 2
	cmp	rcx, r8
	je	.LBB0_16
# %bb.4:                                #   in Loop: Header=BB0_3 Depth=1
	vpaddd	ymm0, ymm0, ymmword ptr [rcx]
	lea	rax, [rcx + 32]
	cmp	rax, r8
	je	.LBB0_16
# %bb.5:                                #   in Loop: Header=BB0_3 Depth=1
	vpaddd	ymm1, ymm1, ymmword ptr [rcx + 32]
	lea	rax, [rcx + 64]
	cmp	rax, r8
	je	.LBB0_16
# %bb.6:                                #   in Loop: Header=BB0_3 Depth=1
	vpaddd	ymm2, ymm2, ymmword ptr [rcx + 64]
	lea	rax, [rcx + 96]
	cmp	rax, r8
	je	.LBB0_16
# %bb.7:                                #   in Loop: Header=BB0_3 Depth=1
	vpaddd	ymm3, ymm3, ymmword ptr [rcx + 96]
	sub	rcx, -128
	mov	rax, r8
	sub	rax, rcx
	sar	rax, 2
	lea	r10, [rax + 31]
	cmp	r10, 63
	jb	.LBB0_3
# %bb.8:                                #   in Loop: Header=BB0_3 Depth=1
	test	rax, rax
	cmovns	r10, rax
	sar	r10, 5
	lea	r9, [r10 - 1]
	mov	rdx, r10
	and	rdx, 3
	je	.LBB0_9
# %bb.10:                               #   in Loop: Header=BB0_3 Depth=1
	xor	eax, eax
	mov	rdi, rcx
	.p2align	4, 0x90
.LBB0_11:                               #   Parent Loop BB0_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vpaddd	ymm0, ymm0, ymmword ptr [rdi]
	vpaddd	ymm1, ymm1, ymmword ptr [rdi + 32]
	vpaddd	ymm2, ymm2, ymmword ptr [rdi + 64]
	vpaddd	ymm3, ymm3, ymmword ptr [rdi + 96]
	sub	rdi, -128
	inc	rax
	cmp	rdx, rax
	jne	.LBB0_11
# %bb.12:                               #   in Loop: Header=BB0_3 Depth=1
	mov	rdx, r10
	sub	rdx, rax
	cmp	r9, 3
	jae	.LBB0_14
	jmp	.LBB0_15
.LBB0_9:                                #   in Loop: Header=BB0_3 Depth=1
	mov	rdi, rcx
	mov	rdx, r10
	cmp	r9, 3
	jb	.LBB0_15
	.p2align	4, 0x90
.LBB0_14:                               #   Parent Loop BB0_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vpaddd	ymm0, ymm0, ymmword ptr [rdi]
	vpaddd	ymm1, ymm1, ymmword ptr [rdi + 32]
	vpaddd	ymm2, ymm2, ymmword ptr [rdi + 64]
	vpaddd	ymm3, ymm3, ymmword ptr [rdi + 96]
	vpaddd	ymm0, ymm0, ymmword ptr [rdi + 128]
	vpaddd	ymm1, ymm1, ymmword ptr [rdi + 160]
	vpaddd	ymm2, ymm2, ymmword ptr [rdi + 192]
	vpaddd	ymm3, ymm3, ymmword ptr [rdi + 224]
	vpaddd	ymm0, ymm0, ymmword ptr [rdi + 256]
	vpaddd	ymm1, ymm1, ymmword ptr [rdi + 288]
	vpaddd	ymm2, ymm2, ymmword ptr [rdi + 320]
	vpaddd	ymm3, ymm3, ymmword ptr [rdi + 352]
	vpaddd	ymm0, ymm0, ymmword ptr [rdi + 384]
	vpaddd	ymm1, ymm1, ymmword ptr [rdi + 416]
	vpaddd	ymm2, ymm2, ymmword ptr [rdi + 448]
	vpaddd	ymm3, ymm3, ymmword ptr [rdi + 480]
	add	rdi, 512
	add	rdx, -4
	jne	.LBB0_14
	jmp	.LBB0_15
.LBB0_16:
	mov	edi, -1
	cmp	r8, rsi
	jne	.LBB0_17
	jmp	.LBB0_18
.LBB0_1:
	vpxor	xmm1, xmm1, xmm1
	vpxor	xmm2, xmm2, xmm2
	vpxor	xmm3, xmm3, xmm3
	vpxor	xmm0, xmm0, xmm0
.LBB0_17:
	mov	rax, r8
	sub	rax, rsi
	add	rax, 32
	shr	rax, 2
	vmovd	xmm4, edi
	vpbroadcastd	ymm4, xmm4
	mov	ecx, 8
	sub	ecx, eax
	vmovd	xmm5, ecx
	vpbroadcastd	ymm5, xmm5
	vmovdqa	ymm6, ymmword ptr [rip + .LCPI0_0] # ymm6 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm4, ymm6, ymm4
	vpcmpgtd	ymm5, ymm5, ymm6
	vpand	ymm4, ymm4, ymm5
	vpand	ymm4, ymm4, ymmword ptr [r8]
	vpaddd	ymm0, ymm4, ymm0
.LBB0_18:
	vpaddd	ymm0, ymm1, ymm0
	vpaddd	ymm1, ymm2, ymm3
	vpaddd	ymm0, ymm1, ymm0
	vpermq	ymm1, ymm0, 78          # ymm1 = ymm0[2,3,0,1]
	vpaddd	ymm0, ymm0, ymm1
	vpshufd	ymm1, ymm0, 78          # ymm1 = ymm0[2,3,0,1,6,7,4,5]
	vpaddd	xmm0, xmm0, xmm1
	vpshufd	xmm1, xmm0, 229         # xmm1 = xmm0[1,1,2,3]
	vpaddd	xmm0, xmm1, xmm0
	vmovd	eax, xmm0
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z6reducePiS_, .Lfunc_end0-_Z6reducePiS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
