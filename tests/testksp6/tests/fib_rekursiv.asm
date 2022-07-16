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
	popl	0
	pushl	0
	call	_fib_rekursiv
	drop	1
	pushr
	popl	1
	pushl	1
	call	_writeInteger
	drop	1
	pushc	10
	call	_writeCharacter
	drop	1
__0:
	rsf
	ret

//
// Integer fib_rekursiv(Integer)
//
_fib_rekursiv:
	asf	0
	pushl	-3
	pushc	3
	lt
	brf	__2
	pushc	1
	popr
	jmp	__1
	jmp	__3
__2:
	pushl	-3
	pushc	1
	sub
	call	_fib_rekursiv
	drop	1
	pushr
	pushl	-3
	pushc	2
	sub
	call	_fib_rekursiv
	drop	1
	pushr
	add
	popr
	jmp	__1
__3:
__1:
	rsf
	ret
