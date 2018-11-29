.global main

        .text
main:                                   
        mov     $message, %rdi
        call    puts
        ret
message:
        .asciz "Hola, mundo"