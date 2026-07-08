%option c++
%option yylineno
%x COMMENT

%{
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "parser.tab.hpp"
#include "lexer.h"

using namespace std;

stringstream comentario;
void logToken(string t) {
    ofstream f("registro_de_tokens.txt", ios::app);
    f << t << endl;
    f.close();
}

%}


/* Definicio dels patrons per nombres y caracters */

DIGIT           [0-9]
SIGN            [+-]
FLOAT           {DIGIT}+"."{DIGIT}+([eE]{SIGN}?{DIGIT}+)?
INTEGER         {DIGIT}+
CARACTER        \'([^\\\'\n]|\\.)\'

/* Definicio de patrons per cadenes y booleans */

STRING          \"([^\\\"]|\\.)*\"        
BOOL            vertader|fals

/* Definicio per identificador */

IDENTIFICADOR  [a-zA-Z_][a-zA-Z0-9_]*


%%


"``"[^\n]* { /* ignorar el comentari */ }

"ññ" {
    comentario.str(""); 
    comentario.clear();
    BEGIN(COMMENT);
}
<COMMENT>"ññ" {
    //cout << "COMENTARI: " << comentario.str() << "\n";
    BEGIN(INITIAL);
}
<COMMENT>.    { comentario << YYText(); }
<COMMENT>\n   { comentario << "\n"; }
<COMMENT><<EOF>> {
    std::cerr << "ERROR: comentari sense tancar" << std::endl;
    yyterminate(); // Detiene el analizador inmediatamente
}


"constant"   { 
    logToken("MOD_CONSTANT");
    return MOD_CONSTANT; }


"enter"      { 
    logToken("TIPUS_ENTER");
    return TIPUS_ENTER; }
"caracter"   { 
    logToken("TIPUS_CARACTER");
    return TIPUS_CARACTER; }
"cadena"     { 
    logToken("TIPUS_CADENA");
    return TIPUS_CADENA; }
"boolea"     { 
    logToken("TIPUS_BOOLEA");
    return TIPUS_BOOLEA; }
"void"       { 
    logToken("TIPUS_VOID");
    return TIPUS_VOID; }


"tupla"      { 
    logToken("OBJ_TUPLA");
    return OBJ_TUPLA; }


"="          { 
    logToken("ASSIGN");
    return ASSIGN; }
";"          { 
    logToken("PUNTICOMA");
    return PUNTICOMA; }
","          { 
    logToken("COMA");
    return COMA; }
"."          { 
    logToken("PUNT");
    return PUNT; }
":"          { 
    logToken("DOBLEPUNT");
    return DOBLEPUNT; }


"mes"        { 
    logToken("SUMA");
    return SUMA; }
"menys"      { 
    logToken("RESTA");
    return RESTA; }
"per"        { 
    logToken("MULT");
    return MULT; }
"entre"      { 
    logToken("DIV");
    return DIV; }
"modul"      { 
    logToken("MODUL");
    return MODUL; }
"//"         { 
    logToken("DIVISIO_ENTER");
    return DIVISIO_ENTER; }


"mateixque"  { 
    logToken("IGUALTAT");
    return IGUALTAT; }
"distint"    { 
    logToken("DIFERENT");
    return DIFERENT; }
"<="         { 
    logToken("MENOR_IGUAL");
    return MENOR_IGUAL; }
">="         { 
    logToken("MAJOR_IGUAL");
    return MAJOR_IGUAL; }
"<"          { 
    logToken("MENOR");
    return MENOR; }
">"          { 
    logToken("MAJOR");
    return MAJOR; }
"++"         { 
    logToken("INC");
    return INC; }
"--"         { 
    logToken("DEC");
    return DEC; }
"+="         { 
    logToken("MES_IGUAL");
    return MES_IGUAL; }
"-="         { 
    logToken("MENYS_IGUAL");
    return MENYS_IGUAL; }


"&&"         { 
    logToken("AND");
    return AND; }  
"||"         { 
    logToken("OR");
    return OR; }    
"no"         { 
    logToken("NOT");
    return NOT; }


"("          { 
    logToken("PAR_OPEN");
    return PAR_OPEN; }
")"          { 
    logToken("PAR_CLOSE");
    return PAR_CLOSE; }
"ç"          { 
    logToken("KEY_OPEN_CLOSE");
    return KEY_OPEN_CLOSE; }
"¿"          { 
    logToken("COND_OPEN");
    return COND_OPEN; }
"?"          { 
    logToken("COND_CLOSE");
    return COND_CLOSE; } 
"["          { 
    logToken("CLAUDATOR_OPEN");
    return CLAUDATOR_OPEN; }
"]"          { 
    logToken("CLAUDATOR_CLOSE");
    return CLAUDATOR_CLOSE; }


"es"         { 
    logToken("INICI_COND");
    return INICI_COND; }
"sinoes"     { 
    logToken("CONTINUACIO_COND");
    return CONTINUACIO_COND; }
"altre"      { 
    logToken("FI_COND");
    return FI_COND; }



"mentre"     { 
    logToken("BUCLE_MENTRE");
    return BUCLE_MENTRE; }
"recorrer"   { 
    logToken("BUCLE_PER");
    return BUCLE_PER; }



"funcio"     { 
    logToken("INICI_FUNCIO");
    return INICI_FUNCIO; }
"->"         { 
    logToken("RETORN");
    return RETORN; }
"retorna"    { 
    logToken("RET");
    return RET; }



"imprimeix"  { 
    logToken("FUNC_IMPRIMEIX");
    return FUNC_IMPRIMEIX; }
"entrada"    { 
    logToken("FUNC_ENTRADA");
    return FUNC_ENTRADA; }
"cast"       { 
    logToken("FUNC_CAST");
    return FUNC_CAST; }

"main"       { 
    logToken("MAIN");
    return MAIN; }


{INTEGER}   { 
    yylval.ival = atoi(YYText());
    logToken("INTEGER");
    return INTEGER;
}

{CARACTER}  {
    yylval.sval = new string(YYText());
    logToken("CARACTER");
    return CARACTER;
}

{STRING} { 
    yylval.sval = new string(YYText());
    logToken("STRING");
    return STRING;
}

{BOOL}  { 
    yylval.bval = (strcmp(YYText(), "vertader") == 0); 
    logToken("BOOL");
    return BOOL; 
}

{IDENTIFICADOR} { 
    yylval.sval = new string(YYText());
    logToken("ID");
    return ID; 
}



[ \t\r]+    { /* ignorar */ }

\n          { /* flex incrementa el nombre de linea amb yylineno */ }

.           { 
              cerr << "Error lexic: Caracter inesperat '" << YYText() 
                   << "' en línia " << yylineno << endl;
              return ERROR_TOKEN; 
            }

%%


int yyFlexLexer::yywrap() { return 1; }

// main excluido
