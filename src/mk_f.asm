;;; make file - mk_f.asm
	
section .text use32
	global new_file

%idefine file_name [ebp+8]
	
new_file:
	push ebp
	mov ebp,esp

	mov eax,8
	mov ebx,file_name
	mov ecx,0100h
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