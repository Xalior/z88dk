;
;       Z88dk Generic Floating Point Math Library
;
;       set flags per FA - ( bc ix de )
;
;       $Id: compare.asm,v 1.2 2012-04-17 16:37:46 stefano Exp $:

		XLIB	compare

		LIB	sgn

		XREF	setflgs
		XREF	fa

.COMPARE 
	LD     A,B
        OR      A
        JP      Z,SGN           ;bc ix de = 0, so
;                               sign of FA is result
        CALL    SGN
        LD      A,C
        JP      Z,SETFLGS       ;FA = 0, so sign of
;                               -(bc ix de) is result
        LD      HL,FA+4
        XOR     (HL)
        LD      A,C
        JP      M,SETFLGS       ;operands have opposite
;                               signs, so result is sign
;                               of -(bc ix de)

        CALL    CPFRAC
        RRA                     ;recover cy bit
        XOR     C       ;reverse sign if numbers are negative
        JP      SETFLGS

.CPFRAC INC     HL      ;compare  bc ix de  to (HL)
        LD      A,B
        CP      (HL)
        RET     NZ
        DEC     HL
        LD      A,C
        CP      (HL)
        RET     NZ
        DEC     HL
        LD      A,IXH
        CP      (HL)
        RET     NZ
        DEC     HL
		LD      A,IXL
        CP      (HL)
        RET     NZ
        DEC     HL
        LD      A,D
        CP      (HL)
        RET     NZ
        DEC     HL
        LD      A,E
        SUB     (HL)
        RET     NZ
        POP     HL      ;return zero to program
        RET             ;that called "COMPARE"


