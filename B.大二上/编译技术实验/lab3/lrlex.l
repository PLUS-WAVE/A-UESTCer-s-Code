%{
    #include <stdlib.h>
    #include "ast.h"
    #include "lrparser.tab.h"
    int type;
%}

%%
[ \t\n] ;
(\/\/.*\n)|(\/\*.*\*\/) ;

int { type = Y_INT; return Y_INT; }
float { type = Y_FLOAT; return Y_FLOAT; }

void { type = Y_VOID; return Y_VOID; }
const { return Y_CONST; }
if { return Y_IF; }
else { return Y_ELSE; }
while { return Y_WHILE; }
break { return Y_BREAK; }
continue { return Y_CONTINUE; }
return { return Y_RETURN; }

"+" { return Y_ADD; }
"-" { return Y_SUB; }
"*" { return Y_MUL; }
"/" { return Y_DIV; }
"%" { return Y_MODULO; }
"<" { return Y_LESS; }
"<=" { return Y_LESSEQ; }
">" { return Y_GREAT; }
">=" { return Y_GREATEQ; }
"!=" { return Y_NOTEQ; }
"==" { return Y_EQ; }
"!" { return Y_NOT; }
"&&" { return Y_AND; }
"||" { return Y_OR; }
"=" { return Y_ASSIGN; }

"(" { return Y_LPAR; }
")" { return Y_RPAR; }
"{" { return Y_LBRACKET; }
"}" { return Y_RBRACKET; }
"[" { return Y_LSQUARE; }
"]" { return Y_RSQUARE; }
"," { return Y_COMMA; }
";" { return Y_SEMICOLON; }

[0-9]+ { yylval.int_value = atoi(yytext); return num_INT; }
[0-9]*\.[0-9]+ { yylval.float_value = atof(yytext); return num_FLOAT; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.id_name = strdup(yytext); return Y_ID; }
0x[0-9a-fA-F]+ { yylval.int_value = strtol(yytext, NULL, 16); return num_INT; }
%%

int yywrap() {
	return 1;
}