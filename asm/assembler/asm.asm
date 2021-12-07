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
		lit1 byte '"a"', 0
		lit2 sdword 1
.data
		mx sdword 0
		ma sdword 0
.code
fi PROC, 
	a : sdword  
push ebx
push edx

pop edx
pop ebx
mov eax, lit1
ret
fi ENDP
main PROC

mov ebx, mx
cmp mx, ebx
ja L1
jna L2

L1:

L2:

push lit2
call ExitProcess
main ENDP
end mainda PROC  
	
push ebx
push edx

pop edx
pop ebx
mov eax, ma
ret
da ENDP
