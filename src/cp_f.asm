;;; copy file
	
section .text use32
	global copy_file

%idefine dst_f [ebp+8]
%idefine src_f [ebp+12]

copy_file:
	push ebp
	mov ebp,esp
	
	;; otwarcie pliku zrodla
	mov eax, 5
	mov ebx, src_f
	mov ecx, 2
	mov edx, 111000000b	; 700 - zabro innym dostpu
	int 80h

	cmp eax,0
	jl _blad	
	mov [des_src],eax	; deskryptor otwartego pliku zrodla
	
	;;utoworzenie pliku przeznaczenia 
	mov eax,8
	mov ebx, dst_f
	mov ecx, 111000000b 	;  prawa 700
	int 80h

	cmp eax,0
	jl _blad
	
	mov [des_dst],eax	; deskryptor otwartego pliku przeznaczenia
	jmp read_save
	
_blad:
	mov eax,1
	jmp _end
	 
read_save:
	mov eax,3
	mov ebx,[des_src]
	mov ecx,bufor
	mov edx,400h		; 1 kB
	int 80h

	cmp eax,0
	jl _blad
	
	cmp eax,edx
	jne _zakoncz
	
	mov eax,4
	mov ebx,[des_dst]
	mov ecx,bufor
	mov edx,400h
	int 80h

	cmp eax,0
	jl _blad
	
	jmp read_save

_zakoncz:
	mov [ile],eax
	mov eax,4
	mov ebx,[des_dst]
	mov ecx,bufor
	mov edx,[ile]
	int 80h
	
_close:		
	;;; close files 
	mov eax,6
	mov ebx,[des_dst]
	int 80h
		
	mov eax,6
	mov ebx,[des_src]
	int 80h	
		
ok:	
	mov eax,0
	
_end:
	leave
	ret
			
segment .bss
	bufor	resb 400h	; 1kB
	des_src resd 1
	des_dst resd 1
	ile	resw 1