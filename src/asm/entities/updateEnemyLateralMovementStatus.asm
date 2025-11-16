;-------------------------------------------------------------------------------
; Updates enemy horizontal movement toward its objective.
; Receives:
;     XMM0 holds float currentSpeed
;   , XMM1 holds float velocity
;   , XMM2 holds float objectiveX
;   , RDI holds float* enemyX pointer
; Returns: nothing
;-------------------------------------------------------------------------------
section .text
global updateEnemyLateralMovementStatus

updateEnemyLateralMovementStatus:
  push rbp
  mov rbp, rsp

  ; newPosition = this->currentSpeed * this->velocity
  movss xmm3, xmm0
  mulss xmm3, xmm1

  ; distanceDiff = this->objective.getBounds().x - this->bounds.x
  movss xmm4, xmm2
  subss xmm4, dword ptr [rdi]

  ; (distanceDiff < 0)
  xorps xmm5, xmm5
  ucomiss xmm4, xmm5
  je done
  jg objectiveIsRight

objectiveIsLeft:
  subss dword ptr [rdi], xmm3
  jmp done

objectiveIsRight:
  addss dword ptr [rdi], xmm3

done:
  mov rsp, rbp
  pop rbp
  ret
