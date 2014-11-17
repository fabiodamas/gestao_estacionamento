#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>

struct registro {
   char placa[20]; 
   char dataentrada[20]; 
   char horaentrada[20]; 
   char datasaida[20]; 
   char horasaida[20]; 
   char valor[15]; 
   char fechado;
   char status;
   
} reg;

FILE *fp;

/*prototipo das funcoes*/
void entradaVeiculo (void);
void saidaVeiculo (void);
void abrirMovimento(void);
void listarMovimento(void);

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
       printf("\t# Entrada de Veiculo                                   #\n");
       printf("\t########################################################\n\n\n");
       printf("\n Digite uma das opcoes: \n\n");
       printf("\n <I> - Entrada de Veiculo");
       printf("\n <d> - Saida de Veiculo");
       printf("\n <L> - Listar");
       printf("\n <S> - Sair");
       printf("\n\n\n Opcao:");
       gets(opcao);
       
       
       op=tolower(*opcao);
       
    } 
	while(!strchr("idls",op));
	
       switch(op){/*D*/
	  case 'i' : entradaVeiculo(); break;
	  case 'd' : saidaVeiculo(); break;
	  case 'l' : listarMovimento(); break;
	  case 's' : exit(0);
       }
 }while(1);
}

/*Funcoes*/
// void abrirMovimento(const char tipo[3])
int abrirMovimento(const char tipo[3])
{
     if((fp=fopen("D:\\gestao_estacionamento\\movimento.dat", tipo))==NULL){
	 	printf("\n O arquivo nao pode ser aberto!!\n");
      	return(0) ;
     }
     else{
     	return(1);
     }     
}

void entradaVeiculo(void)
{    //char *um="0";
	 std::string myStr = "";
	
     abrirMovimento("ab+");
     fseek(fp,0L, SEEK_END);

     do
     {
	printf("\n Digite a placa (Sem o hifen) ou <FIM> para sair:\n\n");
	gets(reg.placa);

	if ((strcmp(reg.placa,"fim")!=0)&&(strcmp(reg.placa,"FIM")!=0)){

		strcpy(reg.datasaida, myStr.c_str());
		strcpy(reg.horasaida, myStr.c_str());
		strcpy(reg.valor, myStr.c_str());
		
		printf("\n Data de Entrada:"); 
		gets(reg.dataentrada);

		printf("\n Hora de Entrada:"); 
		gets(reg.horaentrada);
		
	    reg.fechado='0';		    
		
		reg.status='1';
	    reg.fechado='0';		    
	    
		if(fwrite(&reg, sizeof(struct registro), 1, fp) != 1)
		{
		printf("\n Erro de gravacao!!");
		getch();
		}
		else
		{   printf("\n Gravacao feita com sucesso...\n\n");}
		}
     }while((strcmp(reg.placa,"fim")!=0)&&(strcmp(reg.placa,"FIM")!=0));
     fclose(fp);
}

void listarMovimento(void) {
   int cont=0;
   int qtd;

   qtd = abrirMovimento("rb");
   
   if (qtd!=0) {
	   fseek(fp, 0L, SEEK_SET);
	   fread(&reg, sizeof(struct registro),1, fp);
	   do
	   {
	      if (reg.status!='0')
		 {
		    printf("\nPlaca de Entrada: %s",reg.placa);
		    printf("\nData de Entrada.: %s",reg.dataentrada);
		    printf("\nHora de Entrada.: %s",reg.horaentrada);
		    printf("\nData de Saida...: %s",reg.datasaida);
		    printf("\nHora de Saida...: %s",reg.horasaida);
		    printf("\nValor...........: %s",reg.valor);
		    
	        if (reg.fechado !='0') {
	        	printf("\nFechado.........: Sim");
	        }
		    else{
	        	printf("\nFechado.........: Nao");
		    }  
		    
		    printf("\n");
		    cont++;
		 }
	      fread(&reg, sizeof(struct registro),1, fp);
	      }while(!feof(fp));
	   printf("\n#Numero de Registros=%d",cont);
	   printf("\n Pressione qualquer tecla para voltar");
	   getch();   	
   }
   
}


int buscaVeiculo (void){
   int achou=-1,posicao=0;
   char placap[20];
   abrirMovimento("rb");
   printf("\nDigite a placa (sem o hifen):");
   gets(placap);
   rewind(fp);
   while((!feof(fp))&&(achou==-1))
   {
      fread(&reg, sizeof(struct registro), 1, fp);
      if (!feof(fp))
	 {if (strcmp(placap, reg.placa)==0)
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


void saidaVeiculo(void){
   int pos;
   pos=buscaVeiculo();
   if (pos==-1)
      {
	 printf("\nEntrada inexistente no arquivo");
	 getch();
      }
      else if(pos==-2)
	      {
		 printf("\nEntrada inexistente no arquivo!");
		 getch();
	      }
	      else
		 {
		    abrirMovimento("rb+");
		    fseek(fp,pos*sizeof(struct registro),SEEK_CUR);
		    fread(&reg, sizeof(struct registro), 1, fp);
		    printf("\nDados da entrada:");
		    printf("\nPlaca..........:%s",reg.placa);
		    printf("\nData da entrada:%s",reg.dataentrada);
		    printf("\nHora da entrada:%s",reg.horaentrada);
		    printf("\nPressione qualquer tecla para continuar...");
		    printf("\n");
		    printf("\n");
		    getch();
		    
			strcpy(reg.placa,       reg.placa);
			strcpy(reg.dataentrada, reg.dataentrada);
			strcpy(reg.horaentrada, reg.horaentrada);
		    
					    
		    printf("\nInforme os dados da saida:");		    
		    printf("\nData de Saida: ");
		    gets(reg.datasaida);
		    
		    printf("\nHora da Saida: ");
		    gets(reg.horasaida);		    
		    
  		    reg.fechado='1';		    
		    reg.status='1';
		    
		    fseek(fp,pos*sizeof(struct registro),SEEK_SET);
		    if(fwrite(&reg, sizeof(struct registro),1, fp)!=1)
		       {
			  printf("\nErro na gravacao...");
		       }
		       else
			  {
			     printf("\n Saida realizada com sucesso...");
			     getch();
			  }
		 }
   fclose(fp);
}














