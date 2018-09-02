#include <stdio.h>

typedef struct contato{
	char *nome[50];
	int *num;
}ctt;


void *pBuffer;

void menu(){
	printf("Escolha uma opção:\n0 - Sair\n1 - Incluir\n2 - Apagar\n3 - Buscar\n4 - Listar\n");
	scanf("%d",pBuffer[1]);
	//int *x = (*int) malloc(sizeof(int));
}

void inserir(){
	pBuffer = realloc(pBuffer, (2 * sizeof(int) + ((int)pBuffer[0] + 1) * sizeof(ctt)));
	void *aux;
	aux = pBuffer[2 * sizeof(int) + (int)pBuffer[0] * sizeof(ctt)];
	printf("Digite o nome e o número da pessoa\n");
	/*while(scanf("%c",aux) && *aux != ' '){
		pBuffer = realloc(pBuffer, (2 * sizeof(int) + ((int)pBuffer[0] + 1) * sizeof(ctt)));
	}*/
	scanf("[&\n]%s",aux);//relloc *char cabe uma string? ler letra por letra? 1001 reallocs -> *char[50] = **char
	scanf("%d",aux);
	*pBuffer = *pBuffer + 1; 
}


int main (){
	pBuffer = malloc(2 * sizeof(int));
	*pBuffer = 0;

do{
	menu();
	switch((int)pBuffer[1]){
		case 0: break;
		case 1: incluir();break;
		case 2: apagar();break;
		case 3: buscar();break;
		case 4: listar();break;
	}

}while(*x != 0);
	
}