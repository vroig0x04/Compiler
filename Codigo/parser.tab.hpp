/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 96 "parser.y"

    #include "taula_simbols.h"
    extern int error_count;

#line 54 "parser.tab.hpp"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    MOD_CONSTANT = 258,            /* MOD_CONSTANT  */
    TIPUS_ENTER = 259,             /* TIPUS_ENTER  */
    TIPUS_CARACTER = 260,          /* TIPUS_CARACTER  */
    TIPUS_CADENA = 261,            /* TIPUS_CADENA  */
    TIPUS_BOOLEA = 262,            /* TIPUS_BOOLEA  */
    TIPUS_VOID = 263,              /* TIPUS_VOID  */
    OBJ_TUPLA = 264,               /* OBJ_TUPLA  */
    ASSIGN = 265,                  /* ASSIGN  */
    PUNTICOMA = 266,               /* PUNTICOMA  */
    COMA = 267,                    /* COMA  */
    PUNT = 268,                    /* PUNT  */
    DOBLEPUNT = 269,               /* DOBLEPUNT  */
    SUMA = 270,                    /* SUMA  */
    RESTA = 271,                   /* RESTA  */
    MULT = 272,                    /* MULT  */
    DIV = 273,                     /* DIV  */
    MODUL = 274,                   /* MODUL  */
    DIVISIO_ENTER = 275,           /* DIVISIO_ENTER  */
    IGUALTAT = 276,                /* IGUALTAT  */
    DIFERENT = 277,                /* DIFERENT  */
    MENOR_IGUAL = 278,             /* MENOR_IGUAL  */
    MAJOR_IGUAL = 279,             /* MAJOR_IGUAL  */
    MENOR = 280,                   /* MENOR  */
    MAJOR = 281,                   /* MAJOR  */
    MES_IGUAL = 282,               /* MES_IGUAL  */
    MENYS_IGUAL = 283,             /* MENYS_IGUAL  */
    INC = 284,                     /* INC  */
    DEC = 285,                     /* DEC  */
    AND = 286,                     /* AND  */
    OR = 287,                      /* OR  */
    NOT = 288,                     /* NOT  */
    PAR_OPEN = 289,                /* PAR_OPEN  */
    PAR_CLOSE = 290,               /* PAR_CLOSE  */
    KEY_OPEN_CLOSE = 291,          /* KEY_OPEN_CLOSE  */
    COND_OPEN = 292,               /* COND_OPEN  */
    COND_CLOSE = 293,              /* COND_CLOSE  */
    CLAUDATOR_OPEN = 294,          /* CLAUDATOR_OPEN  */
    CLAUDATOR_CLOSE = 295,         /* CLAUDATOR_CLOSE  */
    INICI_COND = 296,              /* INICI_COND  */
    CONTINUACIO_COND = 297,        /* CONTINUACIO_COND  */
    FI_COND = 298,                 /* FI_COND  */
    BUCLE_MENTRE = 299,            /* BUCLE_MENTRE  */
    BUCLE_PER = 300,               /* BUCLE_PER  */
    INICI_FUNCIO = 301,            /* INICI_FUNCIO  */
    RETORN = 302,                  /* RETORN  */
    RET = 303,                     /* RET  */
    FUNC_IMPRIMEIX = 304,          /* FUNC_IMPRIMEIX  */
    FUNC_ENTRADA = 305,            /* FUNC_ENTRADA  */
    FUNC_CAST = 306,               /* FUNC_CAST  */
    ERROR_TOKEN = 307,             /* ERROR_TOKEN  */
    CHARACTER_LITERAL = 308,       /* CHARACTER_LITERAL  */
    MAIN = 309,                    /* MAIN  */
    FLOAT = 310,                   /* FLOAT  */
    INTEGER = 311,                 /* INTEGER  */
    CARACTER = 312,                /* CARACTER  */
    STRING = 313,                  /* STRING  */
    BOOL = 314,                    /* BOOL  */
    ID = 315                       /* ID  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 101 "parser.y"

    int ival;
    float fval;
    std::string* sval;
    bool bval;
    TipoBasico tipo_expr;  
    std::vector<TipoBasico>* lista_tipos;

#line 140 "parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */
