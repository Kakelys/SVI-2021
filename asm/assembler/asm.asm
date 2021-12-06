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
		lit1 sdword 5
		lit2 sdword 5
		lit3 sdword 0
.data
		mx sdword 0
		my sdword 0
		mz sdword 0
.code
fi PROC, 
	x : dword,  y : dword   
push ebx
push edx

pop edx
pop ebx
mov eax, x
ret
fi ENDP
main PROC
push mx
push my
push mx
push my
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov mx, ebx

push lit1

pop ebx
mov my, ebx

push lit2

pop ebx
mov mz, ebx


mov ebx, my
cmp mz, ebx
je L1
jne L2

L1:

mov ebx, my
cmp mz, ebx
ja L3
jna L4

L3:

push my
call printnumb

L4:

L2:

push lit3
call ExitProcess
main ENDP
end main