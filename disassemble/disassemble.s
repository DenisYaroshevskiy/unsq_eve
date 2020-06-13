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
	sub	rsp, 320
	mov	rdx, rsi
	mov	rsi, rdi
	vxorps	xmm0, xmm0, xmm0
	vmovaps	ymmword ptr [rsp + 160], ymm0
	vmovaps	ymmword ptr [rsp + 128], ymm0
	vmovaps	ymm0, ymmword ptr [rsp + 96]
	vmovaps	ymm1, ymmword ptr [rsp + 128]
	vmovaps	ymm2, ymmword ptr [rsp + 160]
	vmovaps	ymmword ptr [rsp + 64], ymm2
	vmovaps	ymmword ptr [rsp + 32], ymm1
	vmovaps	ymmword ptr [rsp], ymm0
	lea	rdi, [rsp + 192]
	vzeroupper
	call	_ZN8unsq_eve34iteration_one_range_aligned_storesINS_16iteration_traitsILm16ELm2EEEsNS_15_inclusive_scan12inplace_bodyINS_16algorithm_traitsIsLm256ELm2EEEPsN3eve6detail15callable_objectINS8_3tag4add_EvvEEEEEET1_PT0_SH_SF_
	mov	rsp, rbp
	pop	rbp
	.cfi_def_cfa rsp, 8
	ret
.Lfunc_end0:
	.size	_Z9transformPsS_, .Lfunc_end0-_Z9transformPsS_
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5               # -- Begin function _ZN8unsq_eve34iteration_one_range_aligned_storesINS_16iteration_traitsILm16ELm2EEEsNS_15_inclusive_scan12inplace_bodyINS_16algorithm_traitsIsLm256ELm2EEEPsN3eve6detail15callable_objectINS8_3tag4add_EvvEEEEEET1_PT0_SH_SF_
.LCPI1_0:
	.short	1                       # 0x1
	.short	2                       # 0x2
	.short	3                       # 0x3
	.short	4                       # 0x4
	.short	5                       # 0x5
	.short	6                       # 0x6
	.short	7                       # 0x7
	.short	8                       # 0x8
	.short	9                       # 0x9
	.short	10                      # 0xa
	.short	11                      # 0xb
	.short	12                      # 0xc
	.short	13                      # 0xd
	.short	14                      # 0xe
	.short	15                      # 0xf
	.short	16                      # 0x10
.LCPI1_3:
	.short	0                       # 0x0
	.short	1                       # 0x1
	.short	2                       # 0x2
	.short	3                       # 0x3
	.short	4                       # 0x4
	.short	5                       # 0x5
	.short	6                       # 0x6
	.short	7                       # 0x7
	.short	8                       # 0x8
	.short	9                       # 0x9
	.short	10                      # 0xa
	.short	11                      # 0xb
	.short	12                      # 0xc
	.short	13                      # 0xd
	.short	14                      # 0xe
	.short	15                      # 0xf
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4
.LCPI1_1:
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2
.LCPI1_2:
	.long	6                       # 0x6
	.section	.text._ZN8unsq_eve34iteration_one_range_aligned_storesINS_16iteration_traitsILm16ELm2EEEsNS_15_inclusive_scan12inplace_bodyINS_16algorithm_traitsIsLm256ELm2EEEPsN3eve6detail15callable_objectINS8_3tag4add_EvvEEEEEET1_PT0_SH_SF_,"axG",@progbits,_ZN8unsq_eve34iteration_one_range_aligned_storesINS_16iteration_traitsILm16ELm2EEEsNS_15_inclusive_scan12inplace_bodyINS_16algorithm_traitsIsLm256ELm2EEEPsN3eve6detail15callable_objectINS8_3tag4add_EvvEEEEEET1_PT0_SH_SF_,comdat
	.weak	_ZN8unsq_eve34iteration_one_range_aligned_storesINS_16iteration_traitsILm16ELm2EEEsNS_15_inclusive_scan12inplace_bodyINS_16algorithm_traitsIsLm256ELm2EEEPsN3eve6detail15callable_objectINS8_3tag4add_EvvEEEEEET1_PT0_SH_SF_
	.p2align	4, 0x90
	.type	_ZN8unsq_eve34iteration_one_range_aligned_storesINS_16iteration_traitsILm16ELm2EEEsNS_15_inclusive_scan12inplace_bodyINS_16algorithm_traitsIsLm256ELm2EEEPsN3eve6detail15callable_objectINS8_3tag4add_EvvEEEEEET1_PT0_SH_SF_,@function
_ZN8unsq_eve34iteration_one_range_aligned_storesINS_16iteration_traitsILm16ELm2EEEsNS_15_inclusive_scan12inplace_bodyINS_16algorithm_traitsIsLm256ELm2EEEPsN3eve6detail15callable_objectINS8_3tag4add_EvvEEEEEET1_PT0_SH_SF_: # @_ZN8unsq_eve34iteration_one_range_aligned_storesINS_16iteration_traitsILm16ELm2EEEsNS_15_inclusive_scan12inplace_bodyINS_16algorithm_traitsIsLm256ELm2EEEPsN3eve6detail15callable_objectINS8_3tag4add_EvvEEEEEET1_PT0_SH_SF_
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	push	r14
	push	rbx
	and	rsp, -32
	sub	rsp, 128
	.cfi_offset rbx, -32
	.cfi_offset r14, -24
	mov	r14, rdi
	lea	rax, [rbp + 16]
	mov	rcx, rdx
	sub	rcx, rsi
	cmp	rcx, 31
	jg	.LBB1_5
# %bb.1:
	vmovdqa	ymm2, ymmword ptr [rax + 32]
	vmovdqa	ymm3, ymmword ptr [rax + 64]
	vmovaps	ymm0, ymmword ptr [rax]
	vmovaps	ymmword ptr [rsp + 96], ymm0
	lea	rax, [rsi + 4096]
	and	rax, -4096
	sub	rax, rsi
	cmp	rax, 31
	vmovdqa	ymmword ptr [rsp + 64], ymm2 # 32-byte Spill
	vmovdqa	ymmword ptr [rsp + 32], ymm3 # 32-byte Spill
	jg	.LBB1_3
# %bb.2:
	lea	rax, [rdx - 32]
	mov	rdi, rsi
	sub	rdi, rax
	lea	rax, [rsp + rdi]
	mov	ecx, 32
	sub	rcx, rdi
                                        # kill: def $edi killed $edi killed $rdi
	shr	edi
	dec	edi
	vmovd	xmm0, edi
	vpbroadcastw	ymm0, xmm0
	vmovdqa	ymm1, ymmword ptr [rip + .LCPI1_3] # ymm1 = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
	vpcmpgtw	ymm0, ymm1, ymm0
	vpblendvb	ymm0, ymm2, ymmword ptr [rdx - 32], ymm0
	vpalignr	ymm1, ymm0, ymm2, 14 # ymm1 = ymm2[14,15],ymm0[0,1,2,3,4,5,6,7,8,9,10,11,12,13],ymm2[30,31],ymm0[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm0, ymm1, ymm0
	vpalignr	ymm1, ymm0, ymm2, 12 # ymm1 = ymm2[12,13,14,15],ymm0[0,1,2,3,4,5,6,7,8,9,10,11],ymm2[28,29,30,31],ymm0[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm0, ymm0, ymm1
	vpalignr	ymm1, ymm0, ymm2, 8 # ymm1 = ymm2[8,9,10,11,12,13,14,15],ymm0[0,1,2,3,4,5,6,7],ymm2[24,25,26,27,28,29,30,31],ymm0[16,17,18,19,20,21,22,23]
	vpaddw	ymm0, ymm0, ymm1
	vpshufb	xmm1, xmm0, xmmword ptr [rip + .LCPI1_1] # xmm1 = xmm0[14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	vperm2i128	ymm1, ymm2, ymm1, 33 # ymm1 = ymm2[2,3],ymm1[0,1]
	vpaddw	ymm0, ymm0, ymm1
	vmovdqa	ymmword ptr [rsp], ymm0
	mov	rdi, rsi
	mov	rsi, rax
	mov	rdx, rcx
	jmp	.LBB1_4
.LBB1_5:
	vmovdqu	ymm3, ymmword ptr [rsi]
	cmp	rcx, 65
	jl	.LBB1_16
# %bb.6:
	lea	rcx, [rsi + 32]
	mov	rdi, rcx
	and	rdi, -32
	mov	r8, rdx
	and	r8, -32
	add	r8, -32
	vmovdqa	ymm2, ymmword ptr [rdi]
	vmovdqa	ymm1, ymmword ptr [rax + 32]
	shr	ecx
	and	ecx, 15
	mov	ebx, 16
	sub	ebx, ecx
	vmovd	xmm0, ebx
	vpbroadcastw	ymm0, xmm0
	vmovdqa	ymm4, ymmword ptr [rip + .LCPI1_0] # ymm4 = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16]
	vpsubusw	ymm0, ymm4, ymm0
	vpxor	xmm4, xmm4, xmm4
	vpcmpeqw	ymm0, ymm0, ymm4
	vpblendvb	ymm0, ymm1, ymm3, ymm0
	vpalignr	ymm3, ymm0, ymm1, 14 # ymm3 = ymm1[14,15],ymm0[0,1,2,3,4,5,6,7,8,9,10,11,12,13],ymm1[30,31],ymm0[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm0, ymm3, ymm0
	vpalignr	ymm3, ymm0, ymm1, 12 # ymm3 = ymm1[12,13,14,15],ymm0[0,1,2,3,4,5,6,7,8,9,10,11],ymm1[28,29,30,31],ymm0[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm0, ymm0, ymm3
	vpalignr	ymm3, ymm0, ymm1, 8 # ymm3 = ymm1[8,9,10,11,12,13,14,15],ymm0[0,1,2,3,4,5,6,7],ymm1[24,25,26,27,28,29,30,31],ymm0[16,17,18,19,20,21,22,23]
	vpaddw	ymm0, ymm0, ymm3
	vpshufb	xmm3, xmm0, xmmword ptr [rip + .LCPI1_1] # xmm3 = xmm0[14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	vperm2i128	ymm3, ymm1, ymm3, 33 # ymm3 = ymm1[2,3],ymm3[0,1]
	vpaddw	ymm0, ymm0, ymmword ptr [rax + 64]
	vpaddw	ymm4, ymm0, ymm3
	vpshufhw	ymm3, ymm4, 239 # ymm3 = ymm4[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vpbroadcastd	ymm0, dword ptr [rip + .LCPI1_2] # ymm0 = [6,6,6,6,6,6,6,6]
	vpermd	ymm3, ymm0, ymm3
	vmovdqa	ymmword ptr [rax + 64], ymm3
	vmovdqu	ymmword ptr [rsi], ymm4
	cmp	r8, rdi
	je	.LBB1_7
# %bb.8:
	vpalignr	ymm4, ymm2, ymm1, 14 # ymm4 = ymm1[14,15],ymm2[0,1,2,3,4,5,6,7,8,9,10,11,12,13],ymm1[30,31],ymm2[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm2, ymm4, ymm2
	vpalignr	ymm4, ymm2, ymm1, 12 # ymm4 = ymm1[12,13,14,15],ymm2[0,1,2,3,4,5,6,7,8,9,10,11],ymm1[28,29,30,31],ymm2[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm2, ymm2, ymm4
	vpalignr	ymm4, ymm2, ymm1, 8 # ymm4 = ymm1[8,9,10,11,12,13,14,15],ymm2[0,1,2,3,4,5,6,7],ymm1[24,25,26,27,28,29,30,31],ymm2[16,17,18,19,20,21,22,23]
	vpaddw	ymm2, ymm2, ymm4
	vpshufb	xmm4, xmm2, xmmword ptr [rip + .LCPI1_1] # xmm4 = xmm2[14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	vperm2i128	ymm1, ymm1, ymm4, 33 # ymm1 = ymm1[2,3],ymm4[0,1]
	vpaddw	ymm2, ymm2, ymm3
	vpaddw	ymm1, ymm2, ymm1
	vpshufhw	ymm2, ymm1, 239 # ymm2 = ymm1[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vpermd	ymm2, ymm0, ymm2
	vmovdqa	ymmword ptr [rax + 64], ymm2
	vmovdqa	ymmword ptr [rdi], ymm1
	mov	rsi, rdi
	add	rsi, 32
	vmovdqa	ymm3, ymmword ptr [rdi + 32]
	cmp	rsi, r8
	je	.LBB1_15
# %bb.9:
	vmovdqa	xmm1, xmmword ptr [rip + .LCPI1_1] # xmm1 = [14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	vmovdqa	xmm2, xmmword ptr [rip + .LCPI1_1] # xmm2 = [14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	.p2align	4, 0x90
.LBB1_10:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_12 Depth 2
	vmovdqa	ymm4, ymmword ptr [rax + 32]
	vpalignr	ymm5, ymm3, ymm4, 14 # ymm5 = ymm4[14,15],ymm3[0,1,2,3,4,5,6,7,8,9,10,11,12,13],ymm4[30,31],ymm3[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm3, ymm5, ymm3
	vpalignr	ymm5, ymm3, ymm4, 12 # ymm5 = ymm4[12,13,14,15],ymm3[0,1,2,3,4,5,6,7,8,9,10,11],ymm4[28,29,30,31],ymm3[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm3, ymm3, ymm5
	vpalignr	ymm5, ymm3, ymm4, 8 # ymm5 = ymm4[8,9,10,11,12,13,14,15],ymm3[0,1,2,3,4,5,6,7],ymm4[24,25,26,27,28,29,30,31],ymm3[16,17,18,19,20,21,22,23]
	vpaddw	ymm3, ymm3, ymm5
	vpshufb	xmm5, xmm3, xmm1
	vperm2i128	ymm4, ymm4, ymm5, 33 # ymm4 = ymm4[2,3],ymm5[0,1]
	vpaddw	ymm3, ymm3, ymmword ptr [rax + 64]
	vpaddw	ymm3, ymm3, ymm4
	vpshufhw	ymm4, ymm3, 239 # ymm4 = ymm3[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vpermd	ymm4, ymm0, ymm4
	vmovdqa	ymmworqd ptr [rax + 64], ymm4
	vmovdqa	ymmword ptr [rsi], ymm3
	add	rdi, 64
	mov	rcx, r8
	sub	rcx, rdi
	sar	rcx
	lea	rsi, [rcx + 31]
	cmp	rsi, 63
	jb	.LBB1_13
# %bb.11:                               #   in Loop: Header=BB1_10 Depth=1
	test	rcx, rcx
	cmovns	rsi, rcx
	sar	rsi, 5
	.p2align	4, 0x90
.LBB1_12:                               #   Parent Loop BB1_10 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovdqa	ymm3, ymmword ptr [rdi]
	vmovdqa	ymm4, ymmword ptr [rax + 32]
	vpalignr	ymm5, ymm3, ymm4, 14 # ymm5 = ymm4[14,15],ymm3[0,1,2,3,4,5,6,7,8,9,10,11,12,13],ymm4[30,31],ymm3[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm3, ymm5, ymm3
	vpalignr	ymm5, ymm3, ymm4, 12 # ymm5 = ymm4[12,13,14,15],ymm3[0,1,2,3,4,5,6,7,8,9,10,11],ymm4[28,29,30,31],ymm3[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm3, ymm3, ymm5
	vpalignr	ymm5, ymm3, ymm4, 8 # ymm5 = ymm4[8,9,10,11,12,13,14,15],ymm3[0,1,2,3,4,5,6,7],ymm4[24,25,26,27,28,29,30,31],ymm3[16,17,18,19,20,21,22,23]
	vpaddw	ymm3, ymm3, ymm5
	vpshufb	xmm5, xmm3, xmm2
	vpaddw	ymm3, ymm3, ymmword ptr [rax + 64]
	vperm2i128	ymm4, ymm4, ymm5, 33 # ymm4 = ymm4[2,3],ymm5[0,1]
	vpaddw	ymm3, ymm3, ymm4
	vpshufhw	ymm4, ymm3, 239 # ymm4 = ymm3[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vpermd	ymm4, ymm0, ymm4
	vmovdqa	ymmword ptr [rax + 64], ymm4
	vmovdqa	ymmword ptr [rdi], ymm3
	vmovdqa	ymm3, ymmword ptr [rdi + 32]
	vmovdqa	ymm4, ymmword ptr [rax + 32]
	vpalignr	ymm5, ymm3, ymm4, 14 # ymm5 = ymm4[14,15],ymm3[0,1,2,3,4,5,6,7,8,9,10,11,12,13],ymm4[30,31],ymm3[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm3, ymm5, ymm3
	vpalignr	ymm5, ymm3, ymm4, 12 # ymm5 = ymm4[12,13,14,15],ymm3[0,1,2,3,4,5,6,7,8,9,10,11],ymm4[28,29,30,31],ymm3[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm3, ymm3, ymm5
	vpalignr	ymm5, ymm3, ymm4, 8 # ymm5 = ymm4[8,9,10,11,12,13,14,15],ymm3[0,1,2,3,4,5,6,7],ymm4[24,25,26,27,28,29,30,31],ymm3[16,17,18,19,20,21,22,23]
	vpaddw	ymm3, ymm3, ymm5
	vpshufb	xmm5, xmm3, xmm2
	vperm2i128	ymm4, ymm4, ymm5, 33 # ymm4 = ymm4[2,3],ymm5[0,1]
	vpaddw	ymm3, ymm3, ymmword ptr [rax + 64]
	vpaddw	ymm3, ymm3, ymm4
	vpshufhw	ymm4, ymm3, 239 # ymm4 = ymm3[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vpermd	ymm4, ymm0, ymm4
	vmovdqa	ymmword ptr [rax + 64], ymm4
	vmovdqa	ymmword ptr [rdi + 32], ymm3
	add	rdi, 64
	dec	rsi
	jne	.LBB1_12
.LBB1_13:                               #   in Loop: Header=BB1_10 Depth=1
	vmovdqa	ymm3, ymmword ptr [rdi]
	cmp	rdi, r8
	je	.LBB1_15
# %bb.14:                               #   in Loop: Header=BB1_10 Depth=1
	vmovdqa	ymm4, ymmword ptr [rax + 32]
	vpalignr	ymm5, ymm3, ymm4, 14 # ymm5 = ymm4[14,15],ymm3[0,1,2,3,4,5,6,7,8,9,10,11,12,13],ymm4[30,31],ymm3[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm3, ymm5, ymm3
	vpalignr	ymm5, ymm3, ymm4, 12 # ymm5 = ymm4[12,13,14,15],ymm3[0,1,2,3,4,5,6,7,8,9,10,11],ymm4[28,29,30,31],ymm3[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm3, ymm3, ymm5
	vpalignr	ymm5, ymm3, ymm4, 8 # ymm5 = ymm4[8,9,10,11,12,13,14,15],ymm3[0,1,2,3,4,5,6,7],ymm4[24,25,26,27,28,29,30,31],ymm3[16,17,18,19,20,21,22,23]
	vpaddw	ymm3, ymm3, ymm5
	vpshufb	xmm5, xmm3, xmm1
	vpaddw	ymm3, ymm3, ymmword ptr [rax + 64]
	vperm2i128	ymm4, ymm4, ymm5, 33 # ymm4 = ymm4[2,3],ymm5[0,1]
	vpaddw	ymm3, ymm3, ymm4
	vpshufhw	ymm4, ymm3, 239 # ymm4 = ymm3[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vpermd	ymm4, ymm0, ymm4
	vmovdqa	ymmword ptr [rax + 64], ymm4
	vmovdqa	ymmword ptr [rdi], ymm3
	lea	rsi, [rdi + 32]
	vmovdqa	ymm3, ymmword ptr [rdi + 32]
	cmp	rsi, r8
	jne	.LBB1_10
.LBB1_15:
	mov	rsi, r8
	jmp	.LBB1_16
.LBB1_3:
	mov	rax, rsi
	sub	rax, rdx
	lea	ecx, [rax + 32]
	shr	ecx
	mov	edx, 16
	sub	edx, ecx
	vmovd	xmm0, edx
	vpbroadcastw	ymm0, xmm0
	vpcmpgtw	ymm0, ymm0, ymmword ptr [rip + .LCPI1_3]
	vpblendvb	ymm0, ymm2, ymmword ptr [rsi], ymm0
	vpalignr	ymm1, ymm0, ymm2, 14 # ymm1 = ymm2[14,15],ymm0[0,1,2,3,4,5,6,7,8,9,10,11,12,13],ymm2[30,31],ymm0[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm0, ymm1, ymm0
	vpalignr	ymm1, ymm0, ymm2, 12 # ymm1 = ymm2[12,13,14,15],ymm0[0,1,2,3,4,5,6,7,8,9,10,11],ymm2[28,29,30,31],ymm0[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm0, ymm0, ymm1
	vpalignr	ymm1, ymm0, ymm2, 8 # ymm1 = ymm2[8,9,10,11,12,13,14,15],ymm0[0,1,2,3,4,5,6,7],ymm2[24,25,26,27,28,29,30,31],ymm0[16,17,18,19,20,21,22,23]
	vpaddw	ymm0, ymm0, ymm1
	vpshufb	xmm1, xmm0, xmmword ptr [rip + .LCPI1_1] # xmm1 = xmm0[14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	vperm2i128	ymm1, ymm2, ymm1, 33 # ymm1 = ymm2[2,3],ymm1[0,1]
	vpaddw	ymm0, ymm0, ymm1
	vmovdqa	ymmword ptr [rsp], ymm0
	neg	rax
	mov	rcx, rsp
	mov	rdi, rsi
	mov	rsi, rcx
	mov	rdx, rax
.LBB1_4:
	vzeroupper
	call	memcpy
	vmovaps	ymm2, ymmword ptr [rsp + 32] # 32-byte Reload
	vmovaps	ymm1, ymmword ptr [rsp + 64] # 32-byte Reload
	vmovaps	ymm0, ymmword ptr [rsp + 96]
	vmovaps	ymmword ptr [r14], ymm0
	vmovaps	ymmword ptr [r14 + 32], ymm1
	vmovaps	ymmword ptr [r14 + 64], ymm2
	jmp	.LBB1_17
.LBB1_7:
	vmovdqa	ymm3, ymm2
	mov	rsi, rdi
.LBB1_16:
	lea	rcx, [rdx - 32]
	mov	edi, esi
	sub	edi, ecx
	add	edi, 32
	shr	edi
	vmovdqa	ymm0, ymmword ptr [rax + 32]
	mov	ecx, 16
	sub	ecx, edi
	vmovd	xmm1, ecx
	vpbroadcastw	ymm1, xmm1
	vpcmpgtw	ymm1, ymm1, ymmword ptr [rip + .LCPI1_3]
	vpblendvb	ymm1, ymm0, ymm3, ymm1
	vmovdqu	ymm2, ymmword ptr [rdx - 32]
	vpalignr	ymm3, ymm1, ymm0, 14 # ymm3 = ymm0[14,15],ymm1[0,1,2,3,4,5,6,7,8,9,10,11,12,13],ymm0[30,31],ymm1[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm1, ymm3, ymm1
	vpalignr	ymm3, ymm1, ymm0, 12 # ymm3 = ymm0[12,13,14,15],ymm1[0,1,2,3,4,5,6,7,8,9,10,11],ymm0[28,29,30,31],ymm1[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm1, ymm1, ymm3
	vpalignr	ymm3, ymm1, ymm0, 8 # ymm3 = ymm0[8,9,10,11,12,13,14,15],ymm1[0,1,2,3,4,5,6,7],ymm0[24,25,26,27,28,29,30,31],ymm1[16,17,18,19,20,21,22,23]
	vpaddw	ymm1, ymm1, ymm3
	vmovdqa	xmm3, xmmword ptr [rip + .LCPI1_1] # xmm3 = [14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15]
	vpshufb	xmm4, xmm1, xmm3
	vperm2i128	ymm0, ymm0, ymm4, 33 # ymm0 = ymm0[2,3],ymm4[0,1]
	vpaddw	ymm1, ymm1, ymmword ptr [rax + 64]
	vpaddw	ymm0, ymm1, ymm0
	vpshufhw	ymm1, ymm0, 239 # ymm1 = ymm0[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vpbroadcastd	ymm4, dword ptr [rip + .LCPI1_2] # ymm4 = [6,6,6,6,6,6,6,6]
	vpermd	ymm1, ymm4, ymm1
	vmovdqa	ymmword ptr [rax + 64], ymm1
	vmovdqu	ymmword ptr [rsi], ymm0
	vmovdqa	ymm0, ymmword ptr [rax + 32]
	vpalignr	ymm1, ymm2, ymm0, 14 # ymm1 = ymm0[14,15],ymm2[0,1,2,3,4,5,6,7,8,9,10,11,12,13],ymm0[30,31],ymm2[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddw	ymm1, ymm1, ymm2
	vpalignr	ymm2, ymm1, ymm0, 12 # ymm2 = ymm0[12,13,14,15],ymm1[0,1,2,3,4,5,6,7,8,9,10,11],ymm0[28,29,30,31],ymm1[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddw	ymm1, ymm1, ymm2
	vpalignr	ymm2, ymm1, ymm0, 8 # ymm2 = ymm0[8,9,10,11,12,13,14,15],ymm1[0,1,2,3,4,5,6,7],ymm0[24,25,26,27,28,29,30,31],ymm1[16,17,18,19,20,21,22,23]
	vpaddw	ymm1, ymm1, ymm2
	vpshufb	xmm2, xmm1, xmm3
	vpaddw	ymm1, ymm1, ymmword ptr [rax + 64]
	vperm2i128	ymm0, ymm0, ymm2, 33 # ymm0 = ymm0[2,3],ymm2[0,1]
	vpaddw	ymm0, ymm1, ymm0
	vpshufhw	ymm1, ymm0, 239 # ymm1 = ymm0[0,1,2,3,7,7,6,7,8,9,10,11,15,15,14,15]
	vpermd	ymm1, ymm4, ymm1
	vmovdqa	ymmword ptr [rax + 64], ymm1
	vmovdqu	ymmword ptr [rdx - 32], ymm0
	vmovaps	ymm0, ymmword ptr [rax]
	vmovaps	ymm1, ymmword ptr [rax + 32]
	vmovaps	ymm2, ymmword ptr [rax + 64]
	vmovaps	ymmword ptr [r14 + 64], ymm2
	vmovaps	ymmword ptr [r14 + 32], ymm1
	vmovaps	ymmword ptr [r14], ymm0
.LBB1_17:
	mov	rax, r14
	lea	rsp, [rbp - 16]
	pop	rbx
	pop	r14
	pop	rbp
	.cfi_def_cfa rsp, 8
	vzeroupper
	ret
.Lfunc_end1:
	.size	_ZN8unsq_eve34iteration_one_range_aligned_storesINS_16iteration_traitsILm16ELm2EEEsNS_15_inclusive_scan12inplace_bodyINS_16algorithm_traitsIsLm256ELm2EEEPsN3eve6detail15callable_objectINS8_3tag4add_EvvEEEEEET1_PT0_SH_SF_, .Lfunc_end1-_ZN8unsq_eve34iteration_one_range_aligned_storesINS_16iteration_traitsILm16ELm2EEEsNS_15_inclusive_scan12inplace_bodyINS_16algorithm_traitsIsLm256ELm2EEEPsN3eve6detail15callable_objectINS8_3tag4add_EvvEEEEEET1_PT0_SH_SF_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
