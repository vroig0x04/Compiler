rm -f Estados_tabla_de_simbolos.txt registro_de_tokens.txt Recopilación_de_errores.txt codigo_tres_dir.txt codigo_optimizado.txt codigo_x64.asm optimizacion_x64.asm prog.o prog 

if [ -z "$1" ]; then
    echo "Uso: $0 <archivo_a_parsear>"
    exit 1
fi
./mi_parser "$1" 
if [ -f "optimizacion_x64.asm" ]; then
./compilar_x64.sh
fi
if [ -f "Recopilación_de_errores.txt" ]; then
    echo "Como se han encontrado errores no se ha generado el archivo optimizacion_x64.asm"
fi