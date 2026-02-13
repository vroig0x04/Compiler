default rel
global main
section .data
    format_int: db "%ld", 10, 0
    format_char: db "%c", 10, 0
    format_str: db "%s", 10, 0
    format_in:  db "%ld", 0

LC_0: db "Hola ", 0
LC_1: db "Usuario", 0

section .text
    extern printf
    extern scanf

suma:
    push rbp
    mov rbp, rsp
    sub rsp, 32
    mov [rbp - 8], rdi
    mov [rbp - 16], rsi
    ; t0 = a + b  //  Suma | T1:enter T2:enter TR:enter LIT1:0 LIT2:0 | T1:enter T2:enter TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    add rax, [rbp - 16]
    mov [rbp - 24], rax
    ; return t0  //  Retorno de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 24]
    leave
    ret
    leave
    ret

mayor:
    push rbp
    mov rbp, rsp
    sub rsp, 32
    mov [rbp - 8], rdi
    mov [rbp - 16], rsi
.L0:
    ; t1 = a > b  //  Mayor que | T1:enter T2:enter TR:boolea LIT1:0 LIT2:0 | T1:enter T2:enter TR:boolea LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    cmp rax, [rbp - 16]
    setg al
    movzx rax, al
    mov [rbp - 32], rax
    ; if_false t1, goto L1  //  IF condición falsa | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 32]
    cmp rax, 0
    je .L1
    ; return a  //  Retorno de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    leave
    ret
    ; goto L2  //  Fin IF | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    jmp .L2
.L1:
    ; return b  //  Retorno de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 16]
    leave
    ret
.L2:
    leave
    ret

saludar:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    mov [rbp - 8], rdi
    ; print "Hola "  //  Imprimir expresión | T1:cadena T2:desconocido TR:desconocido LIT1:1 LIT2:0 | T1:cadena T2:desconocido TR:desconocido LIT1:1 LIT2:0
    lea rsi, [rel LC_0]
    lea rdi, [rel format_str]
    xor rax, rax
    call printf
    ; print nombre  //  Imprimir expresión | T1:cadena T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:cadena T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 8]
    lea rdi, [rel format_str]
    xor rax, rax
    call printf
    leave
    ret

main:
    push rbp
    mov rbp, rsp
    sub rsp, 64
    ; x = 10  //  Inicialización | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 10
    mov [rbp - 48], rax
    ; y = 20  //  Inicialización | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 20
    mov [rbp - 56], rax
    ; param x  //  Parámetro de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rdi, [rbp - 48]
    ; param y  //  Parámetro de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 56]
    ; resultado = call suma  //  Inicialización | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    call suma
    mov [rbp - 24], rax
    ; print resultado  //  Imprimir expresión | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 24]
    lea rdi, [rel format_int]
    xor rax, rax
    call printf
    ; param x  //  Parámetro de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rdi, [rbp - 48]
    ; param y  //  Parámetro de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 56]
    ; elMayor = call mayor  //  Inicialización | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    call mayor
    mov [rbp - 8], rax
    ; print elMayor  //  Imprimir expresión | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 8]
    lea rdi, [rel format_int]
    xor rax, rax
    call printf
    ; param "Usuario"  //  Parámetro de función | T1:cadena T2:desconocido TR:desconocido LIT1:1 LIT2:0 | T1:cadena T2:desconocido TR:desconocido LIT1:1 LIT2:0
    lea rdi, [rel LC_1]
    ; call saludar  //  Llamada a función saludar | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    call saludar
    xor rax, rax
    leave
    ret

