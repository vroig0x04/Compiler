#ifndef GENERADOR_X64_H
#define GENERADOR_X64_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <set>
#include <sstream>
#include "generador_tres_dir.h"

class GeneradorX64 {
private:
    std::vector<std::string> section_data;
    std::vector<std::string> section_text;
    std::map<std::string, int> variable_offsets;
    int stack_size = 0;
    std::string current_function;
    
    // Registros scratch seguros 
    const std::string SCRATCH_1 = "r10";
    const std::string SCRATCH_2 = "r11";
    // Registros para paso de parámetros (System V ABI)
    std::vector<std::string> param_regs = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
    // Para llamadas a funciones
    int current_param_index = 0;

    std::map<std::string, std::string> string_literals;
    int string_literal_counter = 0;

public:
    GeneradorX64() {}

    void generarPreambulo() {
        section_data.push_back("default rel");
        section_data.push_back("global main");
        section_data.push_back("section .data");
        section_data.push_back("    format_int: db \"%ld\", 10, 0");
        section_data.push_back("    format_char: db \"%c\", 10, 0"); 
        section_data.push_back("    format_str: db \"%s\", 10, 0");
        section_data.push_back("    format_in:  db \"%ld\", 0");
        section_data.push_back("");
        
        section_text.push_back("section .text");
        section_text.push_back("    extern printf");
        section_text.push_back("    extern scanf");
        section_text.push_back("");
    }

    void generarPrologo(const std::string& nombre_funcion, const std::vector<InstruccionTresDir>& instrucciones, const std::vector<std::string>& params_entrada) {
    current_function = nombre_funcion;
    variable_offsets.clear();
    current_param_index = 0;

    // 1. Identificar variables (locales) y sus tamaños
    std::set<std::string> locals;
    std::map<std::string, int> var_sizes;
    
    // Convertir params_entrada a set para búsqueda rápida
    std::set<std::string> params_set(params_entrada.begin(), params_entrada.end());
    
    for (const auto& instr : instrucciones) {
        // Analizar resultado
        if (!instr.resultado.empty() && 
            !esLiteral(instr.resultado) && 
            instr.resultado != nombre_funcion && 
            params_set.find(instr.resultado) == params_set.end()) {
            locals.insert(instr.resultado);
            if (instr.tipo_resultado == TipoBasico::T_TUPLA) {
                var_sizes[instr.resultado] = 16;
            } else if (var_sizes.find(instr.resultado) == var_sizes.end()) {
                var_sizes[instr.resultado] = 8;
            }
        }
        
        // Analizar operando1
        if (!instr.operando1.empty() && !esLiteral(instr.operando1) && !esEtiqueta(instr.operando1) && params_set.find(instr.operando1) == params_set.end()) {
            locals.insert(instr.operando1);
            if (instr.tipo_operando1 == TipoBasico::T_TUPLA) {
                var_sizes[instr.operando1] = 16;
            } else if (var_sizes.find(instr.operando1) == var_sizes.end()) {
                var_sizes[instr.operando1] = 8;
            }
        }

        // Analizar operando2
        if (!instr.operando2.empty() && !esLiteral(instr.operando2) && !esEtiqueta(instr.operando2) && params_set.find(instr.operando2) == params_set.end()) {
            locals.insert(instr.operando2);
             if (instr.tipo_operando2 == TipoBasico::T_TUPLA) {
                var_sizes[instr.operando2] = 16;
            } else if (var_sizes.find(instr.operando2) == var_sizes.end()) {
                var_sizes[instr.operando2] = 8;
            }
        }
    }

    // 2. Asignar offsets
    int offset = 8; 
    
    // Primero parámetros (asumimos 8 bytes)
    for (const auto& param : params_entrada) {
        variable_offsets[param] = offset;
        offset += 8;
    }

    // Luego variables locales
    for (const auto& var : locals) {
        variable_offsets[var] = offset;
        offset += var_sizes[var]; // 8 o 16
    }

    // Alinear stack a 16 bytes
    stack_size = offset - 8;
    if (stack_size % 16 != 0) stack_size += (16 - (stack_size % 16));
    
    section_text.push_back(nombre_funcion + ":");
    section_text.push_back("    push rbp");
    section_text.push_back("    mov rbp, rsp");
    if (stack_size > 0)
        section_text.push_back("    sub rsp, " + std::to_string(stack_size));
        
    // Copiar parámetros
    for (size_t i = 0; i < params_entrada.size(); ++i) {
        std::string param = params_entrada[i];
        int local_off = variable_offsets[param];
        if (i < 6) {
            section_text.push_back("    mov [rbp - " + std::to_string(local_off) + "], " + param_regs[i]);
        } else {
            int stack_off = 16 + (i - 6) * 8;
            section_text.push_back("    mov rax, [rbp + " + std::to_string(stack_off) + "]");
            section_text.push_back("    mov [rbp - " + std::to_string(local_off) + "], rax");
        }
    }
}

    void generarEpilogo() {
        if (current_function == "main") {
             section_text.push_back("    xor rax, rax");
        }
        section_text.push_back("    leave");
        section_text.push_back("    ret");
        section_text.push_back("");
    }
    
    // Helper para registrar string literales
    std::string registrarStringLiteral(const std::string& str_raw) {
        if (string_literals.count(str_raw)) {
            return string_literals[str_raw];
        }
        std::string label = "LC_" + std::to_string(string_literal_counter++);
        // Limpiar comillas inicial y final si existen
        std::string content = str_raw; 
        // Aseguramos null terminator
        std::string def = label + ": db " + content + ", 0";
        section_data.push_back(def);
        string_literals[str_raw] = label;
        return label;
    }

    void traducirInstruccion(const InstruccionTresDir& instr) {
        if (!instr.etiqueta.empty()) {
            if (instr.etiqueta != current_function)
                section_text.push_back("." + instr.etiqueta + ":"); 
        }

        std::string op = instr.operacion;
        
        if (op.empty() && instr.resultado.empty()) return;

        section_text.push_back("    ; " + instr.toString());

        if (op == "=") {
            // Asignación con soporte para Cadenas y Tuplas
            if (instr.tipo_resultado == TipoBasico::T_TUPLA) {
                 // Copia de tupla (16 bytes)
                 int src_offset = variable_offsets[instr.operando1];
                 int dst_offset = variable_offsets[instr.resultado];
                 
                 // Elem 0: [rbp - offset]
                 section_text.push_back("    mov rax, [rbp - " + std::to_string(src_offset) + "]");
                 section_text.push_back("    mov [rbp - " + std::to_string(dst_offset) + "], rax");
                 
                 // Elem 1: [rbp - (offset + 8)]
                 section_text.push_back("    mov rax, [rbp - " + std::to_string(src_offset + 8) + "]");
                 section_text.push_back("    mov [rbp - " + std::to_string(dst_offset + 8) + "], rax");
            }
            // Si operando1 es literal de cadena ("..."), registrar y cargar dirección
            else if (instr.es_literal1 && instr.operando1.size() > 0 && instr.operando1[0] == '"') {
                 std::string lbl = registrarStringLiteral(instr.operando1);
                 section_text.push_back("    lea rax, [rel " + lbl + "]");
                 guardarDesdeReg(instr.resultado, "rax");
            } else {
                 cargarEnReg("rax", instr.operando1, instr.es_literal1);
                 guardarDesdeReg(instr.resultado, "rax");
            }
        } 
        else if (op == "+") {
            cargarEnReg("rax", instr.operando1, instr.es_literal1);
            if (instr.es_literal2) {
                section_text.push_back("    add rax, " + instr.operando2);
            } else {
                section_text.push_back("    add rax, " + refMemoria(instr.operando2));
            }
            guardarDesdeReg(instr.resultado, "rax");
        }
        else if (op == "-") {
            cargarEnReg("rax", instr.operando1, instr.es_literal1);
            if (instr.es_literal2) {
                section_text.push_back("    sub rax, " + instr.operando2);
            } else {
                section_text.push_back("    sub rax, " + refMemoria(instr.operando2));
            }
            guardarDesdeReg(instr.resultado, "rax");
        }
        else if (op == "*") {
            cargarEnReg("rax", instr.operando1, instr.es_literal1);
            if (instr.es_literal2) {
                section_text.push_back("    imul rax, " + instr.operando2);
            } else {
                section_text.push_back("    imul rax, " + refMemoria(instr.operando2));
            }
            guardarDesdeReg(instr.resultado, "rax");
        }
        else if (op == "/" || op == "//") {
            cargarEnReg("rax", instr.operando1, instr.es_literal1);
            section_text.push_back("    cqo");
            std::string divisor;
            if (instr.es_literal2) {
                section_text.push_back("    mov " + SCRATCH_1 + ", " + instr.operando2);
                divisor = SCRATCH_1;
            } else {
                divisor = "qword " + refMemoria(instr.operando2);
            }
            section_text.push_back("    idiv " + divisor);
            guardarDesdeReg(instr.resultado, "rax");
        }
        else if (op == "%") {
            cargarEnReg("rax", instr.operando1, instr.es_literal1);
            section_text.push_back("    cqo");
            std::string divisor;
            if (instr.es_literal2) {
                section_text.push_back("    mov " + SCRATCH_1 + ", " + instr.operando2);
                divisor = SCRATCH_1;
            } else {
                divisor = "qword " + refMemoria(instr.operando2);
            }
            section_text.push_back("    idiv " + divisor);
            guardarDesdeReg(instr.resultado, "rdx");
        }
        else if (op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=") {
            cargarEnReg("rax", instr.operando1, instr.es_literal1);
            if (instr.es_literal2) {
                 section_text.push_back("    cmp rax, " + instr.operando2);
            } else {
                 section_text.push_back("    cmp rax, " + refMemoria(instr.operando2));
            }
            std::string setcc;
            if (op == "==") setcc = "sete";
            else if (op == "!=") setcc = "setne";
            else if (op == "<") setcc = "setl";
            else if (op == ">") setcc = "setg";
            else if (op == "<=") setcc = "setle";
            else if (op == ">=") setcc = "setge";
            
            section_text.push_back("    " + setcc + " al");
            section_text.push_back("    movzx rax, al");
            guardarDesdeReg(instr.resultado, "rax");
        }
        else if (op == "&&" || op == "||") {
             cargarEnReg("rax", instr.operando1, instr.es_literal1);
             std::string op2_loc;
             if (instr.es_literal2) {
                 std::string val = instr.operando2;
                 if (val == "veritat") val = "1";
                 else if (val == "falsetat") val = "0";
                 section_text.push_back("    mov " + SCRATCH_1 + ", " + val);
                 op2_loc = SCRATCH_1;
             } else {
                 section_text.push_back("    mov " + SCRATCH_1 + ", " + refMemoria(instr.operando2));
                 op2_loc = SCRATCH_1;
             }
             if (op == "&&") section_text.push_back("    and rax, " + op2_loc);
             else section_text.push_back("    or rax, " + op2_loc);
             guardarDesdeReg(instr.resultado, "rax");
        }
        else if (op == "!") {
            cargarEnReg("rax", instr.operando1, instr.es_literal1);
            section_text.push_back("    cmp rax, 0");
            section_text.push_back("    sete al");
            section_text.push_back("    movzx rax, al");
            guardarDesdeReg(instr.resultado, "rax");
        }
        else if (op == "goto") {
            section_text.push_back("    jmp ." + instr.operando1);
        }
        else if (op == "if_false") {
            cargarEnReg("rax", instr.operando1, instr.es_literal1);
            section_text.push_back("    cmp rax, 0");
            std::string label = instr.operando2.substr(5);
            section_text.push_back("    je ." + label);
        }
        else if (op == "param") {
            if (current_param_index < 6) {
                if (instr.es_literal1 && instr.operando1.size() > 0 && instr.operando1[0] == '"') {
                     std::string lbl = registrarStringLiteral(instr.operando1);
                     section_text.push_back("    lea " + param_regs[current_param_index] + ", [rel " + lbl + "]");
                } else {
                     cargarEnReg(param_regs[current_param_index], instr.operando1, instr.es_literal1);
                }
            } else {
                cargarEnReg("rax", instr.operando1, instr.es_literal1);
                section_text.push_back("    push rax");
            }
            current_param_index++;
        }
        else if (op == "call") {
             int stack_params = (current_param_index > 6) ? (current_param_index - 6) : 0;
             if (stack_params % 2 != 0) {
                 section_text.push_back("    sub rsp, 8");
             }
             section_text.push_back("    call " + instr.operando1);
             if (stack_params > 0) {
                 int total_pop = stack_params * 8;
                 if (stack_params % 2 != 0) total_pop += 8;
                 section_text.push_back("    add rsp, " + std::to_string(total_pop));
             }
             if (!instr.resultado.empty()) {
                 guardarDesdeReg(instr.resultado, "rax");
             }
             current_param_index = 0;
        }
        else if (op == "return") {
            if (!instr.operando1.empty()) {
                cargarEnReg("rax", instr.operando1, instr.es_literal1);
            }
            section_text.push_back("    leave");
            section_text.push_back("    ret");
        } else if (op == "tuple_get") {
             int tuple_offset = variable_offsets[instr.operando1];
             std::string res_loc = "[rbp - " + std::to_string(variable_offsets[instr.resultado]) + "]";
             
             if (instr.es_literal2) {
                 // Indice literal
                 int idx = std::stoi(instr.operando2);
                 int effective_offset = tuple_offset + (idx * 8); 
                 section_text.push_back("    mov rax, [rbp - " + std::to_string(effective_offset) + "]");
                 section_text.push_back("    mov " + res_loc + ", rax");
             } else {
                 // Indice variable
                 cargarEnReg("rcx", instr.operando2, false);
                 section_text.push_back("    imul rcx, 8");
                 section_text.push_back("    mov rax, rbp");
                 section_text.push_back("    sub rax, " + std::to_string(tuple_offset)); // base address (elem 0)
                 section_text.push_back("    sub rax, rcx"); 
                 section_text.push_back("    mov rbx, [rax]");
                 section_text.push_back("    mov " + res_loc + ", rbx");
             }
        } else if (op == "tuple_set") {
             int tuple_offset = variable_offsets[instr.resultado];
             cargarEnReg("rdx", instr.operando2, instr.es_literal2); // Load value to RDX
             
             if (instr.es_literal1) {
                 int idx = std::stoi(instr.operando1);
                 int effective_offset = tuple_offset + (idx * 8); 
                 section_text.push_back("    mov [rbp - " + std::to_string(effective_offset) + "], rdx");
             } else {
                 cargarEnReg("rcx", instr.operando1, false); // Load index to RCX
                 section_text.push_back("    imul rcx, 8");
                 section_text.push_back("    mov rax, rbp");
                 section_text.push_back("    sub rax, " + std::to_string(tuple_offset));
                 section_text.push_back("    sub rax, rcx");
                 section_text.push_back("    mov [rax], rdx");
             }
        } else if (op == "print") {
            std::string fmt = "format_int";
            if (instr.tipo_operando1 == TipoBasico::T_CARACTER) {
                fmt = "format_char";
            } else if (instr.tipo_operando1 == TipoBasico::T_CADENA) {
                fmt = "format_str";
            }
            
            cargarEnReg("rsi", instr.operando1, instr.es_literal1);
            section_text.push_back("    lea rdi, [rel " + fmt + "]");
            section_text.push_back("    xor rax, rax"); 
            section_text.push_back("    call printf");
        }
        else if (op == "read") {
            if (!variable_offsets.count(instr.operando1)) {
                 section_text.push_back("    ; Error: variable " + instr.operando1 + " no encontrada para read");
                 return;
            }
            section_text.push_back("    lea rsi, " + refMemoria(instr.operando1));
            section_text.push_back("    lea rdi, [rel format_in]");
            section_text.push_back("    xor rax, rax");
            section_text.push_back("    call scanf");
        }
        else if (op == "cast") {
            cargarEnReg("rax", instr.operando1, instr.es_literal1);
            guardarDesdeReg(instr.resultado, "rax");
        }
    }

    void guardarEnArchivo(const std::string& nombre_archivo) {
        std::ofstream archivo(nombre_archivo);
        if (!archivo.is_open()) return;
        
        // Escribir section .data
        for (const auto& linea : section_data) {
            archivo << linea << std::endl;
        }
        archivo << std::endl;
        
        // Escribir section .text
        for (const auto& linea : section_text) {
            archivo << linea << std::endl;
        }
        archivo.close();
    }

private:
    bool esLiteral(const std::string& s) {
        if (s.empty()) return false;
        // Números, chars, o booleanos o strings
        return isdigit(s[0]) || s[0] == '-' || s[0] == '\'' || s[0] == '"' || s == "veritat" || s == "falsetat";
    }
    
    // Devuelve referencia a memoria [rbp - offset]
    std::string refMemoria(const std::string& var) {
        if (variable_offsets.find(var) != variable_offsets.end()) {
            return "[rbp - " + std::to_string(variable_offsets[var]) + "]";
        }
        return "[rbp - 0] ; VAR DESCONOCIDA: " + var; 
    }
    
    // Carga operando (literal o var) en registro
    void cargarEnReg(const std::string& reg, const std::string& op, bool es_lit) {
        if (es_lit) {
            std::string val = op;
            if (op == "veritat") val = "1";
            else if (op == "falsetat") val = "0";
            else if (op.front() == '\'') val = std::to_string((int)op[1]); 
            else if (op.front() == '"') {
                 std::string lbl = registrarStringLiteral(op);
                 section_text.push_back("    lea " + reg + ", [rel " + lbl + "]");
                 return; 
            }
            
            section_text.push_back("    mov " + reg + ", " + val);
        } else {
            section_text.push_back("    mov " + reg + ", " + refMemoria(op));
        }
    }
    
    // Guarda registro en variable
    void guardarDesdeReg(const std::string& var, const std::string& reg) {
        if (variable_offsets.find(var) == variable_offsets.end()) {
             section_text.push_back("    ; Fatal: variable destino " + var + " no existe en stack");
        } else {
             section_text.push_back("    mov " + refMemoria(var) + ", " + reg);
        }
    }

    bool esEtiqueta(const std::string& s) {
        return s.rfind("L", 0) == 0;
    }
    public:
    void generar_asm_optimizado(const std::string& archivo_entrada, const std::string& archivo_salida) {
        section_data.clear();
        section_text.clear();
        variable_offsets.clear();
        string_literals.clear();
        string_literal_counter = 0;
        
        generarPreambulo();
        
        std::ifstream input(archivo_entrada);
        std::string linea;
        std::vector<InstruccionTresDir> instrucciones_func;
        std::string nombre_func_actual;
        std::vector<std::string> params_func_actual;
        
        while (std::getline(input, linea)) {
            // limpiar
            size_t first = linea.find_first_not_of(" \t");
            if (first == std::string::npos) continue;
            size_t last = linea.find_last_not_of(" \t");
            linea = linea.substr(first, (last - first + 1));
            
            // Ignorar linea vacia
            if (linea.empty()) continue;

             // Parsear número de línea "1. codigo"
            size_t dot_pos = linea.find('.');
            if (dot_pos != std::string::npos && dot_pos < 10) { 
                linea = linea.substr(dot_pos + 1);
                // limpieza
                first = linea.find_first_not_of(" \t");
                if (first != std::string::npos) {
                     linea = linea.substr(first);
                } else {
                    linea = "";
                }
            }
            
            if (linea.empty()) continue;

            // Detectar fin de función
            if (linea.find("// Fin de función:") != std::string::npos) {
                if (!nombre_func_actual.empty()) {
                    generarPrologo(nombre_func_actual, instrucciones_func, params_func_actual);
                    for(const auto& inst : instrucciones_func) {
                        traducirInstruccion(inst);
                    }
                    generarEpilogo();
                }
                instrucciones_func.clear();
                nombre_func_actual = "";
                params_func_actual.clear();
                continue;
            }

            // Detectar inicio de función y params en comentario
            size_t colon_pos = linea.find(':');
            if (colon_pos != std::string::npos) {
                std::string label = linea.substr(0, colon_pos);
                size_t comment_pos = linea.find("//");
                if (comment_pos != std::string::npos) {
                    std::string comment = linea.substr(comment_pos + 2);
                    if (comment.find("Función:") != std::string::npos) {
                        // Es inicio de función
                        nombre_func_actual = label;
                        size_t params_pos = comment.find("PARAMS:");
                        if (params_pos != std::string::npos) {
                            std::string params_str = comment.substr(params_pos + 7);
                            size_t pipe_pos = params_str.find('|');
                            if (pipe_pos != std::string::npos) {
                                params_str = params_str.substr(0, pipe_pos);
                            }
                            
                            std::stringstream ss(params_str);
                            std::string segment;
                            while(std::getline(ss, segment, ',')) {
                                // limpieza
                                segment.erase(0, segment.find_first_not_of(" \t")); 
                                segment.erase(segment.find_last_not_of(" \t") + 1); 
                                if(!segment.empty()) params_func_actual.push_back(segment);
                            }
                        }
                        continue; 
                    }
                }
            }
            if (!nombre_func_actual.empty()) {
                InstruccionTresDir instr = parsearLineaTAC(linea);
                if (!instr.operacion.empty() || !instr.resultado.empty() || !instr.etiqueta.empty()) {
                    instrucciones_func.push_back(instr);
                }
            }
        }
        
        guardarEnArchivo(archivo_salida);
    }

private:
    InstruccionTresDir parsearLineaTAC(std::string linea) {
        InstruccionTresDir instr;
        
        // Separar comentario
        size_t comment_pos = linea.find("//");
        if (comment_pos != std::string::npos) {
            instr.comentario = linea.substr(comment_pos + 2);
            linea = linea.substr(0, comment_pos);
        }
        
        // limpieza
        size_t last = linea.find_last_not_of(" \t");
        if (last == std::string::npos) return instr; 
        linea = linea.substr(0, last + 1);

        // Detectar etiqueta "Lxx:"
        size_t colon_pos = linea.find(':');
        if (colon_pos != std::string::npos) {
            instr.etiqueta = linea.substr(0, colon_pos);
            linea = linea.substr(colon_pos + 1);
            // limpieza
            size_t first = linea.find_first_not_of(" \t");
            if (first == std::string::npos) return instr; 
            linea = linea.substr(first);
        }

        // Analizar instruccion
        std::stringstream ss(linea);
        std::string token1;
        ss >> token1;
        
        if (token1 == "if_false") {
            instr.operacion = "if_false";
            std::string cond;
            ss >> cond;
            if (cond.back() == ',') cond.pop_back(); 
            instr.operando1 = cond;
            instr.es_literal1 = esLiteral(cond);
            std::string goto_kw, label;
            ss >> goto_kw >> label;
            instr.operando2 = "goto " + label; 
        } else if (token1 == "goto") {
            instr.operacion = "goto";
            ss >> instr.operando1;
        } else if (token1 == "param") {
            instr.operacion = "param";
            std::string val;
            char c = ss.peek();
            while(c == ' ' || c == '\t') { ss.get(); c = ss.peek(); }
            
            if (c == '"') {
                 std::getline(ss, val);
            } else {
                 ss >> val;
            }
            instr.operando1 = val;
            
            if (val.find('"') != std::string::npos) instr.tipo_operando1 = TipoBasico::T_CADENA;
            else if (val.find('\'') != std::string::npos) instr.tipo_operando1 = TipoBasico::T_CARACTER;
            else if (isdigit(val[0]) || val[0] == '-') instr.tipo_operando1 = TipoBasico::T_ENTER;
            else if (val == "veritat" || val == "falsetat") instr.tipo_operando1 = TipoBasico::T_BOOLEA;
            
            instr.es_literal1 = esLiteral(val);
        } else if (token1 == "return") {
            instr.operacion = "return";
            ss >> instr.operando1;
            instr.es_literal1 = esLiteral(instr.operando1);
        } else if (token1 == "print") {
            instr.operacion = "print";
            
            char c = ss.peek();
            while(c == ' ' || c == '\t') { ss.get(); c = ss.peek(); }
            
            if (c == '"') {
                std::string parte;
                std::getline(ss, parte);
                size_t first_q = parte.find('"');
                size_t last_q = parte.rfind('"');
                if (first_q != std::string::npos && last_q != std::string::npos && last_q > first_q) {
                     instr.operando1 = parte.substr(first_q, last_q - first_q + 1);
                } else {
                     instr.operando1 = parte;
                }
            } else {
                ss >> instr.operando1; 
            }
            
            instr.es_literal1 = esLiteral(instr.operando1);
            if (instr.es_literal1) {
                if (instr.operando1.find('"') != std::string::npos) instr.tipo_operando1 = TipoBasico::T_CADENA;
                else if (instr.operando1.find('\'') != std::string::npos) instr.tipo_operando1 = TipoBasico::T_CARACTER;
                else instr.tipo_operando1 = TipoBasico::T_ENTER;
            } else {
                 instr.tipo_operando1 = TipoBasico::T_ENTER; 
            }
        } else if (token1 == "read") {
            instr.operacion = "read";
            ss >> instr.operando1;
        } else {
            size_t eq_pos = linea.find('=');
            if (eq_pos != std::string::npos) {
                instr.resultado = token1;
                std::string eq;
                ss >> eq;          
                char c = ss.peek();
                while(c == ' ' || c == '\t') { ss.get(); c = ss.peek(); }
                
                std::string op1;
                if (c == '"') {
                     std::string parte;
                     std::getline(ss, parte);
                     size_t first_q = parte.find('"');
                     size_t last_q = parte.rfind('"');
                     if (first_q != std::string::npos && last_q != std::string::npos && last_q > first_q) {
                         op1 = parte.substr(first_q, last_q - first_q + 1);
                     } else {
                         op1 = parte;
                     }
                     instr.operacion = "=";
                     instr.operando1 = op1;
                } else {
                    ss >> op1;
                    
                    if (op1 == "call") {
                        instr.operacion = "call";
                        ss >> instr.operando1;
                    } else {
                        std::string op;
                        if (ss >> op) {
                            if (op.find("//") == 0) {
                                instr.operacion = "=";
                                instr.operando1 = op1;
                            } else {
                                instr.operacion = op;
                                instr.operando1 = op1;
                                ss >> instr.operando2;
                            }
                        } else {
                            // Asignacion simple
                            instr.operacion = "=";
                            instr.operando1 = op1;
                        }
                    }
                }
                
                instr.es_literal1 = esLiteral(instr.operando1);
                instr.es_literal2 = esLiteral(instr.operando2);
                
            } else {
                if (token1 == "call") {
                    instr.operacion = "call";
                    ss >> instr.operando1;
                } 
            }
        }
        
        if (linea.find('[') != std::string::npos && linea.find('=') != std::string::npos) {
             
             size_t open_br = linea.find('[');
             size_t close_br = linea.find(']');
             size_t eq_pos = linea.find('=');
             
             if (open_br < eq_pos) {
                 instr.operacion = "tuple_set";
                 instr.resultado = linea.substr(0, open_br);
                 instr.resultado.erase(instr.resultado.find_last_not_of(" \t")+1);
                 //limpiar
                 instr.operando1 = linea.substr(open_br+1, close_br - open_br - 1); // index
                 instr.operando2 = linea.substr(eq_pos+1); // value
                 // Limpiar operando2
                 size_t first = instr.operando2.find_first_not_of(" \t");
                 if (first != std::string::npos) {
                     size_t last = instr.operando2.find_last_not_of(" \t");
                     instr.operando2 = instr.operando2.substr(first, last - first + 1);
                 } else {
                     instr.operando2 = "";
                 }
                 
                 instr.tipo_resultado = TipoBasico::T_TUPLA;
             } else {
                 instr.operacion = "tuple_get";
                 instr.resultado = linea.substr(0, eq_pos);
                 // limpiar
                 instr.resultado.erase(instr.resultado.find_last_not_of(" \t")+1);
                 
                 std::string rhs = linea.substr(eq_pos+1);
                 size_t rhs_open = rhs.find('[');
                 size_t rhs_close = rhs.find(']');
                 
                 instr.operando1 = rhs.substr(0, rhs_open);
                 // limpiar
                 instr.operando1.erase(0, instr.operando1.find_first_not_of(" \t"));
                 instr.operando1.erase(instr.operando1.find_last_not_of(" \t")+1);
                 
                 instr.operando2 = rhs.substr(rhs_open+1, rhs_close - rhs_open - 1);
                 
                 instr.tipo_operando1 = TipoBasico::T_TUPLA;
             }
        }
        
        // Definir tipos
        if (instr.operacion == "tuple_get") {
             instr.tipo_operando1 = TipoBasico::T_TUPLA; 
        } else if (instr.operacion == "tuple_set") {
             instr.tipo_resultado = TipoBasico::T_TUPLA;
        }

        if (!instr.comentario.empty()) {
            std::stringstream ss(instr.comentario);
            std::string token;
            while (ss >> token) {
                if (token.find("T1:") == 0) {
                    instr.tipo_operando1 = stringToTipoBasico(token.substr(3));
                } else if (token.find("T2:") == 0) {
                    instr.tipo_operando2 = stringToTipoBasico(token.substr(3));
                } else if (token.find("TR:") == 0) {
                    instr.tipo_resultado = stringToTipoBasico(token.substr(3));
                } else if (token.find("LIT1:") == 0) {
                    instr.es_literal1 = (token.substr(5) == "1");
                } else if (token.find("LIT2:") == 0) {
                    instr.es_literal2 = (token.substr(5) == "1");
                }
            }
        }

        return instr;
    }

    TipoBasico stringToTipoBasico(const std::string& s) {
        if (s == "enter") return TipoBasico::T_ENTER;
        if (s == "caracter") return TipoBasico::T_CARACTER;
        if (s == "cadena") return TipoBasico::T_CADENA;
        if (s == "boolea") return TipoBasico::T_BOOLEA;
        if (s == "tupla") return TipoBasico::T_TUPLA;
        if (s == "void") return TipoBasico::T_VOID;
        return TipoBasico::T_UNKNOWN;
    }


};

#endif // GENERADOR_X64_H
