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
ZERO byte 'Ошибка: Деление на нолль', 0

OVER byte 'Ошибка: Выход за диапазон допустимых значений при присваивании'
MIN sdword -32768
MAX sdword 32767
		lit1 sdword 5
		lit2 sdword 8
		lit3 sdword 3
		lit4 byte 'Some Text', 0
		lit5 byte 'And more', 0
		lit6 sdword 0
.data

buffer1 byte 256 dup(0)
buffer2 byte 256 dup(0)
		ma sdword 0
		mb sdword 0
		mstr dword ?
		mstrr dword ?
		mst dword ?
.code
func PROC, 
	funca : sdword  
push ebx
push edx
push lit1

pop ebx
mov funca, ebx
cmp ebx, MAX
jg over_flow
cmp ebx, MIN
jl over_flow


pop edx
pop ebx
mov eax, funca
ret

div_by_0:
call printline
push offset ZERO
call printstr
push - 1
call ExitProcess
over_flow:
call printline
push offset OVER
call printstr
push - 1
call ExitProcess
func ENDP
main PROC
push lit2

pop ebx
mov ma, ebx
cmp ebx, MAX
jg over_flow
cmp ebx, MIN
jl over_flow

push lit3

pop ebx
mov mb, ebx
cmp ebx, MAX
jg over_flow
cmp ebx, MIN
jl over_flow


mov ebx, mb
cmp ma, ebx
jg L1
jle L3

L1:
push mb

pop ebx
mov ma, ebx
cmp ebx, MAX
jg over_flow
cmp ebx, MIN
jl over_flow


jmp L2

L3:
push ma

pop ebx
mov mb, ebx
cmp ebx, MAX
jg over_flow
cmp ebx, MIN
jl over_flow


L2:
push offset lit4

pop ebx
mov mstr, ebx

push offset lit5

pop ebx
mov mstrr, ebx

push mstr
push mstrr
push offset buffer2
call concats
push eax

pop ebx
mov mst, ebx


push ma
call func 

push mstr
call printstr

call printline 

push mstrr
call printstr

push ma
call printnumb

call printline 

push mb
call printnumb


push mb
call factorial 
push eax 
call printnumb

push lit6
call ExitProcess
div_by_0:
call printline
push offset ZERO
call printstr
push - 1
call ExitProcess
over_flow:
call printline
push offset OVER
call printstr
push - 1
call ExitProcess
main ENDP
end main