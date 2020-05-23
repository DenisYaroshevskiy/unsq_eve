	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z13eve_extra_anyRKN3eve7logicalINS_4wideIcNS_5fixedILl128EEENS_11aggregated_EEEEE # -- Begin function _Z13eve_extra_anyRKN3eve7logicalINS_4wideIcNS_5fixedILl128EEENS_11aggregated_EEEEE
	.p2align	4, 0x90
	.type	_Z13eve_extra_anyRKN3eve7logicalINS_4wideIcNS_5fixedILl128EEENS_11aggregated_EEEEE,@function
_Z13eve_extra_anyRKN3eve7logicalINS_4wideIcNS_5fixedILl128EEENS_11aggregated_EEEEE: # @_Z13eve_extra_anyRKN3eve7logicalINS_4wideIcNS_5fixedILl128EEENS_11aggregated_EEEEE
.L_Z13eve_extra_anyRKN3eve7logicalINS_4wideIcNS_5fixedILl128EEENS_11aggregated_EEEEE$local:
	.cfi_startproc
# %bb.0:
	vmovdqa	ymm0, ymmword ptr [rdi + 32]
	vpor	ymm0, ymm0, ymmword ptr [rdi]
	vpor	ymm0, ymm0, ymmword ptr [rdi + 64]
	vpor	ymm0, ymm0, ymmword ptr [rdi + 96]
	vpmovmskb	eax, ymm0
	test	eax, eax
	setne	al
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z13eve_extra_anyRKN3eve7logicalINS_4wideIcNS_5fixedILl128EEENS_11aggregated_EEEEE, .Lfunc_end0-_Z13eve_extra_anyRKN3eve7logicalINS_4wideIcNS_5fixedILl128EEENS_11aggregated_EEEEE
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
