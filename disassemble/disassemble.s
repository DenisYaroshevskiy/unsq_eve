	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z10std_reducePiS_      # -- Begin function _Z10std_reducePiS_
	.p2align	4, 0x90
	.type	_Z10std_reducePiS_,@function
_Z10std_reducePiS_:                     # @_Z10std_reducePiS_
.L_Z10std_reducePiS_$local:
	.cfi_startproc
# %bb.0:
	cmp	rdi, rsi
	je	.LBB0_1
# %bb.2:
	mov	r9, rsi
	sub	r9, rdi
	add	r9, -4
	xor	eax, eax
	cmp	r9, 124
	jb	.LBB0_12
# %bb.3:
	shr	r9, 2
	inc	r9
	mov	r8, r9
	and	r8, -32
	lea	rdx, [r8 - 32]
	mov	rax, rdx
	shr	rax, 5
	inc	rax
	mov	ecx, eax
	and	ecx, 3
	cmp	rdx, 96
	jae	.LBB0_5
# %bb.4:
	vpxor	xmm0, xmm0, xmm0
	xor	edx, edx
	vpxor	xmm1, xmm1, xmm1
	vpxor	xmm2, xmm2, xmm2
	vpxor	xmm3, xmm3, xmm3
	jmp	.LBB0_7
.LBB0_1:
	xor	eax, eax
	ret
.LBB0_5:
	and	rax, -4
	neg	rax
	vpxor	xmm0, xmm0, xmm0
	xor	edx, edx
	vpxor	xmm1, xmm1, xmm1
	vpxor	xmm2, xmm2, xmm2
	vpxor	xmm3, xmm3, xmm3
	.p2align	4, 0x90
.LBB0_6:                                # =>This Inner Loop Header: Depth=1
	vpaddd	ymm0, ymm0, ymmword ptr [rdi + 4*rdx]
	vpaddd	ymm1, ymm1, ymmword ptr [rdi + 4*rdx + 32]
	vpaddd	ymm2, ymm2, ymmword ptr [rdi + 4*rdx + 64]
	vpaddd	ymm3, ymm3, ymmword ptr [rdi + 4*rdx + 96]
	vpaddd	ymm0, ymm0, ymmword ptr [rdi + 4*rdx + 128]
	vpaddd	ymm1, ymm1, ymmword ptr [rdi + 4*rdx + 160]
	vpaddd	ymm2, ymm2, ymmword ptr [rdi + 4*rdx + 192]
	vpaddd	ymm3, ymm3, ymmword ptr [rdi + 4*rdx + 224]
	vpaddd	ymm0, ymm0, ymmword ptr [rdi + 4*rdx + 256]
	vpaddd	ymm1, ymm1, ymmword ptr [rdi + 4*rdx + 288]
	vpaddd	ymm2, ymm2, ymmword ptr [rdi + 4*rdx + 320]
	vpaddd	ymm3, ymm3, ymmword ptr [rdi + 4*rdx + 352]
	vpaddd	ymm0, ymm0, ymmword ptr [rdi + 4*rdx + 384]
	vpaddd	ymm1, ymm1, ymmword ptr [rdi + 4*rdx + 416]
	vpaddd	ymm2, ymm2, ymmword ptr [rdi + 4*rdx + 448]
	vpaddd	ymm3, ymm3, ymmword ptr [rdi + 4*rdx + 480]
	sub	rdx, -128
	add	rax, 4
	jne	.LBB0_6
.LBB0_7:
	test	rcx, rcx
	je	.LBB0_10
# %bb.8:
	lea	rax, [rdi + 4*rdx]
	add	rax, 96
	neg	rcx
	.p2align	4, 0x90
.LBB0_9:                                # =>This Inner Loop Header: Depth=1
	vpaddd	ymm0, ymm0, ymmword ptr [rax - 96]
	vpaddd	ymm1, ymm1, ymmword ptr [rax - 64]
	vpaddd	ymm2, ymm2, ymmword ptr [rax - 32]
	vpaddd	ymm3, ymm3, ymmword ptr [rax]
	sub	rax, -128
	inc	rcx
	jne	.LBB0_9
.LBB0_10:
	vpaddd	ymm1, ymm1, ymm3
	vpaddd	ymm0, ymm0, ymm2
	vpaddd	ymm0, ymm0, ymm1
	vextracti128	xmm1, ymm0, 1
	vpaddd	xmm0, xmm0, xmm1
	vpshufd	xmm1, xmm0, 78          # xmm1 = xmm0[2,3,0,1]
	vpaddd	xmm0, xmm0, xmm1
	vpshufd	xmm1, xmm0, 229         # xmm1 = xmm0[1,1,2,3]
	vpaddd	xmm0, xmm0, xmm1
	vmovd	eax, xmm0
	cmp	r9, r8
	je	.LBB0_13
# %bb.11:
	lea	rdi, [rdi + 4*r8]
	.p2align	4, 0x90
.LBB0_12:                               # =>This Inner Loop Header: Depth=1
	add	eax, dword ptr [rdi]
	add	rdi, 4
	cmp	rsi, rdi
	jne	.LBB0_12
.LBB0_13:
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z10std_reducePiS_, .Lfunc_end0-_Z10std_reducePiS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
