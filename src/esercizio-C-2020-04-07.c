/*
 ============================================================================
 Name        : Rand_Stringhe.c
 Author      : Emiliano Rossi
 Version     :
 Copyright   : 
 Description :
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_MAX 500
#define NEW_LINE 15

int l=0;
char s[]={' ','\n','\0'};
//eventualmente anche 
//char s[] =" ";

//genero un array di stringhe, ognua determinata dai caratteri separatori ' ' e '\n' (o evenrualmente solo ' ')
char ** tokenizza(char * str){
	char ** b_ar_str;
	char * c = strtok(str,s);
	b_ar_str=malloc(sizeof(char *));
	if(b_ar_str == NULL){
			perror("malloc");
			exit (-1);
		}
	while(c!= NULL){
		l++;
		realloc(b_ar_str,l*sizeof(char *) );
		b_ar_str[l-1]=c;
		c=strtok(NULL,s);
	}
  // l rapprensenta la lunghezza dell'array
	return b_ar_str;
}


//queste due funzioni vengono implementate per evitare un possibile loop infinito (non genero mai il numero casuale ultimo)
//probablilità di generare un numero casuale "nuovo" cala al diminuire dell'intervallo di generazione.

//1. Controllo se il numero è già stato chiamato
int contr_a (int ind, int * chiamati, size_t size){
	for(int i =0;i<size;i++)
		if(ind == *(chiamati+i))
			return 1; //torna 1 se già è stato usato l'indice
	return 0;
}

//2. Genero numero sicurmante diverso da tutti quelli precedenti
int genNum_controllato(int ind, int * chiamati,size_t * size){
	if(contr_a(ind,chiamati, *size)){
		ind++;
		if(ind>=l) // evito overflow
			ind =0;
		ind =genNum_controllato(ind,chiamati,size);
	} else{
		*(chiamati+*size)=ind;
		*(size)=*size+1;
	}
	return ind;
}

//stampa casualmente l'array di stringhe
void randomPrint(char ** str){
	int wd=0;
	int * chiamati = malloc(l*sizeof(int));
	if(chiamati == NULL){
		perror("malloc");
		exit (-1);
	}
	int ind;
	size_t size=0;
	if(l!=1){
		do{
			ind =  genNum_controllato(rand() % (l), chiamati,&size);
			//if(str[ind]!= NULL)
			printf("%s ",str[ind]);
			wd++;
			if (wd > NEW_LINE){
				wd=0;
				printf("\n");
			}

		}while(size!=l);
	} else{
	printf("%s",str[0]);
	}
	printf("\n");
  free(chiamati);

}

//leggo il treno di caratteri e posiziono alla fine '/0'
void lettura (char * str){
	char c;
	int i=0;
	while((c=getchar())!= EOF  && i<SIZE_MAX){
	 if(c != '\0'){
		 *(str+i)=c;
	 	 i++;
	 	 }
	}
	*(str+i+1)='\0';
}


int main(int argc, char ** argv) {
  printf("Inserire la striga, massimo %d caratteri\n",SIZE_MAX);

  char  str[SIZE_MAX+1];
  lettura(str);

  char ** parole =tokenizza(str);
  randomPrint(parole);
  free(parole);

  return EXIT_SUCCESS;

}

