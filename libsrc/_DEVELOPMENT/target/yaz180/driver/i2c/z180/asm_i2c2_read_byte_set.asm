;==============================================================================
; Contents of this file are copyright Phillip Stevens
;
; You have permission to use this for NON COMMERCIAL USE ONLY
; If you wish to use it elsewhere, please include an acknowledgement to myself.
;
; https://github.com/feilipu/
;
; https://feilipu.me/
;
;
; This work was authored in Marrakech, Morocco during May/June 2017.

    INCLUDE "config_private.inc"

    SECTION code_driver

    PUBLIC asm_i2c2_read_byte_set

    EXTERN __i2c2RxPtr
    EXTERN __i2c2ControlEcho, __i2c2SlaveAddr, __i2c2SentenceLgth, __i2c2SentenceStop

;   Read from the I2C Interface, using Byte Mode transmission
;   void i2c_read_byte_set( char addr, char *dp, char length, char stop );
;   parameters passed in registers
;   HL = pointer to receive buffer, uint8_t *dp
;   D  = 7 bit address of slave device, uint8_t _i2c2SlaveAddr
;   C  = length of data sentence expected, uint8_t _i2c2SentenceLgth
;   B  = boolean stop at conclusion [1|0], uint8_t _i2c2SentenceStop

.asm_i2c2_read_byte_set
    ld a,(__i2c2ControlEcho)
    tst __IO_I2C_CON_ECHO_BUS_RESTART|__IO_I2C_CON_ECHO_BUS_ILLEGAL
    ret NZ                      ;just exit if a fault

    and __IO_I2C_CON_ECHO_BUS_STOPPED
    jr Z,asm_i2c2_read_byte_set ;if the bus is not stopped, then wait till it is

    ld a,c
    or a                        ;check the sentence expected for zero length
    ret Z                       ;return if the sentence is 0 length

    ld (__i2c2SentenceLgth),a   ;store the sentence length

    ld a,d                      ;store the 7 bit slave address
    scf
    rla                         ;ensure we're reading Bit 0:[R=1]
    ld (__i2c2SlaveAddr),a

    ld a,b                      ;store the stop boolean
    ld (__i2c2SentenceStop),a

    ld (__i2c2RxPtr),hl         ;store the buffer pointer

    ld a,__IO_I2C_CON_ENSIO
    ld (__i2c2ControlEcho),a    ;store enabled in the control echo

    di
    in0 a,(ITC)                 ;get INT/TRAP Control Register (ITC)
    or ITC_ITE2                 ;mask in INT2
    out0 (ITC),a                ;enable external interrupt

    ld a,__IO_I2C_CON_ENSIO|__IO_I2C_CON_STA
    ld bc,__IO_I2C2_PORT_BASE|__IO_I2C_PORT_CON
    out (c),a                   ;set the interface enable and STA bit
    ei
    ret

