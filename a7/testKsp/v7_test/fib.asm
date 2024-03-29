//
// version
//
	.vers	6

//
// execution framework
//
__start:
	call	_main
	call	_exit
__stop:
	jmp	__stop

//
// Integer readInteger()
//
_readInteger:
	asf	0
	rdint
	popr
	rsf
	ret

//
// void writeInteger(Integer)
//
_writeInteger:
	asf	0
	pushl	-3
	wrint
	rsf
	ret

//
// Character readCharacter()
//
_readCharacter:
	asf	0
	rdchr
	popr
	rsf
	ret

//
// void writeCharacter(Character)
//
_writeCharacter:
	asf	0
	pushl	-3
	wrchr
	rsf
	ret

//
// Integer char2int(Character)
//
_char2int:
	asf	0
	pushl	-3
	popr
	rsf
	ret

//
// Character int2char(Integer)
//
_int2char:
	asf	0
	pushl	-3
	popr
	rsf
	ret

//
// void exit()
//
_exit:
	asf	0
	halt
	rsf
	ret

//
// void main()
//
_main:
	asf	2
	call	_readInteger
	pushr
	popl	1
	pushl	1
	call	_fib
	drop	1
	pushr
	popl	0
	pushl	0
	call	_writeInteger
	drop	1
	pushc	10
	call	_writeCharacter
	drop	1
__0:
	rsf
	ret

//
// Integer fib(Integer)
//
_fib:
	asf	3
	pushl	-3
	pushc	2
	lt
	brf	__2
	pushl	-3
	popr
	jmp	__1
__2:
	pushc	0
	popl	0
	pushc	1
	popl	1
	jmp	__4
__3:
	pushl	0
	pushl	1
	add
	popl	2
	pushl	1
	popl	0
	pushl	2
	popl	1
	pushl	-3
	pushc	1
	sub
	popl	-3
__4:
	pushl	-3
	pushc	1
	sub
	pushc	0
	gt
	brt	__3
__5:
	pushl	2
	popr
	jmp	__1
__1:
	rsf
	ret
