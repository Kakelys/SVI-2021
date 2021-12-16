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

printline PROTO
.stack 4096
.const
		lit1 dword 5
		lit2 dword 0
		lit3 dword 8
		lit4 dword 3
		lit5 byte 'Some Text', 0
		lit6 byte 'And more', 0
		lit7 dword 0
.data

buffer1 byte 256 dup(0)
buffer2 byte 256 dup(0)
		funca dword 0
		ma dword 0
		mb dword 0
		mstr dword ?
		mstrr dword ?
		mst dword ?
.code
func PROC  
	
push ebx
push edx
push lit1

pop ebx
mov funca, ebx


push funca
call printnumb

pop edx
pop ebx
mov eax, lit2
ret
func ENDP
main PROC
push lit3

pop ebx
mov ma, ebx

push lit4

pop ebx
mov mb, ebx


mov ebx, mb
cmp ma, ebx
ja L1
jna L3

L1:
push mb

pop ebx
mov ma, ebx


jmp L2

L3:
push ma

pop ebx
mov mb, ebx


L2:
push offset lit5

pop ebx
mov mstr, ebx

push offset lit6

pop ebx
mov mstrr, ebx

push mstr
push mstrr
push offset buffer2
call concats
push eax

pop ebx
mov mst, ebx


push mstr
call printstr

call printline 
push mstrr
call printstr

call printline 
push mb
call printnumb

call printline 

push mb
call factorial 
push eax 
call printnumb

push lit7
call ExitProcess
main ENDP
end main