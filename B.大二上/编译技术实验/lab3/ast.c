#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "lrparser.tab.h"

// 创建新的AST节点
past newAstNode(){
	past node = malloc(sizeof(ast));
	if(node == NULL)
	{
		exit(0);
	}
	memset(node, 0, sizeof(ast));
	return node;
}
// 显示AST
void showAst(past node, int nest){
	if(node == NULL)
		return;
	int i = 0;
	if(node->nodeType == TRANSLATION_UNIT){
		showTranstion(node, nest + 1);
		return;
	} else if(node->nodeType == INTEGER_LITERAL){
		printf("%d%s  %d\n", nest-1, node->snodeType, node->ivalue);
	} else if(node->nodeType == FLOATING_LITERAL){
		printf("%d%s  %f\n", nest-1, node->snodeType, node->fvalue);
	} else if(node->nodeType == IF_STMT){
		printf("%d%s\n", nest-1, node->snodeType);
		showAst(node->if_cond, nest+1);
	} else if(node->nodeType == FUNCTION_DECL){
		printf("%d%s  '%s'\n", nest-1, node->snodeType, node->svalue);
	} else if(node->nodeType == PARM_DECL){
		showParaDecl(node);
		return;
	} else if(node->nodeType == COMPOUND_STMT){
		printf("%d%s\n", nest-1, node->snodeType);
		node = node->right;
		showCompoundStmt(node, nest + 1);
		return;
	} else if(node->nodeType == VAR_DECL){
		printf("%d%s: '%s'\n", nest-1, node->snodeType, node->svalue);
	} else if(node->nodeType == CALL_EXPR){
		printf("%d%s\n", nest-1, node->snodeType);
	} else if(node->nodeType == INIT_LIST_EXPR){
		printf("%d%s\n", nest-1, node->snodeType);
	}else if(node->nodeType == ARRAY_SUBSCRIPT_EXPR){
		printf("%d%s\n", nest-1, node->snodeType);
	}else if(node->nodeType == PAREN_EXPR){
		printf("%d%s\n", nest-1, node->snodeType);
	} else if(node->nodeType==DECL_REF_EXPR){
		printf("%d%s: '%s'\n", nest-1, node->snodeType, node->svalue);
	} else if(node->svalue != NULL){
		printf("%d%s  '%s'\n", nest-1, node->snodeType, node->svalue);
	} else{
		if(node->snodeType)
		printf("%d%s\n", nest-1, node->snodeType);
		else
		nest--;
	}
	showAst(node->left, nest+1);
	showAst(node->right, nest+1);
}
// 显示整个翻译单元的AST
void showTranstion(past node, int nest){
	if(node == NULL){
		return;
	}
	while(node->right != NULL){
		showAst(node->left, nest);
		node = node->right;
	}
	showAst(node->left, nest);
}
// 显示函数调用
void showCallExp(past node, int nest){ 
	if(node == NULL){
		return;
	}
	while(node->right != NULL){
		showAst(node->left, nest);
		node = node->right;
	}
	showAst(node->left, nest);
}
// 显示复合语句的AST
void showCompoundStmt(past node, int nest){
	if(node == NULL){
		return;
	}
	while(node->right != NULL){
		showAst(node->left, nest);
		node = node->right;
	}
	showAst(node->left, nest);
}
// 显示函数参数的AST
void showParaDecl(past node){
	if(node == NULL){
		return;
	}
	int symm = 1;
	past stack[100];
	int top = 0;
    while(top || node){
		if(node != NULL){ 
			stack[top++] = node;
            node = node->left;
        }else if(top != 0){   
			node = stack[--top];
			if(symm == 1){
				printf("%d%s '%s'\n", symm,node->snodeType, node->svalue);
				symm--;
			} else {
				printf("%d%s '%s'\n", symm,node->snodeType, node->svalue);
			}
            node = node->right;
        }
    }
}
// 获取标识符
char* get_id(char* id){
	int i = 0;
	while(id[i] != '\0'){
		i++;
	}
	char* s = malloc(sizeof(char) * (i + 1));
	memcpy(s, id, i + 1);
	return s;
}
// 获取变量类型字符串
char* get_stype(int type){
	char* stype;
	if(type == 0){
		return NULL;
	} else if(type == Y_INT){
		stype = "int";
	} else if(type == Y_FLOAT){
		stype = "float";
	} else {
		stype = "void";
	}
	return stype;
}
// 获取常量类型字符串
char* get_conststype(int type){
	char* stype;
	if(type == 0){
		return NULL;
	} else if(type == Y_INT){
		stype = "const int";
	} else if(type == Y_FLOAT){
		stype = "const float";
	} else {
		stype = "const void";
	}
	return stype;
}
// 创建翻译单元的AST节点
past newCompUnit(past left, past right){
	past node = newAstNode();
	node->nodeType = TRANSLATION_UNIT;
	node->snodeType = "TRANSLATION_UNIT";
	node->left = left;
	node->right = right;
	return node;
}
// 创建声明语句的AST节点
past newDeclStmt(past left, past right){
	past node = newAstNode();
	node->nodeType = DECL_STMT;
	node->snodeType = "DECL_STMT";
	node->left = left;
	node->right = right; 
	return node;
}
// 创建带初始化列表的AST节点
past newDeclStmt1(past left,past right){
	past node = newAstNode();
	node->left = left;
	node->right = right;
	return node;
}
// 创建初始化列表的AST节点
past newInitList(past left, past right){
	past node = newAstNode();
	node->nodeType = INIT_LIST_EXPR;
	node->snodeType = "INIT_LIST_EXPR";
	node->left = left;
	node->right = right; 
	return node;
}
// 创建变量声明的AST节点
past newVarDecl(char* stype, int type, int if_const, char *name, past left, past right){ 
	past node = newAstNode();
	node->nodeType = VAR_DECL;
	node->snodeType = "VAR_DECL";
	node->stype = stype;
	node->left = left;
	node->right = right;
	node->ivalue = type;
	node->svalue = name;
	node->if_const = if_const;
	return node;	
}
// 创建声明引用表达式的AST节点
past newDeclRefExp(char* name, past left, past right){
	past node = newAstNode();
	node->nodeType = DECL_REF_EXPR;
	node->snodeType = "DECL_REF_EXPR";
	node->svalue = name;
	node->left = left;
	node->right = right;
	return node;
}
// 创建函数声明的AST节点
past newFuncDecl(char* stype, int type, char* name, past left, past right){
	past node = newAstNode();
	node->nodeType = FUNCTION_DECL;
	node->snodeType = "FUNCTION_DECL";
	node->svalue = name;
	node->left = left;
	node->right = right;
	node->ivalue = type;
	node->stype = stype;
	return node;	
}
// 创建复合语句的AST节点
past newCompoundStmt(past left, past right){
	past node = newAstNode();
	node->nodeType = COMPOUND_STMT;
	node->snodeType = "COMPOUND_STMT";
	node->left = left;
	node->right = right;
	return node;
}
// 创建数组下标表达式的AST节点
past newArraySubscriptsExp(past left, past right){
	past node = newAstNode();
	node->nodeType = ARRAY_SUBSCRIPT_EXPR;
	node->snodeType = "ARRAY_SUBSCRIPT_EXPR";
	node->left = left;
	node->right = right;
	return node;
}
// 创建二元操作表达式的AST节点
past newBinaryOper(char* soper, int oper, past left, past right){
	past node = newAstNode();
	node->nodeType = BINARY_OPERATOR;
	node->snodeType = "BINARY_OPERATOR";
	node->ivalue = oper;
	node->svalue = soper;
	node->left = left;
	node->right = right;
	return node;
}
// 创建函数调用表达式的AST节点
past newCallExp(char* stype, int type, char* name, past left, past right){
	past node = newAstNode();
	node->nodeType = CALL_EXPR;
	node->snodeType = "CALL_EXPR";
	node->stype = stype;
	node->ivalue = type;
	node->svalue = name;
	node->left = left;
	node->right = right;
	return node;
}
// 创建函数参数的AST节点
past newParaDecl(char* stype,char* name,  past left, past right){
	past node = newAstNode();
	node->nodeType = PARM_DECL;
	node->snodeType = "PARM_DECL";
	node->stype = stype;
	node->svalue = name;
	node->left = left;
	node->right = right;
	return node;
}
// 创建整数字面量的AST节点
past newIntVal(int ival){
	past node = newAstNode();
	node->nodeType = INTEGER_LITERAL;
	node->snodeType = "INTEGER_LITERAL";
	node->ivalue = ival;
	return node;
}
// 创建浮点数字面量的AST节点
past newFloatVal(float fval){
	past node = newAstNode();
	node->nodeType = FLOATING_LITERAL;
	node->snodeType = "FLOATING_LITERAL";
	node->fvalue = fval;
	return node;
}
// 创建if语句的AST节点
// if_cond为条件表达式，left为if复合语句，right为else复合语句
past newIfStmt(past if_cond, past left, past right){ 
	past node = newAstNode();
	node->nodeType = IF_STMT;
	node->snodeType = "IF_STMT";
	node->if_cond = if_cond;
	node->left = left;
	node->right = right;
	if(right != NULL){
		node->svalue = "has else";
	} else {
		node->svalue = "no else";
	}
	return node;
}
// 创建while语句的AST节点
// left为循环条件表达式，right为循环体复合语句
past newWhileStmt(past left, past right){  
	past node = newAstNode();
	node->nodeType = WHILE_STMT;
	node->snodeType = "WHILE_STMT";
	node->left = left;
	node->right = right;
	return node;
}
// 创建括号表达式的AST节点
past newParen(past left, past right){
	past node = newAstNode();
	node->nodeType = PAREN_EXPR;
	node->snodeType = "PAREN_EXPR";
	node->left = left;
	node->right = right;
	return node;
}
// 创建continue语句的AST节点
past newContinueStmt(){
	past node = newAstNode();
	node->nodeType = CONTINUE_STMT;
	node->snodeType = "CONTINUE_STMT";
	return node;
}
// 创建break语句的AST节点
past newBreakStmt(){
	past node = newAstNode();
	node->nodeType = BREAK_STMT;
	node->snodeType = "BREAK_STMT";
	return node;
}
// 创建return语句的AST节点
// left为返回值结点，right默认为NULL
past newReturnStmt(past left, past right){   
	past node = newAstNode();
	node->nodeType = RETURN_STMT;
	node->snodeType = "RETURN_STMT";
	node->left = left;
	node->right = right;
	return node;
}
// 创建类型节点
past newType(int oper){
	past node = newAstNode();
	node->ivalue = oper;
	return node;
}