.586
.model flat,stdcall
includelib libucrt.lib
includelib kernel32.lib
ExitProcess PROTO:DWORD 
linelength PROTO: DWORD
printstr PROTO : DWORD
printnumb PROTO : DWORD
.stack 4096
.const
		lit1 sdword 2
		lit2 sdword 4
		lit3 byte 'dada', 0
		lit4 sdword 2
		lit5 byte '', 0
		lit6 sdword 1
		lit7 sdword 2
		lit8 sdword 3
		lit9 sdword 0
.data
		ma sdword 0
		mx sdword 0
		my dword ?
		mc dword ?
.code
fu PROC, 
	fua : sdword, fux : sdword  
push ebx
push edx

pop edx
pop ebx
mov eax, fua
ret
fu ENDP
main PROC
push lit1

pop ebx
mov mx, ebx

push lit2

pop ebx
mov ma, ebx

mov my, offset lit3
push lit4

pop ebx
mov mx, ebx

mov ecx, my
mov mc, ecx

push mc
call printstr
push mx
push lit6
pop ebx
pop eax
add eax, ebx
push eax

push lit8
push lit7
call fu 
push eax
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov ma, ebx


push lit9
call ExitProcess
main ENDP
end main