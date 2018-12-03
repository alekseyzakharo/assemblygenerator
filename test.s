#-----------------------------------------------------------------------------
# Created By: Aleksey Zakharov 301295506 
#-----------------------------------------------------------------------------
	.global main
	.data

x: .quad 0
y: .quad 0
z: .quad 0
w: .quad 0
s0: .ascii "atoi"
s1: .ascii "a = %d\n"
s2: .ascii "printf"


	.text

main:
	mov	%rdi, -32(%rbp)
	mov	%rsi, -16(%rbp)
	mov	$1, %rax
	mov	$8, %rbx
	mul	%rbx
	mov	%rax, -80(%rbp)
	mov	-16(%rbp), %rbx
	mov	8(%rbx), %rax
	mov	%rax, -96(%rbp)
	mov	-96(%rbp), %rdi
	call s0
	mov	-112(%rbp), %rax
	mov	%rax, -64(%rbp)
	mov	$0, %rax
	mov	%rax, -48(%rbp)
L2:
	mov	-48(%rbp), %rax
	mov	-64(%rbp), %rbx
	cmp	%rax, %rbx
	jl L0
	mov	-48(%rbp), %rax
	mov	-64(%rbp), %rbx
	cmp	%rax, %rbx
	jge L1
L0:
	mov	-48(%rbp), %rax
	mov	$1, %rbx
	add	%rax, %rbx
	mov	%rbx, -144(%rbp)
	mov	-144(%rbp), %rax
	mov	%rax, -128(%rbp)
	mov	-128(%rbp), %rax
	mov	%rax, -48(%rbp)
	jmp	L2
L1:
	mov	$s1, %rdi
	mov	-48(%rbp), %rsi
	call s2
	mov	$1, %rax
	ret
	ret
