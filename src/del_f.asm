;;; delete file - del_f.asm

section .text use32
	global del_file
	
%idefine file_n [ebp+8]
	
del_file:
	push ebp
	mov ebp,esp
	xor ebx,ebx
	
	mov eax,10
	mov ebx,file_n
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
