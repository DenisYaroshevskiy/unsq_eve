	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z6reduceN3eve4wideIiNS_5fixedILl32EEENS_11aggregated_EEE # -- Begin function _Z6reduceN3eve4wideIiNS_5fixedILl32EEENS_11aggregated_EEE
	.p2align	4, 0x90
	.type	_Z6reduceN3eve4wideIiNS_5fixedILl32EEENS_11aggregated_EEE,@function
_Z6reduceN3eve4wideIiNS_5fixedILl32EEENS_11aggregated_EEE: # @_Z6reduceN3eve4wideIiNS_5fixedILl32EEENS_11aggregated_EEE
.L_Z6reduceN3eve4wideIiNS_5fixedILl32EEENS_11aggregated_EEE$local:
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	and	rsp, -32
	sub	rsp, 32
	mov	rax, rdi
	vmovdqa	ymm0, ymmword ptr [rbp + 48]
	vpaddd	ymm0, ymm0, ymmword ptr [rbp + 16]
	vpaddd	ymm0, ymm0, ymmword ptr [rbp + 80]
	vpaddd	ymm0, ymm0, ymmword ptr [rbp + 112]
	vpermq	ymm1, ymm0, 78          # ymm1 = ymm0[2,3,0,1]
	vpaddd	ymm0, ymm0, ymm1
	vpshufd	ymm1, ymm0, 78          # ymm1 = ymm0[2,3,0,1,6,7,4,5]
	vpaddd	ymm0, ymm0, ymm1
	vpshufd	ymm1, ymm0, 177         # ymm1 = ymm0[1,0,3,2,5,4,7,6]
	vpaddd	ymm0, ymm1, ymm0
	vmovdqa	ymmword ptr [rdi], ymm0
	vmovdqa	ymmword ptr [rdi + 32], ymm0
	vmovdqa	ymmword ptr [rdi + 64], ymm0
	vmovdqa	ymmword ptr [rdi + 96], ymm0
	mov	rsp, rbp
	pop	rbp
	.cfi_def_cfa rsp, 8
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z6reduceN3eve4wideIiNS_5fixedILl32EEENS_11aggregated_EEE, .Lfunc_end0-_Z6reduceN3eve4wideIiNS_5fixedILl32EEENS_11aggregated_EEE
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
