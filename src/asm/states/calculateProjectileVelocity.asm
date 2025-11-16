;-------------------------------------------------------------------------------
; Calculates projectile velocity from start position to target position.
; Receives:
;     RDI holds float* projectilVelocityX pointer
;   , RSI holds float* projectileVelocityY pointer
;   , XMM0 holds float mousePositionX
;   , XMM1 holds float mousePositionY
;   , XMM2 holds float startPositionX
;   , XMM3 holds float startPositionY
;   , XMM4 holds float bulletSpeed
; Returns: nothing, modifies projectileVelocityX and projectileVelocityY
;-------------------------------------------------------------------------------
section .text
global calculateProjectileVelocity

calculateProjectileVelocity:
  push rbp
  mov rbp, rsp
  ; Adapted from ChatGPT. Date: Sunday 16 November 2025
  ; prompt: existe alguna instruccion para raiz cuadrada con registros xmm?
  
  ; (mousePosition.x - startPosition.x)
  movss xmm5, xmm0
  subss xmm5, xmm2
  ; (mousePosition.y - startPosition.y)
  movss xmm6, xmm1
  subss xmm6, xmm3
  ; const float length{sqrtf(dir.x * dir.x + dir.y * dir.y)};
  movss xmm7, xmm5
  mulss xmm7, xmm7
  movss xmm0, xmm6
  mulss xmm0, xmm0
  addss xmm7, xmm0
  sqrtss xmm7, xmm7

  ; Normalization of vector coordinates
  xorps xmm0, xmm0
  ucomiss xmm7, xmm0
  je amplifyProjectileSpeed
  divss xmm5, xmm7
  divss xmm6, xmm7

amplifyProjectileSpeed:
  mulss xmm5, xmm4
  mulss xmm6, xmm4
  movss dword [rdi], xmm5
  movss dword [rsi], xmm6

  mov rsp, rbp
  pop rbp
  ret
