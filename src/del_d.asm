;;; make directory - mk_d.asm

section .text use32
	global del_dir

%idefine dir_n [ebp+8]
	
del_dir:
	push ebp
	mov ebp,esp	
	
	mov eax,40
	mov ebx,dir_n
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