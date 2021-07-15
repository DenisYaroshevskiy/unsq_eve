	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z6find_0PKiS0_                 # -- Begin function _Z6find_0PKiS0_
	.p2align	4, 0x90
	.type	_Z6find_0PKiS0_,@function
_Z6find_0PKiS0_:                        # @_Z6find_0PKiS0_
	.cfi_startproc
# %bb.0:
	mov	rax, rsi
	and	rdi, -4
	mov	rcx, rsi
	and	rcx, -4
	cmp	rdi, rcx
	je	.LBB0_21
# %bb.1:
	vpxor	xmm0, xmm0, xmm0
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	edx, dword ptr [rdi]
	mov	dword ptr [rsp - 24], edx
	vpcmpeqd	xmm0, xmm0, xmmword ptr [rsp - 24]
	vmovmskps	edx, xmm0
	and	dl, 1
	jne	.LBB0_2
# %bb.3:
	add	rdi, 4
	cmp	rdi, rcx
	je	.LBB0_20
# %bb.4:
	vpxor	xmm0, xmm0, xmm0
	jmp	.LBB0_5
	.p2align	4, 0x90
.LBB0_19:                               #   in Loop: Header=BB0_5 Depth=1
	cmp	rdi, rcx
	je	.LBB0_20
.LBB0_5:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_15 Depth 2
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	edx, dword ptr [rdi]
	mov	dword ptr [rsp - 24], edx
	vpcmpeqd	xmm1, xmm0, xmmword ptr [rsp - 24]
	vmovmskps	edx, xmm1
	and	dl, 1
	jne	.LBB0_2
# %bb.6:                                #   in Loop: Header=BB0_5 Depth=1
	lea	rdx, [rdi + 4]
	cmp	rdx, rcx
	je	.LBB0_20
# %bb.7:                                #   in Loop: Header=BB0_5 Depth=1
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	esi, dword ptr [rdx]
	mov	dword ptr [rsp - 24], esi
	vpcmpeqd	xmm1, xmm0, xmmword ptr [rsp - 24]
	vmovmskps	esi, xmm1
	and	sil, 1
	jne	.LBB0_8
# %bb.9:                                #   in Loop: Header=BB0_5 Depth=1
	lea	rdx, [rdi + 8]
	cmp	rdx, rcx
	je	.LBB0_20
# %bb.10:                               #   in Loop: Header=BB0_5 Depth=1
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	esi, dword ptr [rdx]
	mov	dword ptr [rsp - 24], esi
	vpcmpeqd	xmm1, xmm0, xmmword ptr [rsp - 24]
	vmovmskps	esi, xmm1
	and	sil, 1
	jne	.LBB0_8
# %bb.11:                               #   in Loop: Header=BB0_5 Depth=1
	lea	rdx, [rdi + 12]
	cmp	rdx, rcx
	je	.LBB0_20
# %bb.12:                               #   in Loop: Header=BB0_5 Depth=1
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	esi, dword ptr [rdx]
	mov	dword ptr [rsp - 24], esi
	vpcmpeqd	xmm1, xmm0, xmmword ptr [rsp - 24]
	vmovmskps	esi, xmm1
	and	sil, 1
	jne	.LBB0_8
# %bb.13:                               #   in Loop: Header=BB0_5 Depth=1
	add	rdi, 16
	mov	rsi, rcx
	sub	rsi, rdi
	sar	rsi, 2
	lea	rdx, [rsi + 3]
	cmp	rdx, 7
	jb	.LBB0_19
# %bb.14:                               #   in Loop: Header=BB0_5 Depth=1
	test	rsi, rsi
	cmovns	rdx, rsi
	sar	rdx, 2
	.p2align	4, 0x90
.LBB0_15:                               #   Parent Loop BB0_5 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	esi, dword ptr [rdi]
	mov	dword ptr [rsp - 24], esi
	vpcmpeqd	xmm1, xmm0, xmmword ptr [rsp - 24]
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	esi, dword ptr [rdi + 4]
	mov	dword ptr [rsp - 24], esi
	vpcmpeqd	xmm2, xmm0, xmmword ptr [rsp - 24]
	vpunpcklqdq	xmm1, xmm1, xmm2        # xmm1 = xmm1[0],xmm2[0]
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	esi, dword ptr [rdi + 8]
	mov	dword ptr [rsp - 24], esi
	vpcmpeqd	xmm2, xmm0, xmmword ptr [rsp - 24]
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	esi, dword ptr [rdi + 12]
	mov	dword ptr [rsp - 24], esi
	vpcmpeqd	xmm3, xmm0, xmmword ptr [rsp - 24]
	vpunpckldq	xmm2, xmm2, xmm3        # xmm2 = xmm2[0],xmm3[0],xmm2[1],xmm3[1]
	vshufps	xmm1, xmm1, xmm2, 72            # xmm1 = xmm1[0,2],xmm2[0,1]
	vmovmskps	esi, xmm1
	test	sil, sil
	jne	.LBB0_16
# %bb.18:                               #   in Loop: Header=BB0_15 Depth=2
	add	rdi, 16
	dec	rdx
	jne	.LBB0_15
	jmp	.LBB0_19
.LBB0_2:
	movzx	eax, dl
	and	eax, 15
	tzcnt	eax, eax
	lea	rax, [rdi + 4*rax]
	ret
.LBB0_20:
	cmp	rcx, rax
	je	.LBB0_22
.LBB0_21:
	mov	edx, ecx
	sub	edx, eax
	add	edx, 4
	shr	edx, 2
	vpxor	xmm0, xmm0, xmm0
	vmovdqa	xmmword ptr [rsp - 24], xmm0
	mov	esi, dword ptr [rcx]
	mov	dword ptr [rsp - 24], esi
	vpcmpeqd	xmm0, xmm0, xmmword ptr [rsp - 24]
	vmovmskps	esi, xmm0
	mov	dil, 1
	sub	dil, dl
	bzhi	edx, esi, edi
	and	edx, 1
	tzcnt	esi, edx
	test	dx, dx
	lea	rcx, [rcx + 4*rsi]
	cmovne	rax, rcx
.LBB0_22:
	ret
.LBB0_16:
	movzx	eax, sil
	tzcnt	eax, eax
	lea	rax, [rdi + 4*rax]
	ret
.LBB0_8:
	movzx	eax, sil
	and	eax, 15
	tzcnt	eax, eax
	lea	rax, [rdx + 4*rax]
	ret
.Lfunc_end0:
	.size	_Z6find_0PKiS0_, .Lfunc_end0-_Z6find_0PKiS0_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 12.0.0 (https://github.com/llvm/llvm-project.git 02bc320545deb0212a43acae24fcf2383755d383)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
