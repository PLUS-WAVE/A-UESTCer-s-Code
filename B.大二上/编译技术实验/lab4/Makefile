all:  ast.c ast.h genllvm.c genllvm.h lex.yy.c lrparser.tab.c main.c
	gcc -L/evecode/libs -I/evecode/include/ -o 203 -O0 -g  ast.c ast.h genllvm.c genllvm.h lex.yy.c lrparser.tab.c main.c -lfl -lm 

lrparser.tab.c : lrparser.y
	 bison -d lrparser.y

lex.yy.c : lrlex.l
	 flex -o lex.yy.c lrlex.l
