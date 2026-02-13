#ifndef POSIBLETAULA_H
#define POSIBLETAULA_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>

// Tipos básicos de datos
enum class TipoBasico {
    T_VOID, T_ENTER, T_CARACTER, T_CADENA, T_BOOLEA, T_TUPLA, T_UNKNOWN
};

// Tipos de descripción
enum class TipoDesc {
    D_NUL, D_VAR, D_CONST, D_PROC, D_CAMP, D_ARG
//   0       1      2       3        4      5
};

// Descripción de un símbolo con información de tipos
class Descripcion {
public:
    TipoDesc tipo;
    TipoBasico tipo_basico;
    std::string valor;
    int address;
    bool inicializada;                          // Para constantes
    std::vector<TipoBasico> tipos_parametros;   // Para funciones
    TipoBasico tipo_retorno;                    // Para funciones
    int tam_tupla;                              // Para tuplas
    std::vector<TipoBasico> tipos_tupla;        // Para tipos de elementos de tupla

    // Constructor por defecto
    Descripcion(TipoDesc t = TipoDesc::D_NUL, std::string v = "", TipoBasico tb = TipoBasico::T_UNKNOWN) 
        : tipo(t), tipo_basico(tb), valor(v), address(0), inicializada(false), 
          tipo_retorno(TipoBasico::T_VOID), tam_tupla(0), tipos_tupla({}) {}

    // Constructor para variables/constantes
    Descripcion(TipoDesc t, TipoBasico tb) 
        : tipo(t), tipo_basico(tb), valor(""), address(0), inicializada(false),
          tipo_retorno(TipoBasico::T_VOID), tam_tupla(0), tipos_tupla({}) {}

    // Constructor para funciones
    Descripcion(TipoDesc t, TipoBasico tr, std::vector<TipoBasico> tp)
        : tipo(t), tipo_basico(TipoBasico::T_VOID), valor(""), address(0), inicializada(false),
          tipos_parametros(tp), tipo_retorno(tr), tam_tupla(0), tipos_tupla({}) {}

    std::string toString() const;
    std::string tipoBasicoToString() const;
    static std::string tipoBasicoToString(TipoBasico tb);
};


// Entrada de la Taula de Descripció (td)
struct EntradaTD {
    int np;            // Nivel de profundidad
    Descripcion d;     // Descripción
    int first;         // Índice a 'te'

    EntradaTD(int _np = 0, Descripcion _d = Descripcion()) 
        : np(_np), d(_d), first(0) {}
};

// Entrada de la Taula d'Expansió (te)
struct EntradaTE {
    std::string id;    
    int np;            
    Descripcion d;     
    int next;          

    EntradaTE(std::string _id = "", int _np = -1, Descripcion _d = Descripcion()) 
        : id(_id), np(_np), d(_d), next(0) {}
};

// Clase TablaSimbolos
class TablaSimbolos {
private:
    int n; // Nivel actual
    std::vector<int> ta; 
    std::vector<EntradaTE> te; 
    std::unordered_map<std::string, EntradaTD> td;

public:
    TablaSimbolos();

    void buidar();
    void entrarBloc();
    void salirBloc();
    void posar(const std::string& id, Descripcion d);
    Descripcion consultar(const std::string& id) const;
    void imprimirEstado() const;
};

// Funciones helper para validación de tipos
namespace ValidacionTipos {
    bool esNumerico(TipoBasico t);
    bool esCompatible(TipoBasico t1, TipoBasico t2);
    TipoBasico mayorTipo(TipoBasico t1, TipoBasico t2);
    std::string tipoToString(TipoBasico t);
};

#endif 

/*                                                                                                    
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
                                                                                                    
                                                                                                    
                                     ----=---------------------                                     
                      ------------:--===============--=-==========----                              
                   --=======-=====--:-==++======--===-================---::                         
               -=====================-:-===+=======================--::::::::::                     
              -===================--===---=++====================-::::...::-----:                   
            -=============--------===-----:=++++++++++++++++==--::.....::--=====--::                
           ==++==============----------------++++++++++*+++++=-::.....:--========--::               
          -+++++==+=================----------+**********++==--::...::--===========--::             
         ==++++++++=+++==+==============------=*********+*+====-::::-================-::            
        +++++++++++++++++++++===============---=******##**+++==----==================--:::          
       ==+++++++**+++*+++++++=================--==+=+*##%***++======++++=============---:::         
       =++++++++++***+**++++++++++++======-=-==---=-+*#*-+=+*++====++=================-:::::        
       =++++++***********++++++++=++====---------::==--::-+-+++======================---::::        
      -+++*+***************+*+++++++======-:::..:::::::==-:-=========+================---.:::       
      -+++***#######********++**+++======-:::.::::::::-----===============-------=====-::::::       
      =++**#########*******+*++++++====-:..:::::::::----=================-----------=---::-::       
      =++**#########*##*******++=======-:.::::::::------=----=======--==------------=--::::::       
       +**############*****++======----::::::::::---------------==-------:---------------::::       
       =*############****++====--==--::::.:::::::::----------::---=----------====----------::       
       =**###########**++===--------:::::::::::::--------------------=--:------====--------::       
        +*###########**+====--------:::::::::::--------------=---------=-------------------:        
         **##########*+=====--------::::::::::-----------------------:------------------::::        
          ****######**+====-----------------:::::-----=====----------::--------------------         
           ***######*++++====-------------------:---===----------:::-::::----------:::-----         
            *****###**+++++===----------------------====----------::-----------------:----          
             ***####***+++++======------====-------==-===--------:::---:-----------------           
               **####***++++++================-------===--------------------------------            
                 **###**++++++++==========--==-----======---------:--------------------             
                   *###**++++++++=++==++=================-----------------------------              
                     **#****+++++++++++++====+===============-----------------------                
                       #***********++++++++=+================-=------======--==--=                  
                          **#********+++++++=================-==--=======-======                    
                              *********+++++==++=============================                       
                                  ******+++++++==+======++==++=======+++                            
                                        ***+++++++++=====+++++                                      
                                                                                                    
                                                                                                    
                                                                                Quien diría que el paraguayo es una fruta.                
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
                                                                                                    
*/