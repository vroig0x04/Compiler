#ifndef OPTIMIZACION_H
#define OPTIMIZACION_H

#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <iostream>

class Optimizador {
public:
    std::vector<std::string> optimizarDesdeArchivo(const std::string& nombreArchivo) {
        std::vector<std::string> lineas;
        std::ifstream archivo(nombreArchivo);
        std::string linea;
        
        while (std::getline(archivo, linea)) {
            // Limpiar el número de línea inicial (ej: "1.\t")
            size_t posTab = linea.find('\t');
            if (posTab != std::string::npos) {
                lineas.push_back(linea.substr(posTab + 1));
            } else {
                lineas.push_back(linea);
            }
        }
        archivo.close();

        // Aplicamos 3 pasadas para asegurar que las optimizaciones en cadena se realicen
        std::vector<std::string> codigo = lineas;
        for(int i = 0; i < 3; ++i) {
            codigo = aplicarPasada(codigo);
        }
        return codigo;
    }

private:
    std::vector<std::string> aplicarPasada(const std::vector<std::string>& entrada) {
        std::vector<std::string> salida;
        
        for (size_t i = 0; i < entrada.size(); ++i) {
            std::string actual = entrada[i];
            std::smatch m;

            // --- 1. SIMPLIFICACIONES ALGEBRAICAS DIRECTAS ---
            actual = std::regex_replace(actual, std::regex("([\\w\\d]+)\\s*\\+\\s*0"), "$1");
            actual = std::regex_replace(actual, std::regex("([\\w\\d]+)\\s*\\*\\s*1"), "$1");
            actual = std::regex_replace(actual, std::regex("([\\w\\d]+)\\s*\\*\\s*0"), "0");

            // --- 2. ELIMINACIÓN DE ASIGNACIONES REDUNDANTES (x = x) ---
            if (std::regex_search(actual, m, std::regex("^\\s*([\\w\\d]+)\\s*=\\s*\\1\\s*($|//)"))) {
                continue;
            }

            // --- 3. ELIMINACIÓN DE CÓDIGO INACCESIBLE (Tras return o goto) ---
            salida.push_back(actual);
            if (actual.find("return") != std::string::npos || 
               (actual.find("goto") != std::string::npos && actual.find("if") == std::string::npos)) {
                // Saltamos todo hasta encontrar una etiqueta o el fin de la función
                while (i + 1 < entrada.size() && 
                       entrada[i+1].find(":") == std::string::npos && 
                       entrada[i+1].find("// Fin") == std::string::npos) {
                    i++;
                }
                continue;
            }

            // --- 4. PROPAGACIÓN DE COPIAS / TEMPORALES ---
            // Detecta: t20 = y  Y LUEGO  y = t20  => Borra ambos o simplifica
            if (i + 1 < entrada.size()) {
                std::smatch m1, m2;
                if (std::regex_search(actual, m1, std::regex("^\\s*(t\\d+)\\s*=\\s*(.+?)\\s*($|//)")) &&
                    std::regex_search(entrada[i+1], m2, std::regex("^\\s*([\\w\\d]+)\\s*=\\s*(t\\d+)\\s*($|//)"))) {
                    
                    if (m1[1].str() == m2[2].str()) { 
                        salida.pop_back(); 
                        
                        // Reconstruimos la instrucción fusionada: m2[1] = m1[2]
                        std::string nuevaInstr = m2[1].str() + " = " + m1[2].str();
                        size_t commentPos = entrada[i+1].find("//");
                        if (commentPos != std::string::npos) {
                            nuevaInstr += "  " + entrada[i+1].substr(commentPos);
                        }
                        
                        salida.push_back(nuevaInstr); 
                        i++; 
                        continue;
                    }
                }
            }
        }
        return salida;
    }
};

#endif