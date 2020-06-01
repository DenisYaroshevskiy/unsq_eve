	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4               # -- Begin function _Z22inclusive_scan_inplacePiS_
.LCPI0_0:
	.long	0                       # 0x0
	.long	1                       # 0x1
	.long	2                       # 0x2
	.long	3                       # 0x3
	.text
	.globl	_Z22inclusive_scan_inplacePiS_
	.p2align	4, 0x90
	.type	_Z22inclusive_scan_inplacePiS_,@function
_Z22inclusive_scan_inplacePiS_:         # @_Z22inclusive_scan_inplacePiS_
.L_Z22inclusive_scan_inplacePiS_$local:
	.cfi_startproc
# %bb.0:
	mov	rcx, rdi
	and	rcx, -16
	mov	rax, rsi
	and	rax, -16
	shr	edi, 2
	and	edi, 3
	dec	edi
	cmp	rcx, rax
	je	.LBB0_1
# %bb.2:
	vmovd	xmm0, edi
	vpbroadcastd	xmm0, xmm0
	vmovdqa	xmm1, xmmword ptr [rip + .LCPI0_0] # xmm1 = [0,1,2,3]
	vpcmpgtd	xmm0, xmm1, xmm0
	vpand	xmm1, xmm0, xmmword ptr [rcx]
	vpslldq	xmm2, xmm1, 4           # xmm2 = zero,zero,zero,zero,xmm1[0,1,2,3,4,5,6,7,8,9,10,11]
	vpaddd	xmm1, xmm2, xmm1
	vpslldq	xmm2, xmm1, 8           # xmm2 = zero,zero,zero,zero,zero,zero,zero,zero,xmm1[0,1,2,3,4,5,6,7]
	vpaddd	xmm1, xmm1, xmm2
	vpmaskmovd	xmmword ptr [rcx], xmm0, xmm1
	vpshufd	xmm0, xmm1, 255         # xmm0 = xmm1[3,3,3,3]
	add	rcx, 16
	.p2align	4, 0x90
.LBB0_3:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_9 Depth 2
	cmp	rcx, rax
	je	.LBB0_10
# %bb.4:                                #   in Loop: Header=BB0_3 Depth=1
	vmovdqa	xmm1, xmmword ptr [rcx]
	vpslldq	xmm2, xmm1, 4           # xmm2 = zero,zero,zero,zero,xmm1[0,1,2,3,4,5,6,7,8,9,10,11]
	vpaddd	xmm1, xmm2, xmm1
	vpslldq	xmm2, xmm1, 8           # xmm2 = zero,zero,zero,zero,zero,zero,zero,zero,xmm1[0,1,2,3,4,5,6,7]
	vpaddd	xmm0, xmm1, xmm0
	vpaddd	xmm0, xmm0, xmm2
	vmovdqa	xmmword ptr [rcx], xmm0
	vpshufd	xmm0, xmm0, 255         # xmm0 = xmm0[3,3,3,3]
	lea	rdx, [rcx + 16]
	cmp	rdx, rax
	je	.LBB0_10
# %bb.5:                                #   in Loop: Header=BB0_3 Depth=1
	vmovdqa	xmm1, xmmword ptr [rcx + 16]
	vpslldq	xmm2, xmm1, 4           # xmm2 = zero,zero,zero,zero,xmm1[0,1,2,3,4,5,6,7,8,9,10,11]
	vpaddd	xmm1, xmm2, xmm1
	vpslldq	xmm2, xmm1, 8           # xmm2 = zero,zero,zero,zero,zero,zero,zero,zero,xmm1[0,1,2,3,4,5,6,7]
	vpaddd	xmm0, xmm1, xmm0
	vpaddd	xmm0, xmm0, xmm2
	vmovdqa	xmmword ptr [rcx + 16], xmm0
	vpshufd	xmm0, xmm0, 255         # xmm0 = xmm0[3,3,3,3]
	lea	rdx, [rcx + 32]
	cmp	rdx, rax
	je	.LBB0_10
# %bb.6:                                #   in Loop: Header=BB0_3 Depth=1
	vmovdqa	xmm1, xmmword ptr [rcx + 32]
	vpslldq	xmm2, xmm1, 4           # xmm2 = zero,zero,zero,zero,xmm1[0,1,2,3,4,5,6,7,8,9,10,11]
	vpaddd	xmm1, xmm2, xmm1
	vpslldq	xmm2, xmm1, 8           # xmm2 = zero,zero,zero,zero,zero,zero,zero,zero,xmm1[0,1,2,3,4,5,6,7]
	vpaddd	xmm0, xmm1, xmm0
	vpaddd	xmm0, xmm0, xmm2
	vmovdqa	xmmword ptr [rcx + 32], xmm0
	vpshufd	xmm0, xmm0, 255         # xmm0 = xmm0[3,3,3,3]
	lea	rdx, [rcx + 48]
	cmp	rdx, rax
	je	.LBB0_10
# %bb.7:                                #   in Loop: Header=BB0_3 Depth=1
	vmovdqa	xmm1, xmmword ptr [rcx + 48]
	vpslldq	xmm2, xmm1, 4           # xmm2 = zero,zero,zero,zero,xmm1[0,1,2,3,4,5,6,7,8,9,10,11]
	vpaddd	xmm1, xmm2, xmm1
	vpslldq	xmm2, xmm1, 8           # xmm2 = zero,zero,zero,zero,zero,zero,zero,zero,xmm1[0,1,2,3,4,5,6,7]
	vpaddd	xmm0, xmm1, xmm0
	vpaddd	xmm0, xmm0, xmm2
	vmovdqa	xmmword ptr [rcx + 48], xmm0
	vpshufd	xmm0, xmm0, 255         # xmm0 = xmm0[3,3,3,3]
	add	rcx, 64
	mov	rdi, rax
	sub	rdi, rcx
	sar	rdi, 2
	lea	rdx, [rdi + 15]
	cmp	rdx, 31
	jb	.LBB0_3
# %bb.8:                                #   in Loop: Header=BB0_3 Depth=1
	test	rdi, rdi
	cmovns	rdx, rdi
	sar	rdx, 4
	.p2align	4, 0x90
.LBB0_9:                                #   Parent Loop BB0_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovdqa	xmm1, xmmword ptr [rcx]
	vmovdqa	xmm2, xmmword ptr [rcx + 16]
	vmovdqa	xmm3, xmmword ptr [rcx + 32]
	vmovdqa	xmm4, xmmword ptr [rcx + 48]
	vpslldq	xmm5, xmm1, 4           # xmm5 = zero,zero,zero,zero,xmm1[0,1,2,3,4,5,6,7,8,9,10,11]
	vpaddd	xmm1, xmm5, xmm1
	vpslldq	xmm5, xmm1, 8           # xmm5 = zero,zero,zero,zero,zero,zero,zero,zero,xmm1[0,1,2,3,4,5,6,7]
	vpaddd	xmm0, xmm1, xmm0
	vpaddd	xmm0, xmm0, xmm5
	vmovdqa	xmmword ptr [rcx], xmm0
	vpshufd	xmm0, xmm0, 255         # xmm0 = xmm0[3,3,3,3]
	vpslldq	xmm1, xmm2, 4           # xmm1 = zero,zero,zero,zero,xmm2[0,1,2,3,4,5,6,7,8,9,10,11]
	vpaddd	xmm1, xmm1, xmm2
	vpslldq	xmm2, xmm1, 8           # xmm2 = zero,zero,zero,zero,zero,zero,zero,zero,xmm1[0,1,2,3,4,5,6,7]
	vpaddd	xmm1, xmm1, xmm2
	vpaddd	xmm0, xmm0, xmm1
	vmovdqa	xmmword ptr [rcx + 16], xmm0
	vpshufd	xmm0, xmm0, 255         # xmm0 = xmm0[3,3,3,3]
	vpslldq	xmm1, xmm3, 4           # xmm1 = zero,zero,zero,zero,xmm3[0,1,2,3,4,5,6,7,8,9,10,11]
	vpaddd	xmm1, xmm1, xmm3
	vpslldq	xmm2, xmm1, 8           # xmm2 = zero,zero,zero,zero,zero,zero,zero,zero,xmm1[0,1,2,3,4,5,6,7]
	vpaddd	xmm1, xmm1, xmm2
	vpaddd	xmm0, xmm1, xmm0
	vmovdqa	xmmword ptr [rcx + 32], xmm0
	vpshufd	xmm0, xmm0, 255         # xmm0 = xmm0[3,3,3,3]
	vpslldq	xmm1, xmm4, 4           # xmm1 = zero,zero,zero,zero,xmm4[0,1,2,3,4,5,6,7,8,9,10,11]
	vpaddd	xmm1, xmm1, xmm4
	vpslldq	xmm2, xmm1, 8           # xmm2 = zero,zero,zero,zero,zero,zero,zero,zero,xmm1[0,1,2,3,4,5,6,7]
	vpaddd	xmm1, xmm1, xmm2
	vpaddd	xmm0, xmm1, xmm0
	vmovdqa	xmmword ptr [rcx + 48], xmm0
	vpshufd	xmm0, xmm0, 255         # xmm0 = xmm0[3,3,3,3]
	add	rcx, 64
	dec	rdx
	jne	.LBB0_9
	jmp	.LBB0_3
.LBB0_10:
	mov	edi, -1
	cmp	rax, rsi
	jne	.LBB0_11
# %bb.12:
	ret
.LBB0_1:
	vpxor	xmm0, xmm0, xmm0
.LBB0_11:
	mov	rcx, rax
	sub	rcx, rsi
	add	rcx, 16
	shr	rcx, 2
	vmovd	xmm1, edi
	vpbroadcastd	xmm1, xmm1
	mov	edx, 4
	sub	edx, ecx
	vmovd	xmm2, edx
	vpbroadcastd	xmm2, xmm2
	vmovdqa	xmm3, xmmword ptr [rip + .LCPI0_0] # xmm3 = [0,1,2,3]
	vpcmpgtd	xmm1, xmm3, xmm1
	vpcmpgtd	xmm2, xmm2, xmm3
	vpand	xmm1, xmm1, xmm2
	vpand	xmm2, xmm1, xmmword ptr [rax]
	vpslldq	xmm3, xmm2, 4           # xmm3 = zero,zero,zero,zero,xmm2[0,1,2,3,4,5,6,7,8,9,10,11]
	vpaddd	xmm2, xmm3, xmm2
	vpslldq	xmm3, xmm2, 8           # xmm3 = zero,zero,zero,zero,zero,zero,zero,zero,xmm2[0,1,2,3,4,5,6,7]
	vpaddd	xmm0, xmm2, xmm0
	vpaddd	xmm0, xmm0, xmm3
	vpmaskmovd	xmmword ptr [rax], xmm1, xmm0
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
