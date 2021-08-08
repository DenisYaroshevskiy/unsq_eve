	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5                               # -- Begin function _Z6removePdS_d
.LCPI0_0:
	.quad	0                               # 0x0
	.quad	1                               # 0x1
	.quad	2                               # 0x2
	.quad	3                               # 0x3
	.text
	.globl	_Z6removePdS_d
	.p2align	4, 0x90
	.type	_Z6removePdS_d,@function
_Z6removePdS_d:                         # @_Z6removePdS_d
	.cfi_startproc
# %bb.0:
	mov	rax, rdi
	xor	r8d, r8d
	cmp	rdi, rsi
	cmove	rsi, r8
	cmovne	r8, rdi
	cmp	r8, rsi
	je	.LBB0_10
# %bb.1:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	and	rsp, -32
	sub	rsp, 96
	mov	rdx, r8
	and	rdx, -32
	mov	r11, rsi
	and	r11, -32
	mov	r9d, r8d
	shr	r9d, 3
	and	r9d, 3
	cmp	rdx, r11
	je	.LBB0_2
# %bb.3:
	vmovapd	ymm1, ymmword ptr [rdx]
	vbroadcastsd	ymm0, xmm0
	vcmpneqpd	ymm2, ymm0, ymm1
	vmovmskpd	ecx, ymm2
	shrx	ecx, ecx, r9d
	shlx	ecx, ecx, r9d
	popcnt	r10d, ecx
	and	ecx, 7
	shl	rcx, 5
	vmovapd	ymm2, ymmword ptr [rcx + .L__const._ZN3eve6detail20compress_store_impl_INS_14ignore_extremaEdNS_5fixedILl4EEEPdEEPT0_RKNS0_7delay_tERKNS_6ssse3_ET_NS_10avx_abi_v04wideIS6_T1_EENS_7logicalISI_EET2_.patterns]
	vpermps	ymm1, ymm2, ymm1
	vmovq	xmm2, r10
	vpbroadcastq	ymm2, xmm2
	vpcmpgtq	ymm2, ymm2, ymmword ptr [rip + .LCPI0_0]
	lea	rcx, [rdx + 8*r9]
	vmaskmovpd	ymmword ptr [rdx + 8*r9], ymm2, ymm1
	lea	rcx, [rcx + 8*r10]
	add	rdx, 32
	cmp	rdx, r11
	je	.LBB0_6
	.p2align	4, 0x90
.LBB0_4:                                # =>This Inner Loop Header: Depth=1
	vmovapd	ymm1, ymmword ptr [rdx]
	vcmpneqpd	ymm2, ymm0, ymm1
	vmovmskpd	edi, ymm2
	xor	r9d, r9d
	popcnt	r9d, edi
	and	edi, 7
	shl	rdi, 5
	vmovapd	ymm2, ymmword ptr [rdi + .L__const._ZN3eve6detail20compress_store_impl_INS_14ignore_extremaEdNS_5fixedILl4EEEPdEEPT0_RKNS0_7delay_tERKNS_6ssse3_ET_NS_10avx_abi_v04wideIS6_T1_EENS_7logicalISI_EET2_.patterns]
	vpermps	ymm1, ymm2, ymm1
	vmovupd	ymmword ptr [rcx], ymm1
	lea	rcx, [rcx + 8*r9]
	add	rdx, 32
	cmp	rdx, r11
	jne	.LBB0_4
.LBB0_6:
	cmp	rsi, r11
	je	.LBB0_9
# %bb.7:
	xor	r9d, r9d
	jmp	.LBB0_8
.LBB0_2:
	vbroadcastsd	ymm0, xmm0
	mov	rcx, rdx
.LBB0_8:
	mov	edx, r11d
	sub	edx, esi
	add	edx, 32
	shr	edx, 3
	vmovapd	ymm1, ymmword ptr [r11]
	vcmpneqpd	ymm0, ymm0, ymm1
	vmovmskpd	esi, ymm0
	mov	dil, 4
	sub	dil, dl
	mov	rdx, -1
	shlx	rdx, rdx, rdi
	not	edx
	shrx	edx, edx, r9d
	shlx	edx, edx, r9d
	and	edx, esi
	xor	esi, esi
	popcnt	esi, edx
	and	edx, 7
	shl	rdx, 5
	vmovapd	ymm0, ymmword ptr [rdx + .L__const._ZN3eve6detail20compress_store_impl_INS_14ignore_extremaEdNS_5fixedILl4EEEPdEEPT0_RKNS0_7delay_tERKNS_6ssse3_ET_NS_10avx_abi_v04wideIS6_T1_EENS_7logicalISI_EET2_.patterns]
	vpermps	ymm0, ymm0, ymm1
	lea	rdx, [rcx + 8*r9]
	vmovq	xmm1, rsi
	vpbroadcastq	ymm1, xmm1
	vpcmpgtq	ymm1, ymm1, ymmword ptr [rip + .LCPI0_0]
	vmaskmovpd	ymmword ptr [rcx + 8*r9], ymm1, ymm0
	lea	rcx, [rdx + 8*rsi]
.LBB0_9:
	sub	rcx, r8
	add	rax, rcx
	mov	rsp, rbp
	pop	rbp
	.cfi_def_cfa rsp, 8
	.cfi_restore rbp
.LBB0_10:
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z6removePdS_d, .Lfunc_end0-_Z6removePdS_d
	.cfi_endproc
                                        # -- End function
	.type	.L__const._ZN3eve6detail20compress_store_impl_INS_14ignore_extremaEdNS_5fixedILl4EEEPdEEPT0_RKNS0_7delay_tERKNS_6ssse3_ET_NS_10avx_abi_v04wideIS6_T1_EENS_7logicalISI_EET2_.patterns,@object # @__const._ZN3eve6detail20compress_store_impl_INS_14ignore_extremaEdNS_5fixedILl4EEEPdEEPT0_RKNS0_7delay_tERKNS_6ssse3_ET_NS_10avx_abi_v04wideIS6_T1_EENS_7logicalISI_EET2_.patterns
	.section	.rodata,"a",@progbits
	.p2align	5
.L__const._ZN3eve6detail20compress_store_impl_INS_14ignore_extremaEdNS_5fixedILl4EEEPdEEPT0_RKNS0_7delay_tERKNS_6ssse3_ET_NS_10avx_abi_v04wideIS6_T1_EENS_7logicalISI_EET2_.patterns:
	.quad	30064771078                     # 0x700000006
	.quad	0                               # 0x0
	.quad	0                               # 0x0
	.quad	0                               # 0x0
	.quad	4294967296                      # 0x100000000
	.quad	30064771078                     # 0x700000006
	.quad	0                               # 0x0
	.quad	0                               # 0x0
	.quad	12884901890                     # 0x300000002
	.quad	30064771078                     # 0x700000006
	.quad	0                               # 0x0
	.quad	0                               # 0x0
	.quad	4294967296                      # 0x100000000
	.quad	12884901890                     # 0x300000002
	.quad	30064771078                     # 0x700000006
	.quad	0                               # 0x0
	.quad	21474836484                     # 0x500000004
	.quad	30064771078                     # 0x700000006
	.quad	0                               # 0x0
	.quad	0                               # 0x0
	.quad	4294967296                      # 0x100000000
	.quad	21474836484                     # 0x500000004
	.quad	30064771078                     # 0x700000006
	.quad	0                               # 0x0
	.quad	12884901890                     # 0x300000002
	.quad	21474836484                     # 0x500000004
	.quad	30064771078                     # 0x700000006
	.quad	0                               # 0x0
	.quad	4294967296                      # 0x100000000
	.quad	12884901890                     # 0x300000002
	.quad	21474836484                     # 0x500000004
	.quad	30064771078                     # 0x700000006
	.size	.L__const._ZN3eve6detail20compress_store_impl_INS_14ignore_extremaEdNS_5fixedILl4EEEPdEEPT0_RKNS0_7delay_tERKNS_6ssse3_ET_NS_10avx_abi_v04wideIS6_T1_EENS_7logicalISI_EET2_.patterns, 256

	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 13.0.0 (https://github.com/llvm/llvm-project.git e3251f2ec44bd65f440d215517f135c39f22d1b9)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
