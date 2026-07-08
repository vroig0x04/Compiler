/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"
 
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


#line 166 "parser.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_MOD_CONSTANT = 3,               /* MOD_CONSTANT  */
  YYSYMBOL_TIPUS_ENTER = 4,                /* TIPUS_ENTER  */
  YYSYMBOL_TIPUS_CARACTER = 5,             /* TIPUS_CARACTER  */
  YYSYMBOL_TIPUS_CADENA = 6,               /* TIPUS_CADENA  */
  YYSYMBOL_TIPUS_BOOLEA = 7,               /* TIPUS_BOOLEA  */
  YYSYMBOL_TIPUS_VOID = 8,                 /* TIPUS_VOID  */
  YYSYMBOL_OBJ_TUPLA = 9,                  /* OBJ_TUPLA  */
  YYSYMBOL_ASSIGN = 10,                    /* ASSIGN  */
  YYSYMBOL_PUNTICOMA = 11,                 /* PUNTICOMA  */
  YYSYMBOL_COMA = 12,                      /* COMA  */
  YYSYMBOL_PUNT = 13,                      /* PUNT  */
  YYSYMBOL_DOBLEPUNT = 14,                 /* DOBLEPUNT  */
  YYSYMBOL_SUMA = 15,                      /* SUMA  */
  YYSYMBOL_RESTA = 16,                     /* RESTA  */
  YYSYMBOL_MULT = 17,                      /* MULT  */
  YYSYMBOL_DIV = 18,                       /* DIV  */
  YYSYMBOL_MODUL = 19,                     /* MODUL  */
  YYSYMBOL_DIVISIO_ENTER = 20,             /* DIVISIO_ENTER  */
  YYSYMBOL_IGUALTAT = 21,                  /* IGUALTAT  */
  YYSYMBOL_DIFERENT = 22,                  /* DIFERENT  */
  YYSYMBOL_MENOR_IGUAL = 23,               /* MENOR_IGUAL  */
  YYSYMBOL_MAJOR_IGUAL = 24,               /* MAJOR_IGUAL  */
  YYSYMBOL_MENOR = 25,                     /* MENOR  */
  YYSYMBOL_MAJOR = 26,                     /* MAJOR  */
  YYSYMBOL_MES_IGUAL = 27,                 /* MES_IGUAL  */
  YYSYMBOL_MENYS_IGUAL = 28,               /* MENYS_IGUAL  */
  YYSYMBOL_INC = 29,                       /* INC  */
  YYSYMBOL_DEC = 30,                       /* DEC  */
  YYSYMBOL_AND = 31,                       /* AND  */
  YYSYMBOL_OR = 32,                        /* OR  */
  YYSYMBOL_NOT = 33,                       /* NOT  */
  YYSYMBOL_PAR_OPEN = 34,                  /* PAR_OPEN  */
  YYSYMBOL_PAR_CLOSE = 35,                 /* PAR_CLOSE  */
  YYSYMBOL_KEY_OPEN_CLOSE = 36,            /* KEY_OPEN_CLOSE  */
  YYSYMBOL_COND_OPEN = 37,                 /* COND_OPEN  */
  YYSYMBOL_COND_CLOSE = 38,                /* COND_CLOSE  */
  YYSYMBOL_CLAUDATOR_OPEN = 39,            /* CLAUDATOR_OPEN  */
  YYSYMBOL_CLAUDATOR_CLOSE = 40,           /* CLAUDATOR_CLOSE  */
  YYSYMBOL_INICI_COND = 41,                /* INICI_COND  */
  YYSYMBOL_CONTINUACIO_COND = 42,          /* CONTINUACIO_COND  */
  YYSYMBOL_FI_COND = 43,                   /* FI_COND  */
  YYSYMBOL_BUCLE_MENTRE = 44,              /* BUCLE_MENTRE  */
  YYSYMBOL_BUCLE_PER = 45,                 /* BUCLE_PER  */
  YYSYMBOL_INICI_FUNCIO = 46,              /* INICI_FUNCIO  */
  YYSYMBOL_RETORN = 47,                    /* RETORN  */
  YYSYMBOL_RET = 48,                       /* RET  */
  YYSYMBOL_FUNC_IMPRIMEIX = 49,            /* FUNC_IMPRIMEIX  */
  YYSYMBOL_FUNC_ENTRADA = 50,              /* FUNC_ENTRADA  */
  YYSYMBOL_FUNC_CAST = 51,                 /* FUNC_CAST  */
  YYSYMBOL_ERROR_TOKEN = 52,               /* ERROR_TOKEN  */
  YYSYMBOL_CHARACTER_LITERAL = 53,         /* CHARACTER_LITERAL  */
  YYSYMBOL_MAIN = 54,                      /* MAIN  */
  YYSYMBOL_FLOAT = 55,                     /* FLOAT  */
  YYSYMBOL_INTEGER = 56,                   /* INTEGER  */
  YYSYMBOL_CARACTER = 57,                  /* CARACTER  */
  YYSYMBOL_STRING = 58,                    /* STRING  */
  YYSYMBOL_BOOL = 59,                      /* BOOL  */
  YYSYMBOL_ID = 60,                        /* ID  */
  YYSYMBOL_YYACCEPT = 61,                  /* $accept  */
  YYSYMBOL_start = 62,                     /* start  */
  YYSYMBOL_programa = 63,                  /* programa  */
  YYSYMBOL_declaraciones = 64,             /* declaraciones  */
  YYSYMBOL_main_function = 65,             /* main_function  */
  YYSYMBOL_66_1 = 66,                      /* $@1  */
  YYSYMBOL_function_def = 67,              /* function_def  */
  YYSYMBOL_68_2 = 68,                      /* $@2  */
  YYSYMBOL_params = 69,                    /* params  */
  YYSYMBOL_param_list = 70,                /* param_list  */
  YYSYMBOL_param = 71,                     /* param  */
  YYSYMBOL_return_type = 72,               /* return_type  */
  YYSYMBOL_declaration = 73,               /* declaration  */
  YYSYMBOL_obj_compl = 74,                 /* obj_compl  */
  YYSYMBOL_modifier = 75,                  /* modifier  */
  YYSYMBOL_type = 76,                      /* type  */
  YYSYMBOL_assignment = 77,                /* assignment  */
  YYSYMBOL_expression = 78,                /* expression  */
  YYSYMBOL_logical_or = 79,                /* logical_or  */
  YYSYMBOL_logical_and = 80,               /* logical_and  */
  YYSYMBOL_equality = 81,                  /* equality  */
  YYSYMBOL_relational = 82,                /* relational  */
  YYSYMBOL_additive = 83,                  /* additive  */
  YYSYMBOL_multiplicative = 84,            /* multiplicative  */
  YYSYMBOL_unary = 85,                     /* unary  */
  YYSYMBOL_primary = 86,                   /* primary  */
  YYSYMBOL_cast_expression = 87,           /* cast_expression  */
  YYSYMBOL_input_output_expression = 88,   /* input_output_expression  */
  YYSYMBOL_literal = 89,                   /* literal  */
  YYSYMBOL_conditional = 90,               /* conditional  */
  YYSYMBOL_91_3 = 91,                      /* $@3  */
  YYSYMBOL_92_4 = 92,                      /* $@4  */
  YYSYMBOL_93_5 = 93,                      /* $@5  */
  YYSYMBOL_94_6 = 94,                      /* $@6  */
  YYSYMBOL_else_chain = 95,                /* else_chain  */
  YYSYMBOL_96_7 = 96,                      /* $@7  */
  YYSYMBOL_97_8 = 97,                      /* $@8  */
  YYSYMBOL_98_9 = 98,                      /* $@9  */
  YYSYMBOL_99_10 = 99,                     /* $@10  */
  YYSYMBOL_100_11 = 100,                   /* $@11  */
  YYSYMBOL_while_statement = 101,          /* while_statement  */
  YYSYMBOL_102_12 = 102,                   /* $@12  */
  YYSYMBOL_103_13 = 103,                   /* $@13  */
  YYSYMBOL_104_14 = 104,                   /* $@14  */
  YYSYMBOL_for_statement = 105,            /* for_statement  */
  YYSYMBOL_106_15 = 106,                   /* $@15  */
  YYSYMBOL_107_16 = 107,                   /* $@16  */
  YYSYMBOL_108_17 = 108,                   /* $@17  */
  YYSYMBOL_109_18 = 109,                   /* $@18  */
  YYSYMBOL_for_init = 110,                 /* for_init  */
  YYSYMBOL_for_declaration = 111,          /* for_declaration  */
  YYSYMBOL_for_update = 112,               /* for_update  */
  YYSYMBOL_block_instructions = 113,       /* block_instructions  */
  YYSYMBOL_statement = 114,                /* statement  */
  YYSYMBOL_return_statement = 115,         /* return_statement  */
  YYSYMBOL_arguments = 116,                /* arguments  */
  YYSYMBOL_argument_list = 117             /* argument_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   518

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  125
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  243

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   315


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   148,   148,   152,   154,   157,   158,   159,   165,   163,
     228,   227,   317,   319,   322,   323,   326,   341,   343,   347,
     359,   374,   393,   414,   423,   443,   485,   490,   491,   492,
     493,   494,   499,   532,   567,   587,   611,   615,   633,   640,
     658,   665,   680,   695,   702,   717,   732,   747,   762,   769,
     785,   801,   808,   824,   840,   855,   870,   877,   891,   906,
     921,   922,   939,   959,   963,   985,  1019,  1046,  1084,  1085,
    1086,  1090,  1105,  1116,  1128,  1133,  1138,  1143,  1152,  1159,
    1169,  1175,  1151,  1193,  1203,  1211,  1221,  1227,  1202,  1239,
    1237,  1258,  1265,  1274,  1257,  1302,  1309,  1319,  1324,  1301,
    1373,  1374,  1375,  1379,  1390,  1412,  1416,  1421,  1426,  1431,
    1436,  1441,  1443,  1447,  1448,  1449,  1450,  1451,  1452,  1453,
    1454,  1459,  1475,  1479,  1486,  1496
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "MOD_CONSTANT",
  "TIPUS_ENTER", "TIPUS_CARACTER", "TIPUS_CADENA", "TIPUS_BOOLEA",
  "TIPUS_VOID", "OBJ_TUPLA", "ASSIGN", "PUNTICOMA", "COMA", "PUNT",
  "DOBLEPUNT", "SUMA", "RESTA", "MULT", "DIV", "MODUL", "DIVISIO_ENTER",
  "IGUALTAT", "DIFERENT", "MENOR_IGUAL", "MAJOR_IGUAL", "MENOR", "MAJOR",
  "MES_IGUAL", "MENYS_IGUAL", "INC", "DEC", "AND", "OR", "NOT", "PAR_OPEN",
  "PAR_CLOSE", "KEY_OPEN_CLOSE", "COND_OPEN", "COND_CLOSE",
  "CLAUDATOR_OPEN", "CLAUDATOR_CLOSE", "INICI_COND", "CONTINUACIO_COND",
  "FI_COND", "BUCLE_MENTRE", "BUCLE_PER", "INICI_FUNCIO", "RETORN", "RET",
  "FUNC_IMPRIMEIX", "FUNC_ENTRADA", "FUNC_CAST", "ERROR_TOKEN",
  "CHARACTER_LITERAL", "MAIN", "FLOAT", "INTEGER", "CARACTER", "STRING",
  "BOOL", "ID", "$accept", "start", "programa", "declaraciones",
  "main_function", "$@1", "function_def", "$@2", "params", "param_list",
  "param", "return_type", "declaration", "obj_compl", "modifier", "type",
  "assignment", "expression", "logical_or", "logical_and", "equality",
  "relational", "additive", "multiplicative", "unary", "primary",
  "cast_expression", "input_output_expression", "literal", "conditional",
  "$@3", "$@4", "$@5", "$@6", "else_chain", "$@7", "$@8", "$@9", "$@10",
  "$@11", "while_statement", "$@12", "$@13", "$@14", "for_statement",
  "$@15", "$@16", "$@17", "$@18", "for_init", "for_declaration",
  "for_update", "block_instructions", "statement", "return_statement",
  "arguments", "argument_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-158)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-99)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -158,    14,    28,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
       5,   -16,  -158,  -158,  -158,  -158,    40,   211,   -20,   211,
      20,    26,  -158,     6,    -4,    55,    57,   211,    32,   458,
    -158,    37,    52,    68,   107,  -158,    62,   458,  -158,   458,
     458,   458,   458,    87,    97,    98,  -158,  -158,  -158,  -158,
      16,   123,   115,   125,    41,   142,    54,   153,  -158,    61,
    -158,  -158,  -158,   149,   211,   124,    52,   211,  -158,   165,
    -158,  -158,  -158,   -11,   458,   458,   211,   458,   458,  -158,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,  -158,  -158,   458,  -158,  -158,  -158,
    -158,  -158,   458,  -158,   147,   148,   168,  -158,   150,   172,
      13,   125,    41,   142,   142,    54,    54,    54,    54,   153,
     153,  -158,  -158,  -158,  -158,  -158,  -158,   141,   152,  -158,
    -158,   458,  -158,   458,  -158,    79,  -158,  -158,   156,  -158,
     177,  -158,   155,   163,   164,   458,   130,  -158,   189,   196,
    -158,  -158,  -158,  -158,   209,   145,  -158,  -158,  -158,  -158,
      15,  -158,   458,   458,   458,   458,  -158,  -158,  -158,  -158,
     458,   458,   116,   161,  -158,   212,  -158,  -158,    54,    54,
      49,   184,   190,   458,   214,  -158,   216,  -158,  -158,    85,
     458,   458,   458,   191,  -158,   216,  -158,   217,  -158,  -158,
     193,  -158,  -158,  -158,   -19,   205,   265,   170,   171,    29,
    -158,   197,  -158,  -158,  -158,  -158,  -158,  -158,  -158,    63,
     200,   203,   201,  -158,  -158,  -158,  -158,   325,   458,  -158,
     206,   195,   385,  -158,  -158,  -158,   207,  -158,  -158,   445,
    -158,    63,  -158
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,    26,    27,    28,    29,    30,    31,
       0,     0,     4,     6,     5,     7,     0,     0,     0,     0,
       0,     0,    23,     0,     0,     0,     0,    12,     0,     0,
      19,     0,    17,     0,    13,    14,     0,     0,    20,     0,
       0,     0,     0,     0,     0,     0,    74,    77,    75,    76,
      64,     0,    36,    38,    40,    43,    48,    51,    56,    60,
      68,    69,    63,    24,     0,     0,    17,     0,    16,     0,
      58,    59,    57,     0,     0,     0,     0,   122,     0,    21,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    61,    62,     0,    18,     8,    10,
      15,    22,     0,    70,     0,     0,     0,   124,     0,   123,
       0,    37,    39,    41,    42,    46,    47,    44,    45,    49,
      50,    52,    53,    54,    55,    25,   111,     0,     0,    73,
      72,     0,    67,     0,    65,     0,   111,    66,     0,   125,
       0,     9,     0,     0,     0,     0,    64,   114,     0,     0,
     116,   117,   118,   112,     0,     0,    71,   113,    78,    91,
     102,   121,     0,     0,     0,     0,   115,   120,   119,    11,
       0,     0,     0,     0,   101,     0,   100,    32,    34,    35,
       0,     0,     0,     0,   103,    95,    65,    79,    92,     0,
       0,     0,     0,     0,    93,     0,   104,     0,    33,    80,
       0,    96,   111,   111,   110,     0,     0,     0,     0,     0,
     105,     0,    81,    94,   106,   107,   108,   109,    97,    83,
       0,     0,     0,    82,   111,    84,    89,     0,     0,   111,
       0,     0,     0,    99,    85,    90,     0,    86,   111,     0,
      87,    83,    88
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
     178,   181,   242,  -158,  -158,   -15,  -157,   -29,  -158,   179,
     167,    35,   -69,    22,   -14,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,    10,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,  -158,
    -158,  -158,  -131,  -158,  -158,  -158,  -158
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    12,    13,   126,    14,   127,    33,    34,
      35,    65,   147,    16,    17,    18,   148,   149,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,   150,
     170,   193,   202,   219,   223,   228,   236,   238,   241,   229,
     151,   171,   194,   200,   152,   191,   204,   220,   230,   175,
     176,   211,   135,   153,   154,   108,   109
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      51,   102,    23,   174,    25,   155,    29,    30,    69,   110,
     207,   208,    36,    73,     3,   115,   116,   117,   118,     5,
       6,     7,     8,     9,   103,    70,    71,    72,    88,    89,
      19,     4,     5,     6,     7,     8,     9,    10,    20,   162,
      24,   209,    37,    38,    21,   104,   105,   210,   107,    97,
      77,    22,    36,   134,    26,    78,   163,   164,   216,   217,
      27,   106,    82,    83,    88,    89,    28,   125,   183,    88,
      89,   205,   206,   128,    11,   172,   121,   122,   123,   124,
     140,    31,     4,     5,     6,     7,     8,     9,    10,   186,
      94,    95,    32,   227,   178,   179,   180,    63,   232,    64,
      88,    89,   138,    66,   139,   221,   222,   239,    39,    40,
     119,   120,    41,    42,   189,   141,   161,   113,   114,    67,
     142,    74,    68,   143,   144,   195,   162,   145,    43,    44,
      45,    75,    76,   177,    79,    46,    47,    48,    49,   146,
     162,   181,   182,   163,   164,   173,   140,    80,     4,     5,
       6,     7,     8,     9,    10,   183,    81,   163,   164,    96,
      98,   196,   197,   198,    77,    84,    85,    86,    87,   165,
      90,    91,    92,    93,    39,    40,   101,   136,    41,    42,
     131,   169,   129,   130,   133,   132,   142,   137,   157,   143,
     144,   156,   158,   145,    43,    44,    45,   159,   160,   231,
     166,    46,    47,    48,    49,   146,   140,   167,     4,     5,
       6,     7,     8,     9,    10,     5,     6,     7,     8,     9,
     168,   184,   187,   185,   190,   188,   192,   199,   201,   203,
     214,   215,   218,   234,    39,    40,   224,   226,    41,    42,
     225,   212,   233,   237,    15,   100,   142,    99,   112,   143,
     144,   242,     0,   145,    43,    44,    45,     0,     0,   111,
       0,    46,    47,    48,    49,   146,   140,     0,     4,     5,
       6,     7,     8,     9,    10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    39,    40,     0,     0,    41,    42,
       0,   213,     0,     0,     0,     0,   142,     0,     0,   143,
     144,     0,     0,   145,    43,    44,    45,     0,     0,     0,
       0,    46,    47,    48,    49,   146,   140,     0,     4,     5,
       6,     7,     8,     9,    10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    39,    40,     0,     0,    41,    42,
       0,   -98,     0,     0,     0,     0,   142,     0,     0,   143,
     144,     0,     0,   145,    43,    44,    45,     0,     0,     0,
       0,    46,    47,    48,    49,   146,   140,     0,     4,     5,
       6,     7,     8,     9,    10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    39,    40,     0,     0,    41,    42,
       0,   235,     0,     0,     0,     0,   142,     0,     0,   143,
     144,     0,     0,   145,    43,    44,    45,     0,     0,     0,
       0,    46,    47,    48,    49,   146,   140,     0,     4,     5,
       6,     7,     8,     9,    10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    39,    40,     0,     0,    41,    42,
       0,   240,     0,     0,     0,     0,   142,    39,    40,   143,
     144,    41,    42,   145,    43,    44,    45,     0,     0,     0,
       0,    46,    47,    48,    49,   146,     0,    43,    44,    45,
       0,     0,     0,     0,    46,    47,    48,    49,    50
};

static const yytype_int16 yycheck[] =
{
      29,    12,    17,   160,    19,   136,    10,    11,    37,    78,
      29,    30,    27,    42,     0,    84,    85,    86,    87,     4,
       5,     6,     7,     8,    35,    39,    40,    41,    15,    16,
      25,     3,     4,     5,     6,     7,     8,     9,    54,    10,
      60,    60,    10,    11,    60,    74,    75,   204,    77,    64,
      34,    11,    67,    40,    34,    39,    27,    28,    29,    30,
      34,    76,    21,    22,    15,    16,    60,    96,    39,    15,
      16,   202,   203,   102,    46,    60,    90,    91,    92,    93,
       1,    26,     3,     4,     5,     6,     7,     8,     9,    40,
      29,    30,    35,   224,   163,   164,   165,    60,   229,    47,
      15,    16,   131,    35,   133,    42,    43,   238,    29,    30,
      88,    89,    33,    34,   183,    36,   145,    82,    83,    12,
      41,    34,    60,    44,    45,    40,    10,    48,    49,    50,
      51,    34,    34,   162,    11,    56,    57,    58,    59,    60,
      10,   170,   171,    27,    28,   160,     1,    32,     3,     4,
       5,     6,     7,     8,     9,    39,    31,    27,    28,    10,
      36,   190,   191,   192,    34,    23,    24,    25,    26,    39,
      17,    18,    19,    20,    29,    30,    11,    36,    33,    34,
      12,    36,    35,    35,    12,    35,    41,    35,    11,    44,
      45,    35,    37,    48,    49,    50,    51,    34,    34,   228,
      11,    56,    57,    58,    59,    60,     1,    11,     3,     4,
       5,     6,     7,     8,     9,     4,     5,     6,     7,     8,
      11,    60,    38,    11,    10,    35,    10,    36,    11,    36,
      60,    60,    35,    38,    29,    30,    36,    36,    33,    34,
      37,    36,    36,    36,     2,    67,    41,    66,    81,    44,
      45,   241,    -1,    48,    49,    50,    51,    -1,    -1,    80,
      -1,    56,    57,    58,    59,    60,     1,    -1,     3,     4,
       5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    33,    34,
      -1,    36,    -1,    -1,    -1,    -1,    41,    -1,    -1,    44,
      45,    -1,    -1,    48,    49,    50,    51,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,     1,    -1,     3,     4,
       5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    33,    34,
      -1,    36,    -1,    -1,    -1,    -1,    41,    -1,    -1,    44,
      45,    -1,    -1,    48,    49,    50,    51,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,     1,    -1,     3,     4,
       5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    33,    34,
      -1,    36,    -1,    -1,    -1,    -1,    41,    -1,    -1,    44,
      45,    -1,    -1,    48,    49,    50,    51,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,     1,    -1,     3,     4,
       5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    33,    34,
      -1,    36,    -1,    -1,    -1,    -1,    41,    29,    30,    44,
      45,    33,    34,    48,    49,    50,    51,    -1,    -1,    -1,
      -1,    56,    57,    58,    59,    60,    -1,    49,    50,    51,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    60
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    62,    63,     0,     3,     4,     5,     6,     7,     8,
       9,    46,    64,    65,    67,    73,    74,    75,    76,    25,
      54,    60,    11,    76,    60,    76,    34,    34,    60,    10,
      11,    26,    35,    69,    70,    71,    76,    10,    11,    29,
      30,    33,    34,    49,    50,    51,    56,    57,    58,    59,
      60,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    60,    47,    72,    35,    12,    60,    78,
      85,    85,    85,    78,    34,    34,    34,    34,    39,    11,
      32,    31,    21,    22,    23,    24,    25,    26,    15,    16,
      17,    18,    19,    20,    29,    30,    10,    76,    36,    72,
      71,    11,    12,    35,    78,    78,    76,    78,   116,   117,
      83,    80,    81,    82,    82,    83,    83,    83,    83,    84,
      84,    85,    85,    85,    85,    78,    66,    68,    78,    35,
      35,    12,    35,    12,    40,   113,    36,    35,    78,    78,
       1,    36,    41,    44,    45,    48,    60,    73,    77,    78,
      90,   101,   105,   114,   115,   113,    35,    11,    37,    34,
      34,    78,    10,    27,    28,    39,    11,    11,    11,    36,
      91,   102,    60,    76,    77,   110,   111,    78,    83,    83,
      83,    78,    78,    39,    60,    11,    40,    38,    35,    83,
      10,   106,    10,    92,   103,    40,    78,    78,    78,    36,
     104,    11,    93,    36,   107,   113,   113,    29,    30,    60,
      77,   112,    36,    36,    60,    60,    29,    30,    35,    94,
     108,    42,    43,    95,    36,    37,    36,   113,    96,   100,
     109,    78,   113,    36,    38,    36,    97,    36,    98,   113,
      36,    99,    95
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    61,    62,    63,    63,    64,    64,    64,    66,    65,
      68,    67,    69,    69,    70,    70,    71,    72,    72,    73,
      73,    73,    73,    73,    74,    74,    75,    76,    76,    76,
      76,    76,    77,    77,    77,    77,    78,    79,    79,    80,
      80,    81,    81,    81,    82,    82,    82,    82,    82,    83,
      83,    83,    84,    84,    84,    84,    84,    85,    85,    85,
      85,    85,    85,    86,    86,    86,    86,    86,    86,    86,
      86,    87,    88,    88,    89,    89,    89,    89,    91,    92,
      93,    94,    90,    95,    96,    97,    98,    99,    95,   100,
      95,   102,   103,   104,   101,   106,   107,   108,   109,   105,
     110,   110,   110,   111,   111,   112,   112,   112,   112,   112,
     112,   113,   113,   114,   114,   114,   114,   114,   114,   114,
     114,   115,   116,   116,   117,   117
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     0,     9,
       0,    10,     0,     1,     1,     3,     2,     0,     2,     3,
       4,     5,     6,     2,     5,     7,     1,     1,     1,     1,
       1,     1,     3,     6,     3,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     2,     2,     2,
       1,     2,     2,     1,     1,     4,     5,     4,     1,     1,
       3,     6,     4,     4,     1,     1,     1,     1,     0,     0,
       0,     0,    12,     0,     0,     0,     0,     0,    12,     0,
       5,     0,     0,     0,    10,     0,     0,     0,     0,    15,
       1,     1,     0,     2,     4,     1,     2,     2,     2,     2,
       0,     0,     2,     2,     1,     2,     1,     1,     1,     2,
       2,     2,     0,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: programa  */
#line 149 "parser.y"
    {
    }
#line 1503 "parser.tab.cpp"
    break;

  case 5: /* declaraciones: function_def  */
#line 157 "parser.y"
                {}
#line 1509 "parser.tab.cpp"
    break;

  case 6: /* declaraciones: main_function  */
#line 158 "parser.y"
                  {}
#line 1515 "parser.tab.cpp"
    break;

  case 7: /* declaraciones: declaration  */
#line 159 "parser.y"
                {}
#line 1521 "parser.tab.cpp"
    break;

  case 8: /* $@1: %empty  */
#line 165 "parser.y"
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
#line 1546 "parser.tab.cpp"
    break;

  case 9: /* main_function: INICI_FUNCIO MAIN PAR_OPEN PAR_CLOSE return_type KEY_OPEN_CLOSE $@1 block_instructions KEY_OPEN_CLOSE  */
#line 187 "parser.y"
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
#line 1588 "parser.tab.cpp"
    break;

  case 10: /* $@2: %empty  */
#line 228 "parser.y"
    { 
        // Emitir etiqueta de función
        std::string params_str;
        for(size_t i=0; i<current_function_params.size(); ++i) {
            params_str += current_function_params[i];
            if(i < current_function_params.size()-1) params_str += ",";
        }
        generador_codigo.emitirSinResultado("", "", "", *(yyvsp[-4].sval), "Función: " + *(yyvsp[-4].sval) + " PARAMS:" + params_str);
        
        /* 1. Insertar la función en el scope actual (global o padre) */
        TipoBasico tipo_retorno = stringToTipoBasico(current_type);
        funcion_actual.nombre = *(yyvsp[-4].sval);
        funcion_actual.tipo_retorno = tipo_retorno;
        funcion_actual.ha_retornado = false;

        Descripcion f(TipoDesc::D_PROC, tipo_retorno, tipos_parametros_actual);
        try {
            tabla_simbolos.posar(*(yyvsp[-4].sval), f);
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
#line 1630 "parser.tab.cpp"
    break;

  case 11: /* function_def: INICI_FUNCIO ID PAR_OPEN params PAR_CLOSE return_type $@2 KEY_OPEN_CLOSE block_instructions KEY_OPEN_CLOSE  */
#line 266 "parser.y"
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
        std::string func_name = *(yyvsp[-8].sval); // Guardar antes de delete
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
        
        delete (yyvsp[-8].sval);
    }
#line 1685 "parser.tab.cpp"
    break;

  case 16: /* param: type ID  */
#line 327 "parser.y"
{
    /* Registramos el parámetro en el ámbito de la función */
    TipoBasico tipo_param = stringToTipoBasico(current_type);

    tipos_parametros_actual.push_back(tipo_param);
    current_function_params.push_back(*(yyvsp[0].sval)); // Guardar nombre del parámetro
    
    Descripcion p(TipoDesc::D_ARG, tipo_param);
    
    
    delete (yyvsp[0].sval);
}
#line 1702 "parser.tab.cpp"
    break;

  case 17: /* return_type: %empty  */
#line 342 "parser.y"
              {current_type="void";}
#line 1708 "parser.tab.cpp"
    break;

  case 19: /* declaration: type ID PUNTICOMA  */
#line 348 "parser.y"
    {   
        TipoBasico tipo_var = stringToTipoBasico(current_type);
        Descripcion desc(TipoDesc::D_VAR, tipo_var);
        try {
            tabla_simbolos.posar(*(yyvsp[-1].sval), desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        delete (yyvsp[-1].sval);
    }
#line 1723 "parser.tab.cpp"
    break;

  case 20: /* declaration: modifier type ID PUNTICOMA  */
#line 360 "parser.y"
    {
        /* Si hay modificador (const), ajustamos el tipo de descripción */
        TipoDesc t = (current_modifier == Etiquetes::CONSTANT) ? TipoDesc::D_CONST : TipoDesc::D_VAR;
        TipoBasico tipo_var = stringToTipoBasico(current_type);
        Descripcion desc(t, tipo_var);
        try {
            tabla_simbolos.posar(*(yyvsp[-1].sval), desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        delete (yyvsp[-1].sval);
        current_modifier = Etiquetes::NONE; // Resetear modificador
    }
#line 1741 "parser.tab.cpp"
    break;

  case 21: /* declaration: type ID ASSIGN expression PUNTICOMA  */
#line 375 "parser.y"
    {
        TipoBasico tipo_var = stringToTipoBasico(current_type);
        if (!ValidacionTipos::esCompatible(tipo_var, (yyvsp[-1].tipo_expr))) {
            yyerror("Tipos incompatibles en inicialización");
        }
        Descripcion desc(TipoDesc::D_VAR, tipo_var);
        try {
            tabla_simbolos.posar(*(yyvsp[-3].sval), desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        // Generar TAC para la asignación
        if (!pila_operandos.empty()) {
            OperandInfo info = pila_operandos.top(); pila_operandos.pop();
            generador_codigo.emitirAsignacion(*(yyvsp[-3].sval), info.valor, "Inicialización", info.tipo, info.es_literal);
        }
        delete (yyvsp[-3].sval);
    }
#line 1764 "parser.tab.cpp"
    break;

  case 22: /* declaration: modifier type ID ASSIGN expression PUNTICOMA  */
#line 394 "parser.y"
    {
        TipoDesc t = (current_modifier == Etiquetes::CONSTANT) ? TipoDesc::D_CONST : TipoDesc::D_VAR;
        TipoBasico tipo_var = stringToTipoBasico(current_type);
        if (!ValidacionTipos::esCompatible(tipo_var, (yyvsp[-1].tipo_expr))) {
            yyerror("Tipos incompatibles en inicialización");
        }
        Descripcion desc(t, tipo_var);
        try {
            tabla_simbolos.posar(*(yyvsp[-3].sval), desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        // Generar TAC para la asignación
        if (!pila_operandos.empty()) {
            OperandInfo info = pila_operandos.top(); pila_operandos.pop();
            generador_codigo.emitirAsignacion(*(yyvsp[-3].sval), info.valor, "Inicialización", info.tipo, info.es_literal);
        }
        delete (yyvsp[-3].sval);
        current_modifier = Etiquetes::NONE;
    }
#line 1789 "parser.tab.cpp"
    break;

  case 23: /* declaration: obj_compl PUNTICOMA  */
#line 415 "parser.y"
    {
        /* La tupla ya se registró en obj_compl */
        name_aux="";
        complex_type="";
    }
#line 1799 "parser.tab.cpp"
    break;

  case 24: /* obj_compl: OBJ_TUPLA MENOR type MAJOR ID  */
#line 424 "parser.y"
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
            tabla_simbolos.posar(*(yyvsp[0].sval), desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        } 
        name_aux = *(yyvsp[0].sval);
        complex_type = "tupla";
        delete (yyvsp[0].sval);
      }
#line 1823 "parser.tab.cpp"
    break;

  case 25: /* obj_compl: OBJ_TUPLA MENOR type MAJOR ID ASSIGN expression  */
#line 444 "parser.y"
      {
        // Declaración de tupla con asignación: tupla<tipo> var = expr;
        TipoBasico tipo_elemento = stringToTipoBasico(current_type);
        if (tipo_elemento == TipoBasico::T_UNKNOWN) {
            yyerror("Tipo de tupla desconocido");
        }
        
        // Validar que la expresión es una tupla
        if ((yyvsp[0].tipo_expr) != TipoBasico::T_TUPLA) {
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
            tabla_simbolos.posar(*(yyvsp[-2].sval), desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        name_aux = *(yyvsp[-2].sval);
        complex_type = "tupla";
        
        // Generar asignación si hay operandos
        if (!pila_operandos.empty()) {
             OperandInfo info = pila_operandos.top(); pila_operandos.pop();
             // La asignación debe copiar los elementos de la tupla temporal 'info.valor' a '*$5'
             generador_codigo.emitirAsignacion(*(yyvsp[-2].sval), info.valor, "Inicialización tupla", TipoBasico::T_TUPLA, false);
        }
        delete (yyvsp[-2].sval);
      }
#line 1866 "parser.tab.cpp"
    break;

  case 26: /* modifier: MOD_CONSTANT  */
#line 485 "parser.y"
                    {current_modifier = Etiquetes::CONSTANT;}
#line 1872 "parser.tab.cpp"
    break;

  case 27: /* type: TIPUS_ENTER  */
#line 490 "parser.y"
                            {current_type="enter";}
#line 1878 "parser.tab.cpp"
    break;

  case 28: /* type: TIPUS_CARACTER  */
#line 491 "parser.y"
                            {current_type="caracter";}
#line 1884 "parser.tab.cpp"
    break;

  case 29: /* type: TIPUS_CADENA  */
#line 492 "parser.y"
                            {current_type="cadena";}
#line 1890 "parser.tab.cpp"
    break;

  case 30: /* type: TIPUS_BOOLEA  */
#line 493 "parser.y"
                            {current_type="boolea";}
#line 1896 "parser.tab.cpp"
    break;

  case 31: /* type: TIPUS_VOID  */
#line 494 "parser.y"
                            {current_type="void";}
#line 1902 "parser.tab.cpp"
    break;

  case 32: /* assignment: ID ASSIGN expression  */
#line 500 "parser.y"
    {
        try {
            Descripcion var = tabla_simbolos.consultar(*(yyvsp[-2].sval));
            if (var.tipo == TipoDesc::D_CONST) {
                yyerror("No se puede reasignar a una constante");
            }
            // Si la variable es tupla y la expresión es tupla, validar tipos de elementos
            if (var.tipo_basico == TipoBasico::T_TUPLA && (yyvsp[0].tipo_expr) == TipoBasico::T_TUPLA) {
                // Validar que el tipo de elemento de la tupla coincida
                if (!var.tipos_tupla.empty()) {
                    TipoBasico tipo_esperado = var.tipos_tupla[0];
                    if (last_tuple_subtype != TipoBasico::T_UNKNOWN && 
                        !ValidacionTipos::esCompatible(tipo_esperado, last_tuple_subtype)) {
                        yyerror("Tipos incompatibles en elementos de tupla");
                    }
                }
            } else if (!ValidacionTipos::esCompatible(var.tipo_basico, (yyvsp[0].tipo_expr))) {
                yyerror("Tipos incompatibles en asignación");
            }
            
            // Pop el valor de la pila y asignar
            if (!pila_operandos.empty()) {
                 OperandInfo info = pila_operandos.top(); pila_operandos.pop();
                 generador_codigo.emitirAsignacion(*(yyvsp[-2].sval), info.valor, "Asignación", info.tipo, info.es_literal);
            }
            
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        name_aux=*(yyvsp[-2].sval);
        delete (yyvsp[-2].sval);
    }
#line 1939 "parser.tab.cpp"
    break;

  case 33: /* assignment: ID CLAUDATOR_OPEN additive CLAUDATOR_CLOSE ASSIGN expression  */
#line 533 "parser.y"
    {
        try { 
            Descripcion var = tabla_simbolos.consultar(*(yyvsp[-5].sval)); 
            if (var.tipo_basico != TipoBasico::T_TUPLA) { // y asumir que arrays no están implementados o usan otra lógica
                 // Si existieran arrays, aquí iría su lógica. Como solo tenemos tuplas por ahora:
                 yyerror("Variable no es una tupla");
            }
            if (!ValidacionTipos::esNumerico((yyvsp[-3].tipo_expr))) {
                yyerror("El índice debe ser numérico");
            }
            
            // Validar tipo de asignación a elemento
            if (!var.tipos_tupla.empty()) {
                 TipoBasico tipo_elemento = var.tipos_tupla[0];
                 if (!ValidacionTipos::esCompatible(tipo_elemento, (yyvsp[0].tipo_expr))) {
                     yyerror("Tipo incompatible en asignación a elemento de tupla");
                 }
            }

            // Pop expression (valor a asignar) e índice
            if (pila_operandos.size() >= 2) {
                OperandInfo valor = pila_operandos.top(); pila_operandos.pop();
                OperandInfo indice = pila_operandos.top(); pila_operandos.pop();
                
                // Generar código: id[indice] = valor
                generador_codigo.emitir("tuple_set", indice.valor, valor.valor, *(yyvsp[-5].sval), "", "Asignación tupla", 
                                       TipoBasico::T_ENTER, valor.tipo, TipoBasico::T_TUPLA, indice.es_literal, valor.es_literal);
            }
        } catch (const std::exception& e) { 
            yyerror(e.what()); 
        }
        name_aux=*(yyvsp[-5].sval);
        delete (yyvsp[-5].sval);
    }
#line 1978 "parser.tab.cpp"
    break;

  case 34: /* assignment: ID MES_IGUAL additive  */
#line 568 "parser.y"
    {
        try { 
            Descripcion var = tabla_simbolos.consultar(*(yyvsp[-2].sval)); 
            if (!ValidacionTipos::esNumerico(var.tipo_basico)) {
                yyerror("Operando de += debe ser numérico");
            }
            // Pop el valor de additive
            if (!pila_operandos.empty()) {
                OperandInfo info = pila_operandos.top(); pila_operandos.pop();
                std::string temp = generador_codigo.nuevaTemp();
                generador_codigo.emitir("+", *(yyvsp[-2].sval), info.valor, temp, "", "+=", var.tipo_basico, info.tipo, var.tipo_basico, false, info.es_literal);
                generador_codigo.emitirAsignacion(*(yyvsp[-2].sval), temp, "Asignación +=");
            }
        } catch (const std::exception& e) { 
            yyerror(e.what()); 
        }
        name_aux=*(yyvsp[-2].sval);
        delete (yyvsp[-2].sval);
    }
#line 2002 "parser.tab.cpp"
    break;

  case 35: /* assignment: ID MENYS_IGUAL additive  */
#line 588 "parser.y"
    {
        try { 
            Descripcion var = tabla_simbolos.consultar(*(yyvsp[-2].sval)); 
            if (!ValidacionTipos::esNumerico(var.tipo_basico)) {
                yyerror("Operando de -= debe ser numérico");
            }
            // Pop el valor de additive
            if (!pila_operandos.empty()) {
                OperandInfo info = pila_operandos.top(); pila_operandos.pop();
                std::string temp = generador_codigo.nuevaTemp();
                generador_codigo.emitir("-", *(yyvsp[-2].sval), info.valor, temp, "", "-=", var.tipo_basico, info.tipo, var.tipo_basico, false, info.es_literal);
                generador_codigo.emitirAsignacion(*(yyvsp[-2].sval), temp, "Asignación -=");
            }
        } catch (const std::exception& e) { 
            yyerror(e.what()); 
        }
        name_aux=*(yyvsp[-2].sval);
        delete (yyvsp[-2].sval);
    }
#line 2026 "parser.tab.cpp"
    break;

  case 36: /* expression: logical_or  */
#line 611 "parser.y"
               { (yyval.tipo_expr) = (yyvsp[0].tipo_expr); }
#line 2032 "parser.tab.cpp"
    break;

  case 37: /* logical_or: logical_or OR logical_and  */
#line 616 "parser.y"
    {
        if (!ValidacionTipos::esCompatible((yyvsp[-2].tipo_expr), TipoBasico::T_BOOLEA)) {
            yyerror("Operando izquierdo de OR debe ser booleano");
        }
        if (!ValidacionTipos::esCompatible((yyvsp[0].tipo_expr), TipoBasico::T_BOOLEA)) {
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
        (yyval.tipo_expr) = TipoBasico::T_BOOLEA;
    }
#line 2054 "parser.tab.cpp"
    break;

  case 38: /* logical_or: logical_and  */
#line 634 "parser.y"
    { 
        (yyval.tipo_expr) = (yyvsp[0].tipo_expr); 
    }
#line 2062 "parser.tab.cpp"
    break;

  case 39: /* logical_and: logical_and AND equality  */
#line 641 "parser.y"
    {
        if (!ValidacionTipos::esCompatible((yyvsp[-2].tipo_expr), TipoBasico::T_BOOLEA)) {
            yyerror("Operando izquierdo de AND debe ser booleano");
        }
        if (!ValidacionTipos::esCompatible((yyvsp[0].tipo_expr), TipoBasico::T_BOOLEA)) {
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
        (yyval.tipo_expr) = TipoBasico::T_BOOLEA;
    }
#line 2084 "parser.tab.cpp"
    break;

  case 40: /* logical_and: equality  */
#line 659 "parser.y"
    { 
        (yyval.tipo_expr) = (yyvsp[0].tipo_expr); 
    }
#line 2092 "parser.tab.cpp"
    break;

  case 41: /* equality: equality IGUALTAT relational  */
#line 666 "parser.y"
    {
        if (!ValidacionTipos::esCompatible((yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr))) {
            yyerror("Tipos incompatibles en comparación ==");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir("==", op_izq.valor, op_der.valor, temp, "", "Igualdad", (yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr), TipoBasico::T_BOOLEA, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
        }
        (yyval.tipo_expr) = TipoBasico::T_BOOLEA;
    }
#line 2111 "parser.tab.cpp"
    break;

  case 42: /* equality: equality DIFERENT relational  */
#line 681 "parser.y"
    {
        if (!ValidacionTipos::esCompatible((yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr))) {
            yyerror("Tipos incompatibles en comparación !=");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir("!=", op_izq.valor, op_der.valor, temp, "", "Desigualdad", (yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr), TipoBasico::T_BOOLEA, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
        }
        (yyval.tipo_expr) = TipoBasico::T_BOOLEA;
    }
#line 2130 "parser.tab.cpp"
    break;

  case 43: /* equality: relational  */
#line 696 "parser.y"
    { 
        (yyval.tipo_expr) = (yyvsp[0].tipo_expr); 
    }
#line 2138 "parser.tab.cpp"
    break;

  case 44: /* relational: relational MENOR additive  */
#line 703 "parser.y"
    {
        if (!ValidacionTipos::esNumerico((yyvsp[-2].tipo_expr)) || !ValidacionTipos::esNumerico((yyvsp[0].tipo_expr))) {
            yyerror("Operandos de < deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir("<", op_izq.valor, op_der.valor, temp, "", "Menor que", (yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr), TipoBasico::T_BOOLEA, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
        }
        (yyval.tipo_expr) = TipoBasico::T_BOOLEA;
    }
#line 2157 "parser.tab.cpp"
    break;

  case 45: /* relational: relational MAJOR additive  */
#line 718 "parser.y"
    {
        if (!ValidacionTipos::esNumerico((yyvsp[-2].tipo_expr)) || !ValidacionTipos::esNumerico((yyvsp[0].tipo_expr))) {
            yyerror("Operandos de > deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir(">", op_izq.valor, op_der.valor, temp, "", "Mayor que", (yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr), TipoBasico::T_BOOLEA, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
        }
        (yyval.tipo_expr) = TipoBasico::T_BOOLEA;
    }
#line 2176 "parser.tab.cpp"
    break;

  case 46: /* relational: relational MENOR_IGUAL additive  */
#line 733 "parser.y"
    {
        if (!ValidacionTipos::esNumerico((yyvsp[-2].tipo_expr)) || !ValidacionTipos::esNumerico((yyvsp[0].tipo_expr))) {
            yyerror("Operandos de <= deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir("<=", op_izq.valor, op_der.valor, temp, "", "Menor o igual", (yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr), TipoBasico::T_BOOLEA, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
        }
        (yyval.tipo_expr) = TipoBasico::T_BOOLEA;
    }
#line 2195 "parser.tab.cpp"
    break;

  case 47: /* relational: relational MAJOR_IGUAL additive  */
#line 748 "parser.y"
    {
        if (!ValidacionTipos::esNumerico((yyvsp[-2].tipo_expr)) || !ValidacionTipos::esNumerico((yyvsp[0].tipo_expr))) {
            yyerror("Operandos de >= deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir(">=", op_izq.valor, op_der.valor, temp, "", "Mayor o igual", (yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr), TipoBasico::T_BOOLEA, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
        }
        (yyval.tipo_expr) = TipoBasico::T_BOOLEA;
    }
#line 2214 "parser.tab.cpp"
    break;

  case 48: /* relational: additive  */
#line 763 "parser.y"
    { 
        (yyval.tipo_expr) = (yyvsp[0].tipo_expr); 
    }
#line 2222 "parser.tab.cpp"
    break;

  case 49: /* additive: additive SUMA multiplicative  */
#line 770 "parser.y"
    {
        if (!ValidacionTipos::esNumerico((yyvsp[-2].tipo_expr)) || !ValidacionTipos::esNumerico((yyvsp[0].tipo_expr))) {
            yyerror("Operandos de suma deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            TipoBasico tipo_res = ValidacionTipos::mayorTipo((yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr));
            generador_codigo.emitir("+", op_izq.valor, op_der.valor, temp, "", "Suma", (yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr), tipo_res, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, tipo_res, false});
        }
        (yyval.tipo_expr) = ValidacionTipos::mayorTipo((yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr));
    }
#line 2242 "parser.tab.cpp"
    break;

  case 50: /* additive: additive RESTA multiplicative  */
#line 786 "parser.y"
    {
        if (!ValidacionTipos::esNumerico((yyvsp[-2].tipo_expr)) || !ValidacionTipos::esNumerico((yyvsp[0].tipo_expr))) {
            yyerror("Operandos de resta deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            TipoBasico tipo_res = ValidacionTipos::mayorTipo((yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr));
            generador_codigo.emitir("-", op_izq.valor, op_der.valor, temp, "", "Resta", (yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr), tipo_res, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, tipo_res, false});
        }
        (yyval.tipo_expr) = ValidacionTipos::mayorTipo((yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr));
    }
#line 2262 "parser.tab.cpp"
    break;

  case 51: /* additive: multiplicative  */
#line 802 "parser.y"
    { 
        (yyval.tipo_expr) = (yyvsp[0].tipo_expr); 
    }
#line 2270 "parser.tab.cpp"
    break;

  case 52: /* multiplicative: multiplicative MULT unary  */
#line 809 "parser.y"
    {
        if (!ValidacionTipos::esNumerico((yyvsp[-2].tipo_expr)) || !ValidacionTipos::esNumerico((yyvsp[0].tipo_expr))) {
            yyerror("Operandos de multiplicación deben ser numéricos");
        }
        // Pop operandos de la pila
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
             TipoBasico tipo_res = ValidacionTipos::mayorTipo((yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr));
            generador_codigo.emitir("*", op_izq.valor, op_der.valor, temp, "", "Multiplicación", (yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr), tipo_res, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, tipo_res, false});
        }
        (yyval.tipo_expr) = ValidacionTipos::mayorTipo((yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr));
    }
#line 2290 "parser.tab.cpp"
    break;

  case 53: /* multiplicative: multiplicative DIV unary  */
#line 825 "parser.y"
    {
        if (!ValidacionTipos::esNumerico((yyvsp[-2].tipo_expr)) || !ValidacionTipos::esNumerico((yyvsp[0].tipo_expr))) {
            yyerror("Operandos de división deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            TipoBasico tipo_res = ValidacionTipos::mayorTipo((yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr));
            generador_codigo.emitir("/", op_izq.valor, op_der.valor, temp, "", "División", (yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr), tipo_res, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, tipo_res, false});
        }
        (yyval.tipo_expr) = ValidacionTipos::mayorTipo((yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr));
    }
#line 2310 "parser.tab.cpp"
    break;

  case 54: /* multiplicative: multiplicative MODUL unary  */
#line 841 "parser.y"
    {
        if ((yyvsp[-2].tipo_expr) != TipoBasico::T_ENTER || (yyvsp[0].tipo_expr) != TipoBasico::T_ENTER) {
            yyerror("Operandos de módulo deben ser enter");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir("%", op_izq.valor, op_der.valor, temp, "", "Módulo", (yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr), TipoBasico::T_ENTER, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_ENTER, false});
        }
        (yyval.tipo_expr) = TipoBasico::T_ENTER;
    }
#line 2329 "parser.tab.cpp"
    break;

  case 55: /* multiplicative: multiplicative DIVISIO_ENTER unary  */
#line 856 "parser.y"
    {
        if (!ValidacionTipos::esNumerico((yyvsp[-2].tipo_expr)) || !ValidacionTipos::esNumerico((yyvsp[0].tipo_expr))) {
            yyerror("Operandos de división entera deben ser numéricos");
        }
        // Pop operandos
        if (pila_operandos.size() >= 2) {
            OperandInfo op_der = pila_operandos.top(); pila_operandos.pop();
            OperandInfo op_izq = pila_operandos.top(); pila_operandos.pop();
            std::string temp = generador_codigo.nuevaTemp();
            generador_codigo.emitir("//", op_izq.valor, op_der.valor, temp, "", "División Entera", (yyvsp[-2].tipo_expr), (yyvsp[0].tipo_expr), TipoBasico::T_ENTER, op_izq.es_literal, op_der.es_literal);
            pila_operandos.push({temp, TipoBasico::T_ENTER, false});
        }
        (yyval.tipo_expr) = TipoBasico::T_ENTER;
    }
#line 2348 "parser.tab.cpp"
    break;

  case 56: /* multiplicative: unary  */
#line 871 "parser.y"
    { 
        (yyval.tipo_expr) = (yyvsp[0].tipo_expr); 
    }
#line 2356 "parser.tab.cpp"
    break;

  case 57: /* unary: NOT unary  */
#line 878 "parser.y"
      {
          if ((yyvsp[0].tipo_expr) != TipoBasico::T_BOOLEA) {
              yyerror("Operando de NOT debe ser booleano");
          }
          // Generar instrucción de negación lógica
          if (!pila_operandos.empty()) {
              OperandInfo op = pila_operandos.top(); pila_operandos.pop();
              std::string temp = generador_codigo.nuevaTemp();
              generador_codigo.emitir("!", op.valor, "", temp, "", "NOT lógico", TipoBasico::T_BOOLEA, TipoBasico::T_UNKNOWN, TipoBasico::T_BOOLEA, op.es_literal, false);
              pila_operandos.push({temp, TipoBasico::T_BOOLEA, false});
          }
          (yyval.tipo_expr) = TipoBasico::T_BOOLEA;
      }
#line 2374 "parser.tab.cpp"
    break;

  case 58: /* unary: INC unary  */
#line 892 "parser.y"
      {
          if (!ValidacionTipos::esNumerico((yyvsp[0].tipo_expr))) {
              yyerror("Operando de ++ debe ser numérico");
          }
          // Generar instrucción de incremento prefijo
          if (!pila_operandos.empty()) {
              OperandInfo op = pila_operandos.top(); pila_operandos.pop();
              std::string temp1 = generador_codigo.nuevaTemp();
              generador_codigo.emitir("+", op.valor, "1", temp1, "", "Incremento prefijo", (yyvsp[0].tipo_expr), TipoBasico::T_ENTER, (yyvsp[0].tipo_expr), op.es_literal, true);
              generador_codigo.emitirAsignacion(op.valor, temp1, "Asignación ++", op.tipo, false);
              pila_operandos.push({temp1, (yyvsp[0].tipo_expr), false});
          }
          (yyval.tipo_expr) = (yyvsp[0].tipo_expr);
      }
#line 2393 "parser.tab.cpp"
    break;

  case 59: /* unary: DEC unary  */
#line 907 "parser.y"
      {
          if (!ValidacionTipos::esNumerico((yyvsp[0].tipo_expr))) {
              yyerror("Operando de -- debe ser numérico");
          }
          // Generar instrucción de decremento prefijo
          if (!pila_operandos.empty()) {
              OperandInfo op = pila_operandos.top(); pila_operandos.pop();
              std::string temp1 = generador_codigo.nuevaTemp();
              generador_codigo.emitir("-", op.valor, "1", temp1, "", "Decremento prefijo", (yyvsp[0].tipo_expr), TipoBasico::T_ENTER, (yyvsp[0].tipo_expr), op.es_literal, true);
              generador_codigo.emitirAsignacion(op.valor, temp1, "Asignación --", op.tipo, false);
              pila_operandos.push({temp1, (yyvsp[0].tipo_expr), false});
          }
          (yyval.tipo_expr) = (yyvsp[0].tipo_expr);
      }
#line 2412 "parser.tab.cpp"
    break;

  case 60: /* unary: primary  */
#line 921 "parser.y"
              { (yyval.tipo_expr) = (yyvsp[0].tipo_expr); }
#line 2418 "parser.tab.cpp"
    break;

  case 61: /* unary: primary INC  */
#line 923 "parser.y"
      {
          if (!ValidacionTipos::esNumerico((yyvsp[-1].tipo_expr))) {
              yyerror("Operando de ++ debe ser numérico");
          }
          // Generar instrucción de incremento postfijo
          if (!pila_operandos.empty()) {
              OperandInfo op = pila_operandos.top(); pila_operandos.pop();
              std::string original = generador_codigo.nuevaTemp();
              generador_codigo.emitirAsignacion(original, op.valor, "Valor original para post-inc", op.tipo, op.es_literal);
              std::string temp = generador_codigo.nuevaTemp();
              generador_codigo.emitir("+", op.valor, "1", temp, "", "Incremento postfijo", (yyvsp[-1].tipo_expr), TipoBasico::T_ENTER, (yyvsp[-1].tipo_expr), op.es_literal, true);
              generador_codigo.emitirAsignacion(op.valor, temp, "Asignación ++", op.tipo, false);
              pila_operandos.push({original, (yyvsp[-1].tipo_expr), false});
          }
          (yyval.tipo_expr) = (yyvsp[-1].tipo_expr);
      }
#line 2439 "parser.tab.cpp"
    break;

  case 62: /* unary: primary DEC  */
#line 940 "parser.y"
      {
          if (!ValidacionTipos::esNumerico((yyvsp[-1].tipo_expr))) {
              yyerror("Operando de -- debe ser numérico");
          }
          // Generar instrucción de decremento postfijo
          if (!pila_operandos.empty()) {
              OperandInfo op = pila_operandos.top(); pila_operandos.pop();
              std::string original = generador_codigo.nuevaTemp();
              generador_codigo.emitirAsignacion(original, op.valor, "Valor original para post-dec", op.tipo, op.es_literal);
              std::string temp = generador_codigo.nuevaTemp();
              generador_codigo.emitir("-", op.valor, "1", temp, "", "Decremento postfijo", (yyvsp[-1].tipo_expr), TipoBasico::T_ENTER, (yyvsp[-1].tipo_expr), op.es_literal, true);
              generador_codigo.emitirAsignacion(op.valor, temp, "Asignación --", op.tipo, false);
              pila_operandos.push({original, (yyvsp[-1].tipo_expr), false});
          }
          (yyval.tipo_expr) = (yyvsp[-1].tipo_expr);
      }
#line 2460 "parser.tab.cpp"
    break;

  case 63: /* primary: literal  */
#line 960 "parser.y"
      { 
          (yyval.tipo_expr) = (yyvsp[0].tipo_expr);
      }
#line 2468 "parser.tab.cpp"
    break;

  case 64: /* primary: ID  */
#line 964 "parser.y"
    {
        try 
        {
            Descripcion s = tabla_simbolos.consultar(*(yyvsp[0].sval));
            (yyval.tipo_expr) = s.tipo_basico;
            pila_operandos.push({*(yyvsp[0].sval), s.tipo_basico, false});  // Push el nombre de la variable
            
            // Si es tupla, actualizar last_tuple_subtype para asignaciones
            if (s.tipo_basico == TipoBasico::T_TUPLA && !s.tipos_tupla.empty()) {
                last_tuple_subtype = s.tipos_tupla[0];
            } else {
                last_tuple_subtype = TipoBasico::T_UNKNOWN;
            }
        } catch (const std::exception& e) {
            yyerror(e.what());
            (yyval.tipo_expr) = TipoBasico::T_UNKNOWN;
        }

        
        delete (yyvsp[0].sval);
    }
#line 2494 "parser.tab.cpp"
    break;

  case 65: /* primary: ID CLAUDATOR_OPEN additive CLAUDATOR_CLOSE  */
#line 986 "parser.y"
    {
        try {
            Descripcion s = tabla_simbolos.consultar(*(yyvsp[-3].sval));
            if (s.tipo_basico != TipoBasico::T_TUPLA) {
                yyerror("Variable no es una tupla");
            }
            if (!ValidacionTipos::esNumerico((yyvsp[-1].tipo_expr))) {
                yyerror("El índice debe ser numérico");
            }
            
            // Pop índice
            if (!pila_operandos.empty()) {
                OperandInfo indice = pila_operandos.top(); pila_operandos.pop();
                std::string temp = generador_codigo.nuevaTemp();
                
                // Generar: temp = id[indice]
                // tipo_operando1 es T_TUPLA para que generarPrologo sepa que 'id' es tupla
                generador_codigo.emitir("tuple_get", *(yyvsp[-3].sval), indice.valor, temp, "", "Acceso tupla", 
                                       TipoBasico::T_TUPLA, TipoBasico::T_ENTER, TipoBasico::T_UNKNOWN, false, indice.es_literal);
                TipoBasico tipo_elem = TipoBasico::T_UNKNOWN;
                if (!s.tipos_tupla.empty()) tipo_elem = s.tipos_tupla[0]; // Simplificación: asume homogénea o primer tipo
                
                pila_operandos.push({temp, tipo_elem, false});
                (yyval.tipo_expr) = tipo_elem;
            } else {
                 (yyval.tipo_expr) = TipoBasico::T_UNKNOWN;
            }
        } catch (const std::exception& e) {
             yyerror(e.what());
             (yyval.tipo_expr) = TipoBasico::T_UNKNOWN;
        }
        delete (yyvsp[-3].sval);
    }
#line 2532 "parser.tab.cpp"
    break;

  case 66: /* primary: PAR_OPEN expression COMA expression PAR_CLOSE  */
#line 1020 "parser.y"
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
        (yyval.tipo_expr) = TipoBasico::T_TUPLA; 
    }
#line 2563 "parser.tab.cpp"
    break;

  case 67: /* primary: ID PAR_OPEN arguments PAR_CLOSE  */
#line 1047 "parser.y"
    {
         try {
            Descripcion s = tabla_simbolos.consultar(*(yyvsp[-3].sval));

            if (s.tipo != TipoDesc::D_PROC) {
                yyerror("El identificador no es una funcion");
            }

            if (s.tipos_parametros.size() != (yyvsp[-1].lista_tipos)->size()) {
                yyerror("Número incorrecto de argumentos");
            }

            for (size_t i = 0; i < s.tipos_parametros.size(); ++i) {
                if (!ValidacionTipos::esCompatible(s.tipos_parametros[i],(*(yyvsp[-1].lista_tipos))[i])) {
                    yyerror("Tipo incompatible en argumento de función");
                }
            }

            (yyval.tipo_expr) = s.tipo_retorno;

            std::string temp = "";
            if ((yyval.tipo_expr) != TipoBasico::T_VOID) {
                temp = generador_codigo.nuevaTemp();
            }
            generador_codigo.emitirCall(*(yyvsp[-3].sval), temp, "Llamada a función " + *(yyvsp[-3].sval));
            if (!temp.empty()) {
                pila_operandos.push({temp, s.tipo_retorno, false});
            }

         } catch (const std::exception& e) {
            yyerror(e.what());
            (yyval.tipo_expr) = TipoBasico::T_UNKNOWN;
         }

         delete (yyvsp[-3].sval);
         delete (yyvsp[-1].lista_tipos);
    }
#line 2605 "parser.tab.cpp"
    break;

  case 68: /* primary: cast_expression  */
#line 1084 "parser.y"
                      { (yyval.tipo_expr) = (yyvsp[0].tipo_expr); }
#line 2611 "parser.tab.cpp"
    break;

  case 69: /* primary: input_output_expression  */
#line 1085 "parser.y"
                              { (yyval.tipo_expr) = (yyvsp[0].tipo_expr); }
#line 2617 "parser.tab.cpp"
    break;

  case 70: /* primary: PAR_OPEN expression PAR_CLOSE  */
#line 1086 "parser.y"
                                    { (yyval.tipo_expr) = (yyvsp[-1].tipo_expr); }
#line 2623 "parser.tab.cpp"
    break;

  case 71: /* cast_expression: FUNC_CAST PAR_OPEN type COMA expression PAR_CLOSE  */
#line 1091 "parser.y"
      {
          // cast retorna el tipo especificado
          (yyval.tipo_expr) = stringToTipoBasico(current_type);
          // Emitir cast
          if (!pila_operandos.empty()) {
              OperandInfo op = pila_operandos.top(); pila_operandos.pop();
              std::string temp = generador_codigo.nuevaTemp();
              generador_codigo.emitirCast(current_type, op.valor, temp, "Cast a " + current_type, op.es_literal);
              pila_operandos.push({temp, stringToTipoBasico(current_type), false});
          }
      }
#line 2639 "parser.tab.cpp"
    break;

  case 72: /* input_output_expression: FUNC_ENTRADA PAR_OPEN expression PAR_CLOSE  */
#line 1106 "parser.y"
      {
          (yyval.tipo_expr) = TipoBasico::T_ENTER;
          // Emitir read
          if (!pila_operandos.empty()) {
              OperandInfo var = pila_operandos.top(); pila_operandos.pop();
              generador_codigo.emitirRead(var.valor, "Leer entrada");
              // Push de vuelta la variable leída
              pila_operandos.push(var);
          }
      }
#line 2654 "parser.tab.cpp"
    break;

  case 73: /* input_output_expression: FUNC_IMPRIMEIX PAR_OPEN expression PAR_CLOSE  */
#line 1117 "parser.y"
      {
          (yyval.tipo_expr) = TipoBasico::T_VOID;
          // Emitir print
          if (!pila_operandos.empty()) {
              OperandInfo expr = pila_operandos.top(); pila_operandos.pop();
              generador_codigo.emitirPrint(expr.valor, "Imprimir expresión", expr.tipo, expr.es_literal);
          }
      }
#line 2667 "parser.tab.cpp"
    break;

  case 74: /* literal: INTEGER  */
#line 1129 "parser.y"
      { 
          (yyval.tipo_expr) = TipoBasico::T_ENTER; 
          pila_operandos.push({valueToString((yyvsp[0].ival)), TipoBasico::T_ENTER, true});
      }
#line 2676 "parser.tab.cpp"
    break;

  case 75: /* literal: STRING  */
#line 1134 "parser.y"
      { 
          (yyval.tipo_expr) = TipoBasico::T_CADENA; 
          pila_operandos.push({*(yyvsp[0].sval), TipoBasico::T_CADENA, true});
      }
#line 2685 "parser.tab.cpp"
    break;

  case 76: /* literal: BOOL  */
#line 1139 "parser.y"
      { 
          (yyval.tipo_expr) = TipoBasico::T_BOOLEA;
          pila_operandos.push({valueToString((yyvsp[0].bval)), TipoBasico::T_BOOLEA, true});
      }
#line 2694 "parser.tab.cpp"
    break;

  case 77: /* literal: CARACTER  */
#line 1144 "parser.y"
      { 
          (yyval.tipo_expr) = TipoBasico::T_CARACTER;
          pila_operandos.push({*(yyvsp[0].sval), TipoBasico::T_CARACTER, true});
      }
#line 2703 "parser.tab.cpp"
    break;

  case 78: /* $@3: %empty  */
#line 1152 "parser.y"
    {
        // Emitir etiqueta de inicio del if
        std::string etiqueta_inicio = generador_codigo.nuevaEtiqueta();
        generador_codigo.emitirEtiqueta(etiqueta_inicio, "Inicio IF");
        pila_etiquetas_inicio.push(etiqueta_inicio);
    }
#line 2714 "parser.tab.cpp"
    break;

  case 79: /* $@4: %empty  */
#line 1159 "parser.y"
    {
        // Después de evaluar expresión, pop condición y emitir salto condicional
        if (!pila_operandos.empty()) {
            OperandInfo condicion = pila_operandos.top(); pila_operandos.pop();
            std::string etiqueta_else = generador_codigo.nuevaEtiqueta();
            generador_codigo.emitirSaltoCondicional(condicion.valor, etiqueta_else, "IF condición falsa", condicion.es_literal);
            pila_etiquetas_else.push(etiqueta_else);
        }
    }
#line 2728 "parser.tab.cpp"
    break;

  case 80: /* $@5: %empty  */
#line 1169 "parser.y"
    {
        /* Nuevo ámbito para el bloque IF */
        tabla_simbolos.entrarBloc();
    }
#line 2737 "parser.tab.cpp"
    break;

  case 81: /* $@6: %empty  */
#line 1175 "parser.y"
    {
        /* Cerrar ámbito IF */
        try { tabla_simbolos.salirBloc(); } catch (const std::exception& e) { yyerror(e.what()); }
        // Después del bloque if, emitir goto a etiqueta fin
        std::string etiqueta_fin = generador_codigo.nuevaEtiqueta();
        generador_codigo.emitirGoto(etiqueta_fin, "Fin IF");
        pila_etiquetas_fin.push(etiqueta_fin);
    }
#line 2750 "parser.tab.cpp"
    break;

  case 82: /* conditional: INICI_COND COND_OPEN $@3 expression COND_CLOSE $@4 KEY_OPEN_CLOSE $@5 block_instructions KEY_OPEN_CLOSE $@6 else_chain  */
#line 1184 "parser.y"
    {
        // Al final, emitir etiqueta fin
        if (!pila_etiquetas_fin.empty()) {
            std::string etiqueta_fin = pila_etiquetas_fin.top(); pila_etiquetas_fin.pop();
            generador_codigo.emitirEtiqueta(etiqueta_fin, "Fin IF completo");
        }
    }
#line 2762 "parser.tab.cpp"
    break;

  case 83: /* else_chain: %empty  */
#line 1195 "parser.y"
    {
        // No hay else, emitir etiqueta else aquí si existe
        if (!pila_etiquetas_else.empty()) {
            std::string etiqueta_else = pila_etiquetas_else.top(); pila_etiquetas_else.pop();
            generador_codigo.emitirEtiqueta(etiqueta_else, "Etiqueta ELSE (vacío)");
        }
    }
#line 2774 "parser.tab.cpp"
    break;

  case 84: /* $@7: %empty  */
#line 1203 "parser.y"
    {
        // Emitir etiqueta else antes del elif
        if (!pila_etiquetas_else.empty()) {
            std::string etiqueta_else = pila_etiquetas_else.top(); pila_etiquetas_else.pop();
            generador_codigo.emitirEtiqueta(etiqueta_else, "Etiqueta ELSE/ELIF");
        }
    }
#line 2786 "parser.tab.cpp"
    break;

  case 85: /* $@8: %empty  */
#line 1211 "parser.y"
    {
        // Evaluar condición del elif, emitir salto
        if (!pila_operandos.empty()) {
            OperandInfo condicion = pila_operandos.top(); pila_operandos.pop();
            std::string etiqueta_siguiente_else = generador_codigo.nuevaEtiqueta();
            generador_codigo.emitirSaltoCondicional(condicion.valor, etiqueta_siguiente_else, "ELIF condición falsa", condicion.es_literal);
            pila_etiquetas_else.push(etiqueta_siguiente_else);
        }
    }
#line 2800 "parser.tab.cpp"
    break;

  case 86: /* $@9: %empty  */
#line 1221 "parser.y"
      {
          /* Nuevo ámbito para ELIF */
          tabla_simbolos.entrarBloc();
      }
#line 2809 "parser.tab.cpp"
    break;

  case 87: /* $@10: %empty  */
#line 1227 "parser.y"
      {
          /* Cerrar ámbito ELIF */
          try { tabla_simbolos.salirBloc(); } catch (const std::exception& e) { yyerror(e.what()); }
          // Goto a fin
          if (!pila_etiquetas_fin.empty()) {
              std::string etiqueta_fin = pila_etiquetas_fin.top(); 
              generador_codigo.emitirGoto(etiqueta_fin, "Fin ELIF");
          }
      }
#line 2823 "parser.tab.cpp"
    break;

  case 89: /* $@11: %empty  */
#line 1239 "parser.y"
      {
          // Emitir etiqueta else antes del else
          if (!pila_etiquetas_else.empty()) {
            std::string etiqueta_else = pila_etiquetas_else.top(); pila_etiquetas_else.pop();
            generador_codigo.emitirEtiqueta(etiqueta_else, "Etiqueta ELSE");
          }
          /* Nuevo ámbito para ELSE */
          tabla_simbolos.entrarBloc();
      }
#line 2837 "parser.tab.cpp"
    break;

  case 90: /* else_chain: FI_COND KEY_OPEN_CLOSE $@11 block_instructions KEY_OPEN_CLOSE  */
#line 1250 "parser.y"
      {
          /* Cerrar ámbito ELSE */
          try { tabla_simbolos.salirBloc(); } catch (const std::exception& e) { yyerror(e.what()); }
      }
#line 2846 "parser.tab.cpp"
    break;

  case 91: /* $@12: %empty  */
#line 1258 "parser.y"
      {
          // Etiqueta de inicio del while
          std::string etiqueta_inicio = generador_codigo.nuevaEtiqueta();
          generador_codigo.emitirEtiqueta(etiqueta_inicio, "Inicio WHILE");
          pila_etiquetas_inicio.push(etiqueta_inicio);
      }
#line 2857 "parser.tab.cpp"
    break;

  case 92: /* $@13: %empty  */
#line 1265 "parser.y"
      {
          // Evaluar condición, if_false goto fin
          if (!pila_operandos.empty()) {
              OperandInfo condicion = pila_operandos.top(); pila_operandos.pop();
              std::string etiqueta_fin = generador_codigo.nuevaEtiqueta();
              generador_codigo.emitirSaltoCondicional(condicion.valor, etiqueta_fin, "WHILE condición falsa", condicion.es_literal);
              pila_etiquetas_fin.push(etiqueta_fin);
          }
      }
#line 2871 "parser.tab.cpp"
    break;

  case 93: /* $@14: %empty  */
#line 1274 "parser.y"
      {
          /* Entrar bloque WHILE */
          tabla_simbolos.entrarBloc();
      }
#line 2880 "parser.tab.cpp"
    break;

  case 94: /* while_statement: BUCLE_MENTRE PAR_OPEN $@12 expression PAR_CLOSE $@13 $@14 KEY_OPEN_CLOSE block_instructions KEY_OPEN_CLOSE  */
#line 1279 "parser.y"
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
#line 2903 "parser.tab.cpp"
    break;

  case 95: /* $@15: %empty  */
#line 1302 "parser.y"
      {
          // Después de init, etiqueta inicio
          std::string etiqueta_inicio = generador_codigo.nuevaEtiqueta();
          generador_codigo.emitirEtiqueta(etiqueta_inicio, "Inicio FOR");
          pila_etiquetas_inicio.push(etiqueta_inicio);
      }
#line 2914 "parser.tab.cpp"
    break;

  case 96: /* $@16: %empty  */
#line 1309 "parser.y"
      {
          // Evaluar condición, if_false goto fin
          if (!pila_operandos.empty()) {
              OperandInfo condicion = pila_operandos.top(); pila_operandos.pop();
              std::string etiqueta_fin = generador_codigo.nuevaEtiqueta();
              generador_codigo.emitirSaltoCondicional(condicion.valor, etiqueta_fin, "FOR condición falsa", condicion.es_literal);
              pila_etiquetas_fin.push(etiqueta_fin);
          }
      }
#line 2928 "parser.tab.cpp"
    break;

  case 97: /* $@17: %empty  */
#line 1319 "parser.y"
      {
          /* Entrar bloque FOR */
          tabla_simbolos.entrarBloc();
      }
#line 2937 "parser.tab.cpp"
    break;

  case 98: /* $@18: %empty  */
#line 1324 "parser.y"
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
#line 2969 "parser.tab.cpp"
    break;

  case 99: /* for_statement: BUCLE_PER PAR_OPEN for_init PUNTICOMA $@15 expression PUNTICOMA $@16 for_update PAR_CLOSE $@17 KEY_OPEN_CLOSE block_instructions $@18 KEY_OPEN_CLOSE  */
#line 1352 "parser.y"
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
#line 2992 "parser.tab.cpp"
    break;

  case 103: /* for_declaration: type ID  */
#line 1380 "parser.y"
      {
        TipoBasico tipo_var = stringToTipoBasico(current_type);
        Descripcion desc(TipoDesc::D_VAR, tipo_var);
        try {
            tabla_simbolos.posar(*(yyvsp[0].sval), desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        delete (yyvsp[0].sval);
      }
#line 3007 "parser.tab.cpp"
    break;

  case 104: /* for_declaration: type ID ASSIGN expression  */
#line 1391 "parser.y"
      {
        TipoBasico tipo_var = stringToTipoBasico(current_type);
        if (!ValidacionTipos::esCompatible(tipo_var, (yyvsp[0].tipo_expr))) {
            yyerror("Tipos incompatibles en inicialización en for");
        }
        Descripcion desc(TipoDesc::D_VAR, tipo_var);
        try {
            tabla_simbolos.posar(*(yyvsp[-2].sval), desc);
        } catch (const std::exception& e) {
            yyerror(e.what());
        }
        // Emitir asignación inicial
        if (!pila_operandos.empty()) {
            OperandInfo valor = pila_operandos.top(); pila_operandos.pop();
            generador_codigo.emitirAsignacion(*(yyvsp[-2].sval), valor.valor, "Inicialización en for", valor.tipo, valor.es_literal);
        }
        delete (yyvsp[-2].sval);
      }
#line 3030 "parser.tab.cpp"
    break;

  case 105: /* for_update: assignment  */
#line 1413 "parser.y"
      {
          for_update_op = "";
      }
#line 3038 "parser.tab.cpp"
    break;

  case 106: /* for_update: INC ID  */
#line 1417 "parser.y"
      {
          for_update_op = "INC " + *(yyvsp[0].sval);
          delete (yyvsp[0].sval);
      }
#line 3047 "parser.tab.cpp"
    break;

  case 107: /* for_update: DEC ID  */
#line 1422 "parser.y"
      {
          for_update_op = "DEC " + *(yyvsp[0].sval);
          delete (yyvsp[0].sval);
      }
#line 3056 "parser.tab.cpp"
    break;

  case 108: /* for_update: ID INC  */
#line 1427 "parser.y"
      {
          for_update_op = "POSTINC " + *(yyvsp[-1].sval);
          delete (yyvsp[-1].sval);
      }
#line 3065 "parser.tab.cpp"
    break;

  case 109: /* for_update: ID DEC  */
#line 1432 "parser.y"
      {
          for_update_op = "POSTDEC " + *(yyvsp[-1].sval);
          delete (yyvsp[-1].sval);
      }
#line 3074 "parser.tab.cpp"
    break;

  case 110: /* for_update: %empty  */
#line 1437 "parser.y"
      {
          for_update_op = "";
      }
#line 3082 "parser.tab.cpp"
    break;

  case 113: /* statement: error PUNTICOMA  */
#line 1447 "parser.y"
                    { yyerrok; }
#line 3088 "parser.tab.cpp"
    break;

  case 121: /* return_statement: RET expression  */
#line 1460 "parser.y"
    {
        funcion_actual.ha_retornado = true;

        if (!ValidacionTipos::esCompatible(funcion_actual.tipo_retorno, (yyvsp[0].tipo_expr))) {
            yyerror("Tipo de retorno incompatible con el retorno de función");
        }
        // Emitir return
        if (!pila_operandos.empty()) {
            OperandInfo valor = pila_operandos.top(); pila_operandos.pop();
            generador_codigo.emitirReturn(valor.valor, "Retorno de función", valor.tipo, valor.es_literal);
        }
    }
#line 3105 "parser.tab.cpp"
    break;

  case 122: /* arguments: %empty  */
#line 1476 "parser.y"
    {
        (yyval.lista_tipos) = new std::vector<TipoBasico>();
    }
#line 3113 "parser.tab.cpp"
    break;

  case 123: /* arguments: argument_list  */
#line 1480 "parser.y"
    {
        (yyval.lista_tipos) = (yyvsp[0].lista_tipos);
    }
#line 3121 "parser.tab.cpp"
    break;

  case 124: /* argument_list: expression  */
#line 1487 "parser.y"
    {
        (yyval.lista_tipos) = new std::vector<TipoBasico>();
        (yyval.lista_tipos)->push_back((yyvsp[0].tipo_expr));
        // Emitir param para el argumento
        if (!pila_operandos.empty()) {
            OperandInfo arg = pila_operandos.top(); pila_operandos.pop();
            generador_codigo.emitirParam(arg.valor, "Parámetro de función", arg.tipo, arg.es_literal);
        }
    }
#line 3135 "parser.tab.cpp"
    break;

  case 125: /* argument_list: argument_list COMA expression  */
#line 1497 "parser.y"
    {
        (yyvsp[-2].lista_tipos)->push_back((yyvsp[0].tipo_expr));
        (yyval.lista_tipos) = (yyvsp[-2].lista_tipos);
        // Emitir param para el argumento
        if (!pila_operandos.empty()) {
            OperandInfo arg = pila_operandos.top(); pila_operandos.pop();
            generador_codigo.emitirParam(arg.valor, "Parámetro de función", arg.tipo, arg.es_literal);
        }
    }
#line 3149 "parser.tab.cpp"
    break;


#line 3153 "parser.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1509 "parser.y"


void yyerror(const char *s) {
    std::cerr << "Error en la línea " << lexer->lineno() << ": " << s << std::endl;
    
    std::ofstream file("Recopilación_de_errores.txt", std::ios::app);
    if (file.is_open()) {
        file << "Error en la línea " << lexer->lineno() << ": " << s << std::endl;
        file.close();
    }
    
    error_count++;
}
