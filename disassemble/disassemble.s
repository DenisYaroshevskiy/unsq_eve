	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2               # -- Begin function _Z4testN3eve4wideIiNS_5fixedILl8EEENS_4avx_EEES4_
.LCPI0_0:
	.long	7                       # 0x7
	.text
	.globl	_Z4testN3eve4wideIiNS_5fixedILl8EEENS_4avx_EEES4_
	.p2align	4, 0x90
	.type	_Z4testN3eve4wideIiNS_5fixedILl8EEENS_4avx_EEES4_,@function
_Z4testN3eve4wideIiNS_5fixedILl8EEENS_4avx_EEES4_: # @_Z4testN3eve4wideIiNS_5fixedILl8EEENS_4avx_EEES4_
.L_Z4testN3eve4wideIiNS_5fixedILl8EEENS_4avx_EEES4_$local:
	.cfi_startproc
# %bb.0:
	mov	rax, rdi
	vperm2i128	ymm2, ymm0, ymm0, 40 # ymm2 = zero,zero,ymm0[0,1]
	vpalignr	ymm2, ymm0, ymm2, 12 # ymm2 = ymm2[12,13,14,15],ymm0[0,1,2,3,4,5,6,7,8,9,10,11],ymm2[28,29,30,31],ymm0[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddd	ymm0, ymm2, ymm0
	vperm2i128	ymm2, ymm0, ymm0, 40 # ymm2 = zero,zero,ymm0[0,1]
	vpalignr	ymm2, ymm0, ymm2, 8 # ymm2 = ymm2[8,9,10,11,12,13,14,15],ymm0[0,1,2,3,4,5,6,7],ymm2[24,25,26,27,28,29,30,31],ymm0[16,17,18,19,20,21,22,23]
	vpaddd	ymm0, ymm0, ymm2
	vperm2i128	ymm2, ymm0, ymm0, 40 # ymm2 = zero,zero,ymm0[0,1]
	vpaddd	ymm0, ymm0, ymm2
	vperm2i128	ymm2, ymm1, ymm1, 40 # ymm2 = zero,zero,ymm1[0,1]
	vpalignr	ymm2, ymm1, ymm2, 12 # ymm2 = ymm2[12,13,14,15],ymm1[0,1,2,3,4,5,6,7,8,9,10,11],ymm2[28,29,30,31],ymm1[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddd	ymm1, ymm2, ymm1
	vperm2i128	ymm2, ymm1, ymm1, 40 # ymm2 = zero,zero,ymm1[0,1]
	vpalignr	ymm2, ymm1, ymm2, 8 # ymm2 = ymm2[8,9,10,11,12,13,14,15],ymm1[0,1,2,3,4,5,6,7],ymm2[24,25,26,27,28,29,30,31],ymm1[16,17,18,19,20,21,22,23]
	vpaddd	ymm1, ymm1, ymm2
	vperm2i128	ymm2, ymm1, ymm1, 40 # ymm2 = zero,zero,ymm1[0,1]
	vpaddd	ymm1, ymm1, ymm2
	vpbroadcastd	ymm2, dword ptr [rip + .LCPI0_0] # ymm2 = [7,7,7,7,7,7,7,7]
	vpermd	ymm2, ymm2, ymm0
	vpaddd	ymm1, ymm2, ymm1
	vmovdqa	ymmword ptr [rdi], ymm0
	vmovdqa	ymmword ptr [rdi + 32], ymm1
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z4testN3eve4wideIiNS_5fixedILl8EEENS_4avx_EEES4_, .Lfunc_end0-_Z4testN3eve4wideIiNS_5fixedILl8EEENS_4avx_EEES4_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
