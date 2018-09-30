#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct contato{
	char nome[50];
	int *num;
}ctt;


void *pBuffer;
int *p_int;

void menu(){
    int *aux;
	printf("Escolha uma opçao:\n0 - Sair\n1 - Incluir\n2 - Apagar\n3 - Buscar\n4 - Listar\n");
	aux = pBuffer;
	aux++;
	scanf("%d",aux);
	getchar();
}

void inserir(){
	pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int + 1) * sizeof(ctt)));
	p_int = (int*)pBuffer;
	int *i;
	void *aux;
	aux = pBuffer;
	aux = aux + (2 * sizeof(int) + (*p_int) * sizeof(ctt));
    i = p_int + 1;
    *i = 0;
	printf("Digite o nome e o numero da pessoa\n");
	/*while(scanf("%c",aux) && *aux != ' '){
		pBuffer = realloc(pBuffer, (2 * sizeof(int) + ((int)pBuffer[0] + 1) * sizeof(ctt)));
	}*/
	scanf("%[^\n]",(char*)aux);//relloc *char cabe uma string? ler letra por letra? 1001 reallocs -> *char[50] = **char
	getchar();
	while(*((char*)aux) != '\0'){
        (char*)aux++;
        *i = *i + 1;
        printf("Caminhando string\n");
	}
    while(*i <= 51){
        *i = *i + 1;
        (char*)aux++;
    }

	//(char*)aux--;
	scanf("%d",(int*)aux);
	getchar();
	*p_int = *p_int+1;
}

void apagar(){
    pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int) * sizeof(ctt) + 50*sizeof(char)));
    p_int = (int*)pBuffer;
    char *aux;
    int *i;
    ctt *qmeh;
    aux = pBuffer + (2 * sizeof(int) + (*p_int) * sizeof(ctt));
    printf("Digite o nome da pessoa a ser apagada\n");
    scanf("[&\n]%s",aux);
    getchar();
    qmeh = pBuffer + (2 * sizeof(int));
    i = p_int + 1;
    *i = 0;
    while (*i < *p_int){
        printf("While\n");
        if(strcmp(qmeh->nome,aux) == 0){
            *p_int = *p_int - 1;
            ctt *prox;
            prox = qmeh + 1;
            printf("%p\t%p\n",qmeh,aux);
            while(qmeh != aux){
                *qmeh = *prox;
                qmeh++;
                prox++;
            }
            pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int) * sizeof(ctt)));
            p_int = (int*)pBuffer;
            printf("Apagado!!\n");

        }
        else{
            qmeh++;
        }
        *i = *i + 1;
    }
    *i = 2;
}

int buscar(){
    char *busca;
    int *i;
    busca = pBuffer + (2 * sizeof(int) + (*p_int) * sizeof(ctt));
    printf("Digite o nome que deseja procurar\n");
    scanf("%[^\n]", busca);
    getchar();
    ctt *qmeh;
    qmeh = pBuffer + (2* sizeof(int));
    i = p_int + 1;
    *i = 0;
    while(*i < *p_int){
        if(strcmp(qmeh->nome,busca) == 0){
            printf("Nome: %s\tNumero: %d\n",qmeh->nome,qmeh->num);
            return 0;
        }
        qmeh++;
        *i = *i +1;
    }
    *i = 3;
    return 1;
}

void listar(){
    ctt *atual;
    int *i;
    atual = pBuffer + (2* sizeof(int));
    i = p_int + 1;
    *i = 0;
    while(*i < *p_int){
        printf("%d: Nome: %s\tNumero: %d\n",*i,atual->nome,atual->num);
        *i= *i + 1;
        atual++;
    }

    *i = 4;
}

int main (){
	pBuffer = malloc(2 * sizeof(int));
	p_int = (int*)pBuffer;
	*p_int = 0;

do{
	menu();
	switch(*(p_int +1)){
		case 0: break;
		case 1: inserir();break;
		case 2: apagar();break;
		case 3: *(p_int+1) = buscar();
                if(*(p_int+1) != 0){
                    printf("Contato nao encontrado.\n");
                }
                *(p_int+1) = 3;
                break;
		case 4: listar();break;
	}

}while(*(p_int +1) != 0);

return 0;

}
