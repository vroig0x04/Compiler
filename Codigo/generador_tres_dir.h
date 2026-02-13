#ifndef GENERADOR_TRES_DIR_H
#define GENERADOR_TRES_DIR_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "taula_simbols.h"

// Estructura para instrucción de tres direcciones
struct InstruccionTresDir {
    std::string etiqueta;      
    std::string operacion;     
    std::string operando1;     
    std::string operando2;     
    std::string resultado;     // Variable destino 
    std::string comentario;    // Comentario opcional
    TipoBasico tipo_operando1 = TipoBasico::T_UNKNOWN; // Tipo del operando1
    TipoBasico tipo_operando2 = TipoBasico::T_UNKNOWN; // Tipo del operando2
    TipoBasico tipo_resultado = TipoBasico::T_UNKNOWN; // Tipo del resultado
    bool es_literal1 = false;                          // ¿Operando 1 es literal?
    bool es_literal2 = false;                          // ¿Operando 2 es literal?
    
    std::string toString() const {
        std::stringstream ss;
        if (!etiqueta.empty()) {
            ss << etiqueta << ": ";
        }
        if (resultado.empty()) {
            // Instrucciones sin resultado 
            ss << operacion << " " << operando1;
            if (!operando2.empty()) {
                ss << ", " << operando2;
            }
        } else {
            // Instrucciones con resultado (asignaciones)
            if (operacion == "=" || operacion.empty()) {
                // Asignación simple
                ss << resultado << " = " << operando1;
                if (!operando2.empty()) {
                    ss << " " << operando2;
                }
            } else if (operacion == "tuple_get") {
                
                ss << resultado << " = " << operando1 << "[" << operando2 << "]";
            } else if (operacion == "tuple_set") {
                
                ss << resultado << "[" << operando1 << "] = " << operando2;
            } else if (operando2.empty()) {
                // Operador unario (!, ++pre, --pre, ++post, --post)
                ss << resultado << " = " << operacion << " " << operando1;
            } else {
                ss << resultado << " = " << operando1 << " " << operacion << " " << operando2;
            }
        }
        if (!comentario.empty()) {
            ss << "  // " << comentario;
        }
        ss << " | T1:" << ValidacionTipos::tipoToString(tipo_operando1) 
           << " T2:" << ValidacionTipos::tipoToString(tipo_operando2)
           << " TR:" << ValidacionTipos::tipoToString(tipo_resultado)
           << " LIT1:" << (es_literal1 ? "1" : "0")
           << " LIT2:" << (es_literal2 ? "1" : "0");
           
        return ss.str();
    }
};

class GeneradorTresDir {
private:
    std::vector<InstruccionTresDir> codigo;
    int contador_temporales = 0;
    int contador_etiquetas = 0;
    
public:
    GeneradorTresDir() = default;
    
    // Generar nuevo temporal
    std::string nuevaTemp() {
        return "t" + std::to_string(contador_temporales++);
    }
    
    // Generar nueva etiqueta
    std::string nuevaEtiqueta() {
        return "L" + std::to_string(contador_etiquetas++);
    }
    
    // Emitir instrucción de tres direcciones
    void emitir(const std::string& operacion, const std::string& operando1,
                const std::string& operando2, const std::string& resultado,
                const std::string& etiqueta = "", const std::string& comentario = "",
                TipoBasico t1 = TipoBasico::T_UNKNOWN, TipoBasico t2 = TipoBasico::T_UNKNOWN, TipoBasico tr = TipoBasico::T_UNKNOWN,
                bool lit1 = false, bool lit2 = false) {
        InstruccionTresDir instr;
        instr.etiqueta = etiqueta;
        instr.operacion = operacion;
        instr.operando1 = operando1;
        instr.operando2 = operando2;
        instr.resultado = resultado;
        instr.comentario = comentario;
        instr.tipo_operando1 = t1;
        instr.tipo_operando2 = t2;
        instr.tipo_resultado = tr;
        instr.es_literal1 = lit1;
        instr.es_literal2 = lit2;
        codigo.push_back(instr);
    }
    
    // Emitir instrucción sin resultado (goto, etc)
    void emitirSinResultado(const std::string& operacion, const std::string& operando1,
                           const std::string& operando2 = "", const std::string& etiqueta = "",
                           const std::string& comentario = "",
                           TipoBasico t1 = TipoBasico::T_UNKNOWN, TipoBasico t2 = TipoBasico::T_UNKNOWN,
                           bool lit1 = false, bool lit2 = false) {
        InstruccionTresDir instr;
        instr.etiqueta = etiqueta;
        instr.operacion = operacion;
        instr.operando1 = operando1;
        instr.operando2 = operando2;
        instr.resultado = "";
        instr.comentario = comentario;
        instr.tipo_operando1 = t1;
        instr.tipo_operando2 = t2;
        instr.tipo_resultado = TipoBasico::T_UNKNOWN;
        instr.es_literal1 = lit1;
        instr.es_literal2 = lit2;
        codigo.push_back(instr);
    }
    
    // Emitir salto condicional (if_false goto)
    void emitirSaltoCondicional(const std::string& condicion, const std::string& etiqueta_destino,
                               const std::string& comentario = "", bool lit_cond = false) {
        emitirSinResultado("if_false", condicion, "goto " + etiqueta_destino, "", comentario, TipoBasico::T_BOOLEA, TipoBasico::T_UNKNOWN, lit_cond, false);
    }
    
    // Emitir goto incondicional
    void emitirGoto(const std::string& etiqueta_destino, const std::string& comentario = "") {
        emitirSinResultado("goto", etiqueta_destino, "", "", comentario);
    }
    
    // Emitir asignación
    void emitirAsignacion(const std::string& destino, const std::string& origen,
                         const std::string& comentario = "", TipoBasico t_origen = TipoBasico::T_UNKNOWN, bool lit_origen = false) {
        emitir("=", origen, "", destino, "", comentario, t_origen, TipoBasico::T_UNKNOWN, t_origen, lit_origen, false);
    }
    
    // Emitir salto incondicional
    void emitirSalto(const std::string& etiqueta, const std::string& comentario = "") {
        emitirSinResultado("goto", etiqueta, "", "", comentario);
    }
    
    // Emitir salto condicional
    void emitirSaltoCond(const std::string& condicion, const std::string& etiqueta,
                        bool si_falso = true, const std::string& comentario = "") {
        std::string op = si_falso ? "if_false" : "if";
        std::string operando2 = si_falso ? "goto " + etiqueta : etiqueta;
        emitirSinResultado(op, condicion, operando2, "", comentario);
    }
    
    // Emitir etiqueta
    void emitirEtiqueta(const std::string& etiqueta, const std::string& comentario = "") {
        emitirSinResultado("", "", "", etiqueta, comentario);
    }
    
    // Emitir llamada a función
    void emitirCall(const std::string& funcion, const std::string& resultado = "",
                   const std::string& comentario = "") {
        if (resultado.empty()) {
            emitirSinResultado("call", funcion, "", "", comentario);
        } else {
            emitir("call", funcion, "", resultado, "", comentario);
        }
    }
    
    // Emitir parámetro para llamada a función
    void emitirParam(const std::string& parametro, const std::string& comentario = "",
                    TipoBasico tipo = TipoBasico::T_UNKNOWN, bool es_literal = false) {
        emitirSinResultado("param", parametro, "", "", comentario, tipo, TipoBasico::T_UNKNOWN, es_literal, false);
    }
    
    // Emitir return
    void emitirReturn(const std::string& valor = "", const std::string& comentario = "",
                     TipoBasico tipo = TipoBasico::T_UNKNOWN, bool es_literal = false) {
        if (valor.empty()) {
            emitirSinResultado("return", "", "", "", comentario);
        } else {
            emitirSinResultado("return", valor, "", "", comentario, tipo, TipoBasico::T_UNKNOWN, es_literal, false);
        }
    }
    
    // Emitir print
    void emitirPrint(const std::string& expresion, const std::string& comentario = "",
                    TipoBasico tipo = TipoBasico::T_UNKNOWN, bool es_literal = false) {
        emitirSinResultado("print", expresion, "", "", comentario, tipo, TipoBasico::T_UNKNOWN, es_literal, false);
    }
    
    // Emitir read
    void emitirRead(const std::string& variable, const std::string& comentario = "") {
        emitirSinResultado("read", variable, "", "", comentario);
    }
    
    // Emitir cast
    void emitirCast(const std::string& tipo, const std::string& expresion, const std::string& resultado,
                   const std::string& comentario = "", bool es_literal = false) {
        emitir("cast", tipo, expresion, resultado, "", comentario, TipoBasico::T_UNKNOWN, TipoBasico::T_UNKNOWN, TipoBasico::T_UNKNOWN, false, es_literal);
    }
    
    // Emitir lectura de tupla: resultado = tupla[indice]
    void emitirTupleGet(const std::string& tupla, int indice, const std::string& resultado,
                       const std::string& comentario = "") {
        emitir("tuple_get", tupla, std::to_string(indice), resultado, "", comentario, 
               TipoBasico::T_UNKNOWN, TipoBasico::T_ENTER, TipoBasico::T_UNKNOWN,
               false, true); // indice es literal
    }

    // Emitir escritura en tupla: tupla[indice] = valor
    void emitirTupleSet(const std::string& tupla, int indice, const std::string& valor,
                       const std::string& comentario = "", bool es_literal_valor = false) {
        emitir("tuple_set", std::to_string(indice), valor, tupla, "", comentario, 
               TipoBasico::T_ENTER, TipoBasico::T_UNKNOWN, TipoBasico::T_UNKNOWN, 
               true, es_literal_valor); // indice es literal
    }
    
    // Obtener todo el código generado
    const std::vector<InstruccionTresDir>& obtenerCodigo() const {
        return codigo;
    }
    
    // Imprimir código de tres direcciones
    void imprimir(std::ostream& os = std::cout) const {
        for (size_t i = 0; i < codigo.size(); ++i) {
            os << std::to_string(i + 1) << ".\t" << codigo[i].toString() << "\n";
        }
    }
    
    // Guardar código en archivo
    void guardarEnArchivo(const std::string& nombre_archivo) const {
        std::ofstream archivo(nombre_archivo);
        if (archivo.is_open()) {
            imprimir(archivo);
            archivo.close();
            std::cout << "Código de tres direcciones guardado en: " << nombre_archivo << "\n";
        } else {
            std::cerr << "Error al abrir archivo: " << nombre_archivo << "\n";
        }
    }
};

#endif 
