.586													
.model flat, stdcall										
includelib libucrt.lib
includelib kernel32.lib		
includelib "C:\apapka\programms\Git\prog_lang\labs\asm\Debug\stdlib.lib"

ExitProcess PROTO: DWORD	


EXTRN line_length: proc
EXTRN ret_1: proc

.stack 4096

.const
	

.data
	
.code


main PROC													
    
	


INVOKE ExitProcess, 0									
main ENDP												
end main  