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
ZERO byte '??????: ??????? ?? ????', 0

OVER byte '??????: ????? ?? ???????? ?????????? ???????? ??? ????????????'
MIN sdword -32768
MAX sdword 32767
		lit1 sdword 5
		lit2 sdword 0
		lit3 sdword 8
		lit4 sdword 3
		lit5 byte 'some                                                                                   text', 0
		lit6 byte 'and more', 0
		lit7 sdword 7
		lit8 sdword 2
		lit9 sdword 2
		lit10 sdword 2
		lit11 sdword 0
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
mov eax, lit2
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
push lit3

pop ebx
mov ma, ebx
cmp ebx, MAX
jg over_flow
cmp ebx, MIN
jl over_flow

push lit4

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


push ma
call func 

push mst
call printstr

call printline 

push mstrr
call printstr

call printline 
push lit7
push lit8
pop ebx
pop eax
cdq
test ebx, ebx
jz div_by_0
idiv ebx
push eax
cmp ebx, MAX
jg over_flow
cmp ebx, MIN
jl over_flow
push lit9
push lit10
pop ebx
pop eax
add eax, ebx
push eax
cmp ebx, MAX
jg over_flow
cmp ebx, MIN
jl over_flow
pop ebx
pop eax
imul eax, ebx
push eax
cmp ebx, MAX
jg over_flow
cmp ebx, MIN
jl over_flow

pop ebx
mov ma, ebx
cmp ebx, MAX
jg over_flow
cmp ebx, MIN
jl over_flow


push ma
call printnumb

call printline 

push mb
call printnumb


push mb
call factorial 
push eax 
call printnumb

push lit11
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