	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z10any_zeroesPKcS0_    # -- Begin function _Z10any_zeroesPKcS0_
	.p2align	4, 0x90
	.type	_Z10any_zeroesPKcS0_,@function
_Z10any_zeroesPKcS0_:                   # @_Z10any_zeroesPKcS0_
.L_Z10any_zeroesPKcS0_$local:
	.cfi_startproc
# %bb.0:
	mov	rax, rdi
	mov	rdx, rdi
	and	rdx, -32
	mov	rcx, rsi
	and	rcx, -32
	and	eax, 31
	cmp	rdx, rcx
	je	.LBB0_7
# %bb.1:
	vpxor	xmm0, xmm0, xmm0
	vpcmpeqb	ymm0, ymm0, ymmword ptr [rdx]
	vpmovmskb	edi, ymm0
	shrx	edi, edi, eax
	shlx	edi, edi, eax
	mov	al, 1
	test	edi, edi
	je	.LBB0_2
.LBB0_8:
                                        # kill: def $al killed $al killed $rax
	vzeroupper
	ret
.LBB0_2:
	add	rdx, 32
	cmp	rdx, rcx
	je	.LBB0_6
# %bb.3:
	vpxor	xmm0, xmm0, xmm0
	.p2align	4, 0x90
.LBB0_5:                                # =>This Inner Loop Header: Depth=1
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rdx]
	vpmovmskb	edi, ymm1
	test	edi, edi
	jne	.LBB0_8
# %bb.4:                                #   in Loop: Header=BB0_5 Depth=1
	add	rdx, 32
	cmp	rcx, rdx
	jne	.LBB0_5
.LBB0_6:
	xor	eax, eax
	cmp	rcx, rsi
	je	.LBB0_8
.LBB0_7:
	vpxor	xmm0, xmm0, xmm0
	vpcmpeqb	ymm0, ymm0, ymmword ptr [rcx]
	vpmovmskb	edx, ymm0
	sub	esi, ecx
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
.Lfunc_end0:
	.size	_Z10any_zeroesPKcS0_, .Lfunc_end0-_Z10any_zeroesPKcS0_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
