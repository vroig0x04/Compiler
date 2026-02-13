default rel
global main
section .data
    format_int: db "%ld", 10, 0
    format_char: db "%c", 10, 0
    format_str: db "%s", 10, 0
    format_in:  db "%ld", 0


section .text
    extern printf
    extern scanf

suma:
    push rbp
    mov rbp, rsp
    sub rsp, 32
    mov [rbp - 8], rdi
    mov [rbp - 16], rsi
    ; t0 = z + b  // Suma | T1:enter T2:enter TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    add rax, [rbp - 16]
    mov [rbp - 32], rax
    ; r = t0  // Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 32]
    mov [rbp - 24], rax
    ; return r  // Retorno de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 24]
    leave
    ret
    leave
    ret

max:
    push rbp
    mov rbp, rsp
    sub rsp, 32
    mov [rbp - 8], rdi
    mov [rbp - 16], rsi
.L0:
    ; t1 = x > y  // Mayor que | T1:enter T2:enter TR:boolea LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    cmp rax, [rbp - 16]
    setg al
    movzx rax, al
    mov [rbp - 32], rax
    ; if_false t1, goto L1  // IF condición falsa | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 32]
    cmp rax, 0
    je .L1
    ; return x  // Retorno de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    leave
    ret
    ; goto L2  // Fin IF | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    jmp .L2
.L1:
.L2:
    ; return y  // Retorno de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 16]
    leave
    ret
    leave
    ret

esPositiu:
    push rbp
    mov rbp, rsp
    sub rsp, 32
    mov [rbp - 8], rdi
.L3:
    ; t2 = f > 0  // Mayor que | T1:enter T2:enter TR:boolea LIT1:0 LIT2:1
    mov rax, [rbp - 8]
    cmp rax, 0
    setg al
    movzx rax, al
    mov [rbp - 24], rax
    ; if_false t2, goto L4  // IF condición falsa | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 24]
    cmp rax, 0
    je .L4
    ; return veritat  // Retorno de función | T1:boolea T2:desconocido TR:desconocido LIT1:1 LIT2:0
    mov rax, 1
    leave
    ret
    ; goto L5  // Fin IF | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    jmp .L5
.L4:
.L5:
    ; return falsetat  // Retorno de función | T1:boolea T2:desconocido TR:desconocido LIT1:1 LIT2:0
    mov rax, 0
    leave
    ret
    leave
    ret

provaBucles:
    push rbp
    mov rbp, rsp
    sub rsp, 80
    ; i = 0  // Asignación | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 0
    mov [rbp - 24], rax
.L6:
    ; t3 = i < 5  // Menor que | T1:enter T2:enter TR:boolea LIT1:0 LIT2:1
    mov rax, [rbp - 24]
    cmp rax, 5
    setl al
    movzx rax, al
    mov [rbp - 40], rax
    ; if_false t3, goto L7  // WHILE condición falsa | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 40]
    cmp rax, 0
    je .L7
    ; t4 = i + 1  // Suma | T1:enter T2:enter TR:enter LIT1:0 LIT2:1
    mov rax, [rbp - 24]
    add rax, 1
    mov [rbp - 48], rax
    ; i = t4  // Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 48]
    mov [rbp - 24], rax
    ; goto L6  // Volver al inicio WHILE | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    jmp .L6
.L7:
    ; j = 0  // Inicialización en for | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 0
    mov [rbp - 32], rax
.L8:
    ; t5 = j < 3  // Menor que | T1:enter T2:enter TR:boolea LIT1:0 LIT2:1
    mov rax, [rbp - 32]
    cmp rax, 3
    setl al
    movzx rax, al
    mov [rbp - 56], rax
    ; if_false t5, goto L9  // FOR condición falsa | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 56]
    cmp rax, 0
    je .L9
    ; t6 = i + j  // Suma | T1:enter T2:enter TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 24]
    add rax, [rbp - 32]
    mov [rbp - 64], rax
    ; i = t6  // Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 64]
    mov [rbp - 24], rax
    ; t7 = j + 1  // Incremento post en for | T1:enter T2:enter TR:enter LIT1:0 LIT2:1
    mov rax, [rbp - 32]
    add rax, 1
    mov [rbp - 72], rax
    ; j = t7  // Asignación ++ | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 72]
    mov [rbp - 32], rax
    ; goto L8  // Volver al inicio FOR | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    jmp .L8
.L9:
    leave
    ret

provaOperacions:
    push rbp
    mov rbp, rsp
    sub rsp, 64
    ; x = 10  // Asignación | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 10
    mov [rbp - 56], rax
    ; y = 3  // Asignación | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 3
    mov [rbp - 64], rax
    ; t8 = x + y  // Suma | T1:enter T2:enter TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 56]
    add rax, [rbp - 64]
    mov [rbp - 40], rax
    ; x = t8  // Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 40]
    mov [rbp - 56], rax
    ; t9 = x - y  // Resta | T1:enter T2:enter TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 56]
    sub rax, [rbp - 64]
    mov [rbp - 48], rax
    ; x = t9  // Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 48]
    mov [rbp - 56], rax
    ; t10 = x * y  // Multiplicación | T1:enter T2:enter TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 56]
    imul rax, [rbp - 64]
    mov [rbp - 8], rax
    ; x = t10  // Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    mov [rbp - 56], rax
    ; t11 = x // y  // División Entera | T1:enter T2:enter TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 56]
    cqo
    idiv qword [rbp - 64]
    mov [rbp - 16], rax
    ; x = t11  // Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 16]
    mov [rbp - 56], rax
    ; t12 = x / 2  // División | T1:enter T2:enter TR:enter LIT1:0 LIT2:1
    mov rax, [rbp - 56]
    cqo
    mov r10, 2
    idiv r10
    mov [rbp - 24], rax
    ; x = t12  // Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 24]
    mov [rbp - 56], rax
    ; t13 = x % 2  // Módulo | T1:enter T2:enter TR:enter LIT1:0 LIT2:1
    mov rax, [rbp - 56]
    cqo
    mov r10, 2
    idiv r10
    mov [rbp - 32], rdx
    ; x = t13  // Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 32]
    mov [rbp - 56], rax
    ; return x  // Retorno de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 56]
    leave
    ret
    leave
    ret

provaBoolean:
    push rbp
    mov rbp, rsp
    sub rsp, 48
    ; t14 = 10 > 5  // Mayor que | T1:enter T2:enter TR:boolea LIT1:1 LIT2:1
    mov rax, 10
    cmp rax, 5
    setg al
    movzx rax, al
    mov [rbp - 16], rax
    ; t15 = 3 < 4  // Menor que | T1:enter T2:enter TR:boolea LIT1:1 LIT2:1
    mov rax, 3
    cmp rax, 4
    setl al
    movzx rax, al
    mov [rbp - 24], rax
    ; t16 = t14 && t15  // AND lógico | T1:boolea T2:boolea TR:boolea LIT1:0 LIT2:0
    mov rax, [rbp - 16]
    mov r10, [rbp - 24]
    and rax, r10
    mov [rbp - 32], rax
    ; r = t16  // Asignación | T1:boolea T2:desconocido TR:boolea LIT1:0 LIT2:0
    mov rax, [rbp - 32]
    mov [rbp - 8], rax
    ; t17 = r || falsetat  // OR lógico | T1:boolea T2:boolea TR:boolea LIT1:0 LIT2:1
    mov rax, [rbp - 8]
    mov r10, 0
    or rax, r10
    mov [rbp - 40], rax
    ; r = t17  // Asignación | T1:boolea T2:desconocido TR:boolea LIT1:0 LIT2:0
    mov rax, [rbp - 40]
    mov [rbp - 8], rax
    ; t18 = ! r  // NOT lógico | T1:boolea T2:desconocido TR:boolea LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    cmp rax, 0
    sete al
    movzx rax, al
    mov [rbp - 48], rax
    ; r = t18  // Asignación | T1:boolea T2:desconocido TR:boolea LIT1:0 LIT2:0
    mov rax, [rbp - 48]
    mov [rbp - 8], rax
    ; return r  // Retorno de función | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    leave
    ret
    leave
    ret

provaIO:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    ; read x  // Leer entrada | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    lea rsi, [rbp - 8]
    lea rdi, [rel format_in]
    xor rax, rax
    call scanf
    ; print x  // Imprimir expresión | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 8]
    lea rdi, [rel format_int]
    xor rax, rax
    call printf
    leave
    ret

provaCast:
    push rbp
    mov rbp, rsp
    sub rsp, 32
    ; x = 5  // Asignación | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 5
    mov [rbp - 32], rax
    ; t19 = caracter cast x  // Cast a caracter | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    mov [rbp - 24], rax
    ; d = t19  // Asignación | T1:caracter T2:desconocido TR:caracter LIT1:0 LIT2:0
    mov rax, [rbp - 24]
    mov [rbp - 16], rax
    ; return d  // Retorno de función | T1:caracter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 16]
    leave
    ret
    leave
    ret

main:
    push rbp
    mov rbp, rsp
    sub rsp, 176
    ; x = 3  // Inicialización | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 3
    mov [rbp - 152], rax
    ; t20[0] = x  // Init tupla 0 | T1:enter T2:desconocido TR:desconocido LIT1:1 LIT2:0
    mov rdx, [rbp - 152]
    mov [rbp - 96], rdx
    ; t20[1] = y  // Init tupla 1 | T1:enter T2:enter TR:tupla LIT1:1 LIT2:0
    mov rdx, [rbp - 160]
    mov [rbp - 104], rdx
    ; t = t20  // Inicialización tupla | T1:tupla T2:desconocido TR:tupla LIT1:0 LIT2:0
    mov rax, [rbp - 96]
    mov [rbp - 80], rax
    mov rax, [rbp - 104]
    mov [rbp - 88], rax
    ; y = 4  // Asignación | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 4
    mov [rbp - 160], rax
    ; param x  // Parámetro de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rdi, [rbp - 152]
    ; param y  // Parámetro de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 160]
    ; t21 = call suma  // Llamada a función suma | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    call suma
    mov [rbp - 112], rax
    ; z = t21  // Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 112]
    mov [rbp - 168], rax
    ; param z  // Parámetro de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rdi, [rbp - 168]
    ; t22 = call esPositiu  // Llamada a función esPositiu | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    call esPositiu
    mov [rbp - 120], rax
    ; ok = t22  // Asignación | T1:boolea T2:desconocido TR:boolea LIT1:0 LIT2:0
    mov rax, [rbp - 120]
    mov [rbp - 24], rax
.L10:
    ; if_false ok, goto L11  // IF condición falsa | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 24]
    cmp rax, 0
    je .L11
    ; print z  // Imprimir expresión | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 168]
    lea rdi, [rel format_int]
    xor rax, rax
    call printf
    ; goto L12  // Fin IF | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    jmp .L12
.L11:
    ; print x  // Imprimir expresión | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 152]
    lea rdi, [rel format_int]
    xor rax, rax
    call printf
.L12:
    ; call provaBucles  // Llamada a función provaBucles | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    call provaBucles
    ; t23 = call provaOperacions  // Llamada a función provaOperacions | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    call provaOperacions
    mov [rbp - 128], rax
    ; t24 = call provaBoolean  // Llamada a función provaBoolean | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    call provaBoolean
    mov [rbp - 136], rax
    ; call provaIO  // Llamada a función provaIO | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    call provaIO
    ; t25 = call provaCast  // Llamada a función provaCast | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    call provaCast
    mov [rbp - 144], rax
    xor rax, rax
    leave
    ret

