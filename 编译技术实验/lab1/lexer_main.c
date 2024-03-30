#include <stdio.h>
#include <stdlib.h>
#include "token.h"

extern int yylex();
extern _YYLVAL yylval;

int main(int argc, char **argv) {
    int token;
    while((token = yylex()) != 0) {
		if(token <= 260){
			switch (token) {
				case Y_ID:
					printf("<%d, %s>\n", token, yylval.id_name);
                    free(yylval.id_name);                    
					break;
				case num_INT:
					printf("<%d, %d>\n", token, yylval.int_value);
					break;
				case num_FLOAT:
					printf("<%d, %f>\n", token, yylval.float_value);
					break;
				default:
                    printf("<UNKNOWN>\n");
                    break;					
            }	
        }
        else{
            if(token <= 269 || token == 293) {
                char words[10] = "KEYWORD";
                printf("<%d, %s>\n", token, words);
            }else if(token <= 284) {
                char words[10] = "OPERATOR";
                printf("<%d, %s>\n", token, words);
            }else if(token <= 292) {
                char words[10] = "SYMBOL";
                printf("<%d, %s>\n", token, words);
            }else{
                printf("<UNKNOWN>\n");
            }            
        }       
    }
    return 0;
}