section .text
global asmIsKeyPressed
extern IsKeyPressed  ; Raylib function

asmIsKeyPressed:
  push rbx
  call IsKeyPressed wrt ..plt  ; Calls raylib function

  test eax, eax
  setnz al  ; Sets al to 1 if key comparison is not zero (key was pressed)
  movzx eax, al  ; Extends al to eax adding zeroes

  pop rbx
  ret