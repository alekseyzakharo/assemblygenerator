#-----------------------------------------------------------------------------
# Created By: Aleksey Zakharov 301295506 
#-----------------------------------------------------------------------------
	.global main
	.data

s0: .ascii "n = %d\n"
s1: .ascii "printf"




id   tabid   name    type    scope   isArray arrSize isInited    i   b
0 0 x INT GLOBAL false -1 false -1 false
1 0 y INT GLOBAL false -1 false -1 false
2 0 z INT GLOBAL false -1 false -1 false
3 0 0 INT CONST false -1 false -1 false
4 0 w INT GLOBAL false -1 false -1 false
5 0 main LABEL GLOBAL false -1 false -1 false
6 1 n INT LOCAL false -1 false -1 false
7 1 a INT LOCAL false -1 false -1 false
8 1 0 INT CONST false -1 false -1 false
9 2 n INT LOCAL false -1 false -1 false
10 2 1 INT CONST false -1 false -1 false
11 2 AddOp INT LOCAL false -1 false -1 false
12 1 "n = %d\n" STR CONST false -1 false -1 false
13 1 "printf" STR CONST false -1 false -1 false
14 1 2 INT CONST false -1 false -1 false
id   res   opcode   op1  op2   
0 4 ASSIGN 3 -1
1 5 LABEL -1 -1
2 7 ASSIGN 8 -1
3 5 LT 7 6
4 9 GE 7 6
5 11 ADD 7 10
6 9 ASSIGN 11 -1
7 7 ASSIGN 9 -1
8 3 GOTO -1 -1
9 -1 PARAM 12 -1
10 -1 PARAM 6 -1
11 -1 CALL 13 14
12 -1 RET 6 -1
13 -1 RET -1 -1
id   parent   
0 -1
1 0
2 1
