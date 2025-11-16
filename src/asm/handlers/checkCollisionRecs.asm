;-------------------------------------------------------------------------------
; Checks collision between rectangles using AABB.
; Receives:
;     RDI holds bool* result pointer
;   , XMM0 holds rectangle 1 x coordinate
;   , XMM1 holds rectangle 1 y coordinate
;   , XMM2 holds rectangle 1 width
;   , XMM3 holds rectangle 1 height
;   , XMM4 holds rectangle 2 x coordinate
;   , XMM5 holds rectangle 2 y coordinate
;   , XMM6 holds rectangle 2 width
;   , XMM7 holds rectangle 2 height
; Returns: nothing, modifies result pointer.
;-------------------------------------------------------------------------------
section .text
global checkCollisionRecs:
; Adapted from Google Gemini. Date: Sunday 16 November 2025
; prompt: raylib CheckCollisionRecs implementation
checkCollisionRecs:
  push rbp
  mov rbp, rsp

  ; rec1.x >= (rec2.x + rec2.width)
  movss xmm8, xmm4
  addss xmm8, xmm6
  ucomiss xmm0, xmm8
  jge setFalse

  ; (rec1.x + rec1.width) <= rec2.x
  movss xmm8, xmm0
  addss xmm8, xmm2
  ucomiss xmm8, xmm4
  jle setFalse

  ; rec1.y >= (rec2.y + rec2.height)
  movss xmm8, xmm5
  addss xmm8, xmm7
  ucomiss xmm1, xmm8
  jge setFalse

  ; (rec1.y + rec1.height) <= rec2.y
  movss xmm8, xmm1
  addss xmm8, xmm3
  ucomiss xmm8, xmm5
  jle setFalse

  ; return true
  mov rax, 1
  jmp done

setFalse:
  mov rax, 0  ; return false

done:
  mov rsp, rbp
  pop rbp
  mov [rdi], al  ; return result
  ret
