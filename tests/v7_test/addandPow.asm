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
	asf	3
	call	_readInteger
	pushr
	popl	0
	call	_readInteger
	pushr
	popl	1
	pushl	0
	pushl	1
	call	_addition
	drop	2
	pushr
	popl	2
	pushc	40
	call	_writeCharacter
	drop	1
	pushl	0
	call	_writeInteger
	drop	1
	pushc	43
	call	_writeCharacter
	drop	1
	pushl	1
	call	_writeInteger
	drop	1
	pushc	41
	call	_writeCharacter
	drop	1
	pushc	42
	call	_writeCharacter
	drop	1
	pushl	0
	pushl	1
	add
	call	_writeInteger
	drop	1
	pushc	61
	call	_writeCharacter
	drop	1
	pushl	2
	call	_writeInteger
	drop	1
	pushc	10
	call	_writeCharacter
	drop	1
__0:
	rsf
	ret

//
// Integer addition(Integer, Integer)
//
_addition:
	asf	0
	pushl	-4
	pushl	-3
	add
	call	_square
	drop	1
	pushr
	popr
	jmp	__1
__1:
	rsf
	ret

//
// Integer square(Integer)
//
_square:
	asf	0
	pushl	-3
	pushl	-3
	mul
	popr
	jmp	__2
__2:
	rsf
	ret
