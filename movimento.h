#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
 
struct registro_mov {
   char placa[20]; 
   char dataentrada[20]; 
   char horaentrada[20]; 
   char datasaida[20]; 
   char horasaida[20]; 
   char valor[15]; 
   char fechado;
   char status;
   
} registro_mov;

FILE *fp_mov;

/*prototipo das funcoes*/
void entradaVeiculo (void);
void saidaVeiculo (void);
int abrirMovimento(void);
void listarMovimento(void);


/*Funcoes*/
// void abrirMovimento(const char tipo[3])
int abrirMovimento(const char tipo[3])
{
     if((fp_mov=fopen("D:\\gestao_estacionamento\\movimento.dat", tipo))==NULL){
	 	printf("\n Nao ha registros no arquivo!!\n");
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
     fseek(fp_mov,0L, SEEK_END);

     do
     {
	printf("\n Digite a placa (Sem o hifen) ou <FIM> para sair:\n\n");
	gets(registro_mov.placa);

	if ((strcmp(registro_mov.placa,"fim")!=0)&&(strcmp(registro_mov.placa,"FIM")!=0)){

		strcpy(registro_mov.datasaida, myStr.c_str());
		strcpy(registro_mov.horasaida, myStr.c_str());
		strcpy(registro_mov.valor, myStr.c_str());
		
		printf("\n Data de Entrada:"); 
		gets(registro_mov.dataentrada);

		printf("\n Hora de Entrada:"); 
		gets(registro_mov.horaentrada);
		
	    registro_mov.fechado='0';		    
		
		registro_mov.status='1';
	    registro_mov.fechado='0';		    
	    
		if(fwrite(&registro_mov, sizeof(struct registro_mov), 1, fp_mov) != 1)
		{
		printf("\n Erro de gravacao!!");
		getch();
		}
		else
		{   printf("\n Gravacao feita com sucesso...\n\n");}
		}
     }while((strcmp(registro_mov.placa,"fim")!=0)&&(strcmp(registro_mov.placa,"FIM")!=0));
     fclose(fp_mov);
}

void listarMovimento(void) {
   int cont=0;
   int qtd;

   qtd = abrirMovimento("rb");
   
   if (qtd!=0) {
	   fseek(fp_mov, 0L, SEEK_SET);
	   fread(&registro_mov, sizeof(struct registro_mov),1, fp_mov);
	   do
	   {
	      if (registro_mov.status!='0')
		 {
		    printf("\nPlaca de Entrada: %s",registro_mov.placa);
		    printf("\nData de Entrada.: %s",registro_mov.dataentrada);
		    printf("\nHora de Entrada.: %s",registro_mov.horaentrada);
		    printf("\nData de Saida...: %s",registro_mov.datasaida);
		    printf("\nHora de Saida...: %s",registro_mov.horasaida);
		    printf("\nValor...........: %s",registro_mov.valor);
		    
	        if (registro_mov.fechado !='0') {
	        	printf("\nFechado.........: Sim");
	        }
		    else{
	        	printf("\nFechado.........: Nao");
		    }  
		    
		    printf("\n");
		    cont++;
		 }
	      fread(&registro_mov, sizeof(struct registro_mov),1, fp_mov);
	      }while(!feof(fp_mov));
	   printf("\n#Numero de registro_movs=%d",cont);
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
   rewind(fp_mov);
   while((!feof(fp_mov))&&(achou==-1))
   {
      fread(&registro_mov, sizeof(struct registro_mov), 1, fp_mov);
      if (!feof(fp_mov))
	 {if (strcmp(placap, registro_mov.placa)==0)
	    {if (registro_mov.status=='0')
	       {posicao=-2;}
	     achou=1;
	    }
	  else{posicao++;}
	 }
      else{posicao=-1;}
   }
   if (achou==-1)
      {posicao=-1;}
   fclose(fp_mov);
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
		    fseek(fp_mov,pos*sizeof(struct registro_mov),SEEK_CUR);
		    fread(&registro_mov, sizeof(struct registro_mov), 1, fp_mov);
		    printf("\nDados da entrada:");
		    printf("\nPlaca..........:%s",registro_mov.placa);
		    printf("\nData da entrada:%s",registro_mov.dataentrada);
		    printf("\nHora da entrada:%s",registro_mov.horaentrada);
		    printf("\nPressione qualquer tecla para continuar...");
		    printf("\n");
		    printf("\n");
		    getch();
		    
			strcpy(registro_mov.placa,       registro_mov.placa);
			strcpy(registro_mov.dataentrada, registro_mov.dataentrada);
			strcpy(registro_mov.horaentrada, registro_mov.horaentrada);
		    
					    
		    printf("\nInforme os dados da saida:");		    
		    printf("\nData de Saida: ");
		    gets(registro_mov.datasaida);
		    
		    printf("\nHora da Saida: ");
		    gets(registro_mov.horasaida);		    
		    
  		    registro_mov.fechado='1';		    
		    registro_mov.status='1';
		    
		    fseek(fp_mov,pos*sizeof(struct registro_mov),SEEK_SET);
		    if(fwrite(&registro_mov, sizeof(struct registro_mov),1, fp_mov)!=1)
		       {
			  printf("\nErro na gravacao...");
		       }
		       else
			  {
			     printf("\n Saida realizada com sucesso...");
			     getch();
			  }
		 }
   fclose(fp_mov);
}














