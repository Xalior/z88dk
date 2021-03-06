;       .title  "CGB support"
;       .module CGB

        MODULE  set_sprite_palette

        PUBLIC  set_sprite_palette
        PUBLIC  _set_sprite_palette

        SECTION code_driver

        INCLUDE "target/gb/def/gb_globals.def"

;void __LIB__ set_sprite_palette(uint8_t first_palette, uint8_t nb_palettes, uint16_t *rgb_data) __smallc NONBANKED;
_set_sprite_palette:           ; Non-banked
set_sprite_palette:           ; Non-banked
        PUSH    BC
        PUSH    DE

        LD      HL,sp+6         ; Skip return address and registers
        LD      c,(HL)          ; BC = rgb_data
        INC     HL
        LD      b,(HL)
        INC     HL
        LD      D,(HL)          ; D = nb_palettes
        INC     HL
        INC     HL
        LD      E,(HL)          ; E = first_palette

        LD      A,D             ; A = nb_palettes
        ADD     E
        ADD     A               ; A *= 8
        ADD     A
        ADD     A
        LD      D,A

        LD      A,E             ; E = first_palette
        ADD     A               ; A *= 8
        ADD     A
        ADD     A
        LD      E,A             ; A = first BCPS data
loop:
        LDH     A,(STAT)
        AND     0x02
        JR      NZ,loop

        LD      A,E
        LDH     (OCPS),A
        LD      A,(BC)
        LDH     (OCPD),A
        INC     BC              ; next rgb_data
        INC     E               ; next BCPS
        LD      A,E
        CP      A,D
        JR      NZ,loop

        POP     DE
        POP     BC
        RET

