;-------------------------------------------------------------------------------
; Checks collision between rectangles using AABB.
; Receives:
;     RDI holds Rectangle pointer
;   , RSI holds Rectangle pointer
; Returns: true if rectangles are colliding, otherwise false.
; C struct reference from raylib API:
; struct Rectangle {
;     float x;                // Rectangle top-left corner position x
;     float y;                // Rectangle top-left corner position y
;     float width;            // Rectangle width
;     float height;           // Rectangle height
; } Rectangle;
;-------------------------------------------------------------------------------
section .text
global checkCollisionRecs:

checkCollisionRecs:
  push rbp
  mov rbp, rsp

 ; a.x + a.width < b.x
  movss xmm0, [rdi]      ; a.x
  addss xmm0, [rdi + 8]  ; a.width
  movss xmm1, [rsi]      ; b.x
  ucomiss xmm0, xmm1
  jl setFalse

  ; a.y + a.height < b.y
  movss xmm0, [rdi + 4]  ; a.y
  addss xmm0, [rdi + 12] ; a.height
  movss xmm1, [rsi + 4]  ; b.y
  ucomiss xmm0, xmm1
  jl setFalse

  ; b.x + b.width < a.x
  movss xmm0, [rsi]      ; b.x
  addss xmm0, [rsi + 8]  ; b.width
  movss xmm1, [rdi]      ; a.x
  ucomiss xmm0, xmm1
  jl setFalse

  ; b.y + b.height < a.y
  movss xmm0, [rsi + 4]  ; b.y
  addss xmm0, [rsi + 12] ; b.height
  movss xmm1, [rdi + 4]  ; a.y
  ucomiss xmm0, xmm1
  jl setFalse

  ; return true
  mov rax, 1
  jmp done

setFalse:
  mov rax, 0  ; return false

done:
  mov rsp, rbp
  pop rbp
  ret
