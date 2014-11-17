#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include "tarifa.h"
#include "movimento.h"
#include "parametro.h"

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
       printf("\n <4> - Listar Veiculos");
       printf("\n <5> - Fechamento de Caixa");
       printf("\n <6> - Parametros");
       printf("\n <7> - Sair");
       printf("\n\n\n Opcao\:");
       gets(opcao);
       
       
       op=tolower(*opcao);       
    } 
	while(!strchr("1234567",op));
	
       switch(op){
	  case '1' : gestao_tarifacao(); break;
	  case '2' : entradaVeiculo(); break;
	  case '3' : saidaVeiculo(); break;
	  case '4' : listarMovimento(); break;
	  case '5' : ; break;
	  case '6' : gestao_parametro(); break;
	  case '7' : exit(0);
       }
 }while(1);
}



