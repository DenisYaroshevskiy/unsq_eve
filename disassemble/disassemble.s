	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z10any_zeroesPKiS0_            # -- Begin function _Z10any_zeroesPKiS0_
	.p2align	4, 0x90
	.type	_Z10any_zeroesPKiS0_,@function
_Z10any_zeroesPKiS0_:                   # @_Z10any_zeroesPKiS0_
	.cfi_startproc
# %bb.0:
	and	rdi, -4
	mov	r8, rsi
	and	r8, -4
	cmp	rdi, r8
	je	.LBB0_18
# %bb.1:
	vpxor	xmm0, xmm0, xmm0
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	eax, dword ptr [rdi]
	mov	dword ptr [rsp - 24], eax
	vpcmpeqd	xmm0, xmm0, xmmword ptr [rsp - 24]
	vmovmskps	ecx, xmm0
	mov	al, 1
	test	cl, 1
	jne	.LBB0_19
# %bb.2:
	add	rdi, 4
	cmp	rdi, r8
	je	.LBB0_16
# %bb.3:
	vpxor	xmm0, xmm0, xmm0
	jmp	.LBB0_4
	.p2align	4, 0x90
.LBB0_15:                               #   in Loop: Header=BB0_4 Depth=1
	cmp	rdi, r8
	je	.LBB0_16
.LBB0_4:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_13 Depth 2
	mov	ecx, dword ptr [rdi]
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	dword ptr [rsp - 24], ecx
	vpcmpeqd	xmm1, xmm0, xmmword ptr [rsp - 24]
	vmovmskps	ecx, xmm1
	test	cl, 1
	jne	.LBB0_19
# %bb.5:                                #   in Loop: Header=BB0_4 Depth=1
	lea	rcx, [rdi + 4]
	cmp	rcx, r8
	je	.LBB0_16
# %bb.6:                                #   in Loop: Header=BB0_4 Depth=1
	mov	ecx, dword ptr [rcx]
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	dword ptr [rsp - 24], ecx
	vpcmpeqd	xmm1, xmm0, xmmword ptr [rsp - 24]
	vmovmskps	ecx, xmm1
	test	cl, 1
	jne	.LBB0_19
# %bb.7:                                #   in Loop: Header=BB0_4 Depth=1
	lea	rcx, [rdi + 8]
	cmp	rcx, r8
	je	.LBB0_16
# %bb.8:                                #   in Loop: Header=BB0_4 Depth=1
	mov	ecx, dword ptr [rcx]
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	dword ptr [rsp - 24], ecx
	vpcmpeqd	xmm1, xmm0, xmmword ptr [rsp - 24]
	vmovmskps	ecx, xmm1
	test	cl, 1
	jne	.LBB0_19
# %bb.9:                                #   in Loop: Header=BB0_4 Depth=1
	lea	rcx, [rdi + 12]
	cmp	rcx, r8
	je	.LBB0_16
# %bb.10:                               #   in Loop: Header=BB0_4 Depth=1
	mov	ecx, dword ptr [rcx]
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	dword ptr [rsp - 24], ecx
	vpcmpeqd	xmm1, xmm0, xmmword ptr [rsp - 24]
	vmovmskps	ecx, xmm1
	test	cl, 1
	jne	.LBB0_19
# %bb.11:                               #   in Loop: Header=BB0_4 Depth=1
	add	rdi, 16
	mov	rcx, r8
	sub	rcx, rdi
	sar	rcx, 2
	lea	rdx, [rcx + 3]
	cmp	rdx, 7
	jb	.LBB0_15
# %bb.12:                               #   in Loop: Header=BB0_4 Depth=1
	test	rcx, rcx
	cmovns	rdx, rcx
	sar	rdx, 2
	.p2align	4, 0x90
.LBB0_13:                               #   Parent Loop BB0_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	mov	ecx, dword ptr [rdi]
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	dword ptr [rsp - 24], ecx
	vpcmpeqd	xmm1, xmm0, xmmword ptr [rsp - 24]
	mov	ecx, dword ptr [rdi + 4]
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	dword ptr [rsp - 24], ecx
	vpcmpeqd	xmm2, xmm0, xmmword ptr [rsp - 24]
	vpunpcklqdq	xmm1, xmm1, xmm2        # xmm1 = xmm1[0],xmm2[0]
	mov	ecx, dword ptr [rdi + 8]
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	dword ptr [rsp - 24], ecx
	vpcmpeqd	xmm2, xmm0, xmmword ptr [rsp - 24]
	mov	ecx, dword ptr [rdi + 12]
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	dword ptr [rsp - 24], ecx
	vpcmpeqd	xmm3, xmm0, xmmword ptr [rsp - 24]
	vpunpckldq	xmm2, xmm2, xmm3        # xmm2 = xmm2[0],xmm3[0],xmm2[1],xmm3[1]
	vshufps	xmm1, xmm1, xmm2, 72            # xmm1 = xmm1[0,2],xmm2[0,1]
	vmovmskps	ecx, xmm1
	test	cl, cl
	jne	.LBB0_19
# %bb.14:                               #   in Loop: Header=BB0_13 Depth=2
	add	rdi, 16
	dec	rdx
	jne	.LBB0_13
	jmp	.LBB0_15
.LBB0_16:
	cmp	r8, rsi
	je	.LBB0_17
.LBB0_18:
	mov	eax, r8d
	sub	eax, esi
	add	eax, 4
	shr	eax, 2
	vpxor	xmm0, xmm0, xmm0
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	ecx, dword ptr [r8]
	mov	dword ptr [rsp - 24], ecx
	vpcmpeqd	xmm0, xmm0, xmmword ptr [rsp - 24]
	vmovmskps	ecx, xmm0
	mov	dl, 1
	sub	dl, al
	mov	rax, -1
	shlx	rax, rax, rdx
	not	al
	and	al, cl
	and	al, 1
.LBB0_19:
                                        # kill: def $al killed $al killed $rax
	ret
.LBB0_17:
	xor	eax, eax
                                        # kill: def $al killed $al killed $rax
	ret
.Lfunc_end0:
	.size	_Z10any_zeroesPKiS0_, .Lfunc_end0-_Z10any_zeroesPKiS0_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 12.0.0 (https://github.com/llvm/llvm-project.git 02bc320545deb0212a43acae24fcf2383755d383)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
