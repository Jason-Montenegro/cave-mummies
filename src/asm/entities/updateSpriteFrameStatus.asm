;-------------------------------------------------------------------------------
; Updates the sprite frame status.
; Receives: 
;     RDI holds int32_t* gameFrameCounter pointer
;   , RSI holds int32_t totalSpriteFrameCount
;   , RDX holds int32_t* currentSpriteFrame pointer
; Returns: nothing
;-------------------------------------------------------------------------------
section .text
global updateSpriteFrameStatus

updateSpriteFrameStatus:
  push rbp
  mov rbp, rsp

  mov r8, rdx  ; &currentSpriteFrame
  ; this->gameFrameCounter =
  ;   (this->gameFrameCounter + this->totalSpriteFrameCount) % 60;
  mov eax, [rdi]  ; gameFrameCounter
  add eax, esi  ; + totalSpriteFrameCount
  cdq
  mov ebx, 60  ; 60 because the game runs on 60 fps
  idiv ebx  ; Remainder is in EDX
  mov [rdi], edx

  cmp edx, 0
  jne done
  ; this->currentSpriteFrame =
  ;   ++this->currentSpriteFrame % this->totalSpriteFrameCount;
  mov eax, [r8]  ; currentSpriteFrame
  inc eax
  cdq
  mov ebx, esi  ; totalSpriteFrameCount
  idiv ebx  ; Remainder is in edx
  mov [r8], edx

done:
  mov rsp, rbp
  pop rbp
  ret
