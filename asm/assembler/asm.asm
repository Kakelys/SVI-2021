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
		lit1 sdword 0
		lit2 byte 'dada', 0
		lit3 sdword 2
		lit4 sdword 1
		lit5 sdword 2
		lit6 sdword 0
.data
		ma sdword 0
		mx sdword 0
		my dword ?
.code
fu PROC, 
	fua : sdword  
push ebx
push edx

pop edx
pop ebx
mov eax, lit1
ret
fu ENDP
main PROC
mov my, offset lit2
push lit3

pop ebx
mov mx, ebx

push mx
push lit4
pop ebx
pop eax
add eax, ebx
push eax

push fu
call fu 
push eax
pop ebx
pop eax
add eax, ebx
push eax

pop ebx
mov ma, ebx



push my
call linelength 
push eax 
call printnumb

push lit6
call ExitProcess
main ENDP
end main