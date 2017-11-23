	.file	"program.c"
	.globl	msg
	.data
	.align 32
	.type	msg, @object
	.size	msg, 357
msg:
	.ascii	"Switch statements are often implemented using a switch table"
	.ascii	" that consists\nof pointers to code that "
	.string	"are indexed by the value of the integer being\ntested.  In this assignment, you you will need to decode the switch table to\nfind out the value that will unlock the level.  The assembly output of the\nprogram is in 3.06_switch.s for your viewing convenience\n\n"
	.section	.rodata
.LC0:
	.string	"%s"
	.text
	.globl	print_msg
	.type	print_msg, @function
print_msg:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$msg, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	print_msg, .-print_msg
	.section	.rodata
.LC1:
	.string	"Enter the password: "
.LC2:
	.string	"%d"
.LC3:
	.string	"Try again."
.LC4:
	.string	"Good Job."
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$0, %eax
	call	print_msg
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	leaq	-4(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	-4(%rbp), %eax
	subl	$44098, %eax
	cmpl	$4, %eax
	ja	.L3
	movl	%eax, %eax
	movq	.L5(,%rax,8), %rax
	jmp	*%rax
	.section	.rodata
	.align 8
	.align 4
.L5:
	.quad	.L4
	.quad	.L6
	.quad	.L7
	.quad	.L6
	.quad	.L4
	.text
.L4:
	movl	$.LC3, %edi
	call	puts
	jmp	.L8
.L6:
	movl	$.LC3, %edi
	call	puts
	jmp	.L8
.L7:
	movl	$.LC4, %edi
	call	puts
	jmp	.L8
.L3:
	movl	$.LC3, %edi
	call	puts
.L8:
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
