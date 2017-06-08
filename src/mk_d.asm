;;; make directory - mk_d.asm

section .text use32
	global new_dir

%idefine dir_name [ebp+8]

new_dir:
	push ebp
	mov ebp,esp
	
	mov eax,39
	mov ebx,dir_name
	mov ecx, 111111111b		; 777 (prawa)
	int 80h

	cmp eax,0
	jl blad
	jmp ok

blad:
	mov eax,1
	jmp _end
ok:
	mov eax,0
_end:
	leave
	ret