#!/bin/bash

# Script para compilar código x86-64 generado por el compilador Catalan

echo "=== Compilación de código x86-64 ===" 

# Verificar que existe el archivo
if [ ! -f "codigo_x64.asm" ]; then
    echo "Error: No se encontró codigo_x64.asm"
    exit 1
fi

# Compilar con NASM
echo "\n=== COMPILANDO... ==="
nasm -f elf64 optimizacion_x64.asm -o prog.o
if [ $? -ne 0 ]; then
    echo "Error: Fallo en NASM"
    exit 1
fi
echo "    Compilación OK"

# Linkear con libc
echo "\n=== LINKEANDO... ==="
gcc -no-pie prog.o -o prog
if [ $? -ne 0 ]; then
    echo "Error: Fallo en el linker"
    exit 1
fi
echo "    Link OK"

# Ejecutar
echo "\n=== EJECUTANDO... ==="
./prog
exit_code=$?

echo ""
echo "=== Ejecución completada ==="
echo "Código de salida: $exit_code"
exit $exit_code

if [ ! -f "codigo_tres_dir.txt" ]; then
    echo "Error: no se generó código de tres direcciones"
    exit 1
fi

echo "Código de tres direcciones generado correctamente"
echo "Guardado en: codigo_tres_dir.txt"
echo ""
echo "Para generar x64 completo, ejecuta:"
echo "  ./mi_parser $ENTRADA"

exit 0
