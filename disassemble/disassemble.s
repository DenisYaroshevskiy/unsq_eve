	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z11call_strlenPKc              # -- Begin function _Z11call_strlenPKc
	.p2align	4, 0x90
	.type	_Z11call_strlenPKc,@function
_Z11call_strlenPKc:                     # @_Z11call_strlenPKc
	.cfi_startproc
# %bb.0:
	mov	rcx, rdi
	and	rcx, -32
	vpxor	xmm0, xmm0, xmm0
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rcx]
	vpmovmskb	eax, ymm1
	shrx	eax, eax, edi
	shlx	eax, eax, edi
	test	eax, eax
	jne	.LBB0_3
	.p2align	4, 0x90
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rcx + 32]
	add	rcx, 32
	vpmovmskb	eax, ymm1
	test	eax, eax
	je	.LBB0_1
.LBB0_3:
	tzcnt	eax, eax
	mov	eax, eax
	add	rax, rcx
	sub	rax, rdi
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z11call_strlenPKc, .Lfunc_end0-_Z11call_strlenPKc
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 12.0.0 (https://github.com/llvm/llvm-project.git 02bc320545deb0212a43acae24fcf2383755d383)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
