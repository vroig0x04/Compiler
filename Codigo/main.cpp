
#include <iostream>
#include <fstream>
#include <FlexLexer.h>
#include "lexer.h"
#include "parser.tab.hpp"
#include "taula_simbols.h"
#include "generador_tres_dir.h"
#include "generador_x64.h"
#include "optimizacion.h"

extern int yyparse();
extern GeneradorTresDir generador_codigo;
extern GeneradorX64 generador_x64;
const int DEBUGTAULASIMB=0;
const int DEBUG3DIR=0;
const int DEBUGX64=0;
const int DEBUGOPTIMIZACION=0;
yyFlexLexer* lexer;
TablaSimbolos* global_scope_prueba = nullptr;
TablaSimbolos* current_scope_prueba = nullptr;


int yylex() {
    return lexer->yylex();
}

/*
void yyerror(const char *s) {
    fprintf(stderr, "Error del Parser: %s\n", s);
} */

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Ús: " << argv[0] << " fitxer_entrada.txt" << std::endl;
        return 1;
    }
    
    std::ifstream input(argv[1]);
    if (!input.good()) {
        std::cerr << "No es pot obrir el fitxer: " << argv[1] << std::endl;
        return 1;
    }
    std::ifstream archivo(argv[1], std::ios::binary | std::ios::ate);
    // ios::ate nos sitúa al final del archivo inmediatamente
    if( archivo.tellg() <= 0){
        return 0;
    }
    
    global_scope_prueba = new TablaSimbolos();
    current_scope_prueba = global_scope_prueba;
    lexer = new yyFlexLexer(&input);
    
    std::cout << "=== Iniciant l'anàlisi ===" << std::endl;
    
    int resultado = yyparse();
    
    
#if DEBUGTAULASIMB==1
    std::ofstream fileFinal("Estados tabla de simbolos.txt", std::ios::app);
    if(fileFinal.is_open()) {
        fileFinal << "\n=== Tabla de símbolos final ===" << std::endl;
        fileFinal.close();
    }
    global_scope_prueba->imprimirEstado();
#endif
    if (resultado == 0 && error_count == 0) {
        std::cout << "\n=== Anàlisi sintàctica completada amb èxit ===" << std::endl;
        
        
#if DEBUG3DIR==1
        std::cout << "\n=== Código de Tres Direcciones ===" << std::endl;
        generador_codigo.imprimir();
#endif
        generador_codigo.guardarEnArchivo("codigo_tres_dir.txt");
        // Generar código x64 completo
        generador_x64.guardarEnArchivo("codigo_x64.asm");
         // 2. APLICAR OPTIMIZACIÓN
        Optimizador optimizador;
        // Lee el archivo que acabamos de crear y procesa las simplificaciones
        std::vector<std::string> codigo_opt = optimizador.optimizarDesdeArchivo("codigo_tres_dir.txt");
        // 3. GUARDAR CÓDIGO OPTIMIZADO EN OTRO ARCHIVO
        std::ofstream archivoOpt("codigo_optimizado.txt");
        if (archivoOpt.is_open()) {
            for (size_t i = 0; i < codigo_opt.size(); ++i) {
                archivoOpt << (i + 1) << ".\t" << codigo_opt[i] << "\n";
            }
            archivoOpt.close();
            std::cout << "Codi optimitzat guardat a: codigo_optimizado.txt" << std::endl;
        }
        //Generar codigo x64 optimizado
        generador_x64.generar_asm_optimizado("codigo_optimizado.txt", "optimizacion_x64.asm");
    } else {
        std::cout << "\nS'han trobat errors durant l'anàlisi." << std::endl;
    }

    delete lexer;
    return resultado;
}
