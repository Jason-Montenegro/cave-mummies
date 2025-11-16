;-------------------------------------------------------------------------------
; Updates the wall wrap around behaviour for player.
; Receives: 
;     RDI holds bool jumpKeyDown
;   , RSI holds int32_t* jumpCount pointer
;   , RDX holds bool* isJumping pointer
;   , RCX holds float* jumpVelocity pointer
; Returns: nothing, modifies jumpCount, isJumping, and jumpVelocity
;-------------------------------------------------------------------------------
section .rodata
  jumpStrength: dd 30.0
  maxJumps:     dd 2

section .text
global consumePlayerJump

consumePlayerJump:
  push rbp
  mov rbp, rsp

  ; (jumpKeyDown && this->jumpCount < maxJumps)
  cmp dil, 1
  jne done

  mov eax, [rel maxJumps]
  cmp dword [rsi], eax
  jge done

  mov byte [rdx], 1
  movss xmm0, [rel jumpStrength]
  xorps xmm1, xmm1
  subss xmm1, xmm0
  movss [rcx], xmm1
  inc dword [rsi]

done:
  mov rsp, rbp
  pop rbp
  ret
