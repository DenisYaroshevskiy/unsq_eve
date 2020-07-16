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
.LCPI0_3:
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
	.text
	.globl	_Z11min_elementPiS_
	.p2align	4, 0x90
	.type	_Z11min_elementPiS_,@function
_Z11min_elementPiS_:                    # @_Z11min_elementPiS_
	.cfi_startproc
# %bb.0:
	mov	rax, rdi
	cmp	rdi, rsi
	je	.LBB0_18
# %bb.1:
	vpbroadcastd	ymm0, dword ptr [rax]
	mov	r8, rax
	and	r8, -32
	mov	r9, rsi
	and	r9, -32
	mov	edi, eax
	shr	edi, 2
	and	edi, 7
	dec	edi
	cmp	r8, r9
	je	.LBB0_2
# %bb.3:
	vmovd	xmm1, edi
	vpbroadcastd	ymm1, xmm1
	vmovdqa	ymm4, ymmword ptr [rip + .LCPI0_0] # ymm4 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm1, ymm4, ymm1
	vpblendvb	ymm1, ymm0, ymmword ptr [r8], ymm1
	vpminsd	ymm2, ymm0, ymm1
	vpcmpgtd	ymm1, ymm0, ymm1
	vpand	ymm1, ymm1, ymmword ptr [rip + .LCPI0_0]
	lea	rdi, [r8 + 32]
	cmp	rdi, r9
	je	.LBB0_4
# %bb.5:
	mov	ecx, 247
	vmovdqa	ymm6, ymmword ptr [rip + .LCPI0_1] # ymm6 = [38654705672,47244640266,55834574860,64424509454]
	vpxor	xmm3, xmm3, xmm3
	vmovdqa	ymm5, ymmword ptr [rip + .LCPI0_3] # ymm5 = [255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0,255,0,0,0]
	jmp	.LBB0_6
	.p2align	4, 0x90
.LBB0_12:                               #   in Loop: Header=BB0_6 Depth=1
	mov	r8, rdi
	mov	ecx, 255
	vmovdqa	ymm6, ymm4
	cmp	rdi, r9
	je	.LBB0_13
.LBB0_6:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_8 Depth 2
	mov	rdx, r9
	sub	rdx, rdi
	sar	rdx, 2
	cmp	rdx, rcx
	cmovg	rdx, rcx
	test	rdx, rdx
	je	.LBB0_10
# %bb.7:                                #   in Loop: Header=BB0_6 Depth=1
	lea	rcx, [rdi + 4*rdx]
	.p2align	4, 0x90
.LBB0_8:                                #   Parent Loop BB0_6 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	vmovdqa	ymm7, ymmword ptr [rdi]
	vpcmpgtd	ymm8, ymm2, ymm7
	vpminsd	ymm2, ymm2, ymm7
	vpblendvb	ymm1, ymm1, ymm6, ymm8
	vpbroadcastd	ymm7, dword ptr [rip + .LCPI0_2] # ymm7 = [8,8,8,8,8,8,8,8]
	vpaddd	ymm6, ymm6, ymm7
	add	rdi, 32
	cmp	rcx, rdi
	jne	.LBB0_8
# %bb.9:                                #   in Loop: Header=BB0_6 Depth=1
	mov	rdi, rcx
.LBB0_10:                               #   in Loop: Header=BB0_6 Depth=1
	vpcmpgtd	ymm6, ymm0, ymm2
	vmovmskps	ecx, ymm6
	test	ecx, ecx
	je	.LBB0_12
# %bb.11:                               #   in Loop: Header=BB0_6 Depth=1
	vpminsd	ymm0, ymm0, ymm2
	vpermq	ymm3, ymm0, 78          # ymm3 = ymm0[2,3,0,1]
	vpminsd	ymm0, ymm0, ymm3
	vpshufd	ymm3, ymm0, 78          # ymm3 = ymm0[2,3,0,1,6,7,4,5]
	vpminsd	ymm0, ymm0, ymm3
	vpshufd	ymm3, ymm0, 177         # ymm3 = ymm0[1,0,3,2,5,4,7,6]
	vpminsd	ymm0, ymm3, ymm0
	vpcmpeqd	ymm3, ymm0, ymm2
	vpand	ymm1, ymm1, ymm3
	vpandn	ymm3, ymm3, ymm5
	vpor	ymm3, ymm3, ymm1
	mov	rax, r8
	vmovdqa	ymm1, ymm3
	jmp	.LBB0_12
.LBB0_2:
	vmovdqa	ymm4, ymmword ptr [rip + .LCPI0_0] # ymm4 = [0,1,2,3,4,5,6,7]
	vpxor	xmm3, xmm3, xmm3
                                        # implicit-def: $ymm1
	vmovdqa	ymm2, ymm0
	jmp	.LBB0_14
.LBB0_4:
	vmovdqa	ymm4, ymmword ptr [rip + .LCPI0_1] # ymm4 = [38654705672,47244640266,55834574860,64424509454]
	vpxor	xmm3, xmm3, xmm3
.LBB0_13:
	mov	edi, -1
	cmp	r9, rsi
	je	.LBB0_15
.LBB0_14:
	mov	rcx, r9
	sub	rcx, rsi
	add	rcx, 32
	shr	rcx, 2
	vmovd	xmm5, edi
	vpbroadcastd	ymm5, xmm5
	mov	edx, 8
	sub	edx, ecx
	vmovd	xmm6, edx
	vpbroadcastd	ymm6, xmm6
	vmovdqa	ymm7, ymmword ptr [rip + .LCPI0_0] # ymm7 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm5, ymm7, ymm5
	vpcmpgtd	ymm6, ymm6, ymm7
	vpand	ymm5, ymm5, ymm6
	vpblendvb	ymm5, ymm2, ymmword ptr [r9], ymm5
	vpcmpgtd	ymm6, ymm2, ymm5
	vpminsd	ymm2, ymm2, ymm5
	vpblendvb	ymm1, ymm1, ymm4, ymm6
.LBB0_15:
	vpcmpgtd	ymm4, ymm0, ymm2
	vmovmskps	ecx, ymm4
	test	ecx, ecx
	je	.LBB0_17
# %bb.16:
	vpminsd	ymm0, ymm0, ymm2
	vpermq	ymm3, ymm0, 78          # ymm3 = ymm0[2,3,0,1]
	vpminsd	ymm0, ymm0, ymm3
	vpshufd	ymm3, ymm0, 78          # ymm3 = ymm0[2,3,0,1,6,7,4,5]
	vpminsd	ymm0, ymm0, ymm3
	vpshufd	ymm3, ymm0, 177         # ymm3 = ymm0[1,0,3,2,5,4,7,6]
	vpminsd	ymm0, ymm3, ymm0
	vpcmpeqd	ymm0, ymm0, ymm2
	vpand	ymm1, ymm1, ymm0
	vpandn	ymm0, ymm0, ymmword ptr [rip + .LCPI0_3]
	vpor	ymm3, ymm0, ymm1
	mov	rax, r8
.LBB0_17:
	vpermq	ymm0, ymm3, 78          # ymm0 = ymm3[2,3,0,1]
	vpminud	ymm0, ymm0, ymm3
	vpshufd	ymm1, ymm0, 78          # ymm1 = ymm0[2,3,0,1,6,7,4,5]
	vpminud	ymm0, ymm0, ymm1
	vpshufd	xmm1, xmm0, 177         # xmm1 = xmm0[1,0,3,2]
	vpminud	xmm0, xmm1, xmm0
	vmovd	ecx, xmm0
	lea	rax, [rax + 4*rcx]
.LBB0_18:
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
