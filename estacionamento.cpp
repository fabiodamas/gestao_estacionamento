#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
struct registro {
   char marca[40];
   char numeracao[5];
   char tipo[20];
   char cor[20];
   char preco[40];
   char status;
   } reg;
FILE *fp;
/*prototipo das funcoes*/
void incluir (void);
void consultar(void);
void excluir(void);
void alterar(void);
void abrir(void);
void listar(void);
void help(void);

int main(void)
{
 char opcao[2], op;
 do{
    do{
       
       printf("\n\n\n\n\n\n\n");
       printf("\t########################################################\n");
       printf("\t#        					       #\n");
       printf("\t#     Programa de Cadastro de Sapatos Versao 1.13      #\n");
       printf("\t#                                                      #\n");
       printf("\t########################################################\n\n\n");
       printf("\n Digite uma das op‡oes\n\n");
       printf("\n <I> - Incluir");
       printf("\n <A> - Alterar");
       printf("\n <E> - Excluir");
       printf("\n <C> - Consultar");
       printf("\n <L> - Listar");
       printf("\n <H> - Ajuda");
       printf("\n <S> - Sair");
       printf("\n\n\n Op‡ao:");
       gets(opcao);
       op=tolower(*opcao);
    } while(!strchr("iaeclsh",op));
       switch(op){/*D*/
	  case 'i' : incluir(); break;
	  case 'a' : alterar(); break;
	  case 'e' : excluir(); break;
	  case 'c' : consultar(); break;
	  case 'l' : listar(); break;
	  case 's' : exit(0);
	  case 'h' : help(); break;
       }
 }while(1);
}
		    /*Fun‡oes*/
void help(void) {
	
	printf("\a\n\n\n\n\n\n\n");
	printf("\t########################################################\n");
	printf("\t# Programa feito por.: KrowniX                         #\n");
	printf("\t# Qualquer d£vida/erro entre em contato krownix@lab.br #\n");
	printf("\t########################################################\n\n\n");
	printf("\t\t\tTecle <ENTER> para voltar");
	getch();
}
void abrir(char tipo[3])
{
     if((fp=fopen("C:\\tmp\\sapato.dat", tipo))==NULL)
     {printf("\n O arquivo nao pode ser aberto!!\n");
      getch();
      exit(1);
     }
}
void incluir(void)
{    //char *um="0";
     abrir("ab+");
     fseek(fp,0L, SEEK_END);

     do
     {
	printf("\n Digite o marca ou <FIM> para sair:\n\n");
	gets(reg.marca);

	if ((strcmp(reg.marca,"fim")!=0)&&(strcmp(reg.marca,"FIM")!=0)){
		printf("\n Numero:"); gets(reg.numeracao);
		printf("\n Tipo:"); gets(reg.tipo);
		printf("\n Cor:"); gets(reg.cor);
		printf("\n Pre‡o:"); gets(reg.preco);
		reg.status='1';
		if(fwrite(&reg, sizeof(struct registro), 1, fp) != 1)
		{
		printf("\n Erro de grava‡Æo!!");
		getch();
		}
		else
		{   printf("\n Grava‡Æo feita com sucesso...\n\n");}
		}
     }while((strcmp(reg.marca,"fim")!=0)&&(strcmp(reg.marca,"FIM")!=0));
     fclose(fp);
}
int busca (void){
   int achou=-1,posicao=0;
   char marcap[40];
   abrir("rb");
   printf("\nDigite o marca a ser procurada:");
   gets(marcap);
   rewind(fp);
   while((!feof(fp))&&(achou==-1))
   {
      fread(&reg, sizeof(struct registro), 1, fp);
      if (!feof(fp))
	 {if (strcmp(marcap, reg.marca)==0)
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
void consultar(void){
   int pos;
   pos=busca();
   if(pos==-1)
      {
	 printf("\nSapato inexistente no arquivo!");
	 getch();
      }
      else if(pos==-2)
	      {
		 printf("\nSapato inexistente no arquivo!");
		 getch();
	      }
	      else
		 {
		    abrir("rb+");
		    fseek(fp,pos*sizeof(struct registro),SEEK_SET);
		    fread(&reg, sizeof(struct registro), 1, fp);
		    printf("\nMarca:%s",reg.marca);
		    printf("\nNumero:%s",reg.numeracao);
		    printf("\nTipo:%s",reg.tipo);
		    printf("\nCor:%s",reg.cor);
		    printf("\nPre‡o:%s",reg.preco);
		    getch();
		 }
   fclose(fp);
}
void alterar(void){
   int pos;
   pos=busca();
   if (pos==-1)
      {
	 printf("\nSapato inexistente no arquivo");
	 getch();
      }
      else if(pos==-2)
	      {
		 printf("\nSapato inexistente no arquivo!");
		 getch();
	      }
	      else
		 {
		    abrir("rb+");
		    fseek(fp,pos*sizeof(struct registro),SEEK_CUR);
		    fread(&reg, sizeof(struct registro), 1, fp);
		    printf("\nDeseja alterar o seguinte registro...");
		    printf("\nSapato:%s",reg.marca);
		    printf("\nNumero:%s",reg.numeracao);
		    printf("\nTipo:%s",reg.tipo);
		    printf("\nCor:%s",reg.cor);
		    printf("\nPre‡o:%s",reg.preco);
		    getch();
		    printf("\nDigite as informacoes corretas:");
		    printf("\nSapato:");
		    gets(reg.marca);
		    printf("\nNumero:");
		    gets(reg.numeracao);
		    printf("\nTipo:");
		    gets(reg.tipo);
		    printf("\nCor:");
		    gets(reg.cor);
		    printf("\nPre‡o:");
		    gets(reg.preco);
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
void listar(void) {
   int cont=0;

   abrir("rb");
   fseek(fp, 0L, SEEK_SET);
   fread(&reg, sizeof(struct registro),1, fp);
   do
   {
      if (reg.status!='0')
	 {
	    printf("\nMarca: %s",reg.marca);
	    printf("\nNumero: %s",reg.numeracao);
	    printf("\nTipo: %s",reg.tipo);
	    printf("\nCor: %s",reg.cor);
	    printf("\nPre‡o: %s",reg.preco);
	    cont++;
	 }
      fread(&reg, sizeof(struct registro),1, fp);
      }while(!feof(fp));
   printf("\n#Numero de Registros=%d",cont);
   getch();
}
void excluir(void){
   int pos;
   pos=busca();
   if(pos==-1)
      {
	 printf("\nSapato inexistente no arquivo");
	 getch();
      }
      else
	 {
	    if(pos==-2)
	       {
		  printf("\nSapato excluido do arquivo");
		  getch();
	       }
	       else
		  {
		     abrir("rb+");
		     fseek(fp, pos*sizeof(struct registro), SEEK_SET);
		     fread(&reg, sizeof(struct registro), 1, fp);
		     printf("\nMarca: %s",reg.marca);
		     printf("\nNumero: %s",reg.numeracao);
		     printf("\nTipo: %s",reg.tipo);
		     printf("\nCor: %s",reg.cor);
		     printf("\nPre‡o: %s",reg.preco);
		     printf("\nEste Registro #%d sera excluido",(pos+1));
		     getch();
		     //strcpy(reg.status,"0");
		     reg.status='0';
		     fseek(fp, pos*sizeof(struct registro), SEEK_SET);
		     if(fwrite(&reg, sizeof(struct registro), 1, fp)!=1)
			{
			   printf("\nErro na grava‡ao...");
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
