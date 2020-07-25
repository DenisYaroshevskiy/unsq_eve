	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2               # -- Begin function _Z9remove_0sPiS_
.LCPI0_0:
	.long	1                       # 0x1
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5
.LCPI0_1:
	.long	0                       # 0x0
	.long	1                       # 0x1
	.long	2                       # 0x2
	.long	3                       # 0x3
	.long	4                       # 0x4
	.long	5                       # 0x5
	.long	6                       # 0x6
	.long	7                       # 0x7
	.text
	.globl	_Z9remove_0sPiS_
	.p2align	4, 0x90
	.type	_Z9remove_0sPiS_,@function
_Z9remove_0sPiS_:                       # @_Z9remove_0sPiS_
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	push	r15
	push	r14
	push	rbx
	and	rsp, -32
	sub	rsp, 96
	.cfi_offset rbx, -40
	.cfi_offset r14, -32
	.cfi_offset r15, -24
	mov	rax, rdi
	cmp	rdi, rsi
	je	.LBB0_12
# %bb.1:
	mov	r14, rax
	and	r14, -32
	mov	r8, rsi
	and	r8, -32
	mov	r9d, eax
	shr	r9d, 2
	and	r9d, 7
	movabs	r11, 6148914691236517205
	movabs	r10, 506097522914230528
	cmp	r14, r8
	je	.LBB0_2
# %bb.3:
	vmovdqa	ymm1, ymmword ptr [r14]
	vpbroadcastd	ymm0, dword ptr [rip + .LCPI0_0] # ymm0 = [1,1,1,1,1,1,1,1]
	vpcmpeqd	ymm2, ymm1, ymm0
	vpmovmskb	ecx, ymm2
	not	ecx
	and	al, 28
	shrx	ecx, ecx, eax
	shlx	ecx, ecx, eax
	lea	rax, [r14 + 4*r9]
	pdep	rdx, rcx, r11
	lea	rdx, [rdx + 2*rdx]
	popcnt	ecx, ecx
	pext	rdx, r10, rdx
	vmovq	xmm2, rdx
	vpmovzxbd	ymm2, xmm2      # ymm2 = xmm2[0],zero,zero,zero,xmm2[1],zero,zero,zero,xmm2[2],zero,zero,zero,xmm2[3],zero,zero,zero,xmm2[4],zero,zero,zero,xmm2[5],zero,zero,zero,xmm2[6],zero,zero,zero,xmm2[7],zero,zero,zero
	and	ecx, -4
	vpermd	ymm1, ymm2, ymm1
	add	rax, rcx
	shr	rcx, 2
	vmovd	xmm2, ecx
	vpbroadcastd	ymm2, xmm2
	vpcmpgtd	ymm2, ymm2, ymmword ptr [rip + .LCPI0_1]
	vpmaskmovd	ymmword ptr [r14 + 4*r9], ymm2, ymm1
	add	r14, 32
	.p2align	4, 0x90
.LBB0_4:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_15 Depth 2
	cmp	r14, r8
	je	.LBB0_9
# %bb.5:                                #   in Loop: Header=BB0_4 Depth=1
	vmovdqa	ymm1, ymmword ptr [r14]
	vpcmpeqd	ymm2, ymm1, ymm0
	vpmovmskb	ecx, ymm2
	not	ecx
	pdep	rdx, rcx, r11
	lea	rdx, [rdx + 2*rdx]
	popcnt	ecx, ecx
	pext	rdx, r10, rdx
	vmovq	xmm2, rdx
	vpmovzxbd	ymm2, xmm2      # ymm2 = xmm2[0],zero,zero,zero,xmm2[1],zero,zero,zero,xmm2[2],zero,zero,zero,xmm2[3],zero,zero,zero,xmm2[4],zero,zero,zero,xmm2[5],zero,zero,zero,xmm2[6],zero,zero,zero,xmm2[7],zero,zero,zero
	and	ecx, -4
	vpermd	ymm1, ymm2, ymm1
	vmovdqu	ymmword ptr [rax], ymm1
	add	rax, rcx
	lea	rcx, [r14 + 32]
	cmp	rcx, r8
	je	.LBB0_9
# %bb.6:                                #   in Loop: Header=BB0_4 Depth=1
	vmovdqa	ymm1, ymmword ptr [r14 + 32]
	vpcmpeqd	ymm2, ymm1, ymm0
	vpmovmskb	ecx, ymm2
	not	ecx
	pdep	rdx, rcx, r11
	lea	rdx, [rdx + 2*rdx]
	popcnt	ecx, ecx
	pext	rdx, r10, rdx
	vmovq	xmm2, rdx
	vpmovzxbd	ymm2, xmm2      # ymm2 = xmm2[0],zero,zero,zero,xmm2[1],zero,zero,zero,xmm2[2],zero,zero,zero,xmm2[3],zero,zero,zero,xmm2[4],zero,zero,zero,xmm2[5],zero,zero,zero,xmm2[6],zero,zero,zero,xmm2[7],zero,zero,zero
	and	ecx, -4
	vpermd	ymm1, ymm2, ymm1
	vmovdqu	ymmword ptr [rax], ymm1
	add	rax, rcx
	lea	rcx, [r14 + 64]
	cmp	rcx, r8
	je	.LBB0_9
# %bb.7:                                #   in Loop: Header=BB0_4 Depth=1
	vmovdqa	ymm1, ymmword ptr [r14 + 64]
	vpcmpeqd	ymm2, ymm1, ymm0
	vpmovmskb	ecx, ymm2
	not	ecx
	pdep	rdx, rcx, r11
	lea	rdx, [rdx + 2*rdx]
	popcnt	ecx, ecx
	pext	rdx, r10, rdx
	vmovq	xmm2, rdx
	vpmovzxbd	ymm2, xmm2      # ymm2 = xmm2[0],zero,zero,zero,xmm2[1],zero,zero,zero,xmm2[2],zero,zero,zero,xmm2[3],zero,zero,zero,xmm2[4],zero,zero,zero,xmm2[5],zero,zero,zero,xmm2[6],zero,zero,zero,xmm2[7],zero,zero,zero
	and	ecx, -4
	vpermd	ymm1, ymm2, ymm1
	vmovdqu	ymmword ptr [rax], ymm1
	add	rcx, rax
	lea	rax, [r14 + 96]
	cmp	rax, r8
	je	.LBB0_8
# %bb.13:                               #   in Loop: Header=BB0_4 Depth=1
	vmovdqa	ymm1, ymmword ptr [r14 + 96]
	vpcmpeqd	ymm2, ymm1, ymm0
	vpmovmskb	eax, ymm2
	not	eax
	pdep	rdx, rax, r11
	lea	rdx, [rdx + 2*rdx]
	popcnt	eax, eax
	pext	rdx, r10, rdx
	vmovq	xmm2, rdx
	vpmovzxbd	ymm2, xmm2      # ymm2 = xmm2[0],zero,zero,zero,xmm2[1],zero,zero,zero,xmm2[2],zero,zero,zero,xmm2[3],zero,zero,zero,xmm2[4],zero,zero,zero,xmm2[5],zero,zero,zero,xmm2[6],zero,zero,zero,xmm2[7],zero,zero,zero
	and	eax, -4
	vpermd	ymm1, ymm2, ymm1
	vmovdqu	ymmword ptr [rcx], ymm1
	add	rax, rcx
	sub	r14, -128
	mov	rdx, r8
	sub	rdx, r14
	sar	rdx, 2
	lea	rcx, [rdx + 31]
	cmp	rcx, 63
	jb	.LBB0_4
# %bb.14:                               #   in Loop: Header=BB0_4 Depth=1
	test	rdx, rdx
	cmovns	rcx, rdx
	sar	rcx, 5
	.p2align	4, 0x90
.LBB0_15:                               #   Parent Loop BB0_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovdqa	ymm1, ymmword ptr [r14]
	vpcmpeqd	ymm2, ymm1, ymm0
	vpmovmskb	edx, ymm2
	not	edx
	pdep	rdi, rdx, r11
	lea	rdi, [rdi + 2*rdi]
	popcnt	edx, edx
	pext	rdi, r10, rdi
	vmovq	xmm2, rdi
	vpmovzxbd	ymm2, xmm2      # ymm2 = xmm2[0],zero,zero,zero,xmm2[1],zero,zero,zero,xmm2[2],zero,zero,zero,xmm2[3],zero,zero,zero,xmm2[4],zero,zero,zero,xmm2[5],zero,zero,zero,xmm2[6],zero,zero,zero,xmm2[7],zero,zero,zero
	and	edx, -4
	vpermd	ymm1, ymm2, ymm1
	vmovdqu	ymmword ptr [rax], ymm1
	lea	r9, [rax + rdx]
	vmovdqa	ymm1, ymmword ptr [r14 + 32]
	vpcmpeqd	ymm2, ymm1, ymm0
	vpmovmskb	ebx, ymm2
	not	ebx
	pdep	rdi, rbx, r11
	lea	rdi, [rdi + 2*rdi]
	popcnt	ebx, ebx
	pext	rdi, r10, rdi
	vmovq	xmm2, rdi
	vpmovzxbd	ymm2, xmm2      # ymm2 = xmm2[0],zero,zero,zero,xmm2[1],zero,zero,zero,xmm2[2],zero,zero,zero,xmm2[3],zero,zero,zero,xmm2[4],zero,zero,zero,xmm2[5],zero,zero,zero,xmm2[6],zero,zero,zero,xmm2[7],zero,zero,zero
	and	ebx, -4
	vpermd	ymm1, ymm2, ymm1
	vmovdqu	ymmword ptr [rax + rdx], ymm1
	lea	r15, [r9 + rbx]
	vmovdqa	ymm1, ymmword ptr [r14 + 64]
	vpcmpeqd	ymm2, ymm1, ymm0
	vpmovmskb	eax, ymm2
	not	eax
	pdep	rdi, rax, r11
	lea	rdi, [rdi + 2*rdi]
	xor	edx, edx
	popcnt	edx, eax
	pext	rax, r10, rdi
	vmovq	xmm2, rax
	vpmovzxbd	ymm2, xmm2      # ymm2 = xmm2[0],zero,zero,zero,xmm2[1],zero,zero,zero,xmm2[2],zero,zero,zero,xmm2[3],zero,zero,zero,xmm2[4],zero,zero,zero,xmm2[5],zero,zero,zero,xmm2[6],zero,zero,zero,xmm2[7],zero,zero,zero
	and	edx, -4
	vpermd	ymm1, ymm2, ymm1
	vmovdqu	ymmword ptr [rbx + r9], ymm1
	lea	rdi, [r15 + rdx]
	vmovdqa	ymm1, ymmword ptr [r14 + 96]
	vpcmpeqd	ymm2, ymm1, ymm0
	vpmovmskb	eax, ymm2
	not	eax
	pdep	rbx, rax, r11
	lea	rbx, [rbx + 2*rbx]
	popcnt	eax, eax
	pext	rbx, r10, rbx
	vmovq	xmm2, rbx
	vpmovzxbd	ymm2, xmm2      # ymm2 = xmm2[0],zero,zero,zero,xmm2[1],zero,zero,zero,xmm2[2],zero,zero,zero,xmm2[3],zero,zero,zero,xmm2[4],zero,zero,zero,xmm2[5],zero,zero,zero,xmm2[6],zero,zero,zero,xmm2[7],zero,zero,zero
	and	eax, -4
	add	rax, rdi
	vpermd	ymm1, ymm2, ymm1
	vmovdqu	ymmword ptr [rdx + r15], ymm1
	sub	r14, -128
	dec	rcx
	jne	.LBB0_15
	jmp	.LBB0_4
.LBB0_2:
	mov	rax, r14
	jmp	.LBB0_11
.LBB0_8:
	mov	rax, rcx
.LBB0_9:
	cmp	r8, rsi
	je	.LBB0_12
# %bb.10:
	xor	r9d, r9d
.LBB0_11:
	vmovdqa	ymm0, ymmword ptr [r8]
	vpbroadcastd	ymm1, dword ptr [rip + .LCPI0_0] # ymm1 = [1,1,1,1,1,1,1,1]
	vpcmpeqd	ymm1, ymm0, ymm1
	vpmovmskb	ecx, ymm1
	lea	edx, [4*r9]
	sub	esi, r8d
	and	sil, -4
	mov	rdi, -1
	shlx	rsi, rdi, rsi
	not	esi
	shrx	esi, esi, edx
	shlx	edx, esi, edx
	andn	ecx, ecx, edx
	lea	rdx, [rax + 4*r9]
	pdep	rsi, rcx, r11
	lea	rsi, [rsi + 2*rsi]
	popcnt	ecx, ecx
	pext	rsi, r10, rsi
	vmovq	xmm1, rsi
	vpmovzxbd	ymm1, xmm1      # ymm1 = xmm1[0],zero,zero,zero,xmm1[1],zero,zero,zero,xmm1[2],zero,zero,zero,xmm1[3],zero,zero,zero,xmm1[4],zero,zero,zero,xmm1[5],zero,zero,zero,xmm1[6],zero,zero,zero,xmm1[7],zero,zero,zero
	and	ecx, -4
	vpermd	ymm0, ymm1, ymm0
	add	rdx, rcx
	shr	rcx, 2
	vmovd	xmm1, ecx
	vpbroadcastd	ymm1, xmm1
	vpcmpgtd	ymm1, ymm1, ymmword ptr [rip + .LCPI0_1]
	vpmaskmovd	ymmword ptr [rax + 4*r9], ymm1, ymm0
	mov	rax, rdx
.LBB0_12:
	lea	rsp, [rbp - 24]
	pop	rbx
	pop	r14
	pop	r15
	pop	rbp
	.cfi_def_cfa rsp, 8
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z9remove_0sPiS_, .Lfunc_end0-_Z9remove_0sPiS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git 448bbc512f456df6fc817b0d7041897eea2375b7)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
