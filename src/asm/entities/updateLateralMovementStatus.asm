;-------------------------------------------------------------------------------
; Updates the player lateral movement status.
; Receives:
;     RDI holds bool leftDirection keys condition
;   , RSI holds bool rightDirection keys condition
;   , RDX holds float* xCoordinate pointer
;   , XMM0 holds float velocity
;   , XMM1 holds float currentSpeed
; Returns: nothing, modifies xCoordinate
;-------------------------------------------------------------------------------
section .text
global updateLateralMovementStatus

updateLateralMovementStatus:
  push rbp
  mov rbp, rsp

  ; Make new position
  movss xmm2, xmm0
  mulss xmm2, xmm1

checkLeftKeys:
  cmp dil, 0
  je checkRightKeys
  movss xmm3, [rdx]
  subss xmm3, xmm2
  movss [rdx], xmm3

checkRightKeys:
  cmp sil, 0
  je done
  movss xmm3, [rdx]
  addss xmm3, xmm2
  movss [rdx], xmm3

done:
  mov rsp, rbp
  pop rbp
  ret
