#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct registro_tarifa {
   char hora[5]; //  char numeracao[5];
   char valor[40]; // char preco[40];
   char status;
   
} reg;

FILE *fp_tar;

/*prototipo das funcoes*/
void incluirTarifa (void);
void consultarTarifa(void);
void excluirTarifa(void);
void alterarTarifa(void);
void abrirTarifa(void);
void listarTarifa(void);

int gestao_tarifacao(void)
{
 char opcao[2], op;
    do{
		do{
	       printf("\n\n\n\n\n\n\n");
	       printf("\t########################################################\n");
	       printf("\t# Gestao de Estacionamento  Versao 1.0.0               #\n");
	       printf("\t#                                                      #\n");
	       printf("\t#                                                      #\n");
	       printf("\t# Manutencao de Tarifas                                #\n");
	       printf("\t########################################################\n\n\n");
	       printf("\n Digite uma das opcoes: \n\n");
	       printf("\n <1> - Incluir");
	       printf("\n <2> - Alterar");
	       printf("\n <3> - Excluir");
	       printf("\n <4> - Consultar");
	       printf("\n <5> - Listar");
	       printf("\n <6> - Voltar");
	       printf("\n\n\n Opcao:");
	       gets(opcao);
	       
	       
	       op=tolower(*opcao);
	       
	    } 
		while(!strchr("123456",op));
		
	     switch(op){/*D*/
		  case '1' : incluirTarifa(); break;
		  case '2' : alterarTarifa(); break;
		  case '3' : excluirTarifa(); break;
		  case '4' : consultarTarifa(); break;
		  case '5' : listarTarifa(); break;
		  case '6' : return(0); break;
	    }
	} while(1);	
}

/*Funcoes*/
int abrirTarifa(const char tipo[3])
{
     if((fp_tar=fopen("D:\\gestao_estacionamento\\tarifa.dat", tipo))==NULL){
	 	printf("\n Nao ha registros no arquivo !!\n");
      	return(0) ;
     }
     else{
     	return(1);
     }  
	      
}

void incluirTarifa(void)
{    //char *um="0";
     abrirTarifa("ab+");
     fseek(fp_tar,0L, SEEK_END);

     do
     {
	printf("\n Digite a hora ou <FIM> para sair:\n\n");
	gets(reg.hora);

	if ((strcmp(reg.hora,"fim")!=0)&&(strcmp(reg.hora,"FIM")!=0)){
		printf("\n Valor:"); gets(reg.valor);
		reg.status='1';
		if(fwrite(&reg, sizeof(struct registro_tarifa), 1, fp_tar) != 1)
		{
		printf("\n Erro de gravacao!!");
		getch();
		}
		else
		{   printf("\n Gravacao feita com sucesso...\n\n");}
		}
     }while((strcmp(reg.hora,"fim")!=0)&&(strcmp(reg.hora,"FIM")!=0));
     fclose(fp_tar);
}

int busca (void){
   int achou=-1,posicao=0;
   char horap[5];
   abrirTarifa("rb");
   printf("\nDigite a hora a ser procurada:");
   gets(horap);
   rewind(fp_tar);
   while((!feof(fp_tar))&&(achou==-1))
   {
      fread(&reg, sizeof(struct registro_tarifa), 1, fp_tar);
      if (!feof(fp_tar))
	 {if (strcmp(horap, reg.hora)==0)
	    {if (reg.status=='0')
	       {posicao=-2;}
	     achou=1;
	    }
	  else{posicao++;}
	 }
      else{posicao=-1;}
   }
   if (achou==-1)
      {posicao=-1;}
   fclose(fp_tar);
   return(posicao);
}

void consultarTarifa(void){
   int pos;
   pos=busca();
   if(pos==-1)
      {
	 printf("\n Hora inexistente no arquivo!");
	 getch();
      }
      else if(pos==-2)
	      {
		 printf("\n Hora inexistente no arquivo!");
		 getch();
	      }
	      else
		 {
		    abrirTarifa("rb+");
		    fseek(fp_tar,pos*sizeof(struct registro_tarifa),SEEK_SET);
		    fread(&reg, sizeof(struct registro_tarifa), 1, fp_tar);
		    printf("\nHora:%s",reg.hora);
		    printf("\nValor:%s",reg.valor);
		    getch();
		 }
   fclose(fp_tar);
}
void alterarTarifa(void){
   int pos;
   pos=busca();
   if (pos==-1)
      {
	 printf("\nHora inexistente no arquivo");
	 getch();
      }
      else if(pos==-2)
	      {
		 printf("\nHora inexistente no arquivo!");
		 getch();
	      }
	      else
		 {
		    abrirTarifa("rb+");
		    fseek(fp_tar,pos*sizeof(struct registro_tarifa),SEEK_CUR);
		    fread(&reg, sizeof(struct registro_tarifa), 1, fp_tar);
		    printf("\nDeseja alterar o seguinte registro_tarifa:");
		    printf("\nHora:%s",reg.hora);
		    printf("\nValor:%s",reg.valor);
		    
		    printf("\nPressione qualquer tecla para continuar...");
		    printf("\n");
		    getch();
		    printf("\nDigite as informacoes corretas:");
		    printf("\nHora:");
		    gets(reg.hora);
		    printf("\nValor:");
		    gets(reg.valor);
		    reg.status='1';
		    fseek(fp_tar,pos*sizeof(struct registro_tarifa),SEEK_SET);
		    if(fwrite(&reg, sizeof(struct registro_tarifa),1, fp_tar)!=1)
		       {
			  printf("\nErro na gravacao...");
		       }
		       else
			  {
			     printf("\nRegravacao feita com sucesso...");
			     getch();
			  }
		 }
   fclose(fp_tar);
}
void listarTarifa(void) {
   int cont=0;
   int qtd;
   
   qtd = abrirTarifa("rb");

   if (qtd!=0) {   
   	 fseek(fp_tar, 0L, SEEK_SET);
	 fread(&reg, sizeof(struct registro_tarifa),1, fp_tar);
	   do
	   {
	      if (reg.status!='0')
		 {
		    printf("\nHora..: %s",reg.hora);
		    printf("\nValor.: %s",reg.valor);
		    printf("\n");
		    cont++;
		 }
	      fread(&reg, sizeof(struct registro_tarifa),1, fp_tar);
	      }while(!feof(fp_tar));
	   printf("\n#Numero de Registros=%d",cont);
	   printf("\n Pressione qualquer tecla para voltar");
	   getch();
  }
}
void excluirTarifa(void){
   int pos;
   pos=busca();
   if(pos==-1)
      {
	 printf("\nHora inexistente no arquivo");
	 getch();
      }
      else
	 {
	    if(pos==-2)
	       {
		  printf("\nHora excluida do arquivo");
		  getch();
	       }
	       else
		  {
		     abrirTarifa("rb+");
		     fseek(fp_tar, pos*sizeof(struct registro_tarifa), SEEK_SET);
		     fread(&reg, sizeof(struct registro_tarifa), 1, fp_tar);
		     printf("\nHora: %s",reg.hora);
		     printf("\nValor: %s",reg.valor);
		     printf("\nEste registro_tarifa #%d sera excluido",(pos+1));
		     getch();
		     //strcpy(reg.status,"0");
		     reg.status='0';
		     fseek(fp_tar, pos*sizeof(struct registro_tarifa), SEEK_SET);
		     if(fwrite(&reg, sizeof(struct registro_tarifa), 1, fp_tar)!=1)
			{
			   printf("\nErro na gravacao...");
			   getch();
			}
			else
			{
			   printf("\nExclusao feita com sucesso!");
			   getch();
			}
		  }
	 }
   fclose(fp_tar);
}

