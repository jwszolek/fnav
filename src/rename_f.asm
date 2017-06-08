;;; rename file

section .text use32
	global rename_file
	
%idefine dst_f [ebp+8]
%idefine src_f [ebp+12]
	
rename_file:
	push ebp
	mov ebp,esp
		
	mov eax,38
	mov ebx,src_f
	mov ecx,dst_f
	int 80h

	cmp eax,0
	jl _blad

	mov eax,0
	jmp _end
_blad:
	mov eax,1
_end:	
	leave
	ret