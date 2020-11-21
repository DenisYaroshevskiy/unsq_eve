	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z7reversePcS_                  # -- Begin function _Z7reversePcS_
	.p2align	4, 0x90
	.type	_Z7reversePcS_,@function
_Z7reversePcS_:                         # @_Z7reversePcS_
	.cfi_startproc
# %bb.0:
	jmp	_ZN8unsq_eve7reverseINS_16algorithm_traitsIcLm256ELm1EEEPcEEvT0_S4_ # TAILCALL
.Lfunc_end0:
	.size	_Z7reversePcS_, .Lfunc_end0-_Z7reversePcS_
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5                               # -- Begin function _ZN8unsq_eve7reverseINS_16algorithm_traitsIcLm256ELm1EEEPcEEvT0_S4_
.LCPI1_0:
	.byte	15                              # 0xf
	.byte	14                              # 0xe
	.byte	13                              # 0xd
	.byte	12                              # 0xc
	.byte	11                              # 0xb
	.byte	10                              # 0xa
	.byte	9                               # 0x9
	.byte	8                               # 0x8
	.byte	7                               # 0x7
	.byte	6                               # 0x6
	.byte	5                               # 0x5
	.byte	4                               # 0x4
	.byte	3                               # 0x3
	.byte	2                               # 0x2
	.byte	1                               # 0x1
	.byte	0                               # 0x0
	.byte	15                              # 0xf
	.byte	14                              # 0xe
	.byte	13                              # 0xd
	.byte	12                              # 0xc
	.byte	11                              # 0xb
	.byte	10                              # 0xa
	.byte	9                               # 0x9
	.byte	8                               # 0x8
	.byte	7                               # 0x7
	.byte	6                               # 0x6
	.byte	5                               # 0x5
	.byte	4                               # 0x4
	.byte	3                               # 0x3
	.byte	2                               # 0x2
	.byte	1                               # 0x1
	.byte	0                               # 0x0
	.section	.text._ZN8unsq_eve7reverseINS_16algorithm_traitsIcLm256ELm1EEEPcEEvT0_S4_,"axG",@progbits,_ZN8unsq_eve7reverseINS_16algorithm_traitsIcLm256ELm1EEEPcEEvT0_S4_,comdat
	.weak	_ZN8unsq_eve7reverseINS_16algorithm_traitsIcLm256ELm1EEEPcEEvT0_S4_
	.p2align	4, 0x90
	.type	_ZN8unsq_eve7reverseINS_16algorithm_traitsIcLm256ELm1EEEPcEEvT0_S4_,@function
_ZN8unsq_eve7reverseINS_16algorithm_traitsIcLm256ELm1EEEPcEEvT0_S4_: # @_ZN8unsq_eve7reverseINS_16algorithm_traitsIcLm256ELm1EEEPcEEvT0_S4_
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
	sub	rsp, 64
	.cfi_offset rbx, -40
	.cfi_offset r14, -32
	.cfi_offset r15, -24
	cmp	rdi, rsi
	je	.LBB1_15
# %bb.1:
	mov	rbx, rsi
	mov	r14, rdi
	mov	rax, rsi
	sub	rax, rdi
	mov	r15, rax
	shr	r15, 6
	mov	rcx, r15
	shl	rcx, 6
	sub	rax, rcx
	cmp	rax, 31
	jg	.LBB1_16
# %bb.2:
	mov	rcx, r15
	shl	rcx, 5
	lea	rdi, [r14 + rcx]
	mov	rax, rbx
	sub	rax, rcx
	add	rcx, r14
	add	rcx, 4096
	and	rcx, -4096
	sub	rcx, rdi
	cmp	rcx, 31
	jg	.LBB1_5
# %bb.3:
	lea	rdx, [rax - 32]
	sub	rdx, rdi
	vmovdqu	ymm0, ymmword ptr [rax - 32]
	vpshufb	ymm0, ymm0, ymmword ptr [rip + .LCPI1_0] # ymm0 = ymm0[15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16]
	vpermq	ymm0, ymm0, 78                  # ymm0 = ymm0[2,3,0,1]
	vmovdqa	ymmword ptr [rsp], ymm0
	add	rdx, 32
	je	.LBB1_8
# %bb.4:
	mov	rsi, rsp
	jmp	.LBB1_7
.LBB1_16:
	inc	r15
	jmp	.LBB1_9
.LBB1_5:
	mov	rcx, rdi
	sub	rcx, rax
	vmovdqu	ymm0, ymmword ptr [rdi]
	vpshufb	ymm0, ymm0, ymmword ptr [rip + .LCPI1_0] # ymm0 = ymm0[15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16]
	vpermq	ymm0, ymm0, 78                  # ymm0 = ymm0[2,3,0,1]
	vmovdqa	ymmword ptr [rsp], ymm0
	mov	rdx, rcx
	neg	rdx
	je	.LBB1_8
# %bb.6:
	add	rcx, 32
	lea	rsi, [rsp + rcx]
.LBB1_7:
	vzeroupper
	call	memcpy
.LBB1_8:
	test	r15, r15
	je	.LBB1_15
.LBB1_9:
	test	r15b, 1
	jne	.LBB1_11
# %bb.10:
	mov	rax, r15
	cmp	r15, 1
	jne	.LBB1_13
	jmp	.LBB1_15
.LBB1_11:
	lea	rax, [r15 - 1]
	vmovdqu	ymm0, ymmword ptr [r14]
	vmovdqu	ymm1, ymmword ptr [rbx - 32]
	vmovdqa	ymm2, ymmword ptr [rip + .LCPI1_0] # ymm2 = [15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0]
	vpshufb	ymm0, ymm0, ymm2
	vpermq	ymm0, ymm0, 78                  # ymm0 = ymm0[2,3,0,1]
	vmovdqu	ymmword ptr [rbx - 32], ymm0
	add	rbx, -32
	vpshufb	ymm0, ymm1, ymm2
	vpermq	ymm0, ymm0, 78                  # ymm0 = ymm0[2,3,0,1]
	vmovdqu	ymmword ptr [r14], ymm0
	add	r14, 32
	cmp	r15, 1
	je	.LBB1_15
.LBB1_13:
	add	rbx, -32
	vmovdqa	ymm0, ymmword ptr [rip + .LCPI1_0] # ymm0 = [15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0]
	.p2align	4, 0x90
.LBB1_14:                               # =>This Inner Loop Header: Depth=1
	vmovdqu	ymm1, ymmword ptr [r14]
	vmovdqu	ymm2, ymmword ptr [rbx]
	vpshufb	ymm1, ymm1, ymm0
	vpermq	ymm1, ymm1, 78                  # ymm1 = ymm1[2,3,0,1]
	vpshufb	ymm2, ymm2, ymm0
	vpermq	ymm2, ymm2, 78                  # ymm2 = ymm2[2,3,0,1]
	vmovdqu	ymmword ptr [rbx], ymm1
	vmovdqu	ymmword ptr [r14], ymm2
	vmovdqu	ymm1, ymmword ptr [r14 + 32]
	vmovdqu	ymm2, ymmword ptr [rbx - 32]
	vpshufb	ymm1, ymm1, ymm0
	vpermq	ymm1, ymm1, 78                  # ymm1 = ymm1[2,3,0,1]
	vmovdqu	ymmword ptr [rbx - 32], ymm1
	add	rbx, -64
	vpshufb	ymm1, ymm2, ymm0
	vpermq	ymm1, ymm1, 78                  # ymm1 = ymm1[2,3,0,1]
	vmovdqu	ymmword ptr [r14 + 32], ymm1
	add	r14, 64
	add	rax, -2
	jne	.LBB1_14
.LBB1_15:
	lea	rsp, [rbp - 24]
	pop	rbx
	pop	r14
	pop	r15
	pop	rbp
	.cfi_def_cfa rsp, 8
	vzeroupper
	ret
.Lfunc_end1:
	.size	_ZN8unsq_eve7reverseINS_16algorithm_traitsIcLm256ELm1EEEPcEEvT0_S4_, .Lfunc_end1-_ZN8unsq_eve7reverseINS_16algorithm_traitsIcLm256ELm1EEEPcEEvT0_S4_
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
	.ident	"clang version 12.0.0 (https://github.com/llvm/llvm-project.git d4f1a3c6e2c6031eb45ddb51e3f4fbf50bde6ed8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
	.addrsig_sym _GLOBAL__sub_I_disassemble.cc
	.addrsig_sym _ZN3eve6detail12cpuid_statesE
