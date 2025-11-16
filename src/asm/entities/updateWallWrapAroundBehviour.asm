;-------------------------------------------------------------------------------
; Updates the wall wrap around behaviour for player.
; Receives: 
;     XMM0 holds float screenWidth
;   , RDI holds float* xCoordinate pointer
;   , XMM1 holds float playerWidth
; Returns: nothing
;-------------------------------------------------------------------------------
section .text
global updateWallWrapAroundBehviour
updateWallWrapAroundBehviour:
  push rbp
  mov rbp, rsp
  mov xmm2, dword ptr [rdi]  ; &this->bounds.x

wrapAroundRightWall:
  ; Walks on right wall, appears on left wall
  ; (this->bounds.x > screenWidth)
  ucomiss xmm2, xmm0
  jle wrapAroundLeftWall
  ; this->bounds.x = -this->bounds.width;
  xorps xmm3, xmm3
  subss xmm3, xmm1
  movss dword ptr [rdi], xmm3

wrapAroundLeftWall:
  ; Walks on left wall, appears on right wall
  ; (this->bounds.x + this->bounds.width < 0)
  movss xmm3, xmm2
  addss xmm3, xmm1
  xorps xmm4, xmm4
  ucomiss xmm3, xmm4
  jge done
  ; this->bounds.x = screenWidth;
  movss dword ptr [rdi], xmm0

done:
  mov rsp, rbp
  pop rbp
  ret
