	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5               # -- Begin function _Z11min_elementPiS_
.LCPI0_0:
	.long	0                       # 0x0
	.long	1                       # 0x1
	.long	2                       # 0x2
	.long	3                       # 0x3
	.long	4                       # 0x4
	.long	5                       # 0x5
	.long	6                       # 0x6
	.long	7                       # 0x7
.LCPI0_1:
	.quad	38654705672             # 0x900000008
	.quad	47244640266             # 0xb0000000a
	.quad	55834574860             # 0xd0000000c
	.quad	64424509454             # 0xf0000000e
.LCPI0_6:
	.byte	255                     # 0xff
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.byte	255                     # 0xff
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.byte	255                     # 0xff
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.byte	255                     # 0xff
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.byte	255                     # 0xff
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.byte	255                     # 0xff
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.byte	255                     # 0xff
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.byte	255                     # 0xff
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.byte	0                       # 0x0
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2
.LCPI0_2:
	.long	8                       # 0x8
.LCPI0_3:
	.long	16                      # 0x10
.LCPI0_4:
	.long	24                      # 0x18
.LCPI0_5:
	.long	32                      # 0x20
	.text
	.globl	_Z11min_elementPiS_
	.p2align	4, 0x90
	.type	_Z11min_elementPiS_,@function
_Z11min_elementPiS_:                    # @_Z11min_elementPiS_
	.cfi_startproc
# %bb.0:
	push	r15
	.cfi_def_cfa_offset 16
	push	r14
	.cfi_def_cfa_offset 24
	push	r12
	.cfi_def_cfa_offset 32
	push	rbx
	.cfi_def_cfa_offset 40
	.cfi_offset rbx, -40
	.cfi_offset r12, -32
	.cfi_offset r14, -24
	.cfi_offset r15, -16
	mov	rax, rdi
	cmp	rdi, rsi
	je	.LBB0_24
# %bb.1:
	vpbroadcastd	ymm0, dword ptr [rax]
	mov	rdx, rax
	and	rdx, -32
	mov	r9, rsi
	and	r9, -32
	mov	ecx, eax
	shr	ecx, 2
	and	ecx, 7
	dec	ecx
	cmp	rdx, r9
	je	.LBB0_2
# %bb.3:
	vmovd	xmm1, ecx
	vpbroadcastd	ymm2, xmm1
	vmovdqa	ymm1, ymmword ptr [rip + .LCPI0_0] # ymm1 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm2, ymm1, ymm2
	vpblendvb	ymm2, ymm0, ymmword ptr [rdx], ymm2
	vpminsd	ymm3, ymm0, ymm2
	vpcmpgtd	ymm2, ymm0, ymm2
	vpand	ymm2, ymm2, ymmword ptr [rip + .LCPI0_0]
	lea	rdi, [rdx + 32]
	cmp	rdi, r9
	je	.LBB0_4
# %bb.5:
	mov	ebx, 247
	vmovdqa	ymm5, ymmword ptr [rip + .LCPI0_1] # ymm5 = [38654705672,47244640266,55834574860,64424509454]
	vmovdqa	ymm4, ymmword ptr [rip + .LCPI0_6] # ymm4 = [255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0]
	movabs	r8, 4611686018427387896
	mov	r10, rdx
	mov	r11, rdi
	jmp	.LBB0_6
	.p2align	4, 0x90
.LBB0_19:                               #   in Loop: Header=BB0_6 Depth=1
	mov	ebx, 255
	mov	r10, rdx
	vmovdqa	ymm5, ymm1
	mov	rdi, r11
	cmp	r11, r9
	je	.LBB0_20
.LBB0_6:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_11 Depth 2
                                        #     Child Loop BB0_15 Depth 2
	mov	r15, r9
	sub	r15, rdi
	sar	r15, 2
	cmp	r15, rbx
	cmovg	r15, rbx
	mov	rdx, r15
	shr	rdx, 3
	je	.LBB0_7
# %bb.8:                                #   in Loop: Header=BB0_6 Depth=1
	lea	r14, [rdx - 1]
	mov	r12, rdx
	and	r12, 3
	je	.LBB0_9
# %bb.10:                               #   in Loop: Header=BB0_6 Depth=1
	xor	ecx, ecx
	mov	rbx, r11
	.p2align	4, 0x90
.LBB0_11:                               #   Parent Loop BB0_6 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovdqa	ymm6, ymmword ptr [rdi]
	vpcmpgtd	ymm7, ymm3, ymm6
	vpblendvb	ymm2, ymm2, ymm5, ymm7
	vpminsd	ymm3, ymm3, ymm6
	vpbroadcastd	ymm6, dword ptr [rip + .LCPI0_2] # ymm6 = [8,8,8,8,8,8,8,8]
	vpaddd	ymm5, ymm5, ymm6
	add	rbx, 32
	inc	rcx
	mov	rdi, rbx
	cmp	r12, rcx
	jne	.LBB0_11
# %bb.12:                               #   in Loop: Header=BB0_6 Depth=1
	sub	rdx, rcx
	mov	rdi, rbx
	cmp	r14, 3
	jae	.LBB0_14
	jmp	.LBB0_16
	.p2align	4, 0x90
.LBB0_7:                                #   in Loop: Header=BB0_6 Depth=1
	mov	rdx, rdi
	vpcmpgtd	ymm5, ymm0, ymm3
	vmovmskps	ecx, ymm5
	test	ecx, ecx
	jne	.LBB0_18
	jmp	.LBB0_19
	.p2align	4, 0x90
.LBB0_9:                                #   in Loop: Header=BB0_6 Depth=1
	mov	rbx, r11
	cmp	r14, 3
	jb	.LBB0_16
.LBB0_14:                               #   in Loop: Header=BB0_6 Depth=1
	sub	rbx, -128
	.p2align	4, 0x90
.LBB0_15:                               #   Parent Loop BB0_6 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovdqa	ymm6, ymmword ptr [rdi]
	vpminsd	ymm7, ymm3, ymm6
	vpcmpgtd	ymm3, ymm3, ymm6
	vpblendvb	ymm2, ymm2, ymm5, ymm3
	vpbroadcastd	ymm3, dword ptr [rip + .LCPI0_2] # ymm3 = [8,8,8,8,8,8,8,8]
	vpaddd	ymm3, ymm5, ymm3
	vmovdqa	ymm6, ymmword ptr [rbx - 96]
	vmovdqa	ymm8, ymmword ptr [rbx - 64]
	vmovdqa	ymm9, ymmword ptr [rbx - 32]
	vpminsd	ymm10, ymm7, ymm6
	vpcmpgtd	ymm6, ymm7, ymm6
	vpblendvb	ymm2, ymm2, ymm3, ymm6
	vpbroadcastd	ymm3, dword ptr [rip + .LCPI0_3] # ymm3 = [16,16,16,16,16,16,16,16]
	vpaddd	ymm3, ymm5, ymm3
	vpminsd	ymm6, ymm10, ymm8
	vpcmpgtd	ymm7, ymm10, ymm8
	vpblendvb	ymm2, ymm2, ymm3, ymm7
	vpbroadcastd	ymm3, dword ptr [rip + .LCPI0_4] # ymm3 = [24,24,24,24,24,24,24,24]
	vpaddd	ymm7, ymm5, ymm3
	mov	rdi, rbx
	lea	rbx, [rbx + 128]
	vpminsd	ymm3, ymm6, ymm9
	vpcmpgtd	ymm6, ymm6, ymm9
	vpblendvb	ymm2, ymm2, ymm7, ymm6
	vpbroadcastd	ymm6, dword ptr [rip + .LCPI0_5] # ymm6 = [32,32,32,32,32,32,32,32]
	vpaddd	ymm5, ymm5, ymm6
	add	rdx, -4
	jne	.LBB0_15
.LBB0_16:                               #   in Loop: Header=BB0_6 Depth=1
	and	r15, r8
	lea	rdx, [r11 + 4*r15]
	mov	r11, rdx
	vpcmpgtd	ymm5, ymm0, ymm3
	vmovmskps	ecx, ymm5
	test	ecx, ecx
	je	.LBB0_19
.LBB0_18:                               #   in Loop: Header=BB0_6 Depth=1
	vpminsd	ymm0, ymm0, ymm3
	vpermq	ymm5, ymm0, 78          # ymm5 = ymm0[2,3,0,1]
	vpminsd	ymm0, ymm0, ymm5
	vpshufd	ymm5, ymm0, 78          # ymm5 = ymm0[2,3,0,1,6,7,4,5]
	vpminsd	ymm0, ymm0, ymm5
	vpshufd	ymm5, ymm0, 177         # ymm5 = ymm0[1,0,3,2,5,4,7,6]
	vpminsd	ymm0, ymm5, ymm0
	vpcmpeqd	ymm5, ymm0, ymm3
	vpand	ymm2, ymm2, ymm5
	vpandn	ymm5, ymm5, ymm4
	vpor	ymm2, ymm5, ymm2
	vpermq	ymm5, ymm2, 78          # ymm5 = ymm2[2,3,0,1]
	vpminud	ymm5, ymm5, ymm2
	vpshufd	ymm6, ymm5, 78          # ymm6 = ymm5[2,3,0,1,6,7,4,5]
	vpminud	ymm5, ymm5, ymm6
	vpshufd	ymm6, ymm5, 177         # ymm6 = ymm5[1,0,3,2,5,4,7,6]
	vextracti128	xmm5, ymm5, 1
	vextracti128	xmm6, ymm6, 1
	vpminud	xmm5, xmm6, xmm5
	vpextrd	eax, xmm5, 3
	lea	rax, [r10 + 4*rax]
	mov	rdx, r11
	jmp	.LBB0_19
.LBB0_2:
	vmovdqa	ymm1, ymmword ptr [rip + .LCPI0_0] # ymm1 = [0,1,2,3,4,5,6,7]
                                        # implicit-def: $ymm2
	vmovdqa	ymm3, ymm0
	jmp	.LBB0_21
.LBB0_4:
	vmovdqa	ymm1, ymmword ptr [rip + .LCPI0_1] # ymm1 = [38654705672,47244640266,55834574860,64424509454]
.LBB0_20:
	mov	ecx, -1
	cmp	r9, rsi
	je	.LBB0_22
.LBB0_21:
	mov	rdi, r9
	sub	rdi, rsi
	add	rdi, 32
	shr	rdi, 2
	vmovd	xmm4, ecx
	vpbroadcastd	ymm4, xmm4
	mov	ecx, 8
	sub	ecx, edi
	vmovd	xmm5, ecx
	vpbroadcastd	ymm5, xmm5
	vmovdqa	ymm6, ymmword ptr [rip + .LCPI0_0] # ymm6 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm4, ymm6, ymm4
	vpcmpgtd	ymm5, ymm5, ymm6
	vpand	ymm4, ymm4, ymm5
	vpblendvb	ymm4, ymm3, ymmword ptr [r9], ymm4
	vpcmpgtd	ymm5, ymm3, ymm4
	vpminsd	ymm3, ymm3, ymm4
	vpblendvb	ymm2, ymm2, ymm1, ymm5
.LBB0_22:
	vpcmpgtd	ymm1, ymm0, ymm3
	vmovmskps	ecx, ymm1
	test	ecx, ecx
	je	.LBB0_24
# %bb.23:
	vpminsd	ymm0, ymm0, ymm3
	vpermq	ymm1, ymm0, 78          # ymm1 = ymm0[2,3,0,1]
	vpminsd	ymm0, ymm0, ymm1
	vpshufd	ymm1, ymm0, 78          # ymm1 = ymm0[2,3,0,1,6,7,4,5]
	vpminsd	ymm0, ymm0, ymm1
	vpshufd	ymm1, ymm0, 177         # ymm1 = ymm0[1,0,3,2,5,4,7,6]
	vpminsd	ymm0, ymm1, ymm0
	vpcmpeqd	ymm0, ymm0, ymm3
	vpand	ymm1, ymm2, ymm0
	vpandn	ymm0, ymm0, ymmword ptr [rip + .LCPI0_6]
	vpor	ymm0, ymm0, ymm1
	vpermq	ymm1, ymm0, 78          # ymm1 = ymm0[2,3,0,1]
	vpminud	ymm0, ymm1, ymm0
	vpshufd	ymm1, ymm0, 78          # ymm1 = ymm0[2,3,0,1,6,7,4,5]
	vpminud	ymm0, ymm0, ymm1
	vpshufd	ymm1, ymm0, 177         # ymm1 = ymm0[1,0,3,2,5,4,7,6]
	vextracti128	xmm0, ymm0, 1
	vextracti128	xmm1, ymm1, 1
	vpminud	xmm0, xmm1, xmm0
	vpextrd	eax, xmm0, 3
	lea	rax, [rdx + 4*rax]
.LBB0_24:
	pop	rbx
	.cfi_def_cfa_offset 32
	pop	r12
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_def_cfa_offset 8
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z11min_elementPiS_, .Lfunc_end0-_Z11min_elementPiS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git 448bbc512f456df6fc817b0d7041897eea2375b7)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
