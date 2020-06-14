	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z9transformPsS_        # -- Begin function _Z9transformPsS_
	.p2align	4, 0x90
	.type	_Z9transformPsS_,@function
_Z9transformPsS_:                       # @_Z9transformPsS_
.L_Z9transformPsS_$local:
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	and	rsp, -32
	sub	rsp, 64
	mov	rdx, rsi
	sub	rdx, rdi
	cmp	rdx, 31
	jg	.LBB0_4
# %bb.1:
	lea	rax, [rdi + 4096]
	and	rax, -4096
	sub	rax, rdi
	cmp	rax, 31
	jg	.LBB0_3
# %bb.2:
	lea	rax, [rsi - 32]
	mov	rcx, rdi
	sub	rcx, rax
	vmovdqu	ymm0, ymmword ptr [rsi - 32]
	vpaddw	ymm0, ymm0, ymm0
	vmovdqa	ymmword ptr [rsp], ymm0
	lea	rsi, [rsp + rcx]
	mov	edx, 32
	sub	rdx, rcx
	vzeroupper
	call	memcpy
	mov	rsp, rbp
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.LBB0_4:
	.cfi_def_cfa rbp, 16
	vmovdqu	ymm0, ymmword ptr [rdi]
	cmp	rdx, 65
	jl	.LBB0_20
# %bb.5:
	lea	rcx, [rdi + 32]
	and	rcx, -32
	mov	r8, rsi
	and	r8, -32
	add	r8, -32
	vmovdqa	ymm1, ymmword ptr [rcx]
	vpaddw	ymm0, ymm0, ymm0
	vmovdqu	ymmword ptr [rdi], ymm0
	cmp	r8, rcx
	jne	.LBB0_7
# %bb.6:
	vmovdqa	ymm0, ymm1
	mov	rdi, rcx
	jmp	.LBB0_20
	.p2align	4, 0x90
.LBB0_16:                               #   in Loop: Header=BB0_7 Depth=1
	mov	rcx, rdi
.LBB0_17:                               #   in Loop: Header=BB0_7 Depth=1
	vmovdqa	ymm1, ymmword ptr [rcx]
	cmp	rcx, r8
	je	.LBB0_18
.LBB0_7:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_15 Depth 2
	vpaddw	ymm0, ymm1, ymm1
	vmovdqa	ymmword ptr [rcx], ymm0
	lea	rax, [rcx + 32]
	vmovdqa	ymm0, ymmword ptr [rcx + 32]
	cmp	rax, r8
	je	.LBB0_19
# %bb.8:                                #   in Loop: Header=BB0_7 Depth=1
	vpaddw	ymm0, ymm0, ymm0
	vmovdqa	ymmword ptr [rcx + 32], ymm0
	lea	rax, [rcx + 64]
	vmovdqa	ymm0, ymmword ptr [rcx + 64]
	cmp	rax, r8
	je	.LBB0_19
# %bb.9:                                #   in Loop: Header=BB0_7 Depth=1
	vpaddw	ymm0, ymm0, ymm0
	vmovdqa	ymmword ptr [rcx + 64], ymm0
	lea	rax, [rcx + 96]
	vmovdqa	ymm0, ymmword ptr [rcx + 96]
	cmp	rax, r8
	je	.LBB0_19
# %bb.10:                               #   in Loop: Header=BB0_7 Depth=1
	vpaddw	ymm0, ymm0, ymm0
	vmovdqa	ymmword ptr [rcx + 96], ymm0
	lea	rdi, [rcx + 128]
	mov	r9, r8
	sub	r9, rdi
	mov	rax, r9
	sar	rax
	lea	rdx, [rax + 63]
	cmp	rdx, 127
	jb	.LBB0_16
# %bb.11:                               #   in Loop: Header=BB0_7 Depth=1
	test	rax, rax
	cmovns	rdx, rax
	sar	rdx, 6
	test	dl, 1
	jne	.LBB0_13
# %bb.12:                               #   in Loop: Header=BB0_7 Depth=1
                                        # implicit-def: $rcx
	and	r9, -128
	cmp	r9, 128
	jne	.LBB0_15
	jmp	.LBB0_17
	.p2align	4, 0x90
.LBB0_13:                               #   in Loop: Header=BB0_7 Depth=1
	vmovdqa	ymm0, ymmword ptr [rcx + 128]
	vmovdqa	ymm1, ymmword ptr [rcx + 160]
	vmovdqa	ymm2, ymmword ptr [rcx + 192]
	vmovdqa	ymm3, ymmword ptr [rcx + 224]
	vpaddw	ymm0, ymm0, ymm0
	vpaddw	ymm1, ymm1, ymm1
	vpaddw	ymm2, ymm2, ymm2
	vpaddw	ymm3, ymm3, ymm3
	vmovdqa	ymmword ptr [rcx + 128], ymm0
	vmovdqa	ymmword ptr [rcx + 160], ymm1
	vmovdqa	ymmword ptr [rcx + 192], ymm2
	vmovdqa	ymmword ptr [rcx + 224], ymm3
	add	rcx, 256
	dec	rdx
	mov	rdi, rcx
	and	r9, -128
	cmp	r9, 128
	je	.LBB0_17
	.p2align	4, 0x90
.LBB0_15:                               #   Parent Loop BB0_7 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovdqa	ymm0, ymmword ptr [rdi]
	vmovdqa	ymm1, ymmword ptr [rdi + 32]
	vmovdqa	ymm2, ymmword ptr [rdi + 64]
	vmovdqa	ymm3, ymmword ptr [rdi + 96]
	vpaddw	ymm0, ymm0, ymm0
	vpaddw	ymm1, ymm1, ymm1
	vpaddw	ymm2, ymm2, ymm2
	vpaddw	ymm3, ymm3, ymm3
	vmovdqa	ymmword ptr [rdi], ymm0
	vmovdqa	ymmword ptr [rdi + 32], ymm1
	vmovdqa	ymmword ptr [rdi + 64], ymm2
	vmovdqa	ymmword ptr [rdi + 96], ymm3
	vmovdqa	ymm0, ymmword ptr [rdi + 128]
	vmovdqa	ymm1, ymmword ptr [rdi + 160]
	vmovdqa	ymm2, ymmword ptr [rdi + 192]
	vmovdqa	ymm3, ymmword ptr [rdi + 224]
	vpaddw	ymm0, ymm0, ymm0
	vpaddw	ymm1, ymm1, ymm1
	vpaddw	ymm2, ymm2, ymm2
	vpaddw	ymm3, ymm3, ymm3
	vmovdqa	ymmword ptr [rdi + 128], ymm0
	vmovdqa	ymmword ptr [rdi + 160], ymm1
	vmovdqa	ymmword ptr [rdi + 192], ymm2
	vmovdqa	ymmword ptr [rdi + 224], ymm3
	add	rdi, 256
	add	rdx, -2
	jne	.LBB0_15
	jmp	.LBB0_16
.LBB0_3:
	vmovdqu	ymm0, ymmword ptr [rdi]
	vpaddw	ymm0, ymm0, ymm0
	vmovdqa	ymmword ptr [rsp], ymm0
	mov	rsi, rsp
	vzeroupper
	call	memcpy
	mov	rsp, rbp
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.LBB0_18:
	.cfi_def_cfa rbp, 16
	vmovdqa	ymm0, ymm1
.LBB0_19:
	mov	rdi, r8
.LBB0_20:
	vmovdqu	ymm1, ymmword ptr [rsi - 32]
	vpaddw	ymm0, ymm0, ymm0
	vmovdqu	ymmword ptr [rdi], ymm0
	vpaddw	ymm0, ymm1, ymm1
	vmovdqu	ymmword ptr [rsi - 32], ymm0
	mov	rsp, rbp
	pop	rbp
	.cfi_def_cfa rsp, 8
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z9transformPsS_, .Lfunc_end0-_Z9transformPsS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
