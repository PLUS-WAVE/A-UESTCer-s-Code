%{
    #include <stdio.h>
    #include "ast.h"
    int yylex(void);
    void yyerror(char *s);
    extern int type;
%}

%union
{
    int token;
    int int_value;
    float float_value;
    char* id_name;
    past pAst;
};
%token <int_value> num_INT Y_INT Y_VOID Y_CONST Y_IF Y_ELSE Y_WHILE Y_BREAK Y_CONTINUE Y_FLOAT Y_RETURN
%token <int_value> Y_ADD Y_COMMA Y_DIV  Y_LPAR Y_SUB Y_LSQUARE Y_MODULO Y_MUL Y_NOT Y_RPAR Y_RSQUARE Y_RBRACKET
%token <int_value> Y_LESS Y_LESSEQ Y_GREAT Y_GREATEQ Y_NOTEQ Y_EQ Y_AND Y_OR Y_ASSIGN Y_LBRACKET Y_SEMICOLON
%token <float_value> num_FLOAT
%token <id_name> Y_ID 
%token YYEOF
%type  <pAst>	program Exp AddExp MulExp UnaryExp CallParams PrimaryExp LVal ArraySubscripts
%type  <pAst>	Block BlockItem BlockItems Stmt Stmt1 RelExp EqExp LAndExp LOrExp  
%type  <pAst>	FuncDef FuncParam FuncParams Type 
%type  <pAst>  CompUnit Decl ConstDecl ConstDefs ConstDef ConstExps ConstInitVal ConstInitVals 
%type  <pAst>  VarDecl VarDecls VarDef InitVal InitVals ConstExp

%%
program: CompUnit YYEOF{showAst($1,0);}
            ;
CompUnit: VarDef CompUnit {past l=newCompUnit($1,NULL);l->right=$2;$$=l;}
        |ConstDecl CompUnit {past l=newCompUnit($1,NULL);l->right=$2;$$=l;}
        |FuncDef CompUnit {past l=newCompUnit($1,NULL);l->right=$2;$$=l;}
        |Decl {$$=newCompUnit($1,NULL);}
        |FuncDef{$$=newCompUnit($1,NULL);}
        |VarDef{$$=newCompUnit($1,NULL);}
        ;
Decl:ConstDecl
    |VarDecl
    ;
VarDecl: Type VarDef Y_SEMICOLON {$$ = newDeclStmt(NULL, $2);} 
        | Type VarDef VarDecls Y_SEMICOLON {$$ = newDeclStmt($2, $3);}
        ;
 
VarDecls: Y_COMMA VarDef {$$ = $2;}
         | Y_COMMA VarDef VarDecls {$$ = newDeclStmt1($2, $3);}
         ;

VarDef: Y_ID {$$ = newVarDecl(get_stype(type), type, 0, $1, NULL, NULL);}
       | Y_ID Y_ASSIGN InitVal {$$ = newVarDecl(get_stype(type), type, 0, $1, NULL, $3);}
       | Y_ID ConstExps {$$ = newVarDecl(get_stype(type), type, 0, $1, NULL, NULL); }
       | Y_ID ConstExps Y_ASSIGN InitVal {$$ = newVarDecl(get_stype(type), type, 0, $1, NULL, $4); }
       |Type Y_ID Y_ASSIGN InitVal Y_SEMICOLON {$$ = newVarDecl(get_stype(type), type, 0, $2, NULL, $4);}
       |Type Y_ID Y_SEMICOLON {$$ = newVarDecl(get_stype(type), type, 0, $2, NULL, NULL);}
       |Type Y_ID ConstExps Y_SEMICOLON {$$ = newVarDecl(get_stype(type), type, 0, $2, NULL, NULL);}
       ; 

InitVal: Exp
        | Exp Y_COMMA Exp {$$ = newInitList($1,$3);}
        | Y_LBRACKET Y_RBRACKET {$$ = newInitList(NULL,NULL);}
        | Y_LBRACKET Exp Y_RBRACKET {$$ = newInitList($2,NULL);}
        | Y_LBRACKET Exp Y_COMMA Exp Y_RBRACKET {$$ = newInitList($2,$4);}
        | Y_LBRACKET InitVals Y_COMMA InitVals Y_RBRACKET {$$ = newInitList(newDeclStmt1($2,$4),NULL) ; }
        ;

InitVals: InitVal Y_COMMA InitVal {$$ = newDeclStmt1($1,$3); }
         ;
ConstDecl: Y_CONST Type ConstDef Y_SEMICOLON {$$ = newDeclStmt1(NULL, $3);} 
          | Y_CONST Type ConstDefs Y_SEMICOLON {$$ = newDeclStmt1(NULL, $3);}
          ;

ConstDefs: ConstDef Y_COMMA ConstDef {$$ = newDeclStmt1($1, $3);}
          | ConstDefs Y_COMMA ConstDef {$$ = newDeclStmt1($1, $3);}
          ;

ConstDef: Y_ID Y_ASSIGN ConstInitVal {$$ = newVarDecl(get_conststype(type), type, 1, $1, NULL, $3);}
         | Y_ID ConstExps Y_ASSIGN ConstInitVal {$$ = newVarDecl(get_conststype(type), type, 1, $1, NULL, $4); }
         ; 

ConstExps: Y_LSQUARE ConstExp Y_RSQUARE {$$ = $2;}
         | Y_LSQUARE ConstExp Y_RSQUARE ConstExps {$$ = $2; }
         ;

ConstInitVal: ConstExp
             | Y_LBRACKET Y_RBRACKET {$$ = NULL; }
             | Y_LBRACKET ConstInitVal Y_RBRACKET {$$ = $2;}
             | Y_LBRACKET ConstInitVal ConstInitVals Y_RBRACKET {$$ = newInitList($2,$3); }
             ;

ConstInitVals: Y_COMMA ConstInitVal {$$ = $2;}
              | Y_COMMA ConstInitVal ConstInitVals {$$ = newDeclStmt1($2,$3); }
              ;         
               
ConstExp: AddExp
          ;

FuncDef: Type Y_ID Y_LPAR Y_RPAR Block {$$ = newFuncDecl(get_stype($1->ivalue), $1->ivalue,$2, NULL, newCompoundStmt(NULL, $5));}
        | Type Y_ID Y_LPAR FuncParams Y_RPAR Block {$$ = newFuncDecl(get_stype($1->ivalue), $1->ivalue, $2, $4, newCompoundStmt(NULL, $6));}    
        ;

FuncParams: FuncParam 
           | FuncParams Y_COMMA FuncParam {$$=newDeclStmt1($1,$3);}
           ;

FuncParam: Type Y_ID {$$ = newParaDecl(get_stype($1->ivalue), $2, NULL, NULL);}
          | Type Y_ID Y_LSQUARE Y_RSQUARE {$$ = newParaDecl(get_stype($1->ivalue), $2, NULL, NULL);}
          | Type Y_ID ArraySubscripts {$$ = newParaDecl(get_stype($1->ivalue), $2, NULL, NULL);}
          | Type Y_ID Y_LSQUARE Y_RSQUARE ArraySubscripts {$$ = newParaDecl(get_stype($1->ivalue), $2, NULL, NULL);}
          ;

Type: Y_INT {yylval.int_value = Y_INT;$$ = newType(Y_INT);}
     | Y_FLOAT {yylval.int_value = Y_FLOAT;$$ = newType(Y_FLOAT);}
     | Y_VOID {yylval.int_value = Y_VOID;$$ = newType(Y_VOID);}
     ;

Stmt: LVal Y_ASSIGN Exp Y_SEMICOLON {$$ = newBinaryOper("=", Y_ASSIGN, $1, $3);}
     | Y_SEMICOLON {$$ = NULL;}
     | Exp Y_SEMICOLON {$$ = $1;}
     | Block 
     | Y_WHILE Y_LPAR LOrExp Y_RPAR Stmt {$$ = newWhileStmt($3, newCompoundStmt(NULL,$5));}
     | Y_IF Y_LPAR LOrExp Y_RPAR Block {$$ = newIfStmt($3, newCompoundStmt(NULL,$5), NULL);}
     | Y_IF Y_LPAR LOrExp Y_RPAR Block Y_ELSE Block {$$ = newIfStmt($3, newCompoundStmt(NULL,$5), newCompoundStmt(NULL,$7));}
     | Y_IF Y_LPAR LOrExp Y_RPAR Stmt1 {$$ = newIfStmt($3, $5, NULL);}
     | Y_IF Y_LPAR LOrExp Y_RPAR Stmt1 Y_ELSE Stmt1 {$$ = newIfStmt($3, $5, $7);}
     | Y_IF Y_LPAR LOrExp Y_RPAR Stmt1 Y_ELSE Block {$$ = newIfStmt($3, $5, newCompoundStmt(NULL,$7));}
     | Y_IF Y_LPAR LOrExp Y_RPAR Block Y_ELSE Stmt1 {$$ = newIfStmt($3, newCompoundStmt(NULL,$5), $7);}
     | Y_BREAK Y_SEMICOLON {$$ = newBreakStmt();}
     | Y_CONTINUE Y_SEMICOLON {$$ = newContinueStmt();}
     | Y_RETURN Exp Y_SEMICOLON {$$ = newReturnStmt($2, NULL);}
     | Y_RETURN Y_SEMICOLON {$$ = newReturnStmt(NULL, NULL);}
     ;
Stmt1: LVal Y_ASSIGN Exp Y_SEMICOLON {$$ = newBinaryOper("=", Y_ASSIGN, $1, $3);}
     | Y_SEMICOLON {$$ = NULL;}
     | Exp Y_SEMICOLON {$$ = $1;}
     | Block 
     | Y_WHILE Y_LPAR LOrExp Y_RPAR Stmt {$$ = newWhileStmt($3, newCompoundStmt(NULL,$5));}
     | Y_IF Y_LPAR LOrExp Y_RPAR Block {$$ = newIfStmt($3, newCompoundStmt(NULL,$5), NULL);}
     | Y_IF Y_LPAR LOrExp Y_RPAR Block Y_ELSE Block {$$ = newIfStmt($3, newCompoundStmt(NULL,$5), newCompoundStmt(NULL,$7));}
     | Y_IF Y_LPAR LOrExp Y_RPAR Stmt1 {$$ = newIfStmt($3, $5, NULL);}
     | Y_IF Y_LPAR LOrExp Y_RPAR Stmt1 Y_ELSE Stmt1 {$$ = newIfStmt($3, $5, $7);}
     | Y_IF Y_LPAR LOrExp Y_RPAR Stmt1 Y_ELSE Block {$$ = newIfStmt($3, $5, newCompoundStmt(NULL,$7));}
     | Y_IF Y_LPAR LOrExp Y_RPAR Block Y_ELSE Stmt1 {$$ = newIfStmt($3, newCompoundStmt(NULL,$5), $7);}
     | Y_BREAK Y_SEMICOLON {$$ = newBreakStmt();}
     | Y_CONTINUE Y_SEMICOLON {$$ = newContinueStmt();}
     | Y_RETURN Exp Y_SEMICOLON {$$ = newReturnStmt($2, NULL);}
     | Y_RETURN Y_SEMICOLON {$$ = newReturnStmt(NULL, NULL);}
Block: Y_LBRACKET BlockItems Y_RBRACKET {$$ = $2;}
      | Y_LBRACKET Y_RBRACKET {$$ = NULL;}
      ;

BlockItems: BlockItem {$$ = newCompoundStmt($1, NULL);}
           | BlockItem BlockItems {past l = newCompoundStmt($1, NULL); l->right = $2; $$ = l;}
           ;

BlockItem: Decl
          | Stmt 
          ;

RelExp: AddExp
       | AddExp Y_LESS RelExp {$$ = newBinaryOper("<", Y_LESS, $1, $3);}
       | AddExp Y_GREAT RelExp {$$ = newBinaryOper(">", Y_GREAT, $1, $3);}
       | AddExp Y_LESSEQ RelExp {$$ = newBinaryOper("<=", Y_LESSEQ, $1, $3);}
       | AddExp Y_GREATEQ RelExp {$$ = newBinaryOper(">=", Y_GREATEQ, $1, $3);}
       ;

EqExp: RelExp
      | RelExp Y_EQ EqExp {$$ = newBinaryOper("==", Y_EQ, $1, $3);}
      | RelExp Y_NOTEQ EqExp {$$ = newBinaryOper("!=", Y_NOTEQ, $1, $3);}
      ;

LAndExp: EqExp 
        | EqExp Y_AND LAndExp {$$ = newBinaryOper("&&", Y_AND, $1, $3);}
        ;

LOrExp: LAndExp
       | LAndExp Y_OR LOrExp {$$ = newBinaryOper("||", Y_OR, $1, $3);}
       ;

Exp: AddExp  
     ;


AddExp: MulExp
     | AddExp Y_ADD MulExp {$$ = newBinaryOper("+", Y_ADD, $1, $3);}
     | AddExp Y_SUB MulExp {$$ = newBinaryOper("-", Y_SUB, $1, $3);}
     ;

MulExp: UnaryExp
     | MulExp Y_MUL UnaryExp {$$ = newBinaryOper("*", Y_MUL, $1, $3);}
     | MulExp Y_DIV UnaryExp {$$ = newBinaryOper("/", Y_DIV, $1, $3);}
     | MulExp Y_MODULO UnaryExp {$$ = newBinaryOper("%", Y_MODULO, $1, $3);}
     ;

UnaryExp: PrimaryExp
     | LVal Y_LPAR Y_RPAR {$$ = newCallExp(NULL, 0, NULL, $1, NULL);}
     | LVal Y_LPAR CallParams Y_RPAR {$$ = newCallExp(NULL, 0, NULL, $1, $3);}
     | Y_ADD UnaryExp {$$ = newBinaryOper("+", Y_ADD, NULL, $2);}
     | Y_SUB UnaryExp {$$ = newBinaryOper("-", Y_SUB, NULL, $2);}
     | Y_NOT UnaryExp {$$ = newBinaryOper("!", Y_NOT, NULL, $2);}
     ;

CallParams: Exp
     | Exp Y_COMMA CallParams {$$ = newDeclStmt1($1, $3);}
     ;

PrimaryExp: Y_LPAR Exp Y_RPAR {$$ = newParen($2,NULL);}
     | LVal 
     | num_INT {$$ = newIntVal($1);}
     | num_FLOAT {$$ = newFloatVal($1);}
     ;

LVal: Y_ID {$$ = newDeclRefExp($1, NULL, NULL);}
    | ArraySubscripts {$$ = $1;}
    ;

ArraySubscripts: ArraySubscripts Y_LSQUARE Exp Y_RSQUARE {$$=newArraySubscriptsExp($1, $3);}
               | Y_ID Y_LSQUARE Exp Y_RSQUARE {$$=newArraySubscriptsExp(newDeclRefExp($1,NULL,NULL), $3);}
               ;

%%

void yyerror(char *s)
{
    printf("%s",s);
}
int main()
{
	yyparse();
	return 0;
}
