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
	.quad	73014444048             # 0x1100000010
	.quad	81604378642             # 0x1300000012
	.quad	90194313236             # 0x1500000014
	.quad	98784247830             # 0x1700000016
.LCPI0_7:
	.quad	107374182424            # 0x1900000018
	.quad	115964117018            # 0x1b0000001a
	.quad	124554051612            # 0x1d0000001c
	.quad	133143986206            # 0x1f0000001e
	.section	.rodata.cst4,"aM",@progbits,4
	.p2align	2
.LCPI0_2:
	.long	8                       # 0x8
.LCPI0_3:
	.long	16                      # 0x10
.LCPI0_4:
	.long	24                      # 0x18
.LCPI0_5:
	.long	255                     # 0xff
.LCPI0_8:
	.long	32                      # 0x20
	.text
	.globl	_Z11min_elementPiS_
	.p2align	4, 0x90
	.type	_Z11min_elementPiS_,@function
_Z11min_elementPiS_:                    # @_Z11min_elementPiS_
	.cfi_startproc
# %bb.0:
	mov	rax, rdi
	cmp	rdi, rsi
	je	.LBB0_29
# %bb.1:
	vpbroadcastd	ymm0, dword ptr [rax]
	mov	rcx, rax
	and	rcx, -32
	mov	r9, rsi
	and	r9, -32
	mov	edx, eax
	shr	edx, 2
	and	edx, 7
	dec	edx
	cmp	rcx, r9
	je	.LBB0_2
# %bb.3:
	vmovd	xmm1, edx
	vpbroadcastd	ymm1, xmm1
	vmovdqa	ymm14, ymmword ptr [rip + .LCPI0_0] # ymm14 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm1, ymm14, ymm1
	vpblendvb	ymm1, ymm0, ymmword ptr [rcx], ymm1
	vpminsd	ymm10, ymm0, ymm1
	vpcmpgtd	ymm1, ymm0, ymm1
	vpand	ymm1, ymm1, ymmword ptr [rip + .LCPI0_0]
	lea	r10, [rcx + 32]
	cmp	r10, r9
	je	.LBB0_4
# %bb.5:
	vmovdqa	ymm9, ymmword ptr [rip + .LCPI0_1] # ymm9 = [38654705672,47244640266,55834574860,64424509454]
	vxorps	xmm2, xmm2, xmm2
	vmovups	ymmword ptr [rsp - 88], ymm2 # 32-byte Spill
	vbroadcastss	ymm2, dword ptr [rip + .LCPI0_2] # ymm2 = [8,8,8,8,8,8,8,8]
	vmovups	ymmword ptr [rsp - 56], ymm2 # 32-byte Spill
	mov	r8d, 255
	vmovdqa	ymm6, ymm0
	vmovdqa	ymm8, ymm0
	vmovdqa	ymm7, ymm0
                                        # implicit-def: $ymm4
                                        # implicit-def: $ymm3
                                        # implicit-def: $ymm2
	jmp	.LBB0_6
	.p2align	4, 0x90
.LBB0_17:                               #   in Loop: Header=BB0_6 Depth=1
	mov	rcx, r10
	vmovdqa	ymm9, ymm14
	cmp	r10, r9
	je	.LBB0_18
.LBB0_6:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_11 Depth 2
                                        #       Child Loop BB0_15 Depth 3
	vmovdqa	ymm13, ymmword ptr [r10]
	vpminsd	ymm11, ymm10, ymm13
	vpcmpgtd	ymm10, ymm10, ymm13
	vpblendvb	ymm1, ymm1, ymm9, ymm10
	lea	rdx, [r10 + 32]
	vpaddd	ymm13, ymm9, ymmword ptr [rsp - 56] # 32-byte Folded Reload
	cmp	rdx, r9
	je	.LBB0_19
# %bb.7:                                #   in Loop: Header=BB0_6 Depth=1
	vmovdqa	ymm15, ymmword ptr [r10 + 32]
	vpminsd	ymm10, ymm11, ymm15
	vpcmpgtd	ymm11, ymm11, ymm15
	vpblendvb	ymm1, ymm1, ymm13, ymm11
	lea	rdx, [r10 + 64]
	vpbroadcastd	ymm11, dword ptr [rip + .LCPI0_3] # ymm11 = [16,16,16,16,16,16,16,16]
	vpaddd	ymm13, ymm9, ymm11
	cmp	rdx, r9
	je	.LBB0_20
# %bb.8:                                #   in Loop: Header=BB0_6 Depth=1
	vmovdqa	ymm15, ymmword ptr [r10 + 64]
	vpminsd	ymm11, ymm10, ymm15
	vpcmpgtd	ymm10, ymm10, ymm15
	vpblendvb	ymm1, ymm1, ymm13, ymm10
	lea	rdx, [r10 + 96]
	vpbroadcastd	ymm10, dword ptr [rip + .LCPI0_4] # ymm10 = [24,24,24,24,24,24,24,24]
	vpaddd	ymm9, ymm9, ymm10
	cmp	rdx, r9
	je	.LBB0_21
# %bb.9:                                #   in Loop: Header=BB0_6 Depth=1
	vmovdqa	ymm13, ymmword ptr [r10 + 96]
	vpminsd	ymm10, ymm11, ymm13
	vpcmpgtd	ymm11, ymm11, ymm13
	vpblendvb	ymm1, ymm1, ymm9, ymm11
	sub	r10, -128
	jmp	.LBB0_11
	.p2align	4, 0x90
.LBB0_10:                               #   in Loop: Header=BB0_11 Depth=2
	shl	rdi, 7
	add	rdi, r10
	mov	rcx, r10
	mov	r10, rdi
	vmovdqa	ymm14, ymm5
.LBB0_11:                               #   Parent Loop BB0_6 Depth=1
                                        # =>  This Loop Header: Depth=2
                                        #       Child Loop BB0_15 Depth 3
	vpminsd	ymm9, ymm10, ymm8
	vpminsd	ymm11, ymm6, ymm7
	vpminsd	ymm9, ymm9, ymm11
	vpcmpgtd	ymm11, ymm0, ymm9
	vmovmskps	edx, ymm11
	test	edx, edx
	je	.LBB0_13
# %bb.12:                               #   in Loop: Header=BB0_11 Depth=2
	vpminsd	ymm0, ymm0, ymm9
	vpermq	ymm9, ymm0, 78          # ymm9 = ymm0[2,3,0,1]
	vpminsd	ymm0, ymm0, ymm9
	vpshufd	ymm9, ymm0, 78          # ymm9 = ymm0[2,3,0,1,6,7,4,5]
	vpminsd	ymm0, ymm0, ymm9
	vpshufd	ymm9, ymm0, 177         # ymm9 = ymm0[1,0,3,2,5,4,7,6]
	vpminsd	ymm0, ymm9, ymm0
	vpcmpeqd	ymm9, ymm10, ymm0
	vpand	ymm1, ymm9, ymm1
	vpbroadcastd	ymm11, dword ptr [rip + .LCPI0_5] # ymm11 = [255,255,255,255,255,255,255,255]
	vpandn	ymm9, ymm9, ymm11
	vpor	ymm1, ymm9, ymm1
	vpcmpeqd	ymm9, ymm0, ymm6
	vpand	ymm4, ymm9, ymm4
	vpandn	ymm9, ymm9, ymm11
	vpor	ymm4, ymm9, ymm4
	vpcmpeqd	ymm9, ymm8, ymm0
	vpand	ymm3, ymm9, ymm3
	vpandn	ymm9, ymm9, ymm11
	vpor	ymm3, ymm9, ymm3
	vpcmpeqd	ymm9, ymm0, ymm7
	vpand	ymm2, ymm9, ymm2
	vpandn	ymm9, ymm9, ymm11
	vpor	ymm2, ymm9, ymm2
	vpminud	ymm9, ymm1, ymm3
	vpminud	ymm11, ymm4, ymm2
	vpminud	ymm5, ymm9, ymm11
	vmovdqu	ymmword ptr [rsp - 88], ymm5 # 32-byte Spill
	mov	rax, rcx
.LBB0_13:                               #   in Loop: Header=BB0_11 Depth=2
	mov	rcx, r9
	sub	rcx, r10
	sar	rcx, 2
	cmp	rcx, 256
	cmovge	rcx, r8
	lea	rdi, [rcx + 31]
	cmp	rdi, 63
	jb	.LBB0_17
# %bb.14:                               #   in Loop: Header=BB0_11 Depth=2
	test	rcx, rcx
	cmovns	rdi, rcx
	sar	rdi, 5
	lea	rcx, [rdi - 1]
	mov	rdx, r10
	vmovdqa	ymm15, ymmword ptr [rip + .LCPI0_7] # ymm15 = [107374182424,115964117018,124554051612,133143986206]
	vmovdqa	ymm13, ymmword ptr [rip + .LCPI0_6] # ymm13 = [73014444048,81604378642,90194313236,98784247830]
	vmovdqa	ymm11, ymmword ptr [rip + .LCPI0_1] # ymm11 = [38654705672,47244640266,55834574860,64424509454]
	vmovdqa	ymm5, ymm14
	vmovdqa	ymm9, ymm14
	.p2align	4, 0x90
.LBB0_15:                               #   Parent Loop BB0_6 Depth=1
                                        #     Parent Loop BB0_11 Depth=2
                                        # =>    This Inner Loop Header: Depth=3
	vmovdqa	ymm12, ymmword ptr [rdx]
	vpcmpgtd	ymm14, ymm10, ymm12
	vpminsd	ymm10, ymm10, ymm12
	vmovdqa	ymm12, ymmword ptr [rdx + 32]
	vpblendvb	ymm1, ymm1, ymm9, ymm14
	vpcmpgtd	ymm14, ymm6, ymm12
	vpminsd	ymm6, ymm6, ymm12
	vmovdqa	ymm12, ymmword ptr [rdx + 64]
	vpblendvb	ymm4, ymm4, ymm11, ymm14
	vpcmpgtd	ymm14, ymm8, ymm12
	vpblendvb	ymm3, ymm3, ymm13, ymm14
	vmovdqa	ymm14, ymmword ptr [rdx + 96]
	vpminsd	ymm8, ymm8, ymm12
	vpcmpgtd	ymm12, ymm7, ymm14
	vpminsd	ymm7, ymm7, ymm14
	vpblendvb	ymm2, ymm2, ymm15, ymm12
	test	rcx, rcx
	je	.LBB0_10
# %bb.16:                               #   in Loop: Header=BB0_15 Depth=3
	vpbroadcastd	ymm12, dword ptr [rip + .LCPI0_8] # ymm12 = [32,32,32,32,32,32,32,32]
	vpaddd	ymm15, ymm15, ymm12
	vpaddd	ymm13, ymm13, ymm12
	vpaddd	ymm11, ymm11, ymm12
	vpaddd	ymm9, ymm9, ymm12
	dec	rcx
	sub	rdx, -128
	jmp	.LBB0_15
.LBB0_2:
	vmovdqa	ymm14, ymmword ptr [rip + .LCPI0_0] # ymm14 = [0,1,2,3,4,5,6,7]
	vpxor	xmm12, xmm12, xmm12
	vmovdqa	ymm6, ymm0
	vmovdqa	ymm8, ymm0
	vmovdqa	ymm7, ymm0
                                        # implicit-def: $ymm4
                                        # implicit-def: $ymm3
                                        # implicit-def: $ymm2
                                        # implicit-def: $ymm1
	vmovdqa	ymm9, ymm0
	jmp	.LBB0_25
.LBB0_4:
	vmovdqa	ymm14, ymmword ptr [rip + .LCPI0_1] # ymm14 = [38654705672,47244640266,55834574860,64424509454]
	vxorps	xmm2, xmm2, xmm2
	vmovups	ymmword ptr [rsp - 88], ymm2 # 32-byte Spill
	vmovdqa	ymm6, ymm0
	vmovdqa	ymm8, ymm0
	vmovdqa	ymm7, ymm0
                                        # implicit-def: $ymm4
                                        # implicit-def: $ymm3
                                        # implicit-def: $ymm2
	cmp	r9, rsi
	jne	.LBB0_24
	jmp	.LBB0_23
.LBB0_18:
	mov	rcx, r9
	cmp	r9, rsi
	jne	.LBB0_24
	jmp	.LBB0_23
.LBB0_19:
	vmovdqa	ymm10, ymm11
.LBB0_20:
	vmovdqa	ymm14, ymm13
	cmp	r9, rsi
	je	.LBB0_23
.LBB0_24:
	vmovdqu	ymm12, ymmword ptr [rsp - 88] # 32-byte Reload
	mov	edx, -1
	vmovdqa	ymm9, ymm10
.LBB0_25:
	mov	rdi, r9
	sub	rdi, rsi
	add	rdi, 32
	shr	rdi, 2
	vmovd	xmm5, edx
	vpbroadcastd	ymm10, xmm5
	mov	edx, 8
	sub	edx, edi
	vmovd	xmm5, edx
	vpbroadcastd	ymm5, xmm5
	vmovdqa	ymm11, ymmword ptr [rip + .LCPI0_0] # ymm11 = [0,1,2,3,4,5,6,7]
	vpcmpgtd	ymm10, ymm11, ymm10
	vpcmpgtd	ymm5, ymm5, ymm11
	vpand	ymm5, ymm10, ymm5
	vpblendvb	ymm5, ymm9, ymmword ptr [r9], ymm5
	vpminsd	ymm10, ymm9, ymm5
	vpcmpgtd	ymm5, ymm9, ymm5
	vpblendvb	ymm1, ymm1, ymm14, ymm5
	jmp	.LBB0_26
.LBB0_21:
	vmovdqa	ymm10, ymm11
	vmovdqa	ymm14, ymm9
	cmp	r9, rsi
	jne	.LBB0_24
.LBB0_23:
	vmovdqu	ymm12, ymmword ptr [rsp - 88] # 32-byte Reload
.LBB0_26:
	vpminsd	ymm5, ymm6, ymm7
	vpminsd	ymm5, ymm8, ymm5
	vpminsd	ymm5, ymm10, ymm5
	vpcmpgtd	ymm9, ymm0, ymm5
	vmovmskps	edx, ymm9
	test	edx, edx
	je	.LBB0_28
# %bb.27:
	vpminsd	ymm0, ymm0, ymm5
	vpermq	ymm5, ymm0, 78          # ymm5 = ymm0[2,3,0,1]
	vpminsd	ymm0, ymm0, ymm5
	vpshufd	ymm5, ymm0, 78          # ymm5 = ymm0[2,3,0,1,6,7,4,5]
	vpminsd	ymm0, ymm0, ymm5
	vpshufd	ymm5, ymm0, 177         # ymm5 = ymm0[1,0,3,2,5,4,7,6]
	vpminsd	ymm0, ymm5, ymm0
	vpcmpeqd	ymm5, ymm10, ymm0
	vpand	ymm1, ymm1, ymm5
	vpbroadcastd	ymm9, dword ptr [rip + .LCPI0_5] # ymm9 = [255,255,255,255,255,255,255,255]
	vpandn	ymm5, ymm5, ymm9
	vpor	ymm1, ymm5, ymm1
	vpcmpeqd	ymm5, ymm0, ymm6
	vpand	ymm4, ymm4, ymm5
	vpandn	ymm5, ymm5, ymm9
	vpor	ymm4, ymm5, ymm4
	vpcmpeqd	ymm5, ymm8, ymm0
	vpand	ymm3, ymm3, ymm5
	vpandn	ymm5, ymm5, ymm9
	vpor	ymm3, ymm5, ymm3
	vpminud	ymm1, ymm1, ymm3
	vpcmpeqd	ymm0, ymm0, ymm7
	vpand	ymm2, ymm2, ymm0
	vpandn	ymm0, ymm0, ymm9
	vpor	ymm0, ymm0, ymm2
	vpminud	ymm0, ymm4, ymm0
	vpminud	ymm12, ymm1, ymm0
	mov	rax, rcx
.LBB0_28:
	vpermq	ymm0, ymm12, 78         # ymm0 = ymm12[2,3,0,1]
	vpminud	ymm0, ymm12, ymm0
	vpshufd	ymm1, ymm0, 78          # ymm1 = ymm0[2,3,0,1,6,7,4,5]
	vpminud	ymm0, ymm0, ymm1
	vpshufd	xmm1, xmm0, 177         # xmm1 = xmm0[1,0,3,2]
	vpminud	xmm0, xmm1, xmm0
	vmovd	ecx, xmm0
	lea	rax, [rax + 4*rcx]
.LBB0_29:
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
