;-------------------------------------------------------------------------------
; Updates the player sprint status.
; Receives:
;     RDI holds bool isKeyDown(KEY_LEFT_SHIFT)
;   , RSI holds float* velocity pointer
;   , RDX holds bool isKeyReleased(KEY_LEFT_SHIFT)
;   , XMM0 holds float baseVelocity
;   , XMM1 holds float sprintVelocityBoost
; Returns: nothing, modifies velocity
;-------------------------------------------------------------------------------
section .text
global updatePlayerSprintStatus

updatePlayerSprintStatus:
  push rbp
  mov rbp, rsp

checkKeyDown:
  cmp dil, 0
  je checkKeyReleased
  movss xmm2, xmm0
  mulss xmm2, xmm1
  addss xmm2, xmm0
  movss [rsi], xmm2

checkKeyReleased:
  cmp dl, 0
  je done
  movss [rsi], xmm0

done:
  mov rsp, rbp
  pop rbp
  ret
