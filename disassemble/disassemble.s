	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z3anyPKiS0_i           # -- Begin function _Z3anyPKiS0_i
	.p2align	4, 0x90
	.type	_Z3anyPKiS0_i,@function
_Z3anyPKiS0_i:                          # @_Z3anyPKiS0_i
	.cfi_startproc
# %bb.0:
	mov	rax, rdi
	vmovd	xmm0, edx
	vpbroadcastd	ymm0, xmm0
	mov	rdx, rdi
	and	rdx, -32
	mov	r10, rsi
	and	r10, -32
	shr	eax, 2
	and	eax, 7
	cmp	rdx, r10
	je	.LBB0_1
# %bb.2:
	vpcmpeqd	ymm1, ymm0, ymmword ptr [rdx]
	vpmovmskb	edi, ymm1
	shl	eax, 2
	shrx	edi, edi, eax
	shlx	edi, edi, eax
	mov	al, 1
	test	edi, edi
	je	.LBB0_3
.LBB0_20:
                                        # kill: def $al killed $al killed $rax
	vzeroupper
	ret
.LBB0_1:
	shl	eax, 2
.LBB0_19:
	mov	ecx, r10d
	sub	ecx, esi
	vpcmpeqd	ymm0, ymm0, ymmword ptr [r10]
	vpmovmskb	edx, ymm0
	add	cl, 32
	and	cl, -4
	mov	sil, 32
	sub	sil, cl
	mov	rcx, -1
	shlx	rcx, rcx, rsi
	not	ecx
	shrx	ecx, ecx, eax
	shlx	eax, ecx, eax
	test	eax, edx
	setne	al
                                        # kill: def $al killed $al killed $rax
	vzeroupper
	ret
.LBB0_3:
	add	rdx, 32
	cmp	rdx, r10
	je	.LBB0_18
# %bb.4:
	movabs	r8, 4611686018427387872
	jmp	.LBB0_5
.LBB0_16:                               #   in Loop: Header=BB0_5 Depth=1
	mov	rdx, r9
.LBB0_17:                               #   in Loop: Header=BB0_5 Depth=1
	cmp	rdx, r10
	je	.LBB0_18
.LBB0_5:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_14 Depth 2
	vpcmpeqd	ymm1, ymm0, ymmword ptr [rdx]
	vmovmskps	edi, ymm1
	test	edi, edi
	jne	.LBB0_20
# %bb.6:                                #   in Loop: Header=BB0_5 Depth=1
	lea	rdi, [rdx + 32]
	cmp	rdi, r10
	je	.LBB0_18
# %bb.7:                                #   in Loop: Header=BB0_5 Depth=1
	vpcmpeqd	ymm1, ymm0, ymmword ptr [rdi]
	vmovmskps	edi, ymm1
	test	edi, edi
	jne	.LBB0_20
# %bb.8:                                #   in Loop: Header=BB0_5 Depth=1
	lea	rdi, [rdx + 64]
	cmp	rdi, r10
	je	.LBB0_18
# %bb.9:                                #   in Loop: Header=BB0_5 Depth=1
	vpcmpeqd	ymm1, ymm0, ymmword ptr [rdi]
	vmovmskps	edi, ymm1
	test	edi, edi
	jne	.LBB0_20
# %bb.10:                               #   in Loop: Header=BB0_5 Depth=1
	lea	rdi, [rdx + 96]
	cmp	rdi, r10
	je	.LBB0_18
# %bb.11:                               #   in Loop: Header=BB0_5 Depth=1
	vpcmpeqd	ymm1, ymm0, ymmword ptr [rdi]
	vmovmskps	edi, ymm1
	test	edi, edi
	jne	.LBB0_20
# %bb.12:                               #   in Loop: Header=BB0_5 Depth=1
	sub	rdx, -128
	mov	rdi, r10
	sub	rdi, rdx
	sar	rdi, 2
	lea	r9, [rdi + 31]
	cmp	r9, 63
	jb	.LBB0_17
# %bb.13:                               #   in Loop: Header=BB0_5 Depth=1
	test	rdi, rdi
	cmovns	r9, rdi
	mov	rdi, r9
	sar	rdi, 5
	and	r9, r8
	lea	r9, [rdx + 4*r9]
	.p2align	4, 0x90
.LBB0_14:                               #   Parent Loop BB0_5 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vpcmpeqd	ymm1, ymm0, ymmword ptr [rdx]
	vpcmpeqd	ymm2, ymm0, ymmword ptr [rdx + 32]
	vpor	ymm1, ymm2, ymm1
	vpcmpeqd	ymm2, ymm0, ymmword ptr [rdx + 64]
	vpcmpeqd	ymm3, ymm0, ymmword ptr [rdx + 96]
	vpor	ymm2, ymm2, ymm3
	vpor	ymm1, ymm1, ymm2
	vmovmskps	ecx, ymm1
	test	ecx, ecx
	jne	.LBB0_20
# %bb.15:                               #   in Loop: Header=BB0_14 Depth=2
	sub	rdx, -128
	dec	rdi
	jne	.LBB0_14
	jmp	.LBB0_16
.LBB0_18:
	xor	eax, eax
	cmp	r10, rsi
	jne	.LBB0_19
	jmp	.LBB0_20
.Lfunc_end0:
	.size	_Z3anyPKiS0_i, .Lfunc_end0-_Z3anyPKiS0_i
	.cfi_endproc
                                        # -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90         # -- Begin function _GLOBAL__sub_I_disassemble.cc
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
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git 448bbc512f456df6fc817b0d7041897eea2375b7)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
	.addrsig_sym _GLOBAL__sub_I_disassemble.cc
	.addrsig_sym _ZN3eve6detail12cpuid_statesE
