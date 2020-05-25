	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.globl	_Z10find_zeroePKcS0_    # -- Begin function _Z10find_zeroePKcS0_
	.p2align	4, 0x90
	.type	_Z10find_zeroePKcS0_,@function
_Z10find_zeroePKcS0_:                   # @_Z10find_zeroePKcS0_
.L_Z10find_zeroePKcS0_$local:
	.cfi_startproc
# %bb.0:
	mov	rax, rsi
	mov	rcx, rdi
	and	rcx, -32
	mov	rdx, rsi
	and	rdx, -32
	and	edi, 31
	cmp	rcx, rdx
	je	.LBB0_22
# %bb.1:
	vpxor	xmm0, xmm0, xmm0
	vpcmpeqb	ymm0, ymm0, ymmword ptr [rcx]
	vpmovmskb	esi, ymm0
	shrx	esi, esi, edi
	shlx	esi, esi, edi
	test	esi, esi
	je	.LBB0_3
.LBB0_2:
	tzcnt	eax, esi
	add	rcx, rax
	mov	rax, rcx
	vzeroupper
	ret
.LBB0_3:
	add	rcx, 32
	cmp	rcx, rdx
	je	.LBB0_20
# %bb.4:
	vpxor	xmm0, xmm0, xmm0
	jmp	.LBB0_5
	.p2align	4, 0x90
.LBB0_19:                               #   in Loop: Header=BB0_5 Depth=1
	cmp	rcx, rdx
	je	.LBB0_20
.LBB0_5:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_15 Depth 2
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rcx]
	vpmovmskb	esi, ymm1
	test	esi, esi
	jne	.LBB0_2
# %bb.6:                                #   in Loop: Header=BB0_5 Depth=1
	lea	rsi, [rcx + 32]
	cmp	rsi, rdx
	je	.LBB0_20
# %bb.7:                                #   in Loop: Header=BB0_5 Depth=1
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rsi]
	vpmovmskb	edi, ymm1
	test	edi, edi
	jne	.LBB0_8
# %bb.9:                                #   in Loop: Header=BB0_5 Depth=1
	lea	rsi, [rcx + 64]
	cmp	rsi, rdx
	je	.LBB0_20
# %bb.10:                               #   in Loop: Header=BB0_5 Depth=1
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rsi]
	vpmovmskb	edi, ymm1
	test	edi, edi
	jne	.LBB0_8
# %bb.11:                               #   in Loop: Header=BB0_5 Depth=1
	lea	rsi, [rcx + 96]
	cmp	rsi, rdx
	je	.LBB0_20
# %bb.12:                               #   in Loop: Header=BB0_5 Depth=1
	vpcmpeqb	ymm1, ymm0, ymmword ptr [rsi]
	vpmovmskb	edi, ymm1
	test	edi, edi
	jne	.LBB0_8
# %bb.13:                               #   in Loop: Header=BB0_5 Depth=1
	sub	rcx, -128
	mov	rdi, rdx
	sub	rdi, rcx
	lea	r8, [rdi + 127]
	cmp	r8, 255
	jb	.LBB0_19
# %bb.14:                               #   in Loop: Header=BB0_5 Depth=1
	test	rdi, rdi
	cmovns	r8, rdi
	mov	rdi, r8
	sar	rdi, 7
	and	r8, -128
	add	r8, rcx
	.p2align	4, 0x90
.LBB0_15:                               #   Parent Loop BB0_5 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovdqa	ymm4, ymmword ptr [rcx]
	vmovdqa	ymm3, ymmword ptr [rcx + 32]
	vmovdqa	ymm2, ymmword ptr [rcx + 64]
	vmovdqa	ymm1, ymmword ptr [rcx + 96]
	vpcmpeqb	ymm5, ymm4, ymm0
	vpcmpeqb	ymm6, ymm3, ymm0
	vpor	ymm5, ymm6, ymm5
	vpcmpeqb	ymm6, ymm2, ymm0
	vpcmpeqb	ymm7, ymm1, ymm0
	vpor	ymm6, ymm6, ymm7
	vpor	ymm5, ymm5, ymm6
	vpmovmskb	esi, ymm5
	test	esi, esi
	jne	.LBB0_16
# %bb.17:                               #   in Loop: Header=BB0_15 Depth=2
	sub	rcx, -128
	dec	rdi
	jne	.LBB0_15
# %bb.18:                               #   in Loop: Header=BB0_5 Depth=1
	mov	rcx, r8
	jmp	.LBB0_19
.LBB0_20:
	cmp	rdx, rax
	je	.LBB0_23
# %bb.21:
	xor	edi, edi
.LBB0_22:
	vpxor	xmm0, xmm0, xmm0
	vpcmpeqb	ymm0, ymm0, ymmword ptr [rdx]
	vpmovmskb	r8d, ymm0
	mov	esi, eax
	sub	esi, edx
	mov	rcx, -1
	shlx	rcx, rcx, rsi
	not	ecx
	shrx	ecx, ecx, edi
	shlx	ecx, ecx, edi
	and	ecx, r8d
	tzcnt	esi, ecx
	add	rsi, rdx
	test	ecx, ecx
	cmovne	rax, rsi
.LBB0_23:
	vzeroupper
	ret
.LBB0_16:
	vpxor	xmm0, xmm0, xmm0
	vpcmpeqb	ymm4, ymm4, ymm0
	vpmovmskb	r8d, ymm4
	vpcmpeqb	ymm3, ymm3, ymm0
	vpmovmskb	edx, ymm3
	vpcmpeqb	ymm2, ymm2, ymm0
	vpmovmskb	esi, ymm2
	vpcmpeqb	ymm0, ymm1, ymm0
	vpmovmskb	edi, ymm0
	xor	eax, eax
	test	esi, esi
	sete	al
	cmovne	edi, esi
	shl	eax, 5
	or	eax, 64
	test	edx, edx
	mov	esi, 32
	cmove	esi, eax
	cmovne	edi, edx
	xor	eax, eax
	test	r8d, r8d
	cmove	eax, esi
	cmovne	edi, r8d
	tzcnt	edx, edi
	add	edx, eax
	add	rcx, rdx
	mov	rax, rcx
	vzeroupper
	ret
.LBB0_8:
	tzcnt	eax, edi
	add	rsi, rax
	mov	rax, rsi
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z10find_zeroePKcS0_, .Lfunc_end0-_Z10find_zeroePKcS0_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
