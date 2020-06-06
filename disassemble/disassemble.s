	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5               # -- Begin function _Z6reducePKcS0_
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
	.globl	_Z6reducePKcS0_
	.p2align	4, 0x90
	.type	_Z6reducePKcS0_,@function
_Z6reducePKcS0_:                        # @_Z6reducePKcS0_
.L_Z6reducePKcS0_$local:
	.cfi_startproc
# %bb.0:
	mov	rcx, rdi
	and	rcx, -8
	mov	r8, rsi
	and	r8, -8
	and	edi, 7
	cmp	rcx, r8
	je	.LBB0_1
# %bb.2:
	vpmovsxbd	ymm0, qword ptr [rcx]
	dec	edi
	vmovd	xmm1, edi
	vpbroadcastd	ymm1, xmm1
	vmovdqa	ymm2, ymmword ptr [rip + .LCPI0_0] # ymm2 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm1, ymm2, ymm1
	vpand	ymm0, ymm1, ymm0
	add	rcx, 8
	vpxor	xmm1, xmm1, xmm1
	vpxor	xmm2, xmm2, xmm2
	vpxor	xmm3, xmm3, xmm3
	cmp	rcx, r8
	jne	.LBB0_3
.LBB0_14:
	mov	edi, -1
	cmp	r8, rsi
	jne	.LBB0_15
	jmp	.LBB0_16
	.p2align	4, 0x90
.LBB0_12:                               #   in Loop: Header=BB0_3 Depth=1
	add	r9, rax
.LBB0_13:                               #   in Loop: Header=BB0_3 Depth=1
	mov	rcx, r9
	cmp	r9, r8
	je	.LBB0_14
.LBB0_3:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_11 Depth 2
	vpmovsxbd	ymm4, qword ptr [rcx]
	vpaddd	ymm0, ymm0, ymm4
	lea	rax, [rcx + 8]
	cmp	rax, r8
	je	.LBB0_14
# %bb.4:                                #   in Loop: Header=BB0_3 Depth=1
	vpmovsxbd	ymm4, qword ptr [rcx + 8]
	vpaddd	ymm1, ymm1, ymm4
	lea	rax, [rcx + 16]
	cmp	rax, r8
	je	.LBB0_14
# %bb.5:                                #   in Loop: Header=BB0_3 Depth=1
	vpmovsxbd	ymm4, qword ptr [rcx + 16]
	vpaddd	ymm2, ymm2, ymm4
	lea	rax, [rcx + 24]
	cmp	rax, r8
	je	.LBB0_14
# %bb.6:                                #   in Loop: Header=BB0_3 Depth=1
	vpmovsxbd	ymm4, qword ptr [rcx + 24]
	vpaddd	ymm3, ymm3, ymm4
	lea	r9, [rcx + 32]
	mov	rdx, r8
	sub	rdx, r9
	lea	rax, [rdx + 31]
	cmp	rax, 63
	jb	.LBB0_13
# %bb.7:                                #   in Loop: Header=BB0_3 Depth=1
	test	rdx, rdx
	cmovns	rax, rdx
	mov	rdi, rax
	sar	rdi, 5
	test	dil, 1
	jne	.LBB0_9
# %bb.8:                                #   in Loop: Header=BB0_3 Depth=1
	mov	rcx, r9
	and	rax, -32
	and	rdx, -32
	cmp	rdx, 32
	jne	.LBB0_11
	jmp	.LBB0_12
	.p2align	4, 0x90
.LBB0_9:                                #   in Loop: Header=BB0_3 Depth=1
	vpmovsxbd	ymm4, qword ptr [rcx + 32]
	vpaddd	ymm0, ymm0, ymm4
	vpmovsxbd	ymm4, qword ptr [rcx + 40]
	vpaddd	ymm1, ymm1, ymm4
	vpmovsxbd	ymm4, qword ptr [rcx + 48]
	vpaddd	ymm2, ymm2, ymm4
	vpmovsxbd	ymm4, qword ptr [rcx + 56]
	vpaddd	ymm3, ymm3, ymm4
	add	rcx, 64
	dec	rdi
	and	rax, -32
	and	rdx, -32
	cmp	rdx, 32
	je	.LBB0_12
	.p2align	4, 0x90
.LBB0_11:                               #   Parent Loop BB0_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vpmovsxbd	ymm4, qword ptr [rcx]
	vpaddd	ymm0, ymm0, ymm4
	vpmovsxbd	ymm4, qword ptr [rcx + 8]
	vpaddd	ymm1, ymm1, ymm4
	vpmovsxbd	ymm4, qword ptr [rcx + 16]
	vpaddd	ymm2, ymm2, ymm4
	vpmovsxbd	ymm4, qword ptr [rcx + 24]
	vpaddd	ymm3, ymm3, ymm4
	vpmovsxbd	ymm4, qword ptr [rcx + 32]
	vpaddd	ymm0, ymm0, ymm4
	vpmovsxbd	ymm4, qword ptr [rcx + 40]
	vpaddd	ymm1, ymm1, ymm4
	vpmovsxbd	ymm4, qword ptr [rcx + 48]
	vpaddd	ymm2, ymm2, ymm4
	vpmovsxbd	ymm4, qword ptr [rcx + 56]
	vpaddd	ymm3, ymm3, ymm4
	add	rcx, 64
	add	rdi, -2
	jne	.LBB0_11
	jmp	.LBB0_12
.LBB0_1:
	dec	edi
	vpxor	xmm1, xmm1, xmm1
	vpxor	xmm2, xmm2, xmm2
	vpxor	xmm3, xmm3, xmm3
	vpxor	xmm0, xmm0, xmm0
.LBB0_15:
	sub	esi, r8d
	vpmovsxbd	ymm4, qword ptr [r8]
	vmovd	xmm5, edi
	vpbroadcastd	ymm5, xmm5
	vmovd	xmm6, esi
	vpbroadcastd	ymm6, xmm6
	vmovdqa	ymm7, ymmword ptr [rip + .LCPI0_0] # ymm7 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm5, ymm7, ymm5
	vpcmpgtd	ymm6, ymm6, ymm7
	vpand	ymm5, ymm5, ymm6
	vpand	ymm4, ymm5, ymm4
	vpaddd	ymm0, ymm4, ymm0
.LBB0_16:
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
	movsx	eax, al
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z6reducePKcS0_, .Lfunc_end0-_Z6reducePKcS0_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
