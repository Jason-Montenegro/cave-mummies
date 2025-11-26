;-------------------------------------------------------------------------------
; Updates player jump status and vertical position.
; Receives: 
;     RDI holds bool* isJumping pointer
;   , RSI holds float* yCoordinate pointer
;   , RDX holds float* jumpVelocity pointer
;   , RCX holds int32_t* jumpCount pointer
;   , XMM0 holds float groundY
;   , XMM1 holds float playerHeight
; Returns: nothing, modifies isJumping, yCoordinate, jumpVelocity, and jumpCount
;-------------------------------------------------------------------------------
section .rodata
  gravity: dd 1.5

section .text
global updatePlayerJumpStatus

updatePlayerJumpStatus:
  push rbp
  mov rbp, rsp

  cmp byte [rdi], 1
  jne done

  ; newPosition = this->bounds.y + this->jumpVelocity
  movss xmm2, [rsi]
  addss xmm2, [rdx]
  ; this->jumpVelocity += gravity;
  movss xmm3, [rdx]
  movss xmm4, [rel gravity]
  addss xmm3, xmm4
  movss [rdx], xmm3

belowFloorLevel:
  ; (newPosition < 0.0f)
  xorps xmm3, xmm3
  ucomiss xmm2, xmm3
  jae atFloorLevel
  mov dword [rsi], 0
  mov dword [rdx], 0
  jmp done

atFloorLevel:
  ; (newPosition >= groundY - this->texture.height)
  movss xmm3, xmm0
  subss xmm3, xmm1
  ucomiss xmm2, xmm3
  jb aboveFloorLevel

  movss [rsi], xmm3
  mov dword [rdx], 0
  mov dword [rcx], 0
  mov byte [rdi], 0
  jmp done

aboveFloorLevel:
  ; this->bounds.y = newPosition;
  movss [rsi], xmm2

done:
  mov rsp, rbp
  pop rbp
  ret
