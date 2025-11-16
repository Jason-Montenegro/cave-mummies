;-------------------------------------------------------------------------------
; Updates player jump status and vertical position.
; Receives: 
;     RDI holds bool* isJumping pointer
;   , RSI holds float* yCoordinate pointer
;   , RDX holds float* jumpVelocity pointer
;   , XMM0 holds float groundY
;   , XMM1 holds float playerHeight
;   , RCX holds int32_t* jumpCount pointer
; Returns: nothing
;-------------------------------------------------------------------------------
section .rodata
  gravity: dd 1.5
section .text
global updatePlayerJumpStatus

updatePlayerJumpStatus:
  push rbp
  mov rbp, rsp

  cmp byte ptr [rdi], 1
  jne done

  ; newPosition = this->bounds.y + this->jumpVelocity
  movss xmm2, dword ptr [rsi]
  addss xmm2, dword ptr [rdx]
  ; this->jumpVelocity += gravity;
  movss xmm3, [gravity]
  addss dword ptr [rdx], xmm3

belowFloorLevel:
  ; (newPosition < 0.0f)
  xorps xmm3, xmm3
  ucomiss xmm2, xmm3
  jge atFloorLevel
  xor dword ptr [rsi], dword ptr [rsi]
  xor dword ptr [rdx], dword ptr [rdx]
  jmp done

atFloorLevel:
  ; (newPosition >= groundY - this->texture.height)
  movss xmm3, xmm0
  subss xmm3, xmm1
  ucomiss xmm2, xmm3
  jl aboveFloorLevel

  movss dword ptr [rsi], xmm3
  xor dword ptr [rdx], dword ptr [rdx]
  xor dword ptr [rcx], dword ptr [rcx]
  xor byte ptr [rdi], byte ptr [rdi]
  jmp done

aboveFloorLevel:
  ; this->bounds.y = newPosition;
  movss dword ptr [rsi], xmm2

done:
  mov rsp, rbp
  pop rbp
  ret
