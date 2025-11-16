;-------------------------------------------------------------------------------
; Updates the player lateral movement status.
; Receives:
;     RDI holds bool leftDirection keys condition
;   , RSI holds bool rightDirection keys condition
;   , XMM0 holds float velocity
;   , XMM1 holds float currentSpeed
;   , RDX holds float* xCoordinate pointer
; Returns: nothing
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
  subss dword ptr [rdx], xmm2

checkRightKeys:
  cmp sil, 0
  je done
  addss dword ptr [rdx], xmm2

done:
  mov rsp, rbp
  pop rbp
  ret
