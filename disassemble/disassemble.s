	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z9my_strlenPc          # -- Begin function _Z9my_strlenPc
	.p2align	4, 0x90
	.type	_Z9my_strlenPc,@function
_Z9my_strlenPc:                         # @_Z9my_strlenPc
.L_Z9my_strlenPc$local:
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
	je	.LBB0_1
.LBB0_10:
	tzcnt	eax, eax
	add	rax, rcx
	sub	rax, rdi
	vzeroupper
	ret
.LBB0_1:
	vpcmpeqb	ymm0, ymm0, ymmword ptr [rcx + 32]
	vpmovmskb	eax, ymm0
	test	eax, eax
	je	.LBB0_2
.LBB0_9:
	add	rcx, 32
	tzcnt	eax, eax
	add	rax, rcx
	sub	rax, rdi
	vzeroupper
	ret
.LBB0_2:
	add	rcx, 96
	vpxor	xmm0, xmm0, xmm0
	.p2align	4, 0x90
.LBB0_3:                                # =>This Inner Loop Header: Depth=1
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rcx - 32]
	vpmovmskb	eax, ymm1
	test	eax, eax
	jne	.LBB0_8
# %bb.4:                                #   in Loop: Header=BB0_3 Depth=1
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rcx]
	vpmovmskb	eax, ymm1
	test	eax, eax
	jne	.LBB0_10
# %bb.5:                                #   in Loop: Header=BB0_3 Depth=1
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rcx + 32]
	vpmovmskb	eax, ymm1
	test	eax, eax
	jne	.LBB0_9
# %bb.6:                                #   in Loop: Header=BB0_3 Depth=1
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rcx + 64]
	vpmovmskb	eax, ymm1
	sub	rcx, -128
	test	eax, eax
	je	.LBB0_3
# %bb.7:
	add	rcx, -64
	tzcnt	eax, eax
	add	rax, rcx
	sub	rax, rdi
	vzeroupper
	ret
.LBB0_8:
	add	rcx, -32
	tzcnt	eax, eax
	add	rax, rcx
	sub	rax, rdi
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z9my_strlenPc, .Lfunc_end0-_Z9my_strlenPc
	.cfi_endproc
                                        # -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90         # -- Begin function _GLOBAL__sub_I_disassemble.cc
	.type	_GLOBAL__sub_I_disassemble.cc,@function
_GLOBAL__sub_I_disassemble.cc:          # @_GLOBAL__sub_I_disassemble.cc
	.cfi_startproc
# %bb.0:
	push	rax
	.cfi_def_cfa_offset 16
	mov	edi, offset _ZStL8__ioinit
	call	_ZNSt8ios_base4InitC1Ev
	mov	edi, offset _ZNSt8ios_base4InitD1Ev
	mov	esi, offset _ZStL8__ioinit
	mov	edx, offset __dso_handle
	pop	rax
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit            # TAILCALL
.Lfunc_end1:
	.size	_GLOBAL__sub_I_disassemble.cc, .Lfunc_end1-_GLOBAL__sub_I_disassemble.cc
	.cfi_endproc
                                        # -- End function
	.type	_ZStL8__ioinit,@object  # @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.section	.init_array,"aw",@init_array
	.p2align	3
	.quad	_GLOBAL__sub_I_disassemble.cc
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git 84cbd472e59236bd8ec541bc764ababc6a10a878)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
	.addrsig_sym _GLOBAL__sub_I_disassemble.cc
	.addrsig_sym _ZStL8__ioinit
	.addrsig_sym __dso_handle
