; uchar esxdos_m_getdrv(void)

SECTION code_clib
SECTION code_esxdos

PUBLIC esxdos_m_getdrv

EXTERN asm_esxdos_m_getsetdrv

esxdos_m_getdrv:

   ld l,0
   jp asm_esxdos_m_getsetdrv
