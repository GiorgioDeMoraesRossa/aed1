#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//alfabética Z-A -- selection
//email -- quick
//nTelefone -- insertion
//alfabética A-Z -- BBsort
//idade -- merge
typedef struct contato{
	char nome[50],email[20];
	int nTelefone,idade;
}ctt;


void *pBuffer;
int *p_int;

/**ctt mergeSort(ctt *esq,ctt *dir){
    if(esq == dir)
        return esq;


}*/


//cada realloc = int esq, dir + 2 int
void quickSort(){
    int *qnts,*i,*j,*esq,*dir,*auxi;
    ctt *mid,*temp,*aux,*aux2;
    qnts = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt);
    *qnts = *qnts + 1;

    printf("VARIAVEIS :qnts: %d\n",*qnts);
    pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int)+ (*qnts+1)*2* sizeof(int) +(*qnts)*2*sizeof(int) + 2* sizeof(ctt)));
    printf("ALOCOU\n");
    p_int = (int*)pBuffer;

    qnts = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt);



    if(*qnts <= 1){ //caso onde o mid e o temp estao no final
        temp = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int)+ 6 * sizeof(int);
        mid = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int)+ 6 * sizeof(int) + sizeof(ctt);
        esq = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int);                      // quando usa realloc os dados ficam XED EDIJTT EDIJTT(2) EDIJTT(6) EDIJTT(10)
        dir = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int) + sizeof(int);
        i = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int) + 4 * sizeof(int);
        j = i + 1;
    }
    else{ //caso onde mid e temp estao no meio, tem que pular alguns deles
        esq = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int) + (((*qnts -2)*4)+2) * sizeof(int) + (*qnts-2)*2*sizeof(ctt);
        dir = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int) + (((*qnts -2)*4)+3) * sizeof(int) + (*qnts-2)*2*sizeof(ctt);
        temp = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int)+ ((*qnts*4)+2) * sizeof(int)  + (*qnts-1)*2*sizeof(ctt);
        mid = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int)+ ((*qnts*4)+2) * sizeof(int)  + (((*qnts-1)*2)+1)*sizeof(ctt);
        i = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int) + *qnts * 4 * sizeof(int) + (*qnts-1) * 2 * sizeof(ctt);
        j = i + 1;
    }



    printf("esq: %d, dir: %d\n",*esq,*dir);
    aux = pBuffer + 2 * sizeof(int) + ((*esq+*dir)/2) * sizeof(ctt);
    *mid = *aux;

    *i = *esq;
    *j= *dir;

   // printf("I e J iniciais: %d, %d\n",*i,*j);

    aux = pBuffer + 2 * sizeof(int) + *i * sizeof(ctt); //ponteiros recebem o i e j;
    aux2 = pBuffer + 2 * sizeof(int) + (*j-1) * sizeof(ctt);

    do{
        printf("LOOP\n");
        printf("--- esq = %d -- dir = %d -- i = %d -- j = %d\n",*esq,*dir,*i,*j);

        printf("pre while1: aux: %s  mid: %s\n",aux->email,mid->email);
        while(strcmp(aux->email,mid->email) < 0){ // os 2 while estao passando do mid procurando, faz com que coisas que ja estao no seu lugar troquem igual...
                //ele chega aqui, quebra com 0, porém o aux fica com o elemento igual ao meio. Ate ai td bem, agr é necessário que quando ache um elemento <mid
                //não troque de lugar, e sim jogue o elemento pro lado esquerdo.
            *i = *i + 1;
            aux = pBuffer + 2 * sizeof(int) + *i * sizeof(ctt);
            printf("ok  1\n");
        }
         printf("pos while 1: aux: %s \n",aux->email);


        printf("pre while2: aux: %s  mid: %s\n",aux2->email,mid->email);
        while(strcmp(mid->email,aux2->email) < 0){
            *j = *j - 1;
            aux2 = pBuffer + 2 * sizeof(int) + (*j-1) * sizeof(ctt);
            printf("ok  2\n");
        }
        printf("pos while 2: aux: %s \n",aux2->email);


        printf("Pre if\n");
        if(*i <= *j){
            printf("swap %s(%d) por %s(%d)\n",aux->email,*i,aux2->email,*j);
            *temp = *aux;
            *aux = *aux2;
            *aux2 = *temp;
            *i = *i + 1;
            aux++;
            *j = *j - 1;
            aux2--;
        }
    }while(*i <= *j);

    printf("--- esq = %d -- dir = %d -- i = %d -- j = %d\n",*esq,*dir,*i,*j);


    printf("TENTA CHAMAR\n");
    if(*esq < *j){
        //XED EDIJTT() EDIJTT() EDIJTT() EDIJTT
        auxi = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int) + (((*qnts -1)*4)+2) * sizeof(int) + (*qnts-1)*2*sizeof(ctt);
        *auxi = *esq;
        auxi = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int) + (((*qnts -1)*4)+3) * sizeof(int) + (*qnts-1)*2*sizeof(ctt);
        *auxi = *j;
        printf("ESQUERDA\n");
        quickSort();
        printf("VOLTA ESQUERDA\n");
        p_int = (int*)pBuffer;
        qnts = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt);
        *qnts = *qnts - 1;
        pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int)+ (*qnts+1)*2* sizeof(int) +*qnts*2*sizeof(int) + 2*sizeof(ctt)));
        p_int = (int*)pBuffer;
        qnts = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt);

        if(*qnts == 1){
            dir = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int) + sizeof(int);
            i = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int) + 4 * sizeof(int);
        }
        else{
            dir = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int) + (((*qnts -2)*4)+3) * sizeof(int) + (*qnts-2)*2*sizeof(ctt);
            i = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int) + *qnts * 4 * sizeof(int) + (*qnts-1) * 2 * sizeof(ctt);
        }
    }

    if(*i < *dir){
        //XED EDIJTT() EDIJTT() EDIJTT() EDIJTT
        auxi = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int) + (((*qnts -1)*4)+2) * sizeof(int) + (*qnts-1)*2*sizeof(ctt);
        *auxi = *i;
        auxi = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int) + (((*qnts -1)*4)+3) * sizeof(int) + (*qnts-1)*2*sizeof(ctt);
        *auxi = *dir;
        printf("DIREITA\n");
        quickSort();
        printf("VOLTA DIREITA\n");
        p_int = (int*)pBuffer;
        qnts = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt);
        *qnts = *qnts - 1;
        pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int) * sizeof(ctt) + sizeof(int)+ (*qnts+1)*2* sizeof(int) +*qnts * 2 *sizeof(int) + 2 * sizeof(ctt)));
        p_int = (int*)pBuffer;
        qnts = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt);

    }
    if(*qnts == 1){
        pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int) * sizeof(ctt)));
        p_int = (int*)pBuffer;
    }

}

void selectionSort(){
    pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int) * sizeof(ctt)+ 2*sizeof(int) + sizeof(ctt)));
	p_int = (int*)pBuffer;
	int *i,*j;
	ctt *max,*aux,*temp;
	temp = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt) + 2*sizeof(int);
    i = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt);
    j = i + 1;
    for(*i=0;*i < *p_int - 1; *i = *i+1){
        max =  pBuffer + 2 * sizeof(int) + *i * sizeof(ctt);
        for(*j=*i+1; *j < *p_int;*j = *j +1){
            aux =  pBuffer + 2 * sizeof(int) + *j * sizeof(ctt);
            if(strcmp(max->nome,aux->nome) < 0){
                *temp = *max;
                *max = *aux;
                *aux = *temp;
            }
        }
        aux = pBuffer + 2 * sizeof(int) + *i * sizeof(ctt);
        *aux = *max;
    }
    pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int) * sizeof(ctt)));
	p_int = (int*)pBuffer;
}

void BBSort(){
    pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int) * sizeof(ctt)+ 2*sizeof(int) + sizeof(ctt)));
	p_int = (int*)pBuffer;
    ctt *temp,*aux;
    int *i,*j;
    temp = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt)+ 2*sizeof(int);
    i = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt);
    j = i + 1;
    for(*i=0;*i < *p_int - 1; *i = *i+1){
        temp->idade = NULL;
        for(*j=0;*j < *p_int -*i-1; *j = *j+1){
            aux = pBuffer + 2 * sizeof(int) + *j * sizeof(ctt);
            if(strcmp(aux->nome,(aux+1)->nome) > 0 ){
                *temp = *aux;
                *aux = *(aux+1);
                *(aux+1) = *temp;
            }
        }
        if(temp->idade == NULL){
            break;
        }
    }
    pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int) * sizeof(ctt)));
	p_int = (int*)pBuffer;
}

void insertionSort(){
    pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int) * sizeof(ctt)+ 2*sizeof(int) + sizeof(ctt)));
	p_int = (int*)pBuffer;
    ctt *temp,*aux;
    int *i,*j;
    i = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt);
    j = i + 1;
    printf("Pré for\n");
    for(*i = 1;*i < *p_int; *i = *i +1){
        printf("intra for\n");
        *j = *i - 1;
        temp = pBuffer + 2 * sizeof(int) + (*p_int) * sizeof(ctt)+ 2*sizeof(int);
        aux = pBuffer + 2 * sizeof(int) + *i * sizeof(ctt);
        *temp = *aux;
        while(temp->nTelefone < (aux-1)->nTelefone){
            printf("while\n");
            *aux = *(aux-1);
            aux--;
            *j = *j-1;
        }
        *aux = *temp;
        printf("pós while\n");

    }
    printf("pós for\n");
    pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int) * sizeof(ctt)));
	p_int = (int*)pBuffer;
}


void menu(){
    int *aux;
	printf("Escolha uma opcao:\n0 - Sair\n1 - Incluir\n2 - Apagar\n3 - Buscar\n4 - Listar\n");
	aux = pBuffer;
	aux++;
	scanf("%d",aux);
	getchar();
}

void inserir(){
	pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int + 1) * sizeof(ctt)));
	p_int = (int*)pBuffer;
	ctt *novo;
	novo = pBuffer + (2 * sizeof(int) + (*p_int) * sizeof(ctt));
	printf("Digite o nome, email, numero de telefone e idade\n");
	scanf("%[^\n]",novo->nome);
	getchar();
	scanf("%[^\n]",novo->email);
	scanf("%d",&novo->nTelefone);
	//scanf("%d",&novo->idade);
	getchar();
    *p_int = *p_int+1;
}

int apagar(){
    pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int) * sizeof(ctt) + 50*sizeof(char)));
    p_int = (int*)pBuffer;
    char *aux;
    int *i;
    ctt *qmeh;
    aux = pBuffer + (2 * sizeof(int) + (*p_int) * sizeof(ctt));
    printf("Digite o nome da pessoa a ser apagada\n");
    scanf("%[^\n]",aux);
    getchar();
    qmeh = pBuffer + (2 * sizeof(int));
    i = p_int + 1;
    *i = 0;
    while (*i < *p_int){
        if(strcmp(qmeh->nome,aux) == 0){
            *p_int = *p_int - 1;
            ctt *prox;
            prox = qmeh + 1;
            while(qmeh != aux){
                *qmeh = *prox;
                qmeh++;
                prox++;
            }
            pBuffer = realloc(pBuffer, (2 * sizeof(int) + (*p_int) * sizeof(ctt)));
            p_int = (int*)pBuffer;
            printf("Apagado!!\n");
            return 0;

        }
        else{
            qmeh++;
        }
        *i = *i + 1;
    }
    return 1;
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
            printf("Nome: %s\tNumero: %d\n",qmeh->nome,qmeh->nTelefone);
            return 0;
        }
        qmeh++;
        *i = *i +1;
    }
    return 1;
}

void listar(){
    int *i;
    i = p_int + 1;
    printf("Escolha a forma de ordenacao:\n1 - Ordem alfabetica por nome(A-Z)\n2 - Ordem alfabetica por nome(Z-A)\n3 - Ordem alfabetica por email (A-Z)\n4 - Número de telefone\n5 - Idade\n");
    scanf("%d",i);
    switch(*i){
        case 1: BBSort();break;
        case 2: selectionSort();break;

        // realloc inicial = int qnts=0; int esq, dir
        case 3: pBuffer = realloc(pBuffer,(2* sizeof(int)+ *p_int * sizeof(ctt) + sizeof(int) + 2*sizeof(int)));
                p_int = (int*) pBuffer;
                int *aux;
                aux = pBuffer + 2* sizeof(int)+ *p_int * sizeof(ctt);
                *aux = 0;         //seta o contador de chamadas
                aux++;
                *aux = 0; //primeiro a esq
                aux++;
                *aux = *p_int; //primeiro direita
                quickSort();break;
        case 4: insertionSort();break;
   //     case 5:  MergeSort();break;
        default: printf("Opcao invalida\nimprimindo sem ordenacao especifica...\n");break;
    }

    ctt *atual;
    atual = pBuffer + (2* sizeof(int));

    *i = 0;
    while(*i < *p_int){
        printf("%d: Nome: %s\tE-mail: %s\n\tNumero de Telefone: %d\tIdade: %d\n",*i,atual->nome,atual->email,atual->nTelefone,atual->idade);
        *i= *i + 1;
        atual++;
    }
    if(*i == 0 )
        printf("Agenda vazia!\n");
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
		case 2: *(p_int+1) = apagar();
                if(*(p_int+1) != 0){
                    printf("Contato nao encontrado.\n");
                }
                 *(p_int+1) = 2;
                break;
		case 3: *(p_int+1) = buscar();
                if(*(p_int+1) != 0){
                    printf("Contato nao encontrado.\n");
                }
                *(p_int+1) = 3;
                break;
		case 4: listar();break;
	}

}while(*(p_int +1) != 0);

free(pBuffer);
return 0;

}
