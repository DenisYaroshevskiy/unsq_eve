	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5                               # -- Begin function _Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE
.LCPI0_0:
	.long	0                               # 0x0
	.long	1                               # 0x1
	.long	2                               # 0x2
	.long	3                               # 0x3
	.long	4                               # 0x4
	.long	5                               # 0x5
	.long	6                               # 0x6
	.long	7                               # 0x7
	.text
	.globl	_Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE
	.p2align	4, 0x90
	.type	_Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE,@function
_Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE: # @_Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE
	.cfi_startproc
# %bb.0:
	push	rbx
	.cfi_def_cfa_offset 16
	.cfi_offset rbx, -16
	mov	rax, qword ptr [rdi]
	mov	r8, qword ptr [rdi + 8]
	cmp	rax, r8
	je	.LBB0_9
# %bb.1:
	mov	rdx, rax
	and	rdx, -32
	mov	rbx, r8
	and	rbx, -32
	shr	eax, 2
	and	eax, 7
	movabs	r10, 72340172838076673
	movabs	r9, 506097522914230528
	cmp	rdx, rbx
	je	.LBB0_2
# %bb.3:
	vmovdqa	ymm1, ymmword ptr [rdx]
	vpxor	xmm0, xmm0, xmm0
	vpcmpeqd	ymm2, ymm1, ymm0
	vmovmskps	edi, ymm2
	xor	edi, 255
	shrx	edi, edi, eax
	shlx	r11d, edi, eax
	pdep	rdi, r11, r10
	mov	rcx, rdi
	shl	rcx, 8
	sub	rcx, rdi
	pext	rcx, r9, rcx
	vmovq	xmm2, rcx
	vpmovzxbd	ymm2, xmm2              # ymm2 = xmm2[0],zero,zero,zero,xmm2[1],zero,zero,zero,xmm2[2],zero,zero,zero,xmm2[3],zero,zero,zero,xmm2[4],zero,zero,zero,xmm2[5],zero,zero,zero,xmm2[6],zero,zero,zero,xmm2[7],zero,zero,zero
	popcnt	ecx, r11d
	vmovd	xmm3, ecx
	vpbroadcastd	ymm3, xmm3
	vpcmpgtd	ymm3, ymm3, ymmword ptr [rip + .LCPI0_0]
	vpermd	ymm1, ymm2, ymm1
	vpmaskmovd	ymmword ptr [rdx + 4*rax], ymm3, ymm1
	lea	rax, [rdx + 4*rax]
	lea	rdi, [rax + 4*rcx]
	add	rdx, 32
	cmp	rdx, rbx
	je	.LBB0_6
	.p2align	4, 0x90
.LBB0_4:                                # =>This Inner Loop Header: Depth=1
	vmovdqa	ymm1, ymmword ptr [rdx]
	vpcmpeqd	ymm2, ymm1, ymm0
	vmovmskps	eax, ymm2
	xor	eax, 255
	pdep	rsi, rax, r10
	mov	rcx, rsi
	shl	rcx, 8
	sub	rcx, rsi
	pext	rcx, r9, rcx
	vmovq	xmm2, rcx
	vpmovzxbd	ymm2, xmm2              # ymm2 = xmm2[0],zero,zero,zero,xmm2[1],zero,zero,zero,xmm2[2],zero,zero,zero,xmm2[3],zero,zero,zero,xmm2[4],zero,zero,zero,xmm2[5],zero,zero,zero,xmm2[6],zero,zero,zero,xmm2[7],zero,zero,zero
	vpermd	ymm1, ymm2, ymm1
	popcnt	rax, rax
	vmovdqu	ymmword ptr [rdi], ymm1
	lea	rdi, [rdi + 4*rax]
	add	rdx, 32
	cmp	rdx, rbx
	jne	.LBB0_4
.LBB0_6:
	cmp	r8, rbx
	je	.LBB0_9
# %bb.7:
	xor	eax, eax
	jmp	.LBB0_8
.LBB0_2:
	mov	rdi, rdx
.LBB0_8:
	mov	ecx, ebx
	sub	ecx, r8d
	add	ecx, 32
	shr	ecx, 2
	vmovdqa	ymm0, ymmword ptr [rbx]
	vpxor	xmm1, xmm1, xmm1
	vpcmpeqd	ymm1, ymm0, ymm1
	vmovmskps	edx, ymm1
	xor	edx, 255
	mov	sil, 8
	sub	sil, cl
	mov	rcx, -1
	shlx	rcx, rcx, rsi
	not	ecx
	shrx	ecx, ecx, eax
	shlx	ecx, ecx, eax
	and	ecx, edx
	pdep	rdx, rcx, r10
	mov	rsi, rdx
	shl	rsi, 8
	sub	rsi, rdx
	pext	rdx, r9, rsi
	vmovq	xmm1, rdx
	vpmovzxbd	ymm1, xmm1              # ymm1 = xmm1[0],zero,zero,zero,xmm1[1],zero,zero,zero,xmm1[2],zero,zero,zero,xmm1[3],zero,zero,zero,xmm1[4],zero,zero,zero,xmm1[5],zero,zero,zero,xmm1[6],zero,zero,zero,xmm1[7],zero,zero,zero
	popcnt	ecx, ecx
	vmovd	xmm2, ecx
	vpbroadcastd	ymm2, xmm2
	vpcmpgtd	ymm2, ymm2, ymmword ptr [rip + .LCPI0_0]
	vpermd	ymm0, ymm1, ymm0
	vpmaskmovd	ymmword ptr [rdi + 4*rax], ymm2, ymm0
.LBB0_9:
	pop	rbx
	.cfi_def_cfa_offset 8
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE, .Lfunc_end0-_Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 14.0.0 (https://github.com/llvm/llvm-project.git 52fddcdd9c90a550d7a50cbc2013be3314f91d08)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
