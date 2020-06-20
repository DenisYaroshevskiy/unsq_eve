	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z13std_transformPiS_   # -- Begin function _Z13std_transformPiS_
	.p2align	4, 0x90
	.type	_Z13std_transformPiS_,@function
_Z13std_transformPiS_:                  # @_Z13std_transformPiS_
.L_Z13std_transformPiS_$local:
	.cfi_startproc
# %bb.0:
	cmp	rdi, rsi
	je	.LBB0_11
# %bb.1:
	mov	rax, rsi
	sub	rax, rdi
	add	rax, -4
	cmp	rax, 124
	jb	.LBB0_10
# %bb.2:
	shr	rax, 2
	inc	rax
	mov	r8, rax
	and	r8, -32
	lea	rcx, [r8 - 32]
	mov	r9, rcx
	shr	r9, 5
	inc	r9
	test	rcx, rcx
	je	.LBB0_3
# %bb.4:
	mov	rcx, r9
	and	rcx, -2
	neg	rcx
	xor	edx, edx
	.p2align	4, 0x90
.LBB0_5:                                # =>This Inner Loop Header: Depth=1
	vmovdqu	ymm0, ymmword ptr [rdi + 4*rdx]
	vmovdqu	ymm1, ymmword ptr [rdi + 4*rdx + 32]
	vmovdqu	ymm2, ymmword ptr [rdi + 4*rdx + 64]
	vmovdqu	ymm3, ymmword ptr [rdi + 4*rdx + 96]
	vpaddd	ymm0, ymm0, ymm0
	vpaddd	ymm1, ymm1, ymm1
	vpaddd	ymm2, ymm2, ymm2
	vpaddd	ymm3, ymm3, ymm3
	vmovdqu	ymmword ptr [rdi + 4*rdx], ymm0
	vmovdqu	ymmword ptr [rdi + 4*rdx + 32], ymm1
	vmovdqu	ymmword ptr [rdi + 4*rdx + 64], ymm2
	vmovdqu	ymmword ptr [rdi + 4*rdx + 96], ymm3
	vmovdqu	ymm0, ymmword ptr [rdi + 4*rdx + 128]
	vmovdqu	ymm1, ymmword ptr [rdi + 4*rdx + 160]
	vmovdqu	ymm2, ymmword ptr [rdi + 4*rdx + 192]
	vmovdqu	ymm3, ymmword ptr [rdi + 4*rdx + 224]
	vpaddd	ymm0, ymm0, ymm0
	vpaddd	ymm1, ymm1, ymm1
	vpaddd	ymm2, ymm2, ymm2
	vpaddd	ymm3, ymm3, ymm3
	vmovdqu	ymmword ptr [rdi + 4*rdx + 128], ymm0
	vmovdqu	ymmword ptr [rdi + 4*rdx + 160], ymm1
	vmovdqu	ymmword ptr [rdi + 4*rdx + 192], ymm2
	vmovdqu	ymmword ptr [rdi + 4*rdx + 224], ymm3
	add	rdx, 64
	add	rcx, 2
	jne	.LBB0_5
# %bb.6:
	test	r9b, 1
	je	.LBB0_8
.LBB0_7:
	vmovdqu	ymm0, ymmword ptr [rdi + 4*rdx]
	vmovdqu	ymm1, ymmword ptr [rdi + 4*rdx + 32]
	vmovdqu	ymm2, ymmword ptr [rdi + 4*rdx + 64]
	vmovdqu	ymm3, ymmword ptr [rdi + 4*rdx + 96]
	vpaddd	ymm0, ymm0, ymm0
	vpaddd	ymm1, ymm1, ymm1
	vpaddd	ymm2, ymm2, ymm2
	vpaddd	ymm3, ymm3, ymm3
	vmovdqu	ymmword ptr [rdi + 4*rdx], ymm0
	vmovdqu	ymmword ptr [rdi + 4*rdx + 32], ymm1
	vmovdqu	ymmword ptr [rdi + 4*rdx + 64], ymm2
	vmovdqu	ymmword ptr [rdi + 4*rdx + 96], ymm3
.LBB0_8:
	cmp	rax, r8
	je	.LBB0_11
# %bb.9:
	lea	rdi, [rdi + 4*r8]
	.p2align	4, 0x90
.LBB0_10:                               # =>This Inner Loop Header: Depth=1
	shl	dword ptr [rdi]
	add	rdi, 4
	cmp	rsi, rdi
	jne	.LBB0_10
.LBB0_11:
	vzeroupper
	ret
.LBB0_3:
	xor	edx, edx
	test	r9b, 1
	jne	.LBB0_7
	jmp	.LBB0_8
.Lfunc_end0:
	.size	_Z13std_transformPiS_, .Lfunc_end0-_Z13std_transformPiS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
