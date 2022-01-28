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
	mov	rdx, qword ptr [rdi]
	mov	r8, qword ptr [rdi + 8]
	cmp	rdx, r8
	je	.LBB0_9
# %bb.1:
	mov	rdi, rdx
	and	rdi, -32
	mov	r10, r8
	and	r10, -32
	shr	edx, 2
	and	edx, 7
	cmp	rdi, r10
	je	.LBB0_2
# %bb.3:
	vmovdqa	ymm1, ymmword ptr [rdi]
	vpxor	xmm0, xmm0, xmm0
	vpcmpeqd	ymm2, ymm1, ymm0
	vmovd	xmm3, edx
	vpbroadcastd	ymm3, xmm3
	vmovdqa	ymm4, ymmword ptr [rip + .LCPI0_0] # ymm4 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm3, ymm3, ymm4
	vpor	ymm2, ymm2, ymm3
	vpshufd	ymm3, ymm1, 57                  # ymm3 = ymm1[1,2,3,0,5,6,7,4]
	vpblendvb	ymm1, ymm1, ymm3, ymm2
	vpmovmskb	esi, ymm2
	not	esi
	mov	eax, esi
	and	eax, 2062097
	popcnt	r9d, eax
	popcnt	eax, esi
	shr	esi, 17
	and	esi, 13
	add	esi, r9d
	shl	rsi, 5
	vmovdqa	ymm2, ymmword ptr [rsi + _ZN3eve6detail27pattern_8_elements_dwords_vIjEE]
	vpermd	ymm1, ymm2, ymm1
	vmovd	xmm2, eax
	and	eax, -4
	vpbroadcastd	ymm2, xmm2
	vpsrld	ymm2, ymm2, 2
	vpcmpgtd	ymm2, ymm2, ymm4
	vpmaskmovd	ymmword ptr [rdi + 4*rdx], ymm2, ymm1
	lea	rsi, [rdi + 4*rdx]
	add	rsi, rax
	add	rdi, 32
	cmp	rdi, r10
	je	.LBB0_6
	.p2align	4, 0x90
.LBB0_4:                                # =>This Inner Loop Header: Depth=1
	vmovdqa	ymm1, ymmword ptr [rdi]
	vpcmpeqd	ymm2, ymm1, ymm0
	vpshufd	ymm3, ymm1, 57                  # ymm3 = ymm1[1,2,3,0,5,6,7,4]
	vpblendvb	ymm1, ymm1, ymm3, ymm2
	vpmovmskb	eax, ymm2
	not	eax
	mov	edx, eax
	and	edx, 2062097
	popcnt	edx, edx
	popcnt	ecx, eax
	shr	eax, 17
	and	eax, 13
	add	eax, edx
	and	ecx, -4
	shl	rax, 5
	vmovdqa	ymm2, ymmword ptr [rax + _ZN3eve6detail27pattern_8_elements_dwords_vIjEE]
	vpermd	ymm1, ymm2, ymm1
	vmovdqu	ymmword ptr [rsi], ymm1
	add	rsi, rcx
	add	rdi, 32
	cmp	rdi, r10
	jne	.LBB0_4
.LBB0_6:
	cmp	r8, r10
	je	.LBB0_9
# %bb.7:
	xor	edx, edx
	jmp	.LBB0_8
.LBB0_2:
	mov	rsi, rdi
.LBB0_8:
	mov	rax, r10
	sub	rax, r8
	add	rax, 32
	shr	rax, 2
	vmovdqa	ymm1, ymmword ptr [r10]
	vpxor	xmm0, xmm0, xmm0
	vpcmpeqd	ymm2, ymm1, ymm0
	vmovd	xmm0, edx
	vpbroadcastd	ymm3, xmm0
	vmovdqa	ymm0, ymmword ptr [rip + .LCPI0_0] # ymm0 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm3, ymm3, ymm0
	vpor	ymm2, ymm3, ymm2
	mov	ecx, 8
	sub	ecx, eax
	vmovd	xmm3, ecx
	vpbroadcastd	ymm3, xmm3
	vpcmpgtd	ymm3, ymm3, ymm0
	vpandn	ymm2, ymm2, ymm3
	vpshufd	ymm3, ymm1, 57                  # ymm3 = ymm1[1,2,3,0,5,6,7,4]
	vpblendvb	ymm1, ymm3, ymm1, ymm2
	vpmovmskb	eax, ymm2
	mov	ecx, eax
	and	ecx, 2062097
	popcnt	ecx, ecx
	popcnt	edi, eax
	shr	eax, 17
	and	eax, 13
	add	eax, ecx
	shl	rax, 5
	vmovdqa	ymm2, ymmword ptr [rax + _ZN3eve6detail27pattern_8_elements_dwords_vIjEE]
	vpermd	ymm1, ymm2, ymm1
	shr	edi, 2
	vmovd	xmm2, edi
	vpbroadcastd	ymm2, xmm2
	vpcmpgtd	ymm0, ymm2, ymm0
	vpmaskmovd	ymmword ptr [rsi + 4*rdx], ymm0, ymm1
.LBB0_9:
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE, .Lfunc_end0-_Z6removeRNSt3__16vectorIiNS_9allocatorIiEEEE
	.cfi_endproc
                                        # -- End function
	.type	_ZN3eve6detail27pattern_8_elements_dwords_vIjEE,@object # @_ZN3eve6detail27pattern_8_elements_dwords_vIjEE
	.section	.rodata._ZN3eve6detail27pattern_8_elements_dwords_vIjEE,"aG",@progbits,_ZN3eve6detail27pattern_8_elements_dwords_vIjEE,comdat
	.weak	_ZN3eve6detail27pattern_8_elements_dwords_vIjEE
	.p2align	5
_ZN3eve6detail27pattern_8_elements_dwords_vIjEE:
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	1                               # 0x1
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	2                               # 0x2
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	2                               # 0x2
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	1                               # 0x1
	.long	2                               # 0x2
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	2                               # 0x2
	.long	3                               # 0x3
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	2                               # 0x2
	.long	3                               # 0x3
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	1                               # 0x1
	.long	2                               # 0x2
	.long	3                               # 0x3
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	4                               # 0x4
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	4                               # 0x4
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	1                               # 0x1
	.long	4                               # 0x4
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	2                               # 0x2
	.long	4                               # 0x4
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	2                               # 0x2
	.long	4                               # 0x4
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	1                               # 0x1
	.long	2                               # 0x2
	.long	4                               # 0x4
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	2                               # 0x2
	.long	3                               # 0x3
	.long	4                               # 0x4
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	2                               # 0x2
	.long	3                               # 0x3
	.long	4                               # 0x4
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	1                               # 0x1
	.long	2                               # 0x2
	.long	3                               # 0x3
	.long	4                               # 0x4
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	4                               # 0x4
	.long	5                               # 0x5
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	4                               # 0x4
	.long	5                               # 0x5
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	1                               # 0x1
	.long	4                               # 0x4
	.long	5                               # 0x5
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	2                               # 0x2
	.long	4                               # 0x4
	.long	5                               # 0x5
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	2                               # 0x2
	.long	4                               # 0x4
	.long	5                               # 0x5
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	1                               # 0x1
	.long	2                               # 0x2
	.long	4                               # 0x4
	.long	5                               # 0x5
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	2                               # 0x2
	.long	3                               # 0x3
	.long	4                               # 0x4
	.long	5                               # 0x5
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	2                               # 0x2
	.long	3                               # 0x3
	.long	4                               # 0x4
	.long	5                               # 0x5
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	0                               # 0x0
	.long	0                               # 0x0
	.long	1                               # 0x1
	.long	2                               # 0x2
	.long	3                               # 0x3
	.long	4                               # 0x4
	.long	5                               # 0x5
	.long	6                               # 0x6
	.long	7                               # 0x7
	.size	_ZN3eve6detail27pattern_8_elements_dwords_vIjEE, 864

	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 14.0.0 (https://github.com/llvm/llvm-project.git 52fddcdd9c90a550d7a50cbc2013be3314f91d08)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
