	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5                               # -- Begin function _Z3anyPiS_i
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
	.globl	_Z3anyPiS_i
	.p2align	4, 0x90
	.type	_Z3anyPiS_i,@function
_Z3anyPiS_i:                            # @_Z3anyPiS_i
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	push	r15
	push	r14
	push	r12
	push	rbx
	and	rsp, -32
	sub	rsp, 96
	.cfi_offset rbx, -48
	.cfi_offset r12, -40
	.cfi_offset r14, -32
	.cfi_offset r15, -24
	cmp	rdi, rsi
	je	.LBB0_8
# %bb.1:
	vmovd	xmm0, edx
	vpbroadcastd	ymm0, xmm0
	movabs	r8, -4294967296
	movabs	r9, 34359738368
	mov	rcx, rdi
	and	rcx, -32
	mov	rdx, rsi
	and	rdx, -32
	shr	edi, 2
	mov	r12d, edi
	and	r12d, 7
	movabs	r11, 6148914691236517205
	movabs	r10, 506097522914230528
	cmp	rcx, rdx
	je	.LBB0_2
# %bb.3:
	vmovdqa	ymm1, ymmword ptr [rcx]
	vpcmpeqd	ymm2, ymm1, ymm0
	vpmovmskb	edi, ymm2
	not	edi
	lea	ebx, [4*r12]
	shrx	edi, edi, ebx
	shlx	edi, edi, ebx
	lea	r14, [rcx + 4*r12]
	pdep	rbx, rdi, r11
	lea	r15, [rbx + 2*rbx]
	xor	ebx, ebx
	popcnt	ebx, edi
	pext	rdi, r10, r15
	vmovq	xmm2, rdi
	vpmovzxbd	ymm2, xmm2              # ymm2 = xmm2[0],zero,zero,zero,xmm2[1],zero,zero,zero,xmm2[2],zero,zero,zero,xmm2[3],zero,zero,zero,xmm2[4],zero,zero,zero,xmm2[5],zero,zero,zero,xmm2[6],zero,zero,zero,xmm2[7],zero,zero,zero
	shr	ebx, 2
	vpermd	ymm1, ymm2, ymm1
	lea	rdi, [r14 + 4*rbx]
	shl	rbx, 32
	and	rbx, r8
	mov	rax, r9
	sub	rax, rbx
	shr	rax, 32
	mov	ebx, 8
	sub	ebx, eax
	vmovd	xmm2, ebx
	vpbroadcastd	ymm2, xmm2
	vpcmpgtd	ymm2, ymm2, ymmword ptr [rip + .LCPI0_0]
	vpmaskmovd	ymmword ptr [rcx + 4*r12], ymm2, ymm1
	add	rcx, 32
	cmp	rcx, rdx
	je	.LBB0_5
	.p2align	4, 0x90
.LBB0_4:                                # =>This Inner Loop Header: Depth=1
	vmovdqa	ymm1, ymmword ptr [rcx]
	vpcmpeqd	ymm2, ymm1, ymm0
	vpmovmskb	eax, ymm2
	not	eax
	pdep	rbx, rax, r11
	lea	rbx, [rbx + 2*rbx]
	popcnt	eax, eax
	pext	rbx, r10, rbx
	vmovq	xmm2, rbx
	vpmovzxbd	ymm2, xmm2              # ymm2 = xmm2[0],zero,zero,zero,xmm2[1],zero,zero,zero,xmm2[2],zero,zero,zero,xmm2[3],zero,zero,zero,xmm2[4],zero,zero,zero,xmm2[5],zero,zero,zero,xmm2[6],zero,zero,zero,xmm2[7],zero,zero,zero
	and	eax, -4
	vpermd	ymm1, ymm2, ymm1
	vmovdqu	ymmword ptr [rdi], ymm1
	add	rdi, rax
	add	rcx, 32
	cmp	rdx, rcx
	jne	.LBB0_4
.LBB0_5:
	cmp	rdx, rsi
	je	.LBB0_8
# %bb.6:
	xor	r12d, r12d
	jmp	.LBB0_7
.LBB0_2:
	mov	rdi, rcx
.LBB0_7:
	mov	eax, edx
	sub	eax, esi
	vmovdqa	ymm1, ymmword ptr [rdx]
	vpcmpeqd	ymm0, ymm1, ymm0
	vpmovmskb	ecx, ymm0
	lea	edx, [4*r12]
	add	al, 32
	and	al, -4
	mov	sil, 32
	sub	sil, al
	mov	rax, -1
	shlx	rax, rax, rsi
	not	eax
	shrx	eax, eax, edx
	shlx	eax, eax, edx
	andn	eax, ecx, eax
	lea	rcx, [rdi + 4*r12]
	pdep	rdx, rax, r11
	lea	rdx, [rdx + 2*rdx]
	popcnt	eax, eax
	pext	rdx, r10, rdx
	vmovq	xmm0, rdx
	vpmovzxbd	ymm0, xmm0              # ymm0 = xmm0[0],zero,zero,zero,xmm0[1],zero,zero,zero,xmm0[2],zero,zero,zero,xmm0[3],zero,zero,zero,xmm0[4],zero,zero,zero,xmm0[5],zero,zero,zero,xmm0[6],zero,zero,zero,xmm0[7],zero,zero,zero
	shr	eax, 2
	vpermd	ymm0, ymm0, ymm1
	mov	rdx, rax
	shl	rdx, 32
	and	rdx, r8
	sub	r9, rdx
	shr	r9, 32
	mov	edx, 8
	sub	edx, r9d
	vmovd	xmm1, edx
	vpbroadcastd	ymm1, xmm1
	vpcmpgtd	ymm1, ymm1, ymmword ptr [rip + .LCPI0_0]
	vpmaskmovd	ymmword ptr [rdi + 4*r12], ymm1, ymm0
	lea	rdi, [rcx + 4*rax]
.LBB0_8:
	test	rdi, rdi
	setne	al
	lea	rsp, [rbp - 32]
	pop	rbx
	pop	r12
	pop	r14
	pop	r15
	pop	rbp
	.cfi_def_cfa rsp, 8
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z3anyPiS_i, .Lfunc_end0-_Z3anyPiS_i
	.cfi_endproc
                                        # -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90                         # -- Begin function _GLOBAL__sub_I_disassemble.cc
	.type	_GLOBAL__sub_I_disassemble.cc,@function
_GLOBAL__sub_I_disassemble.cc:          # @_GLOBAL__sub_I_disassemble.cc
	.cfi_startproc
# %bb.0:
	xor	eax, eax
	#APP
	xchg	rsi, rbx
	cpuid
	xchg	rsi, rbx
	#NO_APP
	mov	r11d, eax
	xor	eax, eax
	xor	ecx, ecx
	#APP
	xchg	rdi, rbx
	cpuid
	xchg	rdi, rbx
	#NO_APP
	xor	ecx, ecx
	mov	eax, 1
	#APP
	xchg	rsi, rbx
	cpuid
	xchg	rsi, rbx
	#NO_APP
	mov	r8d, edx
	mov	r10d, ecx
	mov	eax, 7
	xor	ecx, ecx
	#APP
	xchg	r9, rbx
	cpuid
	xchg	r9, rbx
	#NO_APP
	cmp	edi, 1970169159
	vxorps	xmm0, xmm0, xmm0
	vmovups	ymmword ptr [rip + _ZN3eve6detail12cpuid_statesE+8], ymm0
	mov	qword ptr [rip + _ZN3eve6detail12cpuid_statesE+40], 0
	sete	byte ptr [rip + _ZN3eve6detail12cpuid_statesE]
	cmp	edi, 1752462657
	sete	byte ptr [rip + _ZN3eve6detail12cpuid_statesE+1]
	test	r11d, r11d
	je	.LBB1_3
# %bb.1:
	mov	eax, r10d
	mov	qword ptr [rip + _ZN3eve6detail12cpuid_statesE+8], rax
	mov	eax, r8d
	mov	qword ptr [rip + _ZN3eve6detail12cpuid_statesE+16], rax
	cmp	r11d, 7
	jb	.LBB1_3
# %bb.2:
	mov	eax, r9d
	mov	qword ptr [rip + _ZN3eve6detail12cpuid_statesE+24], rax
	mov	eax, ecx
	mov	qword ptr [rip + _ZN3eve6detail12cpuid_statesE+32], rax
.LBB1_3:
	mov	eax, -2147483648
	#APP
	xchg	rsi, rbx
	cpuid
	xchg	rsi, rbx
	#NO_APP
	cmp	eax, -2147483647
	jb	.LBB1_5
# %bb.4:
	mov	eax, -2147483647
	xor	ecx, ecx
	#APP
	xchg	rsi, rbx
	cpuid
	xchg	rsi, rbx
	#NO_APP
	mov	eax, ecx
	mov	qword ptr [rip + _ZN3eve6detail12cpuid_statesE+40], rax
.LBB1_5:
	vzeroupper
	ret
.Lfunc_end1:
	.size	_GLOBAL__sub_I_disassemble.cc, .Lfunc_end1-_GLOBAL__sub_I_disassemble.cc
	.cfi_endproc
                                        # -- End function
	.type	_ZN3eve6detail12cpuid_statesE,@object # @_ZN3eve6detail12cpuid_statesE
	.local	_ZN3eve6detail12cpuid_statesE
	.comm	_ZN3eve6detail12cpuid_statesE,48,8
	.section	.init_array,"aw",@init_array
	.p2align	3
	.quad	_GLOBAL__sub_I_disassemble.cc
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 12.0.0 (https://github.com/llvm/llvm-project.git 6ce5b74b82ab4667dde688860f2d3a7be88e46da)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
	.addrsig_sym _GLOBAL__sub_I_disassemble.cc
	.addrsig_sym _ZN3eve6detail12cpuid_statesE
