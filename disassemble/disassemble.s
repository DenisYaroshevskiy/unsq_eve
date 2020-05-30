	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5               # -- Begin function _Z6reducePKcS0_
.LCPI0_0:
	.byte	1                       # 0x1
	.byte	2                       # 0x2
	.byte	3                       # 0x3
	.byte	4                       # 0x4
	.byte	5                       # 0x5
	.byte	6                       # 0x6
	.byte	7                       # 0x7
	.byte	8                       # 0x8
	.byte	9                       # 0x9
	.byte	10                      # 0xa
	.byte	11                      # 0xb
	.byte	12                      # 0xc
	.byte	13                      # 0xd
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	16                      # 0x10
	.byte	17                      # 0x11
	.byte	18                      # 0x12
	.byte	19                      # 0x13
	.byte	20                      # 0x14
	.byte	21                      # 0x15
	.byte	22                      # 0x16
	.byte	23                      # 0x17
	.byte	24                      # 0x18
	.byte	25                      # 0x19
	.byte	26                      # 0x1a
	.byte	27                      # 0x1b
	.byte	28                      # 0x1c
	.byte	29                      # 0x1d
	.byte	30                      # 0x1e
	.byte	31                      # 0x1f
	.byte	32                      # 0x20
.LCPI0_1:
	.byte	0                       # 0x0
	.byte	1                       # 0x1
	.byte	2                       # 0x2
	.byte	3                       # 0x3
	.byte	4                       # 0x4
	.byte	5                       # 0x5
	.byte	6                       # 0x6
	.byte	7                       # 0x7
	.byte	8                       # 0x8
	.byte	9                       # 0x9
	.byte	10                      # 0xa
	.byte	11                      # 0xb
	.byte	12                      # 0xc
	.byte	13                      # 0xd
	.byte	14                      # 0xe
	.byte	15                      # 0xf
	.byte	16                      # 0x10
	.byte	17                      # 0x11
	.byte	18                      # 0x12
	.byte	19                      # 0x13
	.byte	20                      # 0x14
	.byte	21                      # 0x15
	.byte	22                      # 0x16
	.byte	23                      # 0x17
	.byte	24                      # 0x18
	.byte	25                      # 0x19
	.byte	26                      # 0x1a
	.byte	27                      # 0x1b
	.byte	28                      # 0x1c
	.byte	29                      # 0x1d
	.byte	30                      # 0x1e
	.byte	31                      # 0x1f
	.text
	.globl	_Z6reducePKcS0_
	.p2align	4, 0x90
	.type	_Z6reducePKcS0_,@function
_Z6reducePKcS0_:                        # @_Z6reducePKcS0_
.L_Z6reducePKcS0_$local:
	.cfi_startproc
# %bb.0:
	mov	rcx, rdi
	and	rcx, -32
	mov	rax, rsi
	and	rax, -32
	and	edi, 31
	cmp	rcx, rax
	je	.LBB0_1
# %bb.2:
	vmovd	xmm0, edi
	vpbroadcastb	ymm0, xmm0
	vmovdqa	ymm1, ymmword ptr [rip + .LCPI0_0] # ymm1 = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32]
	vpsubusb	ymm0, ymm1, ymm0
	vpxor	xmm1, xmm1, xmm1
	vpcmpeqb	ymm0, ymm0, ymm1
	vpandn	ymm0, ymm0, ymmword ptr [rcx]
	vextracti128	xmm4, ymm0, 1
	vpshufd	xmm1, xmm0, 78          # xmm1 = xmm0[2,3,0,1]
	vpmovsxbd	ymm3, xmm0
	vpmovsxbd	ymm1, xmm1
	vpmovsxbd	ymm2, xmm4
	vpshufd	xmm0, xmm4, 78          # xmm0 = xmm4[2,3,0,1]
	vpmovsxbd	ymm0, xmm0
	add	rcx, 32
	cmp	rcx, rax
	je	.LBB0_4
	.p2align	4, 0x90
.LBB0_3:                                # =>This Inner Loop Header: Depth=1
	vpmovsxbd	ymm4, qword ptr [rcx]
	vpbroadcastq	xmm5, qword ptr [rcx + 8]
	vpaddd	ymm3, ymm3, ymm4
	vpmovsxbd	ymm4, xmm5
	vpaddd	ymm1, ymm1, ymm4
	vpmovsxbd	ymm4, qword ptr [rcx + 16]
	vpaddd	ymm2, ymm2, ymm4
	vpbroadcastq	xmm4, qword ptr [rcx + 24]
	vpmovsxbd	ymm4, xmm4
	vpaddd	ymm0, ymm0, ymm4
	add	rcx, 32
	cmp	rax, rcx
	jne	.LBB0_3
.LBB0_4:
	cmp	rax, rsi
	je	.LBB0_7
# %bb.5:
	xor	edi, edi
	jmp	.LBB0_6
.LBB0_1:
	vpxor	xmm0, xmm0, xmm0
	vpxor	xmm2, xmm2, xmm2
	vpxor	xmm1, xmm1, xmm1
	vpxor	xmm3, xmm3, xmm3
.LBB0_6:
	sub	esi, eax
	vmovd	xmm4, edi
	vpbroadcastb	ymm4, xmm4
	dec	sil
	vmovd	xmm5, esi
	vpbroadcastb	ymm5, xmm5
	vmovdqa	ymm6, ymmword ptr [rip + .LCPI0_0] # ymm6 = [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32]
	vpsubusb	ymm4, ymm6, ymm4
	vpxor	xmm6, xmm6, xmm6
	vpcmpeqb	ymm4, ymm4, ymm6
	vmovdqa	ymm6, ymmword ptr [rip + .LCPI0_1] # ymm6 = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31]
	vpcmpgtb	ymm5, ymm6, ymm5
	vpor	ymm4, ymm4, ymm5
	vpandn	ymm4, ymm4, ymmword ptr [rax]
	vextracti128	xmm5, ymm4, 1
	vpshufd	xmm6, xmm4, 78          # xmm6 = xmm4[2,3,0,1]
	vpmovsxbd	ymm4, xmm4
	vpaddd	ymm3, ymm3, ymm4
	vpmovsxbd	ymm4, xmm6
	vpaddd	ymm1, ymm1, ymm4
	vpmovsxbd	ymm4, xmm5
	vpaddd	ymm2, ymm2, ymm4
	vpshufd	xmm4, xmm5, 78          # xmm4 = xmm5[2,3,0,1]
	vpmovsxbd	ymm4, xmm4
	vpaddd	ymm0, ymm0, ymm4
.LBB0_7:
	vpaddd	ymm2, ymm2, ymm3
	vpaddd	ymm0, ymm0, ymm1
	vpaddd	ymm0, ymm0, ymm2
	vpermq	ymm1, ymm0, 78          # ymm1 = ymm0[2,3,0,1]
	vpaddd	ymm0, ymm0, ymm1
	vpshufd	ymm1, ymm0, 78          # ymm1 = ymm0[2,3,0,1,6,7,4,5]
	vpaddd	xmm0, xmm0, xmm1
	vpshufd	xmm1, xmm0, 229         # xmm1 = xmm0[1,1,2,3]
	vpaddd	xmm0, xmm1, xmm0
	vmovd	eax, xmm0
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z6reducePKcS0_, .Lfunc_end0-_Z6reducePKcS0_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
