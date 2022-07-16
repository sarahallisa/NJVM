_start:
    pushc 2
    pushc 2
    eq
    brt _writeCharacter

_writeCharacter:
    wrchr
    ret
