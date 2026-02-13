rm -f lexer.yy.cpp parser.tab.cpp parser.tab.hpp mi_parser
bison -d -o parser.tab.cpp parser.y      # genera parser.tab.cpp i parser.tab.hpp
flex -o lexer.yy.cpp lexico.l           # genera lexer.yy.cpp
g++ -std=c++17 -o mi_parser main.cpp taula_simbols.cpp parser.tab.cpp lexer.yy.cpp