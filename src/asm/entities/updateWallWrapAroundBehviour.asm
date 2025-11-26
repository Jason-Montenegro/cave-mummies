;-------------------------------------------------------------------------------
; Updates the wall wrap around behaviour for player.
; Receives: 
;     RDI holds float* xCoordinate pointer
;   , XMM0 holds float screenWidth
;   , XMM1 holds float playerWidth
; Returns: nothing, modifies xCoordinate
;-------------------------------------------------------------------------------
section .text
global updateWallWrapAroundBehviour

updateWallWrapAroundBehviour:
  push rbp
  mov rbp, rsp

  movss xmm2, [rdi]  ; &this->bounds.x

wrapAroundRightWall:
  ; Walks on right wall, should then appear on left wall
  ; (this->bounds.x > screenWidth)
  ucomiss xmm2, xmm0
  jbe wrapAroundLeftWall
  ; this->bounds.x = -this->bounds.width;
  xorps xmm3, xmm3
  subss xmm3, xmm1
  movss [rdi], xmm3

wrapAroundLeftWall:
  ; Walks on left wall, should then appear on right wall
  ; (this->bounds.x + this->bounds.width < 0)
  movss xmm3, xmm2
  addss xmm3, xmm1
  xorps xmm4, xmm4
  ucomiss xmm3, xmm4
  jae done
  ; this->bounds.x = screenWidth;
  movss [rdi], xmm0

done:
  mov rsp, rbp
  pop rbp
  ret
