;------------–––------------–––------------–––------------–––------------–––---;
; Copyright 2025 Jason Montenegro-Navarro                                      ;
;------------–––------------–––------------–––------------–––------------–––---;
; @brief Checks collision between raylib rectangles                            ;
; @param a[ebp + 8] First rectangle pointer                                    ;
; @param b[ebp + 12] Second rectangle pointer                                  ;
; @param result[ebp + 16] Result int pointer                                   ;
; @return 1 if the entities are colliding, otherwise 0.                        ;
; @note stores result in result pointer.                                       ;
; @note Assumes struct layout: float x, float y, float width, float height     ;
;------------–––------------–––------------–––------------–––------------–––---;
section .text
global check_collision_recs
  push ebp
  mov ebp, esp
  
  mov esi, [ebp + 8]  ; First entity a
  mov edi, [ebp + 12]  ; Second entity b

  ; Check a.x < b.x + b.width
  fld dword [edi + 0]  ; b.x
  fadd dword [edi + 8]  ; b.width
  fld dword [esi + 0]  ; a.x
  fcomip st0, st1
  jge no_collision

  ; a.x + a.width > b.x
  fld dword [esi + 0]  ; a.x
  fadd dword [esi + 8]  ; a.width
  fld dword [edi + 0]  ; b.x
  fcomip st0, st1
  jle no_collision

  ; a.y < b.y + b.height
  fld dword [edi + 4]  ; b.y
  fadd dword [edi + 12]  ; b.height
  fld dword [esi + 4]  ; a.y
  fcomip st0, st1
  jge no_collision

  ; a.y + a.height > b.y
  fld dword [esi + 4]  ; a.y
  fadd dword [esi + 12]  ; a.height
  fld dword [edi + 4]  ; b.y
  fcomip st0, st1
  jle no_collision

  mov eax, [ebp + 16]  ; Result pointer
  mov dword [eax], 1  ; true
  jmp end_collision_check

no_collision:
  mov eax, [ebp + 16]  ; Result pointer
  mov dword [eax], 0  ; false

end_collision_check:
  mov esp, ebp
  pop ebp
  ret
