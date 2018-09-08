#include <stdio.h>

typedef struct contato{
	char *nome[50];
	int *num;
}ctt;


void *pBuffer;
int *p_int;

void menu(){
    int *aux;
	printf("Escolha uma opção:\n0 - Sair\n1 - Incluir\n2 - Apagar\n3 - Buscar\n4 - Listar\n");
	aux = pBuffer;
	aux++;
	scanf("%d",aux);
	//int *x = (*int) malloc(sizeof(int));
}

void inserir(){
	pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int + 1) * sizeof(ctt)));
	void *aux;
	aux = pBuffer;
	aux = aux + (2 * sizeof(int) + (*p_int) * sizeof(ctt));
	printf("Digite o nome e o número da pessoa\n");
	/*while(scanf("%c",aux) && *aux != ' '){
		pBuffer = realloc(pBuffer, (2 * sizeof(int) + ((int)pBuffer[0] + 1) * sizeof(ctt)));
	}*/
	scanf("[&\n]%s",(char*)aux);//relloc *char cabe uma string? ler letra por letra? 1001 reallocs -> *char[50] = **char
	scanf("%d",(int*)aux);
	//p_int =(int*) pBuffer;
	*p_int = *p_int+1;
}


int main (){
    int *p_int;
	pBuffer = malloc(2 * sizeof(int));
	p_int = (int*)pBuffer;
	*p_int = 0;

do{
	menu();
	switch(*(p_int +1)){
		case 0: break;
		case 1: inserir();break;
		case 2: apagar();break;
		case 3: buscar();break;
		case 4: listar();break;
	}

}while(*(p_int +1) != 0);

}
