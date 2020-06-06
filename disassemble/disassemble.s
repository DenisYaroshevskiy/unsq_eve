	.text
	.intel_syntax noprefix
	.file	"disassemble.cc"
	.section	.rodata.cst32,"aM",@progbits,32
	.p2align	5               # -- Begin function _Z22inclusive_scan_inplacePcS_
.LCPI0_0:
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
.LCPI0_2:
	.byte	15                      # 0xf
	.byte	15                      # 0xf
	.byte	15                      # 0xf
	.byte	15                      # 0xf
	.byte	15                      # 0xf
	.byte	15                      # 0xf
	.byte	15                      # 0xf
	.byte	15                      # 0xf
	.zero	1
	.zero	1
	.zero	1
	.zero	1
	.zero	1
	.zero	1
	.zero	1
	.zero	1
	.byte	15                      # 0xf
	.byte	15                      # 0xf
	.byte	15                      # 0xf
	.byte	15                      # 0xf
	.byte	15                      # 0xf
	.byte	15                      # 0xf
	.byte	15                      # 0xf
	.byte	15                      # 0xf
	.zero	1
	.zero	1
	.zero	1
	.zero	1
	.zero	1
	.zero	1
	.zero	1
	.zero	1
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4
.LCPI0_1:
	.zero	16,15
	.text
	.globl	_Z22inclusive_scan_inplacePcS_
	.p2align	4, 0x90
	.type	_Z22inclusive_scan_inplacePcS_,@function
_Z22inclusive_scan_inplacePcS_:         # @_Z22inclusive_scan_inplacePcS_
.L_Z22inclusive_scan_inplacePcS_$local:
	.cfi_startproc
# %bb.0:
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset rbp, -16
	mov	rbp, rsp
	.cfi_def_cfa_register rbp
	push	r15
	push	r14
	push	rbx
	and	rsp, -32
	sub	rsp, 96
	.cfi_offset rbx, -40
	.cfi_offset r14, -32
	.cfi_offset r15, -24
	mov	r14, rsi
	mov	rbx, rdi
	and	rbx, -32
	mov	r15, rsi
	and	r15, -32
	and	edi, 31
	cmp	rbx, r15
	je	.LBB0_1
# %bb.2:
	lea	eax, [rdi - 1]
	vmovd	xmm0, eax
	vpbroadcastb	ymm0, xmm0
	vmovdqa	ymm1, ymmword ptr [rip + .LCPI0_0] # ymm1 = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31]
	vpcmpgtb	ymm0, ymm1, ymm0
	vpand	ymm0, ymm0, ymmword ptr [rbx]
	vpslldq	ymm1, ymm0, 1           # ymm1 = zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14],zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27,28,29,30]
	vpaddb	ymm0, ymm1, ymm0
	vpslldq	ymm1, ymm0, 2           # ymm1 = zero,zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11,12,13],zero,zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddb	ymm0, ymm1, ymm0
	vpslldq	ymm1, ymm0, 4           # ymm1 = zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddb	ymm0, ymm1, ymm0
	vpslldq	ymm1, ymm0, 8           # ymm1 = zero,zero,zero,zero,zero,zero,zero,zero,ymm0[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm0[16,17,18,19,20,21,22,23]
	vpaddb	ymm0, ymm1, ymm0
	vpshufb	xmm1, xmm0, xmmword ptr [rip + .LCPI0_1] # xmm1 = xmm0[15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15]
	vperm2i128	ymm1, ymm1, ymm1, 40 # ymm1 = zero,zero,ymm1[0,1]
	vpaddb	ymm0, ymm0, ymm1
	vmovdqa	ymmword ptr [rsp + 32], ymm0 # 32-byte Spill
	vmovdqa	ymmword ptr [rsp], ymm0
	mov	edx, 32
	sub	rdx, rdi
	lea	rax, [rbx + rdi]
	lea	rsi, [rsp + rdi]
	mov	rdi, rax
	vzeroupper
	call	memcpy
	vmovdqa	ymm0, ymmword ptr [rsp + 32] # 32-byte Reload
	vpshufb	ymm0, ymm0, ymmword ptr [rip + .LCPI0_2] # ymm0 = ymm0[15,15,15,15,15,15,15,15,u,u,u,u,u,u,u,u,31,31,31,31,31,31,31,31,u,u,u,u,u,u,u,u]
	vpermq	ymm0, ymm0, 170         # ymm0 = ymm0[2,2,2,2]
	add	rbx, 32
	cmp	rbx, r15
	je	.LBB0_5
# %bb.3:
	vmovdqa	xmm1, xmmword ptr [rip + .LCPI0_1] # xmm1 = [15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15]
	vmovdqa	ymm2, ymmword ptr [rip + .LCPI0_2] # ymm2 = <15,15,15,15,15,15,15,15,u,u,u,u,u,u,u,u,15,15,15,15,15,15,15,15,u,u,u,u,u,u,u,u>
	.p2align	4, 0x90
.LBB0_4:                                # =>This Inner Loop Header: Depth=1
	vmovdqa	ymm3, ymmword ptr [rbx]
	vpslldq	ymm4, ymm3, 1           # ymm4 = zero,ymm3[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14],zero,ymm3[16,17,18,19,20,21,22,23,24,25,26,27,28,29,30]
	vpaddb	ymm3, ymm4, ymm3
	vpslldq	ymm4, ymm3, 2           # ymm4 = zero,zero,ymm3[0,1,2,3,4,5,6,7,8,9,10,11,12,13],zero,zero,ymm3[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddb	ymm3, ymm4, ymm3
	vpslldq	ymm4, ymm3, 4           # ymm4 = zero,zero,zero,zero,ymm3[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm3[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddb	ymm3, ymm4, ymm3
	vpslldq	ymm4, ymm3, 8           # ymm4 = zero,zero,zero,zero,zero,zero,zero,zero,ymm3[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm3[16,17,18,19,20,21,22,23]
	vpaddb	ymm3, ymm4, ymm3
	vpshufb	xmm4, xmm3, xmm1
	vperm2i128	ymm4, ymm4, ymm4, 40 # ymm4 = zero,zero,ymm4[0,1]
	vpaddb	ymm0, ymm3, ymm0
	vpaddb	ymm0, ymm0, ymm4
	vmovdqa	ymmword ptr [rbx], ymm0
	vpshufb	ymm0, ymm0, ymm2
	vpermq	ymm0, ymm0, 170         # ymm0 = ymm0[2,2,2,2]
	add	rbx, 32
	cmp	r15, rbx
	jne	.LBB0_4
.LBB0_5:
	cmp	r15, r14
	je	.LBB0_8
# %bb.6:
	xor	edi, edi
	jmp	.LBB0_7
.LBB0_1:
	vpxor	xmm0, xmm0, xmm0
.LBB0_7:
	mov	rax, r15
	sub	rax, r14
	lea	rcx, [rax + 32]
	lea	edx, [rdi - 1]
	vmovd	xmm1, edx
	vpbroadcastb	ymm1, xmm1
	mov	dl, 32
	sub	dl, cl
	vmovd	xmm2, edx
	vpbroadcastb	ymm2, xmm2
	vmovdqa	ymm3, ymmword ptr [rip + .LCPI0_0] # ymm3 = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31]
	vpcmpgtb	ymm1, ymm3, ymm1
	vpcmpgtb	ymm2, ymm2, ymm3
	vpand	ymm1, ymm1, ymm2
	vpand	ymm1, ymm1, ymmword ptr [r15]
	vpslldq	ymm2, ymm1, 1           # ymm2 = zero,ymm1[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14],zero,ymm1[16,17,18,19,20,21,22,23,24,25,26,27,28,29,30]
	vpaddb	ymm1, ymm2, ymm1
	vpslldq	ymm2, ymm1, 2           # ymm2 = zero,zero,ymm1[0,1,2,3,4,5,6,7,8,9,10,11,12,13],zero,zero,ymm1[16,17,18,19,20,21,22,23,24,25,26,27,28,29]
	vpaddb	ymm1, ymm2, ymm1
	vpslldq	ymm2, ymm1, 4           # ymm2 = zero,zero,zero,zero,ymm1[0,1,2,3,4,5,6,7,8,9,10,11],zero,zero,zero,zero,ymm1[16,17,18,19,20,21,22,23,24,25,26,27]
	vpaddb	ymm1, ymm2, ymm1
	vpslldq	ymm2, ymm1, 8           # ymm2 = zero,zero,zero,zero,zero,zero,zero,zero,ymm1[0,1,2,3,4,5,6,7],zero,zero,zero,zero,zero,zero,zero,zero,ymm1[16,17,18,19,20,21,22,23]
	vpaddb	ymm1, ymm2, ymm1
	vpshufb	xmm2, xmm1, xmmword ptr [rip + .LCPI0_1] # xmm2 = xmm1[15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15]
	vperm2i128	ymm2, ymm2, ymm2, 40 # ymm2 = zero,zero,ymm2[0,1]
	vpaddb	ymm0, ymm1, ymm0
	vpaddb	ymm0, ymm0, ymm2
	vmovdqa	ymmword ptr [rsp], ymm0
	add	rax, rdi
	add	rax, 32
	mov	edx, 32
	sub	rdx, rax
	add	r15, rdi
	lea	rsi, [rsp + rdi]
	mov	rdi, r15
	vzeroupper
	call	memcpy
.LBB0_8:
	lea	rsp, [rbp - 24]
	pop	rbx
	pop	r14
	pop	r15
	pop	rbp
	.cfi_def_cfa rsp, 8
	vzeroupper
	ret
.Lfunc_end0:
	.size	_Z22inclusive_scan_inplacePcS_, .Lfunc_end0-_Z22inclusive_scan_inplacePcS_
	.cfi_endproc
                                        # -- End function
	.section	".linker-options","e",@llvm_linker_options
	.ident	"clang version 11.0.0 (https://github.com/llvm/llvm-project.git f794808bb9ec06966a67fe33d41a13b9601768f8)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym __gxx_personality_v0
