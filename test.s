#-----------------------------------------------------------------------------
# Created By: Aleksey Zakharov 301295506 
#-----------------------------------------------------------------------------
	.global main
	.data

x: .quad 0
y: .quad 0
z: .quad 0
w: .quad 0
s0: .ascii "n = %d\n"
s1: .ascii "printf"
symbol size: 8


	.text





id   tabid   name    type    scope   isArray arrSize isInited    i   b
5 0 main LABEL GLOBAL false -1 false -1 false
6 1 n INT LOCAL false -1 false -1 false
7 1 a INT LOCAL false -1 false -1 false
8 1 0 INT CONST false -1 false -1 false
9 2 n INT LOCAL false -1 false -1 false
10 2 1 INT CONST false -1 false -1 false
11 2 AddOp INT LOCAL false -1 false -1 false
14 1 2 INT CONST false -1 false -1 false
id   res   opcode   op1  op2   
1 5 LABEL -1 -1
2 7 ASSIGN 8 -1
3 5 LT 7 6
4 9 GE 7 6
5 11 ADD 7 10
6 9 ASSIGN 11 -1
7 7 ASSIGN 9 -1
8 3 GOTO -1 -1
9 -1 PARAM s0 -1
10 -1 PARAM 6 -1
11 -1 CALL s1 14
12 -1 RET 6 -1
id   parent   
0 -1
1 0
2 1
