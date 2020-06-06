	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5               # -- Begin function _Z6reducePKcS0_
.LCPI0_0:
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
	.text
	.globl	_Z6reducePKcS0_
	.p2align	4, 0x90
	.type	_Z6reducePKcS0_,@function
_Z6reducePKcS0_:                        # @_Z6reducePKcS0_
.L_Z6reducePKcS0_$local:
	.cfi_startproc
# %bb.0:
	mov	rcx, rdi
	and	rcx, -16
	mov	r8, rsi
	and	r8, -16
	and	edi, 15
	cmp	rcx, r8
	je	.LBB0_1
# %bb.2:
	vpmovsxbw	ymm0, xmmword ptr [rcx]
	dec	edi
	vmovd	xmm1, edi
	vpbroadcastw	ymm1, xmm1
	vmovdqa	ymm2, ymmword ptr [rip + .LCPI0_0] # ymm2 = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
	vpcmpgtw	ymm1, ymm2, ymm1
	vpand	ymm0, ymm1, ymm0
	add	rcx, 16
	vpxor	xmm1, xmm1, xmm1
	vpxor	xmm2, xmm2, xmm2
	vpxor	xmm3, xmm3, xmm3
	cmp	rcx, r8
	jne	.LBB0_3
.LBB0_14:
	mov	di, -1
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
	vpmovsxbw	ymm4, xmmword ptr [rcx]
	vpaddw	ymm0, ymm0, ymm4
	lea	rax, [rcx + 16]
	cmp	rax, r8
	je	.LBB0_14
# %bb.4:                                #   in Loop: Header=BB0_3 Depth=1
	vpmovsxbw	ymm4, xmmword ptr [rcx + 16]
	vpaddw	ymm1, ymm1, ymm4
	lea	rax, [rcx + 32]
	cmp	rax, r8
	je	.LBB0_14
# %bb.5:                                #   in Loop: Header=BB0_3 Depth=1
	vpmovsxbw	ymm4, xmmword ptr [rcx + 32]
	vpaddw	ymm2, ymm2, ymm4
	lea	rax, [rcx + 48]
	cmp	rax, r8
	je	.LBB0_14
# %bb.6:                                #   in Loop: Header=BB0_3 Depth=1
	vpmovsxbw	ymm4, xmmword ptr [rcx + 48]
	vpaddw	ymm3, ymm3, ymm4
	lea	r9, [rcx + 64]
	mov	rdx, r8
	sub	rdx, r9
	lea	rax, [rdx + 63]
	cmp	rax, 127
	jb	.LBB0_13
# %bb.7:                                #   in Loop: Header=BB0_3 Depth=1
	test	rdx, rdx
	cmovns	rax, rdx
	mov	rdi, rax
	sar	rdi, 6
	test	dil, 1
	jne	.LBB0_9
# %bb.8:                                #   in Loop: Header=BB0_3 Depth=1
	mov	rcx, r9
	and	rax, -64
	and	rdx, -64
	cmp	rdx, 64
	jne	.LBB0_11
	jmp	.LBB0_12
	.p2align	4, 0x90
.LBB0_9:                                #   in Loop: Header=BB0_3 Depth=1
	vpmovsxbw	ymm4, xmmword ptr [rcx + 64]
	vpaddw	ymm0, ymm0, ymm4
	vpmovsxbw	ymm4, xmmword ptr [rcx + 80]
	vpaddw	ymm1, ymm1, ymm4
	vpmovsxbw	ymm4, xmmword ptr [rcx + 96]
	vpaddw	ymm2, ymm2, ymm4
	vpmovsxbw	ymm4, xmmword ptr [rcx + 112]
	vpaddw	ymm3, ymm3, ymm4
	sub	rcx, -128
	dec	rdi
	and	rax, -64
	and	rdx, -64
	cmp	rdx, 64
	je	.LBB0_12
	.p2align	4, 0x90
.LBB0_11:                               #   Parent Loop BB0_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vpmovsxbw	ymm4, xmmword ptr [rcx]
	vpaddw	ymm0, ymm0, ymm4
	vpmovsxbw	ymm4, xmmword ptr [rcx + 16]
	vpaddw	ymm1, ymm1, ymm4
	vpmovsxbw	ymm4, xmmword ptr [rcx + 32]
	vpaddw	ymm2, ymm2, ymm4
	vpmovsxbw	ymm4, xmmword ptr [rcx + 48]
	vpaddw	ymm3, ymm3, ymm4
	vpmovsxbw	ymm4, xmmword ptr [rcx + 64]
	vpaddw	ymm0, ymm0, ymm4
	vpmovsxbw	ymm4, xmmword ptr [rcx + 80]
	vpaddw	ymm1, ymm1, ymm4
	vpmovsxbw	ymm4, xmmword ptr [rcx + 96]
	vpaddw	ymm2, ymm2, ymm4
	vpmovsxbw	ymm4, xmmword ptr [rcx + 112]
	vpaddw	ymm3, ymm3, ymm4
	sub	rcx, -128
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
	vpmovsxbw	ymm4, xmmword ptr [r8]
	vmovd	xmm5, edi
	vpbroadcastw	ymm5, xmm5
	vmovd	xmm6, esi
	vpbroadcastw	ymm6, xmm6
	vmovdqa	ymm7, ymmword ptr [rip + .LCPI0_0] # ymm7 = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
	vpcmpgtw	ymm5, ymm7, ymm5
	vpcmpgtw	ymm6, ymm6, ymm7
	vpand	ymm5, ymm5, ymm6
	vpand	ymm4, ymm5, ymm4
	vpaddw	ymm0, ymm4, ymm0
.LBB0_16:
	vpaddw	ymm0, ymm1, ymm0
	vpaddw	ymm1, ymm2, ymm3
	vpaddw	ymm0, ymm1, ymm0
	vpermq	ymm1, ymm0, 78          # ymm1 = ymm0[2,3,0,1]
	vpaddw	ymm0, ymm0, ymm1
	vpshufd	ymm1, ymm0, 78          # ymm1 = ymm0[2,3,0,1,6,7,4,5]
	vpaddw	ymm0, ymm0, ymm1
	vpshufd	ymm1, ymm0, 177         # ymm1 = ymm0[1,0,3,2,5,4,7,6]
	vpaddw	xmm0, xmm0, xmm1
	vpsrld	xmm1, xmm0, 16
	vpaddw	xmm0, xmm1, xmm0
	vmovd	eax, xmm0
	movsx	eax, al
                                        # kill: def $ax killed $ax killed $eax
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
