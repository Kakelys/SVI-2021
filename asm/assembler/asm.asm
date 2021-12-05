.586
.model flat,stdcall
includelib libucrt.lib
includelib kernel32.lib
ExitProcess PROTO:DWORD 
line_length PROTO: DWORD
printstr PROTO : DWORD
printnumb PROTO : DWORD
.stack 4096
.const
		lit1 sdword 7
		lit2 sdword 5
		lit3 sdword 5
		lit4 sdword 0
.data
		mx sdword 0
		my sdword 0
		mz sdword 0
.code
fi PROC, 
	x : sdword, y : dword   
push ebx
push edx

pop edx
pop ebx
mov eax, x
ret
fi ENDP
main PROC
push lit1

pop ebx
mov mx, ebx

push lit2

pop ebx
mov my, ebx

push lit3
push mx
pop ebx
pop eax
add eax, ebx
push eax
push my
pop ebx
pop eax
add eax, ebx
push eax
push mx
push mx
pop ebx
pop eax
add eax, ebx
push eax
pop ebx
pop eax
imul eax, ebx
push eax
push mx
pop ebx
pop eax
imul eax, ebx
push eax
push mx
pop ebx
pop eax
imul eax, ebx
push eax
push mx
push my
pop ebx
pop eax
add eax, ebx
push eax
push mx
pop ebx
pop eax
add eax, ebx
push eax
pop ebx
pop eax
imul eax, ebx
push eax
pop ebx
pop eax
imul eax, ebx
push eax

pop ebx
mov mz, ebx


mov ebx, my
cmp mz, ebx
je L1
jne L2

L1: 

mov ebx, my
cmp mz, ebx
je L2
jne L3

L2: 

L3: 

push my
call printnumb

L4: 


push my
push mx
call fi 
push eax 
call printnumb

push lit4
call ExitProcess
main ENDP
end main