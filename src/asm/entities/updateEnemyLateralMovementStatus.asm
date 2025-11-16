;-------------------------------------------------------------------------------
; Updates enemy horizontal movement toward its objective.
; Receives:
;     RDI holds float* enemyX pointer
;   , XMM0 holds float currentSpeed
;   , XMM1 holds float velocity
;   , XMM2 holds float objectiveX
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
  subss xmm4, [rdi]

  ; (distanceDiff < 0)
  xorps xmm5, xmm5
  ucomiss xmm4, xmm5
  je done
  ja objectiveIsRight

objectiveIsLeft:
  movss xmm6, [rdi]
  subss xmm6, xmm3
  movss [rdi], xmm6
  jmp done

objectiveIsRight:
  movss xmm6, [rdi]
  addss xmm6, xmm3
  movss [rdi], xmm6

done:
  mov rsp, rbp
  pop rbp
  ret
