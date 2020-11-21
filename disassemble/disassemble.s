	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z7reversePiS_                  # -- Begin function _Z7reversePiS_
	.p2align	4, 0x90
	.type	_Z7reversePiS_,@function
_Z7reversePiS_:                         # @_Z7reversePiS_
	.cfi_startproc
# %bb.0:
	jmp	_ZN8unsq_eve7reverseINS_16algorithm_traitsIiLm256ELm4EEEPiEEvT0_S4_ # TAILCALL
.Lfunc_end0:
	.size	_Z7reversePiS_, .Lfunc_end0-_Z7reversePiS_
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5                               # -- Begin function _ZN8unsq_eve7reverseINS_16algorithm_traitsIiLm256ELm4EEEPiEEvT0_S4_
.LCPI1_0:
	.long	7                               # 0x7
	.long	6                               # 0x6
	.long	5                               # 0x5
	.long	4                               # 0x4
	.long	3                               # 0x3
	.long	2                               # 0x2
	.long	1                               # 0x1
	.long	0                               # 0x0
.LCPI1_1:
	.long	1                               # 0x1
	.long	2                               # 0x2
	.long	3                               # 0x3
	.long	4                               # 0x4
	.long	5                               # 0x5
	.long	6                               # 0x6
	.long	7                               # 0x7
	.long	8                               # 0x8
.LCPI1_2:
	.long	0                               # 0x0
	.long	1                               # 0x1
	.long	2                               # 0x2
	.long	3                               # 0x3
	.long	4                               # 0x4
	.long	5                               # 0x5
	.long	6                               # 0x6
	.long	7                               # 0x7
	.section	.text._ZN8unsq_eve7reverseINS_16algorithm_traitsIiLm256ELm4EEEPiEEvT0_S4_,"axG",@progbits,_ZN8unsq_eve7reverseINS_16algorithm_traitsIiLm256ELm4EEEPiEEvT0_S4_,comdat
	.weak	_ZN8unsq_eve7reverseINS_16algorithm_traitsIiLm256ELm4EEEPiEEvT0_S4_
	.p2align	4, 0x90
	.type	_ZN8unsq_eve7reverseINS_16algorithm_traitsIiLm256ELm4EEEPiEEvT0_S4_,@function
_ZN8unsq_eve7reverseINS_16algorithm_traitsIiLm256ELm4EEEPiEEvT0_S4_: # @_ZN8unsq_eve7reverseINS_16algorithm_traitsIiLm256ELm4EEEPiEEvT0_S4_
	.cfi_startproc
# %bb.0:
	cmp	rdi, rsi
	je	.LBB1_15
# %bb.1:
	mov	rcx, rsi
	sub	rcx, rdi
	sar	rcx, 2
	mov	rax, rcx
	shr	rax, 4
	mov	rdx, rax
	shl	rdx, 4
	sub	rcx, rdx
	cmp	rcx, 7
	jg	.LBB1_4
# %bb.2:
	mov	rcx, rax
	shl	rcx, 5
	lea	r8, [rdi + rcx]
	mov	rdx, rsi
	sub	rdx, rcx
	add	rcx, rdi
	add	rcx, 4096
	and	rcx, -4096
	sub	rcx, r8
	cmp	rcx, 31
	jg	.LBB1_5
# %bb.3:
	lea	r9, [rdx - 32]
	mov	rcx, r8
	sub	rcx, r9
	shr	rcx, 2
	vmovdqa	ymm0, ymmword ptr [rip + .LCPI1_0] # ymm0 = [7,6,5,4,3,2,1,0]
	vpermd	ymm0, ymm0, ymmword ptr [rdx - 32]
	mov	edx, 8
	sub	edx, ecx
	vmovd	xmm1, edx
	vpbroadcastd	ymm1, xmm1
	vpcmpgtd	ymm1, ymm1, ymmword ptr [rip + .LCPI1_2]
	vpmaskmovd	ymmword ptr [r8], ymm1, ymm0
	test	rax, rax
	jne	.LBB1_7
	jmp	.LBB1_15
.LBB1_4:
	inc	rax
	vmovdqa	ymm0, ymmword ptr [rip + .LCPI1_0] # ymm0 = [7,6,5,4,3,2,1,0]
	jmp	.LBB1_9
.LBB1_5:
	mov	rcx, r8
	sub	rcx, rdx
	add	rcx, 32
	vmovdqa	ymm0, ymmword ptr [rip + .LCPI1_0] # ymm0 = [7,6,5,4,3,2,1,0]
	vpermd	ymm0, ymm0, ymmword ptr [r8]
	sub	r8, rcx
	shr	rcx, 2
	vmovd	xmm1, ecx
	vpbroadcastd	ymm1, xmm1
	vmovdqa	ymm2, ymmword ptr [rip + .LCPI1_1] # ymm2 = [1,2,3,4,5,6,7,8]
	vpcmpgtd	ymm1, ymm2, ymm1
	vpmaskmovd	ymmword ptr [r8], ymm1, ymm0
	test	rax, rax
	je	.LBB1_15
.LBB1_7:
	vmovdqa	ymm0, ymmword ptr [rip + .LCPI1_0] # ymm0 = [7,6,5,4,3,2,1,0]
	jmp	.LBB1_9
	.p2align	4, 0x90
.LBB1_8:                                #   in Loop: Header=BB1_9 Depth=1
	add	rax, -4
	mov	rsi, rcx
	test	rax, rax
	je	.LBB1_15
.LBB1_9:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_14 Depth 2
	vpermd	ymm1, ymm0, ymmword ptr [rdi]
	vpermd	ymm2, ymm0, ymmword ptr [rsi - 32]
	vmovdqu	ymmword ptr [rsi - 32], ymm1
	vmovdqu	ymmword ptr [rdi], ymm2
	cmp	rax, 1
	je	.LBB1_15
# %bb.10:                               #   in Loop: Header=BB1_9 Depth=1
	vpermd	ymm1, ymm0, ymmword ptr [rdi + 32]
	vpermd	ymm2, ymm0, ymmword ptr [rsi - 64]
	vmovdqu	ymmword ptr [rsi - 64], ymm1
	vmovdqu	ymmword ptr [rdi + 32], ymm2
	cmp	rax, 2
	je	.LBB1_15
# %bb.11:                               #   in Loop: Header=BB1_9 Depth=1
	vpermd	ymm1, ymm0, ymmword ptr [rdi + 64]
	vpermd	ymm2, ymm0, ymmword ptr [rsi - 96]
	vmovdqu	ymmword ptr [rsi - 96], ymm1
	vmovdqu	ymmword ptr [rdi + 64], ymm2
	cmp	rax, 3
	je	.LBB1_15
# %bb.12:                               #   in Loop: Header=BB1_9 Depth=1
	lea	rcx, [rsi - 128]
	vpermd	ymm1, ymm0, ymmword ptr [rdi + 96]
	vpermd	ymm2, ymm0, ymmword ptr [rsi - 128]
	vmovdqu	ymmword ptr [rsi - 128], ymm1
	vmovdqu	ymmword ptr [rdi + 96], ymm2
	sub	rdi, -128
	cmp	rax, 8
	jl	.LBB1_8
	.p2align	4, 0x90
.LBB1_14:                               #   Parent Loop BB1_9 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vpermd	ymm1, ymm0, ymmword ptr [rdi]
	vpermd	ymm2, ymm0, ymmword ptr [rcx - 32]
	vmovdqu	ymmword ptr [rcx - 32], ymm1
	vmovdqu	ymmword ptr [rdi], ymm2
	vpermd	ymm1, ymm0, ymmword ptr [rdi + 32]
	vpermd	ymm2, ymm0, ymmword ptr [rcx - 64]
	vmovdqu	ymmword ptr [rcx - 64], ymm1
	vmovdqu	ymmword ptr [rdi + 32], ymm2
	vpermd	ymm1, ymm0, ymmword ptr [rdi + 64]
	vpermd	ymm2, ymm0, ymmword ptr [rcx - 96]
	vmovdqu	ymmword ptr [rcx - 96], ymm1
	vmovdqu	ymmword ptr [rdi + 64], ymm2
	vpermd	ymm1, ymm0, ymmword ptr [rdi + 96]
	vpermd	ymm2, ymm0, ymmword ptr [rcx - 128]
	vmovdqu	ymmword ptr [rcx - 128], ymm1
	add	rcx, -128
	vmovdqu	ymmword ptr [rdi + 96], ymm2
	sub	rdi, -128
	add	rax, -4
	cmp	rax, 8
	jge	.LBB1_14
	jmp	.LBB1_8
.LBB1_15:
	vzeroupper
	ret
.Lfunc_end1:
	.size	_ZN8unsq_eve7reverseINS_16algorithm_traitsIiLm256ELm4EEEPiEEvT0_S4_, .Lfunc_end1-_ZN8unsq_eve7reverseINS_16algorithm_traitsIiLm256ELm4EEEPiEEvT0_S4_
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
	je	.LBB2_3
# %bb.1:
	mov	eax, r10d
	mov	qword ptr [rip + _ZN3eve6detail12cpuid_statesE+8], rax
	mov	eax, r8d
	mov	qword ptr [rip + _ZN3eve6detail12cpuid_statesE+16], rax
	cmp	r11d, 7
	jb	.LBB2_3
# %bb.2:
	mov	eax, r9d
	mov	qword ptr [rip + _ZN3eve6detail12cpuid_statesE+24], rax
	mov	eax, ecx
	mov	qword ptr [rip + _ZN3eve6detail12cpuid_statesE+32], rax
.LBB2_3:
	mov	eax, -2147483648
	#APP
	xchg	rsi, rbx
	cpuid
	xchg	rsi, rbx
	#NO_APP
	cmp	eax, -2147483647
	jb	.LBB2_5
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
.LBB2_5:
	vzeroupper
	ret
.Lfunc_end2:
	.size	_GLOBAL__sub_I_disassemble.cc, .Lfunc_end2-_GLOBAL__sub_I_disassemble.cc
	.cfi_endproc
                                        # -- End function
	.type	_ZN3eve6detail12cpuid_statesE,@object # @_ZN3eve6detail12cpuid_statesE
	.local	_ZN3eve6detail12cpuid_statesE
	.comm	_ZN3eve6detail12cpuid_statesE,48,8
	.section	.init_array,"aw",@init_array
	.p2align	3
	.quad	_GLOBAL__sub_I_disassemble.cc
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 12.0.0 (https://github.com/llvm/llvm-project.git 40a24541029357543ae47664a68a44710e6fee84)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
	.addrsig_sym _GLOBAL__sub_I_disassemble.cc
	.addrsig_sym _ZN3eve6detail12cpuid_statesE
