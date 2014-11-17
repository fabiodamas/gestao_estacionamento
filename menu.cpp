#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include "tarifa.h"

// void gestao_tarifacao(void);
void teste2 (void);


int main(void)
{
 char opcao[2], op;
 do{
    do{
       printf("\n\n\n\n\n\n\n");
       printf("\t########################################################\n");
       printf("\t# Gestao de Estacionamento  Versao 1.0.0               #\n");
       printf("\t#                                                      #\n");
       printf("\t#                                                      #\n");
       printf("\t# Menu Principal                                       #\n");
       printf("\t########################################################\n\n\n");
       printf("\n Digite uma das opcoes: \n\n");
       printf("\n <1> - Tarifacao");
       printf("\n <2> - Entrada de Veiculo");
       printf("\n <3> - Saida de Veiculo");
       printf("\n <4> - Fechamento de Caixa");
       printf("\n <5> - Parametros");
       printf("\n <6> - Sair");
       printf("\n\n\n Opcao:");
       gets(opcao);
       
       
       op=tolower(*opcao);       
    } 
	while(!strchr("123456",op));
	
       switch(op){/*D*/
	  case '1' : gestao_tarifacao(); break;
	  case '2' : teste2(); break;
	  case '3' : ; break;
	  case '4' : ; break;
	  case '5' : ; break;
	  case '6' : exit(0);
       }
 }while(1);
}


void teste2(void)
{   
	printf("\n teste2");
	getch();
}
