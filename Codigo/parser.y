%{ 
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <FlexLexer.h>
#include "lexer.h"
#include "taula_simbols.h"
#include "generador_tres_dir.h"
#include "generador_x64.h"

void yyerror(const char *s);
extern int yylex();
extern int yylineno;
int error_count = 0;

// Generador global de código de tres direcciones
GeneradorTresDir generador_codigo;

// Generador global de código x64
GeneradorX64 generador_x64;

// Flag para generar preámbulo solo una vez
bool preambulo_generado = false;

// Estructura para información de operando
struct OperandInfo {
    std::string valor;
    TipoBasico tipo;
    bool es_literal;
};

// Variables para almacenar valores de expresiones
std::string ultima_expresion = "";
std::string ultima_operacion = "";
std::stack<OperandInfo> pila_operandos; 

// Variables para control de flujo
std::stack<std::string> pila_etiquetas_inicio; 
std::stack<std::string> pila_etiquetas_fin;     
std::stack<std::string> pila_etiquetas_else;    

// Variable para for update
std::string for_update_op = "";

// Variables globales auxiliares
std::string current_type;
std::string currrent_mod;
std::string complex_type="tupla";
std::string name_aux;
std::vector<TipoBasico> tipos_parametros_actual;
TipoBasico last_tuple_subtype = TipoBasico::T_UNKNOWN;
// Información de función actual para validar retornos
struct FuncionActual {
    std::string nombre;
    TipoBasico tipo_retorno;
    bool ha_retornado;
};
FuncionActual funcion_actual = {"main", TipoBasico::T_VOID, true};
// Vector global para guardar nombres de parámetros de la función actual
std::vector<std::string> current_function_params;

// Enum para modificadores
enum class Etiquetes { NONE, CONSTANT, LLARG, NOSIGNE };
Etiquetes current_modifier = Etiquetes::NONE;

// Instancia global de la tabla de símbolos
TablaSimbolos tabla_simbolos;

// Funciones auxiliares para validación semántica
TipoBasico stringToTipoBasico(const std::string& s) {
    if (s == "enter") return TipoBasico::T_ENTER;
    if (s == "caracter") return TipoBasico::T_CARACTER;
    if (s == "cadena") return TipoBasico::T_CADENA;
    if (s == "boolea") return TipoBasico::T_BOOLEA;
    if (s == "tupla") return TipoBasico::T_TUPLA;
    if (s == "void") return TipoBasico::T_VOID;
    return TipoBasico::T_UNKNOWN;
}

// Función auxiliar para convertir valor de token a string
std::string valueToString(int ival) {
    return std::to_string(ival);
}

std::string valueToString(float fval) {
    return std::to_string(fval);
}

std::string valueToString(bool bval) {
    return bval ? "veritat" : "falsetat";
}

%}

%code requires {
    #include "taula_simbols.h"
    extern int error_count;
}

%union {
    int ival;
    float fval;
    std::string* sval;
    bool bval;
    TipoBasico tipo_expr;  
    std::vector<TipoBasico>* lista_tipos;
}

%type <tipo_expr> expression logical_or logical_and equality relational additive multiplicative unary primary literal
%type <tipo_expr> input_output_expression cast_expression
%type <lista_tipos> arguments argument_list

%token MOD_CONSTANT
%token TIPUS_ENTER TIPUS_CARACTER TIPUS_CADENA TIPUS_BOOLEA TIPUS_VOID 
%token OBJ_TUPLA
%token ASSIGN PUNTICOMA COMA PUNT DOBLEPUNT
%token SUMA RESTA MULT DIV MODUL DIVISIO_ENTER
%token IGUALTAT DIFERENT MENOR_IGUAL MAJOR_IGUAL MENOR MAJOR MES_IGUAL MENYS_IGUAL INC DEC
%token AND OR NOT
%token PAR_OPEN PAR_CLOSE KEY_OPEN_CLOSE COND_OPEN COND_CLOSE CLAUDATOR_OPEN CLAUDATOR_CLOSE
%token INICI_COND CONTINUACIO_COND FI_COND
%token BUCLE_MENTRE BUCLE_PER
%token INICI_FUNCIO RETORN RET
%token FUNC_IMPRIMEIX FUNC_ENTRADA FUNC_CAST
%token ERROR_TOKEN
%token CHARACTER_LITERAL
%token MAIN
%token <fval> FLOAT
%token <ival> INTEGER
%token <sval> CARACTER
%token <sval> STRING
%token <bval> BOOL
%token <sval> ID

/* De menor a mayor prioridad */

%left OR
%left AND
%left IGUALTAT DIFERENT
%left MENOR MAJOR MENOR_IGUAL MAJOR_IGUAL
%left SUMA RESTA
%left MULT DIV MODUL DIVISIO_ENTER
%right NOT

%%   /* Sección de reglas gramaticales */
start:
    programa
    {
    }
;
programa: %empty 
    /*vacio*/
    | programa declaraciones
;
declaraciones:
    function_def{}
    |main_function{}
    |declaration{}
;

main_function:
    INICI_FUNCIO MAIN PAR_OPEN PAR_CLOSE return_type
    KEY_OPEN_CLOSE 
    {
        // Emitir etiqueta de main
        generador_codigo.emitirSinResultado("", "", "", "main", "Función: main");
        
        /* 1. Insertar la función en el scope actual (global o padre) */
        TipoBasico tipo_retorno = stringToTipoBasico(current_type);
        funcion_actual.nombre = "main";
        funcion_actual.tipo_retorno =tipo_retorno ;
        if(funcion_actual.tipo_retorno!= TipoBasico::T_VOID){
            throw std::runtime_error("Error: main debe ser void.");
        }
        Descripcion f(TipoDesc::D_PROC, tipo_retorno, {});
        try {
            tabla_simbolos.posar("main", f);
        } catch (const std::exception& e) {
             yyerror(e.what());
        }
        /* Entramos en el ámbito del main */
        tabla_simbolos.entrarBloc();
    }
    block_instructions 
    KEY_OPEN_CLOSE
    {
        // Emitir fin de main
        generador_codigo.emitirSinResultado("", "", "", "", "Fin de función: main");
        
        /* Salimos del ámbito del main */
        try {
            tabla_simbolos.imprimirEstado();
            tabla_simbolos.salirBloc();
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        // Generar código x64 para main
        if (!preambulo_generado) {
            generador_x64.generarPreambulo();
            preambulo_generado = true;
        }
        const auto& codigo = generador_codigo.obtenerCodigo();
        size_t inicio = 0, fin = codigo.size();
        for (size_t i = 0; i < codigo.size(); ++i) {
            if (codigo[i].comentario == "Función: main") {
                inicio = i;
            }
            if (codigo[i].comentario == "Fin de función: main") {
                fin = i + 1;
                break;
            }
        }
        std::vector<InstruccionTresDir> tac_funcion(codigo.begin() + inicio, codigo.begin() + fin);
        
        // Obtener la función de la tabla de símbolos para sacar sus parámetros
        std::vector<std::string> params_names;
        generador_x64.generarPrologo("main", tac_funcion, {});
        for (const auto& instr : tac_funcion) {
            generador_x64.traducirInstruccion(instr);
        }
        generador_x64.generarEpilogo();
    }
;

function_def:
    INICI_FUNCIO ID PAR_OPEN params PAR_CLOSE return_type
    { 
        // Emitir etiqueta de función
        std::string params_str;
        for(size_t i=0; i<current_function_params.size(); ++i) {
            params_str += current_function_params[i];
            if(i < current_function_params.size()-1) params_str += ",";
        }
        generador_codigo.emitirSinResultado("", "", "", *$2, "Función: " + *$2 + " PARAMS:" + params_str);
        
        /* 1. Insertar la función en el scope actual (global o padre) */
        TipoBasico tipo_retorno = stringToTipoBasico(current_type);
        funcion_actual.nombre = *$2;
        funcion_actual.tipo_retorno = tipo_retorno;
        funcion_actual.ha_retornado = false;

        Descripcion f(TipoDesc::D_PROC, tipo_retorno, tipos_parametros_actual);
        try {
            tabla_simbolos.posar(*$2, f);
        } catch (const std::exception& e) {
             yyerror(e.what());
        }
        /* las funciones siguientes no heredarán parámetros anteriores */
        /* 2. Nuevo scope para el cuerpo de la función */
        tabla_simbolos.entrarBloc(); 

        /* 3. Registrar los parámetros en el nuevo scope */
        for(size_t i=0; i<current_function_params.size(); ++i) {
             Descripcion p(TipoDesc::D_ARG, tipos_parametros_actual[i]);
             try {
                tabla_simbolos.posar(current_function_params[i], p);
             } catch (const std::exception& e) {
                yyerror(e.what());
             }
        }
        
        tipos_parametros_actual.clear(); 
    }
    KEY_OPEN_CLOSE block_instructions KEY_OPEN_CLOSE
    {
        // Emitir fin de función
        generador_codigo.emitirSinResultado("", "", "", "", "Fin de función: " + funcion_actual.nombre);
        
        if (funcion_actual.tipo_retorno != TipoBasico::T_VOID &&
            !funcion_actual.ha_retornado) {
            yyerror(
                ("La función '" + funcion_actual.nombre +
                 "' debe retornar un valor").c_str()
            );
        }
        /* 3. Salir del scope de la función */
        try {
            tabla_simbolos.imprimirEstado();
            tabla_simbolos.salirBloc();
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        // Restaurar función actual a main
        funcion_actual.nombre = "main";
        funcion_actual.tipo_retorno = TipoBasico::T_VOID;
        // Generar código x64 para la función
        if (!preambulo_generado) {
            generador_x64.generarPreambulo();
            preambulo_generado = true;
        }
        const auto& codigo = generador_codigo.obtenerCodigo();
        size_t inicio = 0, fin = codigo.size();
        std::string func_name = *$2; // Guardar antes de delete
        for (size_t i = 0; i < codigo.size(); ++i) {
            if (codigo[i].comentario.find("Función: " + func_name) == 0) {
                inicio = i;
            }
            if (codigo[i].comentario == "Fin de función: " + func_name) {
                fin = i + 1;
                break;
            }
        }
        std::vector<InstruccionTresDir> tac_funcion(codigo.begin() + inicio, codigo.begin() + fin);
        generador_x64.generarPrologo(func_name, tac_funcion, current_function_params);
        for (const auto& instr : tac_funcion) {
            generador_x64.traducirInstruccion(instr);
        }
        generador_x64.generarEpilogo();
        
        // Limpiamos params para la siguiente función
        current_function_params.clear();
        
        delete $2;
    }
;
params: %empty 
    /*vacio*/
    | param_list
;
param_list:
    param
    | param_list COMA param
;
param:
    type ID
{
    /* Registramos el parámetro en el ámbito de la función */
    TipoBasico tipo_param = stringToTipoBasico(current_type);

    tipos_parametros_actual.push_back(tipo_param);
    current_function_params.push_back(*$2); // Guardar nombre del parámetro
    
    Descripcion p(TipoDesc::D_ARG, tipo_param);
    
    
    delete $2;
}
;

return_type: %empty 
    /*vacio*/ {current_type="void";}
    | RETORN type 
;

declaration:
    type ID PUNTICOMA
    {   
        TipoBasico tipo_var = stringToTipoBasico(current_type);
        Descripcion desc(TipoDesc::D_VAR, tipo_var);
        try {
            tabla_simbolos.posar(*$2, desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        delete $2;
    }

    | modifier type ID PUNTICOMA
    {
        /* Si hay modificador (const), ajustamos el tipo de descripción */
        TipoDesc t = (current_modifier == Etiquetes::CONSTANT) ? TipoDesc::D_CONST : TipoDesc::D_VAR;
        TipoBasico tipo_var = stringToTipoBasico(current_type);
        Descripcion desc(t, tipo_var);
        try {
            tabla_simbolos.posar(*$3, desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        delete $3;
        current_modifier = Etiquetes::NONE; // Resetear modificador
    }

    | type ID ASSIGN expression PUNTICOMA
    {
        TipoBasico tipo_var = stringToTipoBasico(current_type);
        if (!ValidacionTipos::esCompatible(tipo_var, $4)) {
            yyerror("Tipos incompatibles en inicialización");
        }
        Descripcion desc(TipoDesc::D_VAR, tipo_var);
        try {
            tabla_simbolos.posar(*$2, desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        // Generar TAC para la asignación
        if (!pila_operandos.empty()) {
            OperandInfo info = pila_operandos.top(); pila_operandos.pop();
            generador_codigo.emitirAsignacion(*$2, info.valor, "Inicialización", info.tipo, info.es_literal);
        }
        delete $2;
    }
    | modifier type ID ASSIGN expression PUNTICOMA
    {
        TipoDesc t = (current_modifier == Etiquetes::CONSTANT) ? TipoDesc::D_CONST : TipoDesc::D_VAR;
        TipoBasico tipo_var = stringToTipoBasico(current_type);
        if (!ValidacionTipos::esCompatible(tipo_var, $5)) {
            yyerror("Tipos incompatibles en inicialización");
        }
        Descripcion desc(t, tipo_var);
        try {
            tabla_simbolos.posar(*$3, desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        // Generar TAC para la asignación
        if (!pila_operandos.empty()) {
            OperandInfo info = pila_operandos.top(); pila_operandos.pop();
            generador_codigo.emitirAsignacion(*$3, info.valor, "Inicialización", info.tipo, info.es_literal);
        }
        delete $3;
        current_modifier = Etiquetes::NONE;
    }
    | obj_compl PUNTICOMA
    {
        /* La tupla ya se registró en obj_compl */
        name_aux="";
        complex_type="";
    }
;

obj_compl:
      OBJ_TUPLA MENOR type MAJOR ID 
      {
        // Declaración simple de tupla: tupla<tipo> var;
        TipoBasico tipo_elemento = stringToTipoBasico(current_type);
        if (tipo_elemento == TipoBasico::T_UNKNOWN) {
            yyerror("Tipo de tupla desconocido");
        }
        // Registrar la tupla con tipo T_TUPLA y guardar el tipo de elemento
        Descripcion desc(TipoDesc::D_VAR, TipoBasico::T_TUPLA);
        desc.tam_tupla = 2; // Tupla de 2 elementos
        desc.tipos_tupla.push_back(tipo_elemento); // Guardar tipo de elemento
        try {
            tabla_simbolos.posar(*$5, desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        } 
        name_aux = *$5;
        complex_type = "tupla";
        delete $5;
      }
    | OBJ_TUPLA MENOR type MAJOR ID ASSIGN expression
      {
        // Declaración de tupla con asignación: tupla<tipo> var = expr;
        TipoBasico tipo_elemento = stringToTipoBasico(current_type);
        if (tipo_elemento == TipoBasico::T_UNKNOWN) {
            yyerror("Tipo de tupla desconocido");
        }
        
        // Validar que la expresión es una tupla
        if ($7 != TipoBasico::T_TUPLA) {
            yyerror("Se esperaba una tupla en la inicialización");
        }
        
        // Validar que los tipos de elementos coincidan
        if (last_tuple_subtype != TipoBasico::T_UNKNOWN && 
            !ValidacionTipos::esCompatible(tipo_elemento, last_tuple_subtype)) {
            yyerror("Tipos incompatibles en elementos de tupla");
        }
        
        // Registrar la tupla inicializada con tipo T_TUPLA y tipo de elemento
        Descripcion desc(TipoDesc::D_VAR, TipoBasico::T_TUPLA);
        desc.tam_tupla = 2;
        desc.tipos_tupla.push_back(tipo_elemento); // Guardar tipo de elemento
        try {
            tabla_simbolos.posar(*$5, desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        name_aux = *$5;
        complex_type = "tupla";
        
        // Generar asignación si hay operandos
        if (!pila_operandos.empty()) {
             OperandInfo info = pila_operandos.top(); pila_operandos.pop();
             // La asignación debe copiar los elementos de la tupla temporal 'info.valor' a '*$5'
             generador_codigo.emitirAsignacion(*$5, info.valor, "Inicialización tupla", TipoBasico::T_TUPLA, false);
        }
        delete $5;
      }
;

modifier:
    MOD_CONSTANT    {current_modifier = Etiquetes::CONSTANT;}
    /* Resto de modificadores si se descomentan en el futuro */
;

type:
      TIPUS_ENTER           {current_type="enter";}
    | TIPUS_CARACTER        {current_type="caracter";}
    | TIPUS_CADENA          {current_type="cadena";}
    | TIPUS_BOOLEA          {current_type="boolea";}
    | TIPUS_VOID            {current_type="void";}

;

assignment:
    ID ASSIGN expression 
    {
        try {
            Descripcion var = tabla_simbolos.consultar(*$1);
            if (var.tipo == TipoDesc::D_CONST) {
                yyerror("No se puede reasignar a una constante");
            }
            // Si la variable es tupla y la expresión es tupla, validar tipos de elementos
            if (var.tipo_basico == TipoBasico::T_TUPLA && $3 == TipoBasico::T_TUPLA) {
                // Validar que el tipo de elemento de la tupla coincida
                if (!var.tipos_tupla.empty()) {
                    TipoBasico tipo_esperado = var.tipos_tupla[0];
                    if (last_tuple_subtype != TipoBasico::T_UNKNOWN && 
                        !ValidacionTipos::esCompatible(tipo_esperado, last_tuple_subtype)) {
                        yyerror("Tipos incompatibles en elementos de tupla");
                    }
                }
            } else if (!ValidacionTipos::esCompatible(var.tipo_basico, $3)) {
                yyerror("Tipos incompatibles en asignación");
            }
            
            // Pop el valor de la pila y asignar
            if (!pila_operandos.empty()) {
                 OperandInfo info = pila_operandos.top(); pila_operandos.pop();
                 generador_codigo.emitirAsignacion(*$1, info.valor, "Asignación", info.tipo, info.es_literal);
            }
            
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        name_aux=*$1;
        delete $1;
    }
    | ID CLAUDATOR_OPEN additive CLAUDATOR_CLOSE ASSIGN expression
    {
        try { 
            Descripcion var = tabla_simbolos.consultar(*$1); 
            if (var.tipo_basico != TipoBasico::T_TUPLA) { // y asumir que arrays no están implementados o usan otra lógica
                 // Si existieran arrays, aquí iría su lógica. Como solo tenemos tuplas por ahora:
                 yyerror("Variable no es una tupla");
            }
            if (!ValidacionTipos::esNumerico($3)) {
                yyerror("El índice debe ser numérico");
            }
            
            // Validar tipo de asignación a elemento
            if (!var.tipos_tupla.empty()) {
                 TipoBasico tipo_elemento = var.tipos_tupla[0];
                 if (!ValidacionTipos::esCompatible(tipo_elemento, $6)) {
                     yyerror("Tipo incompatible en asignación a elemento de tupla");
                 }
            }

            // Pop expression (valor a asignar) e índice
            if (pila_operandos.size() >= 2) {
                OperandInfo valor = pila_operandos.top(); pila_operandos.pop();
                OperandInfo indice = pila_operandos.top(); pila_operandos.pop();
                
                // Generar código: id[indice] = valor
                generador_codigo.emitir("tuple_set", indice.valor, valor.valor, *$1, "", "Asignación tupla", 
                                       TipoBasico::T_ENTER, valor.tipo, TipoBasico::T_TUPLA, indice.es_literal, valor.es_literal);
            }
        } catch (const std::exception& e) { 
            yyerror(e.what()); 
        }
        name_aux=*$1;
        delete $1;
    }
    | ID MES_IGUAL additive
    {
        try { 
            Descripcion var = tabla_simbolos.consultar(*$1); 
            if (!ValidacionTipos::esNumerico(var.tipo_basico)) {
                yyerror("Operando de += debe ser numérico");
            }
            // Pop el valor de additive
            if (!pila_operandos.empty()) {
                OperandInfo info = pila_operandos.top(); pila_operandos.pop();
                std::string temp = generador_codigo.nuevaTemp();
                generador_codigo.emitir("+", *$1, info.valor, temp, "", "+=", var.tipo_basico, info.tipo, var.tipo_basico, false, info.es_literal);
                generador_codigo.emitirAsignacion(*$1, temp, "Asignación +=");
            }
        } catch (const std::exception& e) { 
            yyerror(e.what()); 
        }
        name_aux=*$1;
        delete $1;
    } 
    | ID MENYS_IGUAL additive
    {
        try { 
            Descripcion var = tabla_simbolos.consultar(*$1); 
            if (!ValidacionTipos::esNumerico(var.tipo_basico)) {
                yyerror("Operando de -= debe ser numérico");
            }
            // Pop el valor de additive
            if (!pila_operandos.empty()) {
                OperandInfo info = pila_operandos.top(); pila_operandos.pop();
                std::string temp = generador_codigo.nuevaTemp();
                generador_codigo.emitir("-", *$1, info.valor, temp, "", "-=", var.tipo_basico, info.tipo, var.tipo_basico, false, info.es_literal);
                generador_codigo.emitirAsignacion(*$1, temp, "Asignación -=");
            }
        } catch (const std::exception& e) { 
            yyerror(e.what()); 
        }
        name_aux=*$1;
        delete $1;
    }

;

expression:
    logical_or { $$ = $1; }
;

logical_or:
    logical_or OR logical_and
    {
        if (!ValidacionTipos::esCompatible($1, TipoBasico::T_BOOLEA)) {
            yyerror("Operando izquierdo de OR debe ser booleano");
        }
        if (!ValidacionTipos::esCompatible($3, TipoBasico::T_BOOLEA)) {
            yyerror("Operando derecho de OR debe ser booleano");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir("||", op_izq.valor, op_der.valor, temp, "", "OR lógico", TipoBasico::T_BOOLEA, TipoBasico::T_BOOLEA, TipoBasico::T_BOOLEA, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
        }
        $$ = TipoBasico::T_BOOLEA;
    }
    | logical_and 
    { 
        $$ = $1; 
    }
;

logical_and:
    logical_and AND equality
    {
        if (!ValidacionTipos::esCompatible($1, TipoBasico::T_BOOLEA)) {
            yyerror("Operando izquierdo de AND debe ser booleano");
        }
        if (!ValidacionTipos::esCompatible($3, TipoBasico::T_BOOLEA)) {
            yyerror("Operando derecho de AND debe ser booleano");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir("&&", op_izq.valor, op_der.valor, temp, "", "AND lógico", TipoBasico::T_BOOLEA, TipoBasico::T_BOOLEA, TipoBasico::T_BOOLEA, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
        }
        $$ = TipoBasico::T_BOOLEA;
    }
    | equality 
    { 
        $$ = $1; 
    }
;

equality:
    equality IGUALTAT relational
    {
        if (!ValidacionTipos::esCompatible($1, $3)) {
            yyerror("Tipos incompatibles en comparación ==");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir("==", op_izq.valor, op_der.valor, temp, "", "Igualdad", $1, $3, TipoBasico::T_BOOLEA, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
        }
        $$ = TipoBasico::T_BOOLEA;
    }
    | equality DIFERENT relational
    {
        if (!ValidacionTipos::esCompatible($1, $3)) {
            yyerror("Tipos incompatibles en comparación !=");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir("!=", op_izq.valor, op_der.valor, temp, "", "Desigualdad", $1, $3, TipoBasico::T_BOOLEA, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
        }
        $$ = TipoBasico::T_BOOLEA;
    }
    | relational 
    { 
        $$ = $1; 
    }
;

relational:
    relational MENOR additive
    {
        if (!ValidacionTipos::esNumerico($1) || !ValidacionTipos::esNumerico($3)) {
            yyerror("Operandos de < deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir("<", op_izq.valor, op_der.valor, temp, "", "Menor que", $1, $3, TipoBasico::T_BOOLEA, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
        }
        $$ = TipoBasico::T_BOOLEA;
    }
    | relational MAJOR additive
    {
        if (!ValidacionTipos::esNumerico($1) || !ValidacionTipos::esNumerico($3)) {
            yyerror("Operandos de > deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir(">", op_izq.valor, op_der.valor, temp, "", "Mayor que", $1, $3, TipoBasico::T_BOOLEA, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
        }
        $$ = TipoBasico::T_BOOLEA;
    }
    | relational MENOR_IGUAL additive
    {
        if (!ValidacionTipos::esNumerico($1) || !ValidacionTipos::esNumerico($3)) {
            yyerror("Operandos de <= deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir("<=", op_izq.valor, op_der.valor, temp, "", "Menor o igual", $1, $3, TipoBasico::T_BOOLEA, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
        }
        $$ = TipoBasico::T_BOOLEA;
    }
    | relational MAJOR_IGUAL additive
    {
        if (!ValidacionTipos::esNumerico($1) || !ValidacionTipos::esNumerico($3)) {
            yyerror("Operandos de >= deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir(">=", op_izq.valor, op_der.valor, temp, "", "Mayor o igual", $1, $3, TipoBasico::T_BOOLEA, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
        }
        $$ = TipoBasico::T_BOOLEA;
    }
    | additive 
    { 
        $$ = $1; 
    }
;

additive:
    additive SUMA multiplicative
    {
        if (!ValidacionTipos::esNumerico($1) || !ValidacionTipos::esNumerico($3)) {
            yyerror("Operandos de suma deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            TipoBasico tipo_res = ValidacionTipos::mayorTipo($1, $3);
            generador_codigo.emitir("+", op_izq.valor, op_der.valor, temp, "", "Suma", $1, $3, tipo_res, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, tipo_res, false});
        }
        $$ = ValidacionTipos::mayorTipo($1, $3);
    }
    | additive RESTA multiplicative
    {
        if (!ValidacionTipos::esNumerico($1) || !ValidacionTipos::esNumerico($3)) {
            yyerror("Operandos de resta deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            TipoBasico tipo_res = ValidacionTipos::mayorTipo($1, $3);
            generador_codigo.emitir("-", op_izq.valor, op_der.valor, temp, "", "Resta", $1, $3, tipo_res, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, tipo_res, false});
        }
        $$ = ValidacionTipos::mayorTipo($1, $3);
    }
    | multiplicative 
    { 
        $$ = $1; 
    }
;

multiplicative:
    multiplicative MULT unary
    {
        if (!ValidacionTipos::esNumerico($1) || !ValidacionTipos::esNumerico($3)) {
            yyerror("Operandos de multiplicación deben ser numéricos");
        }
        // Pop operandos de la pila
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
             TipoBasico tipo_res = ValidacionTipos::mayorTipo($1, $3);
            generador_codigo.emitir("*", op_izq.valor, op_der.valor, temp, "", "Multiplicación", $1, $3, tipo_res, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, tipo_res, false});
        }
        $$ = ValidacionTipos::mayorTipo($1, $3);
    }
    | multiplicative DIV unary
    {
        if (!ValidacionTipos::esNumerico($1) || !ValidacionTipos::esNumerico($3)) {
            yyerror("Operandos de división deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            TipoBasico tipo_res = ValidacionTipos::mayorTipo($1, $3);
            generador_codigo.emitir("/", op_izq.valor, op_der.valor, temp, "", "División", $1, $3, tipo_res, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, tipo_res, false});
        }
        $$ = ValidacionTipos::mayorTipo($1, $3);
    }
    | multiplicative MODUL unary
    {
        if ($1 != TipoBasico::T_ENTER || $3 != TipoBasico::T_ENTER) {
            yyerror("Operandos de módulo deben ser enter");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir("%", op_izq.valor, op_der.valor, temp, "", "Módulo", $1, $3, TipoBasico::T_ENTER, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_ENTER, false});
        }
        $$ = TipoBasico::T_ENTER;
    }
    | multiplicative DIVISIO_ENTER unary
    {
        if (!ValidacionTipos::esNumerico($1) || !ValidacionTipos::esNumerico($3)) {
            yyerror("Operandos de división entera deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir("//", op_izq.valor, op_der.valor, temp, "", "División Entera", $1, $3, TipoBasico::T_ENTER, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_ENTER, false});
        }
        $$ = TipoBasico::T_ENTER;
    }
    | unary 
    { 
        $$ = $1; 
    }
;

unary:
      NOT unary
      {
          if ($2 != TipoBasico::T_BOOLEA) {
              yyerror("Operando de NOT debe ser booleano");
          }
          // Generar instrucción de negación lógica
          if (!pila_operandos.empty()) {
              OperandInfo op = pila_operandos.top(); pila_operandos.pop();
              std::string temp = generador_codigo.nuevaTemp();
              generador_codigo.emitir("!", op.valor, "", temp, "", "NOT lógico", TipoBasico::T_BOOLEA, TipoBasico::T_UNKNOWN, TipoBasico::T_BOOLEA, op.es_literal, false);
              pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
          }
          $$ = TipoBasico::T_BOOLEA;
      }
    | INC unary
      {
          if (!ValidacionTipos::esNumerico($2)) {
              yyerror("Operando de ++ debe ser numérico");
          }
          // Generar instrucción de incremento prefijo
          if (!pila_operandos.empty()) {
              OperandInfo op = pila_operandos.top(); pila_operandos.pop();
              std::string temp1 = generador_codigo.nuevaTemp();
              generador_codigo.emitir("+", op.valor, "1", temp1, "", "Incremento prefijo", $2, TipoBasico::T_ENTER, $2, op.es_literal, true);
              generador_codigo.emitirAsignacion(op.valor, temp1, "Asignación ++", op.tipo, false);
              pila_operandos.push({temp1, $2, false});
          }
          $$ = $2;
      }
    | DEC unary
      {
          if (!ValidacionTipos::esNumerico($2)) {
              yyerror("Operando de -- debe ser numérico");
          }
          // Generar instrucción de decremento prefijo
          if (!pila_operandos.empty()) {
              OperandInfo op = pila_operandos.top(); pila_operandos.pop();
              std::string temp1 = generador_codigo.nuevaTemp();
              generador_codigo.emitir("-", op.valor, "1", temp1, "", "Decremento prefijo", $2, TipoBasico::T_ENTER, $2, op.es_literal, true);
              generador_codigo.emitirAsignacion(op.valor, temp1, "Asignación --", op.tipo, false);
              pila_operandos.push({temp1, $2, false});
          }
          $$ = $2;
      }
    | primary { $$ = $1; }
    | primary INC
      {
          if (!ValidacionTipos::esNumerico($1)) {
              yyerror("Operando de ++ debe ser numérico");
          }
          // Generar instrucción de incremento postfijo
          if (!pila_operandos.empty()) {
              OperandInfo op = pila_operandos.top(); pila_operandos.pop();
              std::string original = generador_codigo.nuevaTemp();
              generador_codigo.emitirAsignacion(original, op.valor, "Valor original para post-inc", op.tipo, op.es_literal);
              std::string temp = generador_codigo.nuevaTemp();
              generador_codigo.emitir("+", op.valor, "1", temp, "", "Incremento postfijo", $1, TipoBasico::T_ENTER, $1, op.es_literal, true);
              generador_codigo.emitirAsignacion(op.valor, temp, "Asignación ++", op.tipo, false);
              pila_operandos.push({original, $1, false});
          }
          $$ = $1;
      }
    | primary DEC
      {
          if (!ValidacionTipos::esNumerico($1)) {
              yyerror("Operando de -- debe ser numérico");
          }
          // Generar instrucción de decremento postfijo
          if (!pila_operandos.empty()) {
              OperandInfo op = pila_operandos.top(); pila_operandos.pop();
              std::string original = generador_codigo.nuevaTemp();
              generador_codigo.emitirAsignacion(original, op.valor, "Valor original para post-dec", op.tipo, op.es_literal);
              std::string temp = generador_codigo.nuevaTemp();
              generador_codigo.emitir("-", op.valor, "1", temp, "", "Decremento postfijo", $1, TipoBasico::T_ENTER, $1, op.es_literal, true);
              generador_codigo.emitirAsignacion(op.valor, temp, "Asignación --", op.tipo, false);
              pila_operandos.push({original, $1, false});
          }
          $$ = $1;
      }
;

primary:
      literal 
      { 
          $$ = $1;
      }
    | ID
    {
        try 
        {
            Descripcion s = tabla_simbolos.consultar(*$1);
            $$ = s.tipo_basico;
            pila_operandos.push({*$1, s.tipo_basico, false});  // Push el nombre de la variable
            
            // Si es tupla, actualizar last_tuple_subtype para asignaciones
            if (s.tipo_basico == TipoBasico::T_TUPLA && !s.tipos_tupla.empty()) {
                last_tuple_subtype = s.tipos_tupla[0];
            } else {
                last_tuple_subtype = TipoBasico::T_UNKNOWN;
            }
        } catch (const std::exception& e) {
            yyerror(e.what());
            $$ = TipoBasico::T_UNKNOWN;
        }

        
        delete $1;
    }
    | ID CLAUDATOR_OPEN additive CLAUDATOR_CLOSE
    {
        try {
            Descripcion s = tabla_simbolos.consultar(*$1);
            if (s.tipo_basico != TipoBasico::T_TUPLA) {
                yyerror("Variable no es una tupla");
            }
            if (!ValidacionTipos::esNumerico($3)) {
                yyerror("El índice debe ser numérico");
            }
            
            // Pop índice
            if (!pila_operandos.empty()) {
                OperandInfo indice = pila_operandos.top(); pila_operandos.pop();
                std::string temp = generador_codigo.nuevaTemp();
                
                // Generar: temp = id[indice]
                // tipo_operando1 es T_TUPLA para que generarPrologo sepa que 'id' es tupla
                generador_codigo.emitir("tuple_get", *$1, indice.valor, temp, "", "Acceso tupla", 
                                       TipoBasico::T_TUPLA, TipoBasico::T_ENTER, TipoBasico::T_UNKNOWN, false, indice.es_literal);
                TipoBasico tipo_elem = TipoBasico::T_UNKNOWN;
                if (!s.tipos_tupla.empty()) tipo_elem = s.tipos_tupla[0]; // Simplificación: asume homogénea o primer tipo
                
                pila_operandos.push({temp, tipo_elem, false});
                $$ = tipo_elem;
            } else {
                 $$ = TipoBasico::T_UNKNOWN;
            }
        } catch (const std::exception& e) {
             yyerror(e.what());
             $$ = TipoBasico::T_UNKNOWN;
        }
        delete $1;
    }
    | PAR_OPEN expression COMA expression PAR_CLOSE 
    { 
        /* 1. Pop operandos */
        if (pila_operandos.size() >= 2) {
             OperandInfo op2 = pila_operandos.top(); pila_operandos.pop();
             OperandInfo op1 = pila_operandos.top(); pila_operandos.pop();
             
             // Validar homogeneidad (req: "tuplas de enteros", etc.)
             if (!ValidacionTipos::esCompatible(op1.tipo, op2.tipo)) {
                 yyerror("Los elementos de la tupla literal deben ser del mismo tipo");
             }
             
             // Actualizar last_tuple_subtype
             last_tuple_subtype = op1.tipo;
             
             // Generar temporal para la tupla
             std::string temp = generador_codigo.nuevaTemp();
             generador_codigo.emitirTupleSet(temp, 0, op1.valor, "Init tupla 0", op1.es_literal);
             generador_codigo.emitir("tuple_set", "1", op2.valor, temp, "", "Init tupla 1", 
                                     TipoBasico::T_ENTER, op2.tipo, TipoBasico::T_TUPLA, true, op2.es_literal);
             
             pila_operandos.push({temp, TipoBasico::T_TUPLA, false});
        }
        
        /* 3. Devolvemos el tipo general */
        $$ = TipoBasico::T_TUPLA; 
    }
    | ID PAR_OPEN arguments PAR_CLOSE
    {
         try {
            Descripcion s = tabla_simbolos.consultar(*$1);

            if (s.tipo != TipoDesc::D_PROC) {
                yyerror("El identificador no es una funcion");
            }

            if (s.tipos_parametros.size() != $3->size()) {
                yyerror("Número incorrecto de argumentos");
            }

            for (size_t i = 0; i < s.tipos_parametros.size(); ++i) {
                if (!ValidacionTipos::esCompatible(s.tipos_parametros[i],(*$3)[i])) {
                    yyerror("Tipo incompatible en argumento de función");
                }
            }

            $$ = s.tipo_retorno;

            std::string temp = "";
            if ($$ != TipoBasico::T_VOID) {
                temp = generador_codigo.nuevaTemp();
            }
            generador_codigo.emitirCall(*$1, temp, "Llamada a función " + *$1);
            if (!temp.empty()) {
                pila_operandos.push({temp, s.tipo_retorno, false});
            }

         } catch (const std::exception& e) {
            yyerror(e.what());
            $$ = TipoBasico::T_UNKNOWN;
         }

         delete $1;
         delete $3;
    }
    | cast_expression { $$ = $1; }
    | input_output_expression { $$ = $1; }
    | PAR_OPEN expression PAR_CLOSE { $$ = $2; }
;

cast_expression:
      FUNC_CAST PAR_OPEN type COMA expression PAR_CLOSE 
      {
          // cast retorna el tipo especificado
          $$ = stringToTipoBasico(current_type);
          // Emitir cast
          if (!pila_operandos.empty()) {
              OperandInfo op = pila_operandos.top(); pila_operandos.pop();
              std::string temp = generador_codigo.nuevaTemp();
              generador_codigo.emitirCast(current_type, op.valor, temp, "Cast a " + current_type, op.es_literal);
              pila_operandos.push({temp, stringToTipoBasico(current_type), false});
          }
      }
;

input_output_expression:
      FUNC_ENTRADA PAR_OPEN expression PAR_CLOSE
      {
          $$ = TipoBasico::T_ENTER;
          // Emitir read
          if (!pila_operandos.empty()) {
              OperandInfo var = pila_operandos.top(); pila_operandos.pop();
              generador_codigo.emitirRead(var.valor, "Leer entrada");
              // Push de vuelta la variable leída
              pila_operandos.push(var);
          }
      }
      | FUNC_IMPRIMEIX PAR_OPEN expression PAR_CLOSE
      {
          $$ = TipoBasico::T_VOID;
          // Emitir print
          if (!pila_operandos.empty()) {
              OperandInfo expr = pila_operandos.top(); pila_operandos.pop();
              generador_codigo.emitirPrint(expr.valor, "Imprimir expresión", expr.tipo, expr.es_literal);
          }
      }
;

literal:
      INTEGER   
      { 
          $$ = TipoBasico::T_ENTER; 
          pila_operandos.push({valueToString($1), TipoBasico::T_ENTER, true});
      }
    | STRING    
      { 
          $$ = TipoBasico::T_CADENA; 
          pila_operandos.push({*$1, TipoBasico::T_CADENA, true});
      }
    | BOOL      
      { 
          $$ = TipoBasico::T_BOOLEA;
          pila_operandos.push({valueToString($1), TipoBasico::T_BOOLEA, true});
      }
    | CARACTER  
      { 
          $$ = TipoBasico::T_CARACTER;
          pila_operandos.push({*$1, TipoBasico::T_CARACTER, true});
      }
;

conditional:
    INICI_COND COND_OPEN 
    {
        // Emitir etiqueta de inicio del if
        std::string etiqueta_inicio = generador_codigo.nuevaEtiqueta();
        generador_codigo.emitirEtiqueta(etiqueta_inicio, "Inicio IF");
        pila_etiquetas_inicio.push(etiqueta_inicio);
    }
    expression COND_CLOSE
    {
        // Después de evaluar expresión, pop condición y emitir salto condicional
        if (!pila_operandos.empty()) {
            OperandInfo condicion = pila_operandos.top(); pila_operandos.pop();
            std::string etiqueta_else = generador_codigo.nuevaEtiqueta();
            generador_codigo.emitirSaltoCondicional(condicion.valor, etiqueta_else, "IF condición falsa", condicion.es_literal);
            pila_etiquetas_else.push(etiqueta_else);
        }
    }
    KEY_OPEN_CLOSE 
    {
        /* Nuevo ámbito para el bloque IF */
        tabla_simbolos.entrarBloc();
    }
    block_instructions 
    KEY_OPEN_CLOSE
    {
        /* Cerrar ámbito IF */
        try { tabla_simbolos.salirBloc(); } catch (const std::exception& e) { yyerror(e.what()); }
        // Después del bloque if, emitir goto a etiqueta fin
        std::string etiqueta_fin = generador_codigo.nuevaEtiqueta();
        generador_codigo.emitirGoto(etiqueta_fin, "Fin IF");
        pila_etiquetas_fin.push(etiqueta_fin);
    }
    else_chain
    {
        // Al final, emitir etiqueta fin
        if (!pila_etiquetas_fin.empty()) {
            std::string etiqueta_fin = pila_etiquetas_fin.top(); pila_etiquetas_fin.pop();
            generador_codigo.emitirEtiqueta(etiqueta_fin, "Fin IF completo");
        }
    }
;

else_chain: %empty 
    /* vacío */
    {
        // No hay else, emitir etiqueta else aquí si existe
        if (!pila_etiquetas_else.empty()) {
            std::string etiqueta_else = pila_etiquetas_else.top(); pila_etiquetas_else.pop();
            generador_codigo.emitirEtiqueta(etiqueta_else, "Etiqueta ELSE (vacío)");
        }
    }
    | CONTINUACIO_COND COND_OPEN 
    {
        // Emitir etiqueta else antes del elif
        if (!pila_etiquetas_else.empty()) {
            std::string etiqueta_else = pila_etiquetas_else.top(); pila_etiquetas_else.pop();
            generador_codigo.emitirEtiqueta(etiqueta_else, "Etiqueta ELSE/ELIF");
        }
    }
    expression COND_CLOSE
    {
        // Evaluar condición del elif, emitir salto
        if (!pila_operandos.empty()) {
            OperandInfo condicion = pila_operandos.top(); pila_operandos.pop();
            std::string etiqueta_siguiente_else = generador_codigo.nuevaEtiqueta();
            generador_codigo.emitirSaltoCondicional(condicion.valor, etiqueta_siguiente_else, "ELIF condición falsa", condicion.es_literal);
            pila_etiquetas_else.push(etiqueta_siguiente_else);
        }
    }
      KEY_OPEN_CLOSE 
      {
          /* Nuevo ámbito para ELIF */
          tabla_simbolos.entrarBloc();
      }
      block_instructions 
      KEY_OPEN_CLOSE
      {
          /* Cerrar ámbito ELIF */
          try { tabla_simbolos.salirBloc(); } catch (const std::exception& e) { yyerror(e.what()); }
          // Goto a fin
          if (!pila_etiquetas_fin.empty()) {
              std::string etiqueta_fin = pila_etiquetas_fin.top(); 
              generador_codigo.emitirGoto(etiqueta_fin, "Fin ELIF");
          }
      }
      else_chain
    | FI_COND
      KEY_OPEN_CLOSE 
      {
          // Emitir etiqueta else antes del else
          if (!pila_etiquetas_else.empty()) {
            std::string etiqueta_else = pila_etiquetas_else.top(); pila_etiquetas_else.pop();
            generador_codigo.emitirEtiqueta(etiqueta_else, "Etiqueta ELSE");
          }
          /* Nuevo ámbito para ELSE */
          tabla_simbolos.entrarBloc();
      }
      block_instructions 
      KEY_OPEN_CLOSE
      {
          /* Cerrar ámbito ELSE */
          try { tabla_simbolos.salirBloc(); } catch (const std::exception& e) { yyerror(e.what()); }
      }
;

while_statement:
      BUCLE_MENTRE PAR_OPEN 
      {
          // Etiqueta de inicio del while
          std::string etiqueta_inicio = generador_codigo.nuevaEtiqueta();
          generador_codigo.emitirEtiqueta(etiqueta_inicio, "Inicio WHILE");
          pila_etiquetas_inicio.push(etiqueta_inicio);
      }
      expression PAR_CLOSE
      {
          // Evaluar condición, if_false goto fin
          if (!pila_operandos.empty()) {
              OperandInfo condicion = pila_operandos.top(); pila_operandos.pop();
              std::string etiqueta_fin = generador_codigo.nuevaEtiqueta();
              generador_codigo.emitirSaltoCondicional(condicion.valor, etiqueta_fin, "WHILE condición falsa", condicion.es_literal);
              pila_etiquetas_fin.push(etiqueta_fin);
          }
      }
      {
          /* Entrar bloque WHILE */
          tabla_simbolos.entrarBloc();
      }
      KEY_OPEN_CLOSE block_instructions KEY_OPEN_CLOSE
      {
          /* Salir bloque WHILE */
          try {
              tabla_simbolos.salirBloc();
          } catch (const std::exception& e) {
              yyerror(e.what());
          }
          // Goto inicio
          if (!pila_etiquetas_inicio.empty()) {
              std::string etiqueta_inicio = pila_etiquetas_inicio.top(); pila_etiquetas_inicio.pop();
              generador_codigo.emitirGoto(etiqueta_inicio, "Volver al inicio WHILE");
              // Ahora pop fin y emitir etiqueta
              if (!pila_etiquetas_fin.empty()) {
                  std::string etiqueta_fin = pila_etiquetas_fin.top(); pila_etiquetas_fin.pop();
                  generador_codigo.emitirEtiqueta(etiqueta_fin, "Fin WHILE");
              }
          }
      }
    ;

/* recorrer (INIT; COND; INCR) ç ... ç */
for_statement:
      BUCLE_PER PAR_OPEN for_init PUNTICOMA 
      {
          // Después de init, etiqueta inicio
          std::string etiqueta_inicio = generador_codigo.nuevaEtiqueta();
          generador_codigo.emitirEtiqueta(etiqueta_inicio, "Inicio FOR");
          pila_etiquetas_inicio.push(etiqueta_inicio);
      }
      expression PUNTICOMA 
      {
          // Evaluar condición, if_false goto fin
          if (!pila_operandos.empty()) {
              OperandInfo condicion = pila_operandos.top(); pila_operandos.pop();
              std::string etiqueta_fin = generador_codigo.nuevaEtiqueta();
              generador_codigo.emitirSaltoCondicional(condicion.valor, etiqueta_fin, "FOR condición falsa", condicion.es_literal);
              pila_etiquetas_fin.push(etiqueta_fin);
          }
      }
      for_update PAR_CLOSE
      {
          /* Entrar bloque FOR */
          tabla_simbolos.entrarBloc();
      }
      KEY_OPEN_CLOSE block_instructions 
      {
          // Emitir update después del cuerpo del bucle, antes de goto inicio
          if (!for_update_op.empty()) {
              if (for_update_op.substr(0, 3) == "INC") {
                  std::string id = for_update_op.substr(4);
                  std::string temp = generador_codigo.nuevaTemp();
                  generador_codigo.emitir("+", id, "1", temp, "", "Incremento en for", TipoBasico::T_ENTER, TipoBasico::T_ENTER, TipoBasico::T_ENTER, false, true);
                  generador_codigo.emitirAsignacion(id, temp, "Asignación ++");
              } else if (for_update_op.substr(0, 3) == "DEC") {
                  std::string id = for_update_op.substr(4);
                  std::string temp = generador_codigo.nuevaTemp();
                  generador_codigo.emitir("-", id, "1", temp, "", "Decremento en for", TipoBasico::T_ENTER, TipoBasico::T_ENTER, TipoBasico::T_ENTER, false, true);
                  generador_codigo.emitirAsignacion(id, temp, "Asignación --");
              } else if (for_update_op.substr(0, 7) == "POSTINC") {
                  std::string id = for_update_op.substr(8);
                  std::string temp = generador_codigo.nuevaTemp();
                  generador_codigo.emitir("+", id, "1", temp, "", "Incremento post en for", TipoBasico::T_ENTER, TipoBasico::T_ENTER, TipoBasico::T_ENTER, false, true);
                  generador_codigo.emitirAsignacion(id, temp, "Asignación ++");
              } else if (for_update_op.substr(0, 7) == "POSTDEC") {
                  std::string id = for_update_op.substr(8);
                  std::string temp = generador_codigo.nuevaTemp();
                  generador_codigo.emitir("-", id, "1", temp, "", "Decremento post en for", TipoBasico::T_ENTER, TipoBasico::T_ENTER, TipoBasico::T_ENTER, false, true);
                  generador_codigo.emitirAsignacion(id, temp, "Asignación --");
              }
              for_update_op = "";
          }
      }
      KEY_OPEN_CLOSE
      {
          /* Salir bloque FOR */
          try {
              tabla_simbolos.salirBloc();
          } catch (const std::exception& e) {
              yyerror(e.what());
          }
          // Después del bloque y update, goto inicio
          if (!pila_etiquetas_inicio.empty()) {
              std::string etiqueta_inicio = pila_etiquetas_inicio.top(); pila_etiquetas_inicio.pop();
              generador_codigo.emitirGoto(etiqueta_inicio, "Volver al inicio FOR");
              // Emitir etiqueta fin
              if (!pila_etiquetas_fin.empty()) {
                  std::string etiqueta_fin = pila_etiquetas_fin.top(); pila_etiquetas_fin.pop();
                  generador_codigo.emitirEtiqueta(etiqueta_fin, "Fin FOR");
              }
          }
      }
    ;

for_init:
      for_declaration
    | assignment
    | %empty  /* vacío */
;

for_declaration:
      type ID 
      {
        TipoBasico tipo_var = stringToTipoBasico(current_type);
        Descripcion desc(TipoDesc::D_VAR, tipo_var);
        try {
            tabla_simbolos.posar(*$2, desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        delete $2;
      }
    | type ID ASSIGN expression
      {
        TipoBasico tipo_var = stringToTipoBasico(current_type);
        if (!ValidacionTipos::esCompatible(tipo_var, $4)) {
            yyerror("Tipos incompatibles en inicialización en for");
        }
        Descripcion desc(TipoDesc::D_VAR, tipo_var);
        try {
            tabla_simbolos.posar(*$2, desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        // Emitir asignación inicial
        if (!pila_operandos.empty()) {
            OperandInfo valor = pila_operandos.top(); pila_operandos.pop();
            generador_codigo.emitirAsignacion(*$2, valor.valor, "Inicialización en for", valor.tipo, valor.es_literal);
        }
        delete $2;
      }
      

for_update:
      assignment
      {
          for_update_op = "";
      }
    | INC ID
      {
          for_update_op = "INC " + *$2;
          delete $2;
      }
    | DEC ID
      {
          for_update_op = "DEC " + *$2;
          delete $2;
      }
    | ID INC
      {
          for_update_op = "POSTINC " + *$1;
          delete $1;
      }
    | ID DEC
      {
          for_update_op = "POSTDEC " + *$1;
          delete $1;
      }
    | %empty
      {
          for_update_op = "";
      }

block_instructions: %empty 
      /* vacío */
    | block_instructions statement
    ;

statement:
    error PUNTICOMA { yyerrok; }
    |  declaration
    | assignment PUNTICOMA
    | conditional
    | while_statement
    | for_statement
    | return_statement PUNTICOMA
    | expression PUNTICOMA
;


return_statement:
    RET expression 
    {
        funcion_actual.ha_retornado = true;

        if (!ValidacionTipos::esCompatible(funcion_actual.tipo_retorno, $2)) {
            yyerror("Tipo de retorno incompatible con el retorno de función");
        }
        // Emitir return
        if (!pila_operandos.empty()) {
            OperandInfo valor = pila_operandos.top(); pila_operandos.pop();
            generador_codigo.emitirReturn(valor.valor, "Retorno de función", valor.tipo, valor.es_literal);
        }
    }
;

arguments: 
    %empty
    {
        $$ = new std::vector<TipoBasico>();
    }
    | argument_list
    {
        $$ = $1;
    }
;

argument_list:
    expression
    {
        $$ = new std::vector<TipoBasico>();
        $$->push_back($1);
        // Emitir param para el argumento
        if (!pila_operandos.empty()) {
            OperandInfo arg = pila_operandos.top(); pila_operandos.pop();
            generador_codigo.emitirParam(arg.valor, "Parámetro de función", arg.tipo, arg.es_literal);
        }
    }
    | argument_list COMA expression
    {
        $1->push_back($3);
        $$ = $1;
        // Emitir param para el argumento
        if (!pila_operandos.empty()) {
            OperandInfo arg = pila_operandos.top(); pila_operandos.pop();
            generador_codigo.emitirParam(arg.valor, "Parámetro de función", arg.tipo, arg.es_literal);
        }
    }
;


%%

void yyerror(const char *s) {
    std::cerr << "Error en la línea " << lexer->lineno() << ": " << s << std::endl;
    
    std::ofstream file("Recopilación_de_errores.txt", std::ios::app);
    if (file.is_open()) {
        file << "Error en la línea " << lexer->lineno() << ": " << s << std::endl;
        file.close();
    }
    
    error_count++;
}


/* .:**++.         
                                                                                  ..++=--==         
                                                                                 :++==-----         
                                                                                .-=------=:         
                                                                                .----====+          
                                                                                .::::--=+-          
                                                                                .::::--=:           
                                                                                .::::---.           
                                                                                .::::---.           
                                                                                .:::----.           
                                                                                .::::---.           
                                                                                .::::---:           
                                                                               .:::::----.          
                                                                              .::::::::---.         
                                                                             .:::::::::::--.        
                                                                            :::::::::::::---.       
                                                                           ::::::::::::::----.      
                                                                          ::::::::::::--------.     
                                                                         .:::::::::::::--------.    
                                                                        .::::::::::::::---------.   
                                                                       .::::::::-:::::----------.   
                                                                      .:::::::--::::------------.   
                                                                     .:::::::--::::------------:    
                                                                    .:::::::::-:::--------------.    
                                                                   .:::::::::::::---------------.    
                                                                 ..:::::::::::::::--------------.      
          .                                                    ..:::::::::::::::::-------------:       
      .++-----....                                           ..::::::::::::::::::---------------        
     :+----:--::::::::..                                   ..:::::::::::::::::::----------------.        
    .------::=+:::----::::::...                    ....::::::::::::::::::::------------------.         
    :----:::-:::--------::::::::::::.........::::::::::::::::::::--:::::-----------------:.          
    .----::-*::::::-----::::::::::::::::::::::::::::::::::::::-:::::::-------===--------.            
     .----:::::::::::--------::::::::::::::::::::::::::::-----:::::-------==-----------.             
      -----::::::::-:::::---------::::::::::::::::::-------::::---------=------------.               
      .---------::::---:::::--------------------------------------------------------.                
       .-----------------------:-::::::::::::::-----------------------------------.                  
          -+---------------------------------------------------------------------.                    
           .+-----------------------------------------------------------------:.                      
             .=-----------------------------------------------------=-------..                        
              ..++-------------------------------------------------------..                           
                  .===------------------------------------------------.                               
                     ..:=+=-------------------------------------=-...                                 
                          .:--===-----------------------=--:.                                         
                               ...::-==+++++==--::....                                                
                                                                                                     
                                                                                                     
Esta banana soporta todo el peso del parser sobre su infinito potasio.
*/