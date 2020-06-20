	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z19transform_unalignedPsS_ # -- Begin function _Z19transform_unalignedPsS_
	.p2align	4, 0x90
	.type	_Z19transform_unalignedPsS_,@function
_Z19transform_unalignedPsS_:            # @_Z19transform_unalignedPsS_
.L_Z19transform_unalignedPsS_$local:
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	and	rsp, -32
	sub	rsp, 64
	mov	r8, rsi
	mov	rax, rsi
	sub	rax, rdi
	cmp	rax, 32
	jge	.LBB0_1
.LBB0_12:
	cmp	rdi, r8
	je	.LBB0_17
# %bb.13:
	lea	rax, [rdi + 4096]
	and	rax, -4096
	sub	rax, rdi
	cmp	rax, 31
	jg	.LBB0_15
# %bb.14:
	lea	rax, [r8 - 32]
	mov	rcx, rdi
	sub	rcx, rax
	vmovdqu	ymm0, ymmword ptr [r8 - 32]
	vpaddw	ymm0, ymm0, ymm0
	vmovdqa	ymmword ptr [rsp], ymm0
	lea	rsi, [rsp + rcx]
	mov	edx, 32
	sub	rdx, rcx
	jmp	.LBB0_16
.LBB0_1:
	mov	rcx, rdi
	jmp	.LBB0_2
	.p2align	4, 0x90
.LBB0_10:                               #   in Loop: Header=BB0_2 Depth=1
	mov	rdx, r8
	sub	rdx, rdi
.LBB0_11:                               #   in Loop: Header=BB0_2 Depth=1
	mov	rcx, rdi
	cmp	rdx, 32
	jl	.LBB0_12
.LBB0_2:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_9 Depth 2
	vmovdqu	ymm0, ymmword ptr [rcx]
	vpaddw	ymm0, ymm0, ymm0
	vmovdqu	ymmword ptr [rcx], ymm0
	lea	rdi, [rcx + 32]
	mov	rax, r8
	sub	rax, rdi
	cmp	rax, 32
	jl	.LBB0_12
# %bb.3:                                #   in Loop: Header=BB0_2 Depth=1
	vmovdqu	ymm0, ymmword ptr [rcx + 32]
	vpaddw	ymm0, ymm0, ymm0
	vmovdqu	ymmword ptr [rcx + 32], ymm0
	lea	rdi, [rcx + 64]
	mov	rax, r8
	sub	rax, rdi
	cmp	rax, 32
	jl	.LBB0_12
# %bb.4:                                #   in Loop: Header=BB0_2 Depth=1
	vmovdqu	ymm0, ymmword ptr [rcx + 64]
	vpaddw	ymm0, ymm0, ymm0
	vmovdqu	ymmword ptr [rcx + 64], ymm0
	lea	rdi, [rcx + 96]
	mov	rax, r8
	sub	rax, rdi
	cmp	rax, 32
	jl	.LBB0_12
# %bb.5:                                #   in Loop: Header=BB0_2 Depth=1
	vmovdqu	ymm0, ymmword ptr [rcx + 96]
	vpaddw	ymm0, ymm0, ymm0
	vmovdqu	ymmword ptr [rcx + 96], ymm0
	lea	rdi, [rcx + 128]
	mov	rdx, r8
	sub	rdx, rdi
	mov	rsi, rdx
	sar	rsi
	lea	rax, [rsi + 63]
	cmp	rax, 127
	jb	.LBB0_11
# %bb.6:                                #   in Loop: Header=BB0_2 Depth=1
	test	rsi, rsi
	cmovns	rax, rsi
	sar	rax, 6
	test	al, 1
	je	.LBB0_8
# %bb.7:                                #   in Loop: Header=BB0_2 Depth=1
	vmovdqu	ymm0, ymmword ptr [rcx + 128]
	vmovdqu	ymm1, ymmword ptr [rcx + 160]
	vmovdqu	ymm2, ymmword ptr [rcx + 192]
	vmovdqu	ymm3, ymmword ptr [rcx + 224]
	vpaddw	ymm0, ymm0, ymm0
	vpaddw	ymm1, ymm1, ymm1
	vpaddw	ymm2, ymm2, ymm2
	vpaddw	ymm3, ymm3, ymm3
	vmovdqu	ymmword ptr [rcx + 128], ymm0
	vmovdqu	ymmword ptr [rcx + 160], ymm1
	vmovdqu	ymmword ptr [rcx + 192], ymm2
	vmovdqu	ymmword ptr [rcx + 224], ymm3
	add	rcx, 256
	dec	rax
	mov	rdi, rcx
.LBB0_8:                                #   in Loop: Header=BB0_2 Depth=1
	and	rdx, -128
	cmp	rdx, 128
	je	.LBB0_10
	.p2align	4, 0x90
.LBB0_9:                                #   Parent Loop BB0_2 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovdqu	ymm0, ymmword ptr [rdi]
	vmovdqu	ymm1, ymmword ptr [rdi + 32]
	vmovdqu	ymm2, ymmword ptr [rdi + 64]
	vmovdqu	ymm3, ymmword ptr [rdi + 96]
	vpaddw	ymm0, ymm0, ymm0
	vpaddw	ymm1, ymm1, ymm1
	vpaddw	ymm2, ymm2, ymm2
	vpaddw	ymm3, ymm3, ymm3
	vmovdqu	ymmword ptr [rdi], ymm0
	vmovdqu	ymmword ptr [rdi + 32], ymm1
	vmovdqu	ymmword ptr [rdi + 64], ymm2
	vmovdqu	ymmword ptr [rdi + 96], ymm3
	vmovdqu	ymm0, ymmword ptr [rdi + 128]
	vmovdqu	ymm1, ymmword ptr [rdi + 160]
	vmovdqu	ymm2, ymmword ptr [rdi + 192]
	vmovdqu	ymm3, ymmword ptr [rdi + 224]
	vpaddw	ymm0, ymm0, ymm0
	vpaddw	ymm1, ymm1, ymm1
	vpaddw	ymm2, ymm2, ymm2
	vpaddw	ymm3, ymm3, ymm3
	vmovdqu	ymmword ptr [rdi + 128], ymm0
	vmovdqu	ymmword ptr [rdi + 160], ymm1
	vmovdqu	ymmword ptr [rdi + 192], ymm2
	vmovdqu	ymmword ptr [rdi + 224], ymm3
	add	rdi, 256
	add	rax, -2
	jne	.LBB0_9
	jmp	.LBB0_10
.LBB0_15:
	vmovdqu	ymm0, ymmword ptr [rdi]
	vpaddw	ymm0, ymm0, ymm0
	vmovdqa	ymmword ptr [rsp], ymm0
	sub	r8, rdi
	mov	rsi, rsp
	mov	rdx, r8
.LBB0_16:
	vzeroupper
	call	memcpy
.LBB0_17:
	mov	rsp, rbp
	pop	rbp
	.cfi_def_cfa rsp, 8
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z19transform_unalignedPsS_, .Lfunc_end0-_Z19transform_unalignedPsS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
