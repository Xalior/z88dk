;
;       Z88dk Generic Floating Point Math Library
;
;	Shift c ix de b right by a
;
;       $Id: rshift_noaf.asm,v 1.1 2012-04-17 16:37:46 stefano Exp $:


		XLIB	rshift

		XDEF	rsh8


.RSHIFT LD      B,0
.RSH2   SUB     8
        JR      C,RSH4  ;c => 7 or fewer shifts remain
        LD      B,E     ;shift  c ix de b  right by 8...
        LD      E,D
        LD      D,IXL
        ;EX      AF,AF'
		PUSH    AF
        LD      A,IXH
        LD      IXL,A
        ;EX      AF,AF'
		POP     AF
        LD      IXH,C
        LD      C,0     ;...end of shifting
        JR      RSH2
;
.RSH4   ADD     A,9
        LD      L,A
.RSH6   XOR     A
        DEC     L
        RET     Z       ;z => requested shift is complete
        LD      A,C
.RSH8   RRA             ;shift  c ix de b  right by one...
        LD      C,A
        LD      A,IXH
        RRA
        LD      IXH,A
        LD      A,IXL
        RRA
        LD      IXL,A
        RR      D
        RR      E
        RR      B       ;...end of shifting
        JR      RSH6


