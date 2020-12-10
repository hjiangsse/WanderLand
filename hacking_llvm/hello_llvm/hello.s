	.text
	.syntax unified
	.eabi_attribute	67, "2.09"	@ Tag_conformance
	.eabi_attribute	6, 6	@ Tag_CPU_arch
	.eabi_attribute	8, 1	@ Tag_ARM_ISA_use
	.eabi_attribute	9, 1	@ Tag_THUMB_ISA_use
	.fpu	vfpv2
	.eabi_attribute	34, 1	@ Tag_CPU_unaligned_access
	.eabi_attribute	17, 1	@ Tag_ABI_PCS_GOT_use
	.eabi_attribute	20, 1	@ Tag_ABI_FP_denormal
	.eabi_attribute	21, 1	@ Tag_ABI_FP_exceptions
	.eabi_attribute	23, 3	@ Tag_ABI_FP_number_model
	.eabi_attribute	24, 1	@ Tag_ABI_align_needed
	.eabi_attribute	25, 1	@ Tag_ABI_align_preserved
	.eabi_attribute	28, 1	@ Tag_ABI_VFP_args
	.eabi_attribute	38, 1	@ Tag_ABI_FP_16bit_format
	.eabi_attribute	18, 4	@ Tag_ABI_PCS_wchar_t
	.eabi_attribute	26, 2	@ Tag_ABI_enum_size
	.eabi_attribute	14, 0	@ Tag_ABI_PCS_R9_use
	.file	"hello.c"
	.globl	main                    @ -- Begin function main
	.p2align	2
	.type	main,%function
	.code	32                      @ @main
main:
	.fnstart
@ %bb.0:
	.save	{r11, lr}
	push	{r11, lr}
	.setfp	r11, sp
	mov	r11, sp
	ldr	r0, .LCPI0_0
	bl	puts
	mov	r0, #0
	pop	{r11, pc}
	.p2align	2
@ %bb.1:
.LCPI0_0:
	.long	.Lstr
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cantunwind
	.fnend
                                        @ -- End function
	.type	.Lstr,%object           @ @str
	.section	.rodata.str1.16,"aMS",%progbits,1
	.p2align	4
.Lstr:
	.asciz	"This is a hello world!"
	.size	.Lstr, 23


	.ident	"clang version 7.0.1-8+rpi3+deb10u2 (tags/RELEASE_701/final)"
	.section	".note.GNU-stack","",%progbits
	.eabi_attribute	30, 1	@ Tag_ABI_optimization_goals
