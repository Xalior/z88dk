; void __FASTCALL__ delay(unsigned int tstates)

XLIB delay

; Z80 delay routine
; by Jan Bobrowski, license GPL
; wait hl T (including call; hl>=141)
; destroys: af, de, hl

.delay

        ld      de,-141
        add     hl,de
        ld      de,-23
        
.loop

        add     hl,de
        jr      c, loop
        
        ld      a,l
        add     a,15
        jr      nc, g0
        
        cp      8
        jr      c, g1
        
        or      0
        
.g0

        inc     hl

.g1

        rra
        jr      c, b0
        nop

.b0

        rra
        jr      nc, b1
        or      0
        
.b1

        rra
        ret     nc
        ret
