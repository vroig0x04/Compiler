#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>
#include "taula_simbols.h"

// Implementación de métodos de Descripcion
std::string Descripcion::tipoBasicoToString() const {
    return tipoBasicoToString(tipo_basico);
}

std::string Descripcion::tipoBasicoToString(TipoBasico tb) {
    switch(tb) {
        case TipoBasico::T_VOID:     return "void";
        case TipoBasico::T_ENTER:    return "enter";
        case TipoBasico::T_CARACTER: return "caracter";
        case TipoBasico::T_CADENA:   return "cadena";
        case TipoBasico::T_BOOLEA:   return "boolea";
        case TipoBasico::T_TUPLA:    return "tupla";
        case TipoBasico::T_UNKNOWN:  return "desconocido";
        default:                     return "?";
    }
}

std::string Descripcion::toString() const {
    std::string tipoDescStr;
    switch(tipo) {
        case TipoDesc::D_NUL:  tipoDescStr = "NUL"; break;
        case TipoDesc::D_VAR:  tipoDescStr = "VAR"; break;
        case TipoDesc::D_CONST: tipoDescStr = "CONST"; break;
        case TipoDesc::D_PROC: tipoDescStr = "PROC"; break;
        case TipoDesc::D_CAMP: tipoDescStr = "CAMP"; break;
        case TipoDesc::D_ARG:  tipoDescStr = "ARG"; break;
        default:     tipoDescStr = "?"; break;
    }
    return tipoDescStr + "(" + tipoBasicoToString() + ")";
}

// Funciones helper para validación
namespace ValidacionTipos {
    bool esNumerico(TipoBasico t) {
        return t == TipoBasico::T_ENTER;
    }

    bool esCompatible(TipoBasico t1, TipoBasico t2) {
        // Mismo tipo siempre es compatible
        if (t1 == t2) return true;
        
        // Compatibilidad numérica (conversión implícita permitida)
        if (esNumerico(t1) && esNumerico(t2)) return true;
        
        return false;
    }

    TipoBasico mayorTipo(TipoBasico t1, TipoBasico t2) {
        if (t1 == TipoBasico::T_UNKNOWN) return t2;
        if (t2 == TipoBasico::T_UNKNOWN) return t1;
        if (t1 == TipoBasico::T_ENTER && t2 == TipoBasico::T_ENTER) return TipoBasico::T_ENTER;
        return t1;
    }

    std::string tipoToString(TipoBasico t) {
        return Descripcion::tipoBasicoToString(t);
    }
}

// Constructor
TablaSimbolos::TablaSimbolos() {
    buidar();
}

void TablaSimbolos::buidar() {
    n = 0;
    td.clear();
    te.clear();
    ta.clear();
    te.push_back(EntradaTE());
    ta.resize(100,0);
    ta[0] = 0;
    //std::cout << "Tabla de simbolos vaciada." << std::endl;
}

void TablaSimbolos::entrarBloc() {
    n++;
    if(n >= ta.size()) ta.resize(n*2);
    ta[n] = ta[n-1];
    //std::cout << "Entrando en bloque nivel: " << n << std::endl;
}

void TablaSimbolos::salirBloc() {
    if(n==0) throw std::runtime_error("Error: intentar salir del bloque global.");
    int lini = ta[n];
    int lfi = ta[n-1];
    n--;
    for(int i=lini;i>lfi;--i){
        EntradaTE &backup = te[i];
        if(backup.np==-1) td.erase(backup.id);
        else td[backup.id] = EntradaTD(backup.np, backup.d);
    }
    //std::cout << "Salida de bloque. Nivel actual: " << n << std::endl;
}

void TablaSimbolos::posar(const std::string &id, Descripcion d) {
    auto it = td.find(id);
    if(it != td.end() && it->second.np == n){
        throw std::runtime_error("Error semántico: '" + id + "' ya definido en nivel " + std::to_string(n));
    }
    int idxe = ta[n]+1;
    ta[n] = idxe;
    if(idxe>=te.size()) te.resize(idxe+1);
    int np_ant = -1;
    Descripcion d_ant;
    if(it != td.end()){
        np_ant = it->second.np;
        d_ant = it->second.d;
    }
    te[idxe] = EntradaTE(id,np_ant,d_ant);
    td[id] = EntradaTD(n,d);
    
    std::ofstream file("Estados_tabla_de_simbolos.txt", std::ios::app);
    if (file.is_open()) {
        file << "Simbolo '" << id << "' añadido en nivel " << n << std::endl;
        file.close();
    }
}

Descripcion TablaSimbolos::consultar(const std::string &id) const {
    auto it = td.find(id);
    if(!(it==td.end())){
        return it->second.d;
    } else {
        throw std::runtime_error("Error semántico: '" + id + "' no declarado.");
    } 
    
}

void TablaSimbolos::imprimirEstado() const {
    std::ofstream file("Estados_tabla_de_simbolos.txt", std::ios::app);
    if (!file.is_open()) return;
    
    file << "\n--- Estado TD (Nivel " << n << ") ---\n";
    for(auto &p: td){
        file << "ID: " << p.first 
                  << " | Nivel: " << p.second.np
                  << " | Tipo: " << p.second.d.toString() << std::endl;
    }
    file << "----------------------------------\n";
    file.close();
}
