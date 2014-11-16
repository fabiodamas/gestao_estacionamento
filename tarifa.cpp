#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct registro {
   char hora[5]; //  char numeracao[5];
   char valor[40]; // char preco[40];
   char status;
   
} reg;

FILE *fp;

/*prototipo das funcoes*/
void incluirTarifa (void);
void consultarTarifa(void);
void excluirTarifa(void);
void alterarTarifa(void);
void abrirTarifa(void);
void listarTarifa(void);

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
       printf("\t# Manutencao de Tarifas                                #\n");
       printf("\t########################################################\n\n\n");
       printf("\n Digite uma das opcoes: \n\n");
       printf("\n <I> - Incluir");
       printf("\n <A> - Alterar");
       printf("\n <E> - Excluir");
       printf("\n <C> - Consultar");
       printf("\n <L> - Listar");
       printf("\n <S> - Sair");
       printf("\n\n\n Opcao:");
       gets(opcao);
       
       
       op=tolower(*opcao);
       
    } 
	while(!strchr("iaeclsh",op));
	
       switch(op){/*D*/
	  case 'i' : incluirTarifa(); break;
	  case 'a' : alterarTarifa(); break;
	  case 'e' : excluirTarifa(); break;
	  case 'c' : consultarTarifa(); break;
	  case 'l' : listarTarifa(); break;
	  case 's' : exit(0);
       }
 }while(1);
}

/*Funcoes*/
void abrirTarifa(const char tipo[3])
{
     if((fp=fopen("D:\\gestao_estacionamento\\tarifa.dat", tipo))==NULL)
     {printf("\n O arquivo nao pode ser aberto!!\n");
      getch();
      exit(1);
     }
}

void incluirTarifa(void)
{    //char *um="0";
     abrirTarifa("ab+");
     fseek(fp,0L, SEEK_END);

     do
     {
	printf("\n Digite a hora ou <FIM> para sair:\n\n");
	gets(reg.hora);

	if ((strcmp(reg.hora,"fim")!=0)&&(strcmp(reg.hora,"FIM")!=0)){
		printf("\n Valor:"); gets(reg.valor);
		reg.status='1';
		if(fwrite(&reg, sizeof(struct registro), 1, fp) != 1)
		{
		printf("\n Erro de gravacao!!");
		getch();
		}
		else
		{   printf("\n Gravacao feita com sucesso...\n\n");}
		}
     }while((strcmp(reg.hora,"fim")!=0)&&(strcmp(reg.hora,"FIM")!=0));
     fclose(fp);
}

int busca (void){
   int achou=-1,posicao=0;
   char horap[5];
   abrirTarifa("rb");
   printf("\nDigite a hora a ser procurada:");
   gets(horap);
   rewind(fp);
   while((!feof(fp))&&(achou==-1))
   {
      fread(&reg, sizeof(struct registro), 1, fp);
      if (!feof(fp))
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
   fclose(fp);
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
		    fseek(fp,pos*sizeof(struct registro),SEEK_SET);
		    fread(&reg, sizeof(struct registro), 1, fp);
		    printf("\nHora:%s",reg.hora);
		    printf("\nValor:%s",reg.valor);
		    getch();
		 }
   fclose(fp);
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
		    fseek(fp,pos*sizeof(struct registro),SEEK_CUR);
		    fread(&reg, sizeof(struct registro), 1, fp);
		    printf("\nDeseja alterar o seguinte registro:");
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
		    fseek(fp,pos*sizeof(struct registro),SEEK_SET);
		    if(fwrite(&reg, sizeof(struct registro),1, fp)!=1)
		       {
			  printf("\nErro na gravacao...");
		       }
		       else
			  {
			     printf("\nRegravacao feita com sucesso...");
			     getch();
			  }
		 }
   fclose(fp);
}
void listarTarifa(void) {
   int cont=0;

   abrirTarifa("rb");
   fseek(fp, 0L, SEEK_SET);
   fread(&reg, sizeof(struct registro),1, fp);
   do
   {
      if (reg.status!='0')
	 {
	    printf("\nHora..: %s",reg.hora);
	    printf("\nValor.: %s",reg.valor);
	    printf("\n");
	    cont++;
	 }
      fread(&reg, sizeof(struct registro),1, fp);
      }while(!feof(fp));
   printf("\n#Numero de Registros=%d",cont);
   printf("\n Pressione qualquer tecla para voltar");
   getch();
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
		     fseek(fp, pos*sizeof(struct registro), SEEK_SET);
		     fread(&reg, sizeof(struct registro), 1, fp);
		     printf("\nHora: %s",reg.hora);
		     printf("\nValor: %s",reg.valor);
		     printf("\nEste Registro #%d sera excluido",(pos+1));
		     getch();
		     //strcpy(reg.status,"0");
		     reg.status='0';
		     fseek(fp, pos*sizeof(struct registro), SEEK_SET);
		     if(fwrite(&reg, sizeof(struct registro), 1, fp)!=1)
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
   fclose(fp);
}

