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
	mov	r9, rsi
	and	r9, -32
	and	eax, 31
	cmp	rdx, r9
	je	.LBB0_18
# %bb.1:
	vpxor	xmm0, xmm0, xmm0
	vpcmpeqb	ymm0, ymm0, ymmword ptr [rdx]
	vpmovmskb	edi, ymm0
	shrx	edi, edi, eax
	shlx	edi, edi, eax
	mov	al, 1
	test	edi, edi
	je	.LBB0_2
.LBB0_19:
                                        # kill: def $al killed $al killed $rax
	vzeroupper
	ret
.LBB0_2:
	add	rdx, 32
	cmp	rdx, r9
	je	.LBB0_17
# %bb.3:
	vpxor	xmm0, xmm0, xmm0
	jmp	.LBB0_4
.LBB0_15:                               #   in Loop: Header=BB0_4 Depth=1
	mov	rdx, r8
.LBB0_16:                               #   in Loop: Header=BB0_4 Depth=1
	cmp	rdx, r9
	je	.LBB0_17
.LBB0_4:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_13 Depth 2
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rdx]
	vpmovmskb	edi, ymm1
	test	edi, edi
	jne	.LBB0_19
# %bb.5:                                #   in Loop: Header=BB0_4 Depth=1
	lea	rdi, [rdx + 32]
	cmp	rdi, r9
	je	.LBB0_17
# %bb.6:                                #   in Loop: Header=BB0_4 Depth=1
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rdi]
	vpmovmskb	edi, ymm1
	test	edi, edi
	jne	.LBB0_19
# %bb.7:                                #   in Loop: Header=BB0_4 Depth=1
	lea	rdi, [rdx + 64]
	cmp	rdi, r9
	je	.LBB0_17
# %bb.8:                                #   in Loop: Header=BB0_4 Depth=1
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rdi]
	vpmovmskb	edi, ymm1
	test	edi, edi
	jne	.LBB0_19
# %bb.9:                                #   in Loop: Header=BB0_4 Depth=1
	lea	rdi, [rdx + 96]
	cmp	rdi, r9
	je	.LBB0_17
# %bb.10:                               #   in Loop: Header=BB0_4 Depth=1
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rdi]
	vpmovmskb	edi, ymm1
	test	edi, edi
	jne	.LBB0_19
# %bb.11:                               #   in Loop: Header=BB0_4 Depth=1
	sub	rdx, -128
	mov	rdi, r9
	sub	rdi, rdx
	lea	r8, [rdi + 127]
	cmp	r8, 255
	jb	.LBB0_16
# %bb.12:                               #   in Loop: Header=BB0_4 Depth=1
	test	rdi, rdi
	cmovns	r8, rdi
	mov	rdi, r8
	sar	rdi, 7
	and	r8, -128
	add	r8, rdx
	.p2align	4, 0x90
.LBB0_13:                               #   Parent Loop BB0_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rdx]
	vpcmpeqb	ymm2, ymm0, ymmword ptr [rdx + 32]
	vpor	ymm1, ymm2, ymm1
	vpcmpeqb	ymm2, ymm0, ymmword ptr [rdx + 64]
	vpcmpeqb	ymm3, ymm0, ymmword ptr [rdx + 96]
	vpor	ymm2, ymm2, ymm3
	vpor	ymm1, ymm1, ymm2
	vpmovmskb	ecx, ymm1
	test	ecx, ecx
	jne	.LBB0_19
# %bb.14:                               #   in Loop: Header=BB0_13 Depth=2
	sub	rdx, -128
	dec	rdi
	jne	.LBB0_13
	jmp	.LBB0_15
.LBB0_17:
	xor	eax, eax
	cmp	r9, rsi
	je	.LBB0_19
.LBB0_18:
	vpxor	xmm0, xmm0, xmm0
	vpcmpeqb	ymm0, ymm0, ymmword ptr [r9]
	vpmovmskb	ecx, ymm0
	sub	esi, r9d
	mov	rdx, -1
	shlx	rdx, rdx, rsi
	not	edx
	shrx	edx, edx, eax
	shlx	eax, edx, eax
	test	eax, ecx
	setne	al
                                        # kill: def $al killed $al killed $rax
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z10any_zeroesPKcS0_, .Lfunc_end0-_Z10any_zeroesPKcS0_
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
