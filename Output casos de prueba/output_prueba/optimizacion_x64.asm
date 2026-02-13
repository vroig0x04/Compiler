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
    ; r = z + b  //  Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    add rax, [rbp - 16]
    mov [rbp - 24], rax
    ; return r  //  Retorno de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
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
    ; t1 = x > y  //  Mayor que | T1:enter T2:enter TR:boolea LIT1:0 LIT2:0 | T1:enter T2:enter TR:boolea LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    cmp rax, [rbp - 16]
    setg al
    movzx rax, al
    mov [rbp - 32], rax
    ; if_false t1, goto L1  //  IF condición falsa | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 32]
    cmp rax, 0
    je .L1
    ; return x  //  Retorno de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    leave
    ret
    ; goto L2  //  Fin IF | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    jmp .L2
.L1:
.L2:
    ; return y  //  Retorno de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
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
    ; t2 = f > 0  //  Mayor que | T1:enter T2:enter TR:boolea LIT1:0 LIT2:1 | T1:enter T2:enter TR:boolea LIT1:0 LIT2:1
    mov rax, [rbp - 8]
    cmp rax, 0
    setg al
    movzx rax, al
    mov [rbp - 24], rax
    ; if_false t2, goto L4  //  IF condición falsa | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 24]
    cmp rax, 0
    je .L4
    ; return veritat  //  Retorno de función | T1:boolea T2:desconocido TR:desconocido LIT1:1 LIT2:0 | T1:boolea T2:desconocido TR:desconocido LIT1:1 LIT2:0
    mov rax, 1
    leave
    ret
    ; goto L5  //  Fin IF | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    jmp .L5
.L4:
.L5:
    ; return falsetat  //  Retorno de función | T1:boolea T2:desconocido TR:desconocido LIT1:1 LIT2:0 | T1:boolea T2:desconocido TR:desconocido LIT1:1 LIT2:0
    mov rax, 0
    leave
    ret
    leave
    ret

provaBucles:
    push rbp
    mov rbp, rsp
    sub rsp, 48
    ; i = 0  //  Asignación | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 0
    mov [rbp - 24], rax
.L6:
    ; t3 = i < 5  //  Menor que | T1:enter T2:enter TR:boolea LIT1:0 LIT2:1 | T1:enter T2:enter TR:boolea LIT1:0 LIT2:1
    mov rax, [rbp - 24]
    cmp rax, 5
    setl al
    movzx rax, al
    mov [rbp - 40], rax
    ; if_false t3, goto L7  //  WHILE condición falsa | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 40]
    cmp rax, 0
    je .L7
    ; i = i + 1  //  Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 24]
    add rax, [rbp - 0] ; VAR DESCONOCIDA: 1
    mov [rbp - 24], rax
    ; goto L6  //  Volver al inicio WHILE | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    jmp .L6
.L7:
    ; j = 0  //  Inicialización en for | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 0
    mov [rbp - 32], rax
.L8:
    ; t5 = j < 3  //  Menor que | T1:enter T2:enter TR:boolea LIT1:0 LIT2:1 | T1:enter T2:enter TR:boolea LIT1:0 LIT2:1
    mov rax, [rbp - 32]
    cmp rax, 3
    setl al
    movzx rax, al
    mov [rbp - 48], rax
    ; if_false t5, goto L9  //  FOR condición falsa | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 48]
    cmp rax, 0
    je .L9
    ; i = i + j  //  Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 24]
    add rax, [rbp - 32]
    mov [rbp - 24], rax
    ; j = j + 1  //  Asignación ++ | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 32]
    add rax, [rbp - 0] ; VAR DESCONOCIDA: 1
    mov [rbp - 32], rax
    ; goto L8  //  Volver al inicio FOR | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    jmp .L8
.L9:
    leave
    ret

provaOperacions:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    ; x = 10  //  Asignación | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 10
    mov [rbp - 8], rax
    ; y = 3  //  Asignación | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 3
    mov [rbp - 16], rax
    ; x = x + y  //  Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    add rax, [rbp - 16]
    mov [rbp - 8], rax
    ; x = x - y  //  Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    sub rax, [rbp - 16]
    mov [rbp - 8], rax
    ; x = x * y  //  Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    imul rax, [rbp - 16]
    mov [rbp - 8], rax
    ; x = x / 2  //  Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    cqo
    idiv qword [rbp - 0] ; VAR DESCONOCIDA: 2
    mov [rbp - 8], rax
    ; x = x % 2  //  Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    cqo
    idiv qword [rbp - 0] ; VAR DESCONOCIDA: 2
    mov [rbp - 8], rdx
    ; return x  //  Retorno de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    leave
    ret
    leave
    ret

provaBoolean:
    push rbp
    mov rbp, rsp
    sub rsp, 32
    ; t14 = 10 > 5  //  Mayor que | T1:enter T2:enter TR:boolea LIT1:1 LIT2:1 | T1:enter T2:enter TR:boolea LIT1:1 LIT2:1
    mov rax, 10
    cmp rax, 5
    setg al
    movzx rax, al
    mov [rbp - 24], rax
    ; t15 = 3 < 4  //  Menor que | T1:enter T2:enter TR:boolea LIT1:1 LIT2:1 | T1:enter T2:enter TR:boolea LIT1:1 LIT2:1
    mov rax, 3
    cmp rax, 4
    setl al
    movzx rax, al
    mov [rbp - 32], rax
    ; r = t14 && t15  //  Asignación | T1:boolea T2:desconocido TR:boolea LIT1:0 LIT2:0 | T1:boolea T2:desconocido TR:boolea LIT1:0 LIT2:0
    mov rax, [rbp - 24]
    mov r10, [rbp - 32]
    and rax, r10
    mov [rbp - 16], rax
    ; r = r || falsetat  //  Asignación | T1:boolea T2:desconocido TR:boolea LIT1:0 LIT2:0 | T1:boolea T2:desconocido TR:boolea LIT1:0 LIT2:0
    mov rax, [rbp - 16]
    mov r10, [rbp - 0] ; VAR DESCONOCIDA: falsetat
    or rax, r10
    mov [rbp - 16], rax
    ; r = r !  //  Asignación | T1:boolea T2:desconocido TR:boolea LIT1:0 LIT2:0 | T1:boolea T2:desconocido TR:boolea LIT1:0 LIT2:0
    ; return r  //  Retorno de función | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 16]
    leave
    ret
    leave
    ret

provaIO:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    ; read x  //  Leer entrada | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    lea rsi, [rbp - 8]
    lea rdi, [rel format_in]
    xor rax, rax
    call scanf
    ; print x  //  Imprimir expresión | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
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
    ; x = 5  //  Asignación | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 5
    mov [rbp - 24], rax
    ; d = caracter cast x  //  Asignación | T1:caracter T2:desconocido TR:caracter LIT1:0 LIT2:0 | T1:caracter T2:desconocido TR:caracter LIT1:0 LIT2:0
    mov rax, [rbp - 8]
    mov [rbp - 16], rax
    ; return d  //  Retorno de función | T1:caracter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:caracter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 16]
    leave
    ret
    leave
    ret

main:
    push rbp
    mov rbp, rsp
    sub rsp, 160
    ; x = 3  //  Inicialización | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 3
    mov [rbp - 136], rax
    ; t20[0] = x  //  Init tupla 0 | T1:enter T2:desconocido TR:desconocido LIT1:1 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:1 LIT2:0
    mov rdx, [rbp - 136]
    mov [rbp - 96], rdx
    ; t20[1] = y  //  Init tupla 1 | T1:enter T2:enter TR:tupla LIT1:1 LIT2:0 | T1:enter T2:enter TR:tupla LIT1:1 LIT2:0
    mov rdx, [rbp - 144]
    mov [rbp - 104], rdx
    ; t = t20  //  Inicialización tupla | T1:tupla T2:desconocido TR:tupla LIT1:0 LIT2:0 | T1:tupla T2:desconocido TR:tupla LIT1:0 LIT2:0
    mov rax, [rbp - 96]
    mov [rbp - 80], rax
    mov rax, [rbp - 104]
    mov [rbp - 88], rax
    ; y = 4  //  Asignación | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:1 LIT2:0
    mov rax, 4
    mov [rbp - 144], rax
    ; param x  //  Parámetro de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rdi, [rbp - 136]
    ; param y  //  Parámetro de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 144]
    ; z = call suma  //  Asignación | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:enter LIT1:0 LIT2:0
    call suma
    mov [rbp - 152], rax
    ; param z  //  Parámetro de función | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rdi, [rbp - 152]
    ; ok = call esPositiu  //  Asignación | T1:boolea T2:desconocido TR:boolea LIT1:0 LIT2:0 | T1:boolea T2:desconocido TR:boolea LIT1:0 LIT2:0
    call esPositiu
    mov [rbp - 24], rax
.L10:
    ; if_false ok, goto L11  //  IF condición falsa | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:boolea T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rax, [rbp - 24]
    cmp rax, 0
    je .L11
    ; print z  //  Imprimir expresión | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 152]
    lea rdi, [rel format_int]
    xor rax, rax
    call printf
    ; goto L12  //  Fin IF | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    jmp .L12
.L11:
    ; print x  //  Imprimir expresión | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:enter T2:desconocido TR:desconocido LIT1:0 LIT2:0
    mov rsi, [rbp - 136]
    lea rdi, [rel format_int]
    xor rax, rax
    call printf
.L12:
    ; call provaBucles  //  Llamada a función provaBucles | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    call provaBucles
    ; t23 = call provaOperacions  //  Llamada a función provaOperacions | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    call provaOperacions
    mov [rbp - 112], rax
    ; t24 = call provaBoolean  //  Llamada a función provaBoolean | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    call provaBoolean
    mov [rbp - 120], rax
    ; call provaIO  //  Llamada a función provaIO | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    call provaIO
    ; t25 = call provaCast  //  Llamada a función provaCast | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0 | T1:desconocido T2:desconocido TR:desconocido LIT1:0 LIT2:0
    call provaCast
    mov [rbp - 128], rax
    xor rax, rax
    leave
    ret

