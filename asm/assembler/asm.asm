.586
.model flat,stdcall
includelib libucrt.lib
includelib kernel32.lib

ExitProcess PROTO:DWORD 

linelength PROTO: DWORD

printstr PROTO : DWORD

printnumb PROTO : DWORD

concats PROTO: DWORD,: DWORD,: DWORD

factorial PROTO: DWORD
.stack 4096
.const
		lit1 sdword 0
		lit2 byte 'da', 0
		lit3 byte 'da', 0
		lit4 byte 'net', 0
		lit5 sdword 5265
		lit6 sdword 8
		lit7 sdword 0
.data

buffer1 byte 256 dup(0)
buffer2 byte 256 dup(0)
		mfa sdword 0
		mc dword ?
		my dword ?
		ma dword ?
.code
fu PROC  
	
push ebx
push edx

pop edx
pop ebx
mov eax, lit1
ret
fu ENDP
da PROC  
	
push ebx
push edx

pop edx
pop ebx
mov eax, offset lit2
ret
da ENDP
main PROC
push offset lit3

pop ebx
mov my, ebx

push offset lit4

pop ebx
mov ma, ebx

push my
push ma
push offset buffer2
call concats
push eax
push my
push offset buffer1
call concats
push eax

pop ebx
mov mc, ebx


call fu 
mov ebx, lit6
cmp lit5, ebx
ja L1
jna L3

L1:

push my
call printstr

jmp L2

L3:

push ma
call printstr

L2:

push lit7
call ExitProcess
main ENDP
end main