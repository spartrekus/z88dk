; uchar errno_from_esxdos(uchar code)

SECTION code_clib
SECTION code_esxdos

PUBLIC errno_from_esxdos

EXTERN asm_errno_from_esxdos

defc errno_from_esxdos = asm_errno_from_esxdos
