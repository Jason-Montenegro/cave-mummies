;------------–––------------–––------------–––------------–––------------–––---;
; Copyright 2025 Jason Montenegro-Navarro                                      ;
;------------–––------------–––------------–––------------–––------------–––---;
; @brief Updates the sprinting status depending on player's input              ;
; @param velocity[ebp + 8] Pointer to the player's current velocity            ;
; @param baseVelocity[ebp + 12] The player's base velocity                     ;
; @param sprintVelocityBoost[ebp + 16] Sprint boost factor                     ;
; @param isShiftDown[ebp + 20] True if the sprint key is currently pressed.    ;
; @param isShiftReleased[ebp + 24] True if the sprint key has just been        ;
; released                                                                     ;
; @note Stores the new velocity in the velocity pointer.                       ;
;------------–––------------–––------------–––------------–––------------–––---;
section .text
global update_player_sprint
  push ebp
  mov ebp, esp

  mov eax, [ebp + 20]  ; isShiftDown
  cmp eax, 0
  je shift_not_pressed

  ; velocity = baseVelocity + baseVelocity * sprintVelocityBoost
  fld dword [ebp + 12]  ; st0 = baseVelocity
  fld dword [ebp + 12]  ; st1 = baseVelocity
  fmul dword [ebp + 16]  ; st0 = baseVelocity * sprintVelocityBoost
  fadd st0, st1  ; st0 = base + base * boost
  mov eax, [ebp + 8]  ; velocity pointer
  fstp dword [eax]  ; Store result
  jmp end_update_player_sprint

shift_not_pressed:
  mov eax, [ebp + 24]  ; isShiftReleased
  cmp eax, 0
  je end_update_player_sprint

  ; velocity = baseVelocity
  mov eax, [ebp + 8]  ; velocity pointer
  fld dword [ebp + 12]  ; baseVelocity
  fstp dword [eax]  ; Store result

end_update_player_sprint:
  mov esp, ebp
  pop ebp
  ret
