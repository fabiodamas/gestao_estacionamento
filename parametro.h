#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>

struct registro_parametro {
   char vagasdisponiveis[5]; //  char numeracao[5];
   char status;   
} registro_parametro;

FILE *fp_par;

/*prototipo das funcoes*/
void incluirParametro (void);
void consultarParametro(void);
void excluirParametro(void);
void alterarParametro(void);
void abrirParametro(void);
void listarParametro(void);

int gestao_parametro(void)
{
 char opcao[2], op;
    do{
		do{
	       printf("\n\n\n\n\n\n\n");
	       printf("\t########################################################\n");
	       printf("\t# Gestao de Estacionamento  Versao 1.0.0               #\n");
	       printf("\t#                                                      #\n");
	       printf("\t#                                                      #\n");
	       printf("\t# Manutencao de Parametro                              #\n");
	       printf("\t########################################################\n\n\n");
	       printf("\n Digite uma das opcoes: \n\n");
	       printf("\n <1> - Alterar");
	       printf("\n <2> - Listar");
	       printf("\n <3> - Voltar");
	       printf("\n\n\n Opcao:");
	       gets(opcao);
	       
	       
	       op=tolower(*opcao);
	       
	    } 
		while(!strchr("123",op));
		
	     switch(op){
		  case '1' : incluirParametro(); break;
		  case '2' : listarParametro(); break;
		  case '3' : return(0); break;
	    }
	} while(1);	
}

/*Funcoes*/
int abrirParametro(const char tipo[3])
{
     if((fp_par=fopen("D:\\gestao_estacionamento\\parametro.dat", tipo))==NULL){
	 	printf("\n Nao ha parametro gravado!!\n");
	 	getch();
      	return(0) ;
     }
     else{
     	return(1);
     }  
	      
}


void incluirParametro(void)
{    //char *um="0";

     abrirParametro("w");
     fseek(fp_par,0L, SEEK_END);

   
	printf("\n Digite a quantidade de vagas: ou fim \n\n");
	gets(registro_parametro.vagasdisponiveis);

	if ((strcmp(registro_parametro.vagasdisponiveis,"fim")!=0)&&(strcmp(registro_parametro.vagasdisponiveis,"FIM")!=0)){
		registro_parametro.status='1';
		if(fwrite(&registro_parametro, sizeof(struct registro_parametro), 1, fp_par) != 1)
		{
		printf("\n Erro de gravacao!!");
		getch();
		}
		else
		{   printf("\n Gravacao feita com sucesso...\n\n");}
			getch();
		}

     fclose(fp_par);
}


void listarParametro(void) {
   int cont=0;
   int qtd;
   
   qtd = abrirParametro("rb");

   if (qtd!=0) {   
   	 fseek(fp_par, 0L, SEEK_SET);
	 fread(&registro_parametro, sizeof(struct registro_parametro),1, fp_par);
	   do
	   {
	      if (registro_parametro.status!='0')
		 {
		    printf("\nVagas disponiveis..: %s",registro_parametro.vagasdisponiveis);
		    printf("\n");
		    cont++;
		 }
	      fread(&registro_parametro, sizeof(struct registro_parametro),1, fp_par);
	      }while(!feof(fp_par));
	   printf("\n Pressione qualquer tecla para voltar");
	   getch();
  }
}

