default rel
global main
section .data
    format_int: db "%ld", 10, 0
    format_char: db "%c", 10, 0
    format_str: db "%s", 10, 0
    format_in:  db "%ld", 0

LC_0: db "Ana", 0
LC_1: db "Bob", 0

section .text
    extern printf
    extern scanf

main:
    push rbp
    mov rbp, rsp
    sub rsp, 96
    ; punto[0] = 5  // Asignación tupla | T1:enter T2:enter TR:tupla LIT1:1 LIT2:1
    mov rdx, 5
    mov [rbp - 40], rdx
    ; punto[1] = 10  // Asignación tupla | T1:enter T2:enter TR:tupla LIT1:1 LIT2:1
    mov rdx, 10
    mov [rbp - 48], rdx
    ; t0 = punto[0]  // Acceso tupla | T1:tupla T2:enter TR:desconocido LIT1:0 LIT2:1
    mov rax, [rbp - 40]
    mov [rbp - 56], rax
    ; print t0  // Imprimir expresión | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 56]
    lea rdi, [rel format_int]
    xor rax, rax
    call printf
    ; t1 = punto[1]  // Acceso tupla | T1:tupla T2:enter TR:desconocido LIT1:0 LIT2:1
    mov rax, [rbp - 48]
    mov [rbp - 64], rax
    ; print t1  // Imprimir expresión | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 64]
    lea rdi, [rel format_int]
    xor rax, rax
    call printf
    ; nombres[0] = "Ana"  // Asignación tupla | T1:enter T2:cadena TR:tupla LIT1:1 LIT2:1
    lea rdx, [rel LC_0]
    mov [rbp - 8], rdx
    ; nombres[1] = "Bob"  // Asignación tupla | T1:enter T2:cadena TR:tupla LIT1:1 LIT2:1
    lea rdx, [rel LC_1]
    mov [rbp - 16], rdx
    ; t2 = nombres[0]  // Acceso tupla | T1:tupla T2:enter TR:desconocido LIT1:0 LIT2:1
    mov rax, [rbp - 8]
    mov [rbp - 72], rax
    ; print t2  // Imprimir expresión | T1:cadena T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 72]
    lea rdi, [rel format_str]
    xor rax, rax
    call printf
    ; t3 = nombres[1]  // Acceso tupla | T1:tupla T2:enter TR:desconocido LIT1:0 LIT2:1
    mov rax, [rbp - 16]
    mov [rbp - 80], rax
    ; print t3  // Imprimir expresión | T1:cadena T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 80]
    lea rdi, [rel format_str]
    xor rax, rax
    call printf
    ; p2 = punto  // Asignación | T1:tupla T2:desconocido TR:tupla LIT1:0 LIT2:0
    mov rax, [rbp - 40]
    mov [rbp - 24], rax
    mov rax, [rbp - 48]
    mov [rbp - 32], rax
    ; t4 = p2[0]  // Acceso tupla | T1:tupla T2:enter TR:desconocido LIT1:0 LIT2:1
    mov rax, [rbp - 24]
    mov [rbp - 88], rax
    ; print t4  // Imprimir expresión | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 88]
    lea rdi, [rel format_int]
    xor rax, rax
    call printf
    xor rax, rax
    leave
    ret

