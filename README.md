# Compilador para el Lenguaje Ç

## 📋 Descripción del Proyecto

Este repositorio contiene la implementación completa de un compilador para **Ç**, un lenguaje imperativo de propósito específico diseñado para la arquitectura **x86_64**. El proyecto constituye una implementación educativa y funcional de un compilador moderno que integra análisis léxico, sintáctico, semántico y generación de código máquina nativo.

El compilador sigue la arquitectura clásica de compiladores, dividiendo el proceso en múltiples fases:

- **Front-end**: Análisis léxico y sintáctico con generación de árbol de sintaxis abstracta (AST)
- **Análisis semántico**: Verificación de tipos y tabla de símbolos
- **Optimización**: Técnicas de optimización a código intermedio
- **Back-end**: Generación de código de máquina x86_64

---

**Available in other languages:** [English](README.en.md)

## 🏗️ Composición del Proyecto

```
Lenguaje C++:     74.9%  | Lógica principal del compilador
Yacc (Bison):     13.7%  | Análisis sintáctico
Assembly (NASM):   9.7%  | Código generado para x86_64
Lex (Flex):        1.3%  | Análisis léxico
Shell:             0.4%  | Scripts de compilación y ejecución
```

## 🛠️ Herramientas y Dependencias

### Requisitos del Sistema

El compilador requiere las siguientes herramientas para su funcionamiento:

| Herramienta | Propósito | Versión Mínima |
|------------|----------|-----------------|
| **G++** | Compilador C++ | 7.0+ |
| **GCC** | Compilador C | 7.0+ |
| **Flex** | Analizador léxico | 2.6+ |
| **Bison** | Generador de parsers | 3.0+ |
| **NASM** | Ensamblador x86_64 | 2.13+ |
| **Bash** | Intérprete de scripts | 4.0+ |

### Instalación de Dependencias

#### Ubuntu/Debian:
```bash
sudo apt-get install build-essential flex bison nasm
```

#### macOS (Homebrew):
```bash
brew install flex bison nasm gcc
```

#### Fedora/RHEL:
```bash
sudo dnf install gcc g++ flex bison nasm
```

## 📁 Estructura del Repositorio

```
Compiler/
├── Codigo/                          # Directorio principal del código fuente
│   ├── lexico.l                     # Definiciones lexicales (Flex)
│   ├── parser.y                     # Gramática del lenguaje (Bison)
│   ├── main.cpp                     # Punto de entrada del compilador
│   ├── taula_simbols.h/cpp          # Tabla de símbolos
│   ├── generador_tres_dir.h         # Generador de código intermedio (3 direcciones)
│   ├── generador_x64.h              # Generador de código x86_64
│   ├── optimizacion.h               # Optimizaciones de código
│   ├── compilar_x64.sh              # Script de compilación del compilador
│   ├── compilar_y_ejecutar.sh       # Script para compilar y ejecutar programas Ç
│   ├── flex_bison.sh                # Script para regenerar lexer/parser
│   ├── test_*.txt                   # Casos de prueba
│   └── codi_prova.txt               # Programa de prueba de ejemplo
├── Output casos de prueba/          # Resultados de ejecución de casos de prueba
└── README.md                        # Este archivo
```

## 🚀 Guía de Uso

### 1. Preparación Inicial

Primero, clone el repositorio y navegue al directorio de código:

```bash
git clone https://github.com/vroig0x04/Compiler.git
cd Compiler/Codigo
```

### 2. Permisos de Ejecución

Es necesario dar permisos de ejecución a los scripts:

```bash
chmod +x compilar_x64.sh
chmod +x compilar_y_ejecutar.sh
chmod +x flex_bison.sh  # Opcional, solo si necesita regenerar el parser
```

### 3. Compilación del Compilador

Para compilar el compilador por primera vez:

```bash
./compilar_x64.sh
```

Este script generará el ejecutable `mi_parser` que es el compilador funcional.

### 4. Compilar y Ejecutar Programas en Ç

Para compilar un programa escrito en el lenguaje Ç:

```bash
./compilar_y_ejecutar.sh <nombre_fichero>
```

**Ejemplo:**

```bash
./compilar_y_ejecutar.sh codi_prova.txt
```

Este comando:
1. Compila el programa `codi_prova.txt` utilizando el compilador
2. Genera el código ensamblador x86_64
3. Ensambla y enlaza el código
4. Ejecuta el programa resultante

### 5. Regenerar el Parser (Opcional)

Si modifica la gramática del lenguaje en `parser.y` o el léxico en `lexico.l`, debe regenerar el parser:

```bash
./flex_bison.sh
```

Luego, recompile el compilador:

```bash
./compilar_x64.sh
```

## 📝 Sintaxis Básica de Ç

El repositorio incluye varios casos de prueba que demuestran la sintaxis:

- **test_basic.txt**: Operaciones básicas y variables
- **test_control.txt**: Estructuras de control (if, while, for)
- **test_funcions.txt**: Definición y llamada de funciones
- **test_tuples.txt**: Manejo de tuplas
- **test_errors_tipus.txt**: Validación de tipos y manejo de errores

Consulte estos archivos para ejemplos de la sintaxis soportada.

## 🧪 Casos de Prueba

El proyecto incluye una suite de casos de prueba que validan:

- ✅ Análisis léxico y sintáctico
- ✅ Verificación de tipos
- ✅ Generación correcta de código
- ✅ Manejo de errores semánticos
- ✅ Operaciones básicas y avanzadas

Los resultados de las ejecuciones se almacenan en el directorio `Output casos de prueba/`.

## 🔧 Fases del Compilador

### Fase 1: Análisis Léxico
Realizado por **Flex** mediante `lexico.l`, tokeniza el código fuente.

### Fase 2: Análisis Sintáctico
Realizado por **Bison** mediante `parser.y`, construye el árbol de sintaxis abstracta (AST).

### Fase 3: Análisis Semántico
Implementado en C++, valida tipos y mantiene la tabla de símbolos mediante `taula_simbols`.

### Fase 4: Generación de Código Intermedio
Generador de código de tres direcciones (`generador_tres_dir.h`) para optimizaciones.

### Fase 5: Optimización
Módulo `optimizacion.h` aplica optimizaciones al código intermedio.

### Fase 6: Generación de Código Máquina
Generador x86_64 (`generador_x64.h`) produce código ensamblador NASM.

### Fase 7: Ensamblado y Enlazado
Realizado por **NASM** y **GCC**, genera el ejecutable final.

## 📊 Arquitectura de x86_64

El compilador genera código optimizado para la arquitectura x86_64 siguiendo las convenciones de llamada del sistema. El código generado es compatible con sistemas Linux/Unix basados en x86_64.

## ⚠️ Licencia y Derechos de Autor

Este software es propiedad intelectual de **Vicent Roig**. La copia, modificación o distribución no autorizada de este archivo, por cualquier medio, está estrictamente prohibida.

## 🤝 Contribuciones

Las contribuciones no son aceptadas en este momento dado el carácter propietario del proyecto.

## 📞 Contacto

Para consultas relacionadas con este proyecto, contacte al propietario del repositorio.

---

**Última actualización:** Septiembre 2026  
**Versión del Compilador:** 1.0  
**Arquitectura Soportada:** x86_64 (64-bit)
