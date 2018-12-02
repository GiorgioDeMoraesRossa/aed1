#include <stdio.h>
#include <stdlib.h>

typedef struct No* Apontador;

typedef struct No{
    int chave;
    Apontador pEsq,pDir;
}No;

int count = 0;

void inicializa(Apontador *p){
    *p = NULL;
}

int inserir(int novo, Apontador *p){
    if(*p == NULL){
        *p = malloc(sizeof(No));
        (*p)->chave = novo;
        (*p)->pEsq = NULL;
        (*p)->pDir = NULL;
        return 1;
    }
    else if(novo < (*p)->chave){
        if(inserir(novo,&(*p)->pEsq)){
            if(Balanceamento(p))
                return 0;
            else
                return 1;
        }

    }
    else if(novo > (*p)->chave){
        if(inserir(novo,&(*p)->pDir)){
            if(Balanceamento(p))
                return 0;
            else
                return 1;
        }
        else
            return 0;
    }
    else{
        printf("Registro já existente\n");
        return 0;
    }
}

void Pesquisa(int n,Apontador *p){
    if(*p == NULL){
        printf("Erro: número não esta registrado.\n");
        return;
    }
    if(n < (*p)->chave){
        Pesquisa(n,&(*p)->pEsq);
        return;
    }
    if(n > (*p)->chave){
        Pesquisa(n,&(*p)->pDir);
    }
    else
        printf("Dale, achamo a desgrassa\n");

}

void Antecessor(Apontador q,Apontador *r){ //pega o elemento mais a direita
Apontador aux;

if((*r)->pDir != NULL){
    Antecessor(q,&(*r)->pDir);
    return;
}

q->chave = (*r)->chave;
aux = *r;
*r = (*r)->pEsq;
free(aux);
}

void Retira(int x, Apontador *p){
    if(*p == NULL){
        printf("Erro: numero nao registrado.\n");
        return;
    }
    if(x <(*p)->chave){
        Retira(x,&(*p)->pEsq);
        return;
    }
    if(x > (*p)->chave){
        Retira(x,&(*p)->pDir);
        return;
    }

    Apontador aux;

    if((*p)->pDir == NULL){
        aux = *p;
        *p = (*p)->pEsq;
        free(aux);
        return;
    }

    if((*p)->pEsq != NULL){
        Antecessor(*p,&(*p)->pEsq);
        return;
    }

    aux = *p;
    *p = (*p)->pDir;
    free(aux);
}

int Altura(Apontador pRaiz){

    int iEsq,iDir;
    if (pRaiz == NULL)
        return 0;

    iEsq = Altura(pRaiz->pEsq);
    iDir = Altura(pRaiz->pDir);

    if ( iEsq > iDir )
        return iEsq + 1;
    else
        return iDir + 1;

}

int FB (Apontador pRaiz){

    if (pRaiz == NULL)
        return 0;
    return Altura(pRaiz->pEsq)- Altura(pRaiz->pDir);

}

void RSE(Apontador* ppRaiz){

    No *pAux;
    pAux = (*ppRaiz)->pDir;
    (*ppRaiz)->pDir = pAux->pEsq;
    pAux->pEsq = (*ppRaiz);
    (*ppRaiz) = pAux;
}

void RSD(Apontador* ppRaiz){

    No *pAux;
    pAux = (*ppRaiz)->pEsq;
    (*ppRaiz)->pEsq = pAux->pDir;
    pAux->pDir = (*ppRaiz);
    (*ppRaiz) = pAux;
}

int BalancaEsquerda(Apontador* ppRaiz){

    int fbe = FB ( (*ppRaiz)->pEsq );
    if ( fbe > 0 ){
        RSD(ppRaiz);
        return 1;
    }
    else if (fbe < 0 ){ /* Rotação Dupla Direita */

        RSE( &((*ppRaiz)->pEsq) );
        RSD( ppRaiz ); /* &(*ppRaiz) */
        return 1;
    }

    return 0;
}

int BalancaDireita(Apontador* ppRaiz){

    int fbd = FB( (*ppRaiz)->pDir);
    if ( fbd < 0 ){
        RSE (ppRaiz);
        return 1;
    }
    else if (fbd > 0 ){ /* Rotação Dupla Esquerda */

        RSD( &((*ppRaiz)->pDir) );
        RSE( ppRaiz ); /* &(*ppRaiz) */
        return 1;
    }

    return 0;
}

int Balanceamento(Apontador* ppRaiz){

    int fb = FB(*ppRaiz);
    if ( fb > 1)
        return BalancaEsquerda(ppRaiz);
    else if (fb < -1 )
        return BalancaDireita(ppRaiz);
    else
        return 0;

}

void print2DUtil(Apontador *p, int space){
    if (*p == NULL)
        return;

    // aumenta distancia de acordo com a altura da arvore
    space += count;

    // Printa a direita
    print2DUtil(&(*p)->pDir, space);

    // print meio
    printf("\n");
    for (int i = count; i < space; i++)
        printf(" ");
    printf("%d\n", (*p)->chave);

    // print esquerda
    print2DUtil(&(*p)->pEsq, space);
}

void print2D(Apontador *p){
   // passa space como 0 pra raiz, usar a altura do nó da pra printar subÁrvores
   print2DUtil(p, 0);
}

int main (){
    int x,tmp;
    Apontador p;
    inicializa(&p);
    do{
    printf("0-sair\n1-Inserir\n2-Retirar\n3-Buscar\n4-Listar 2D\n");
    scanf("%d",&x);
    switch(x){
        case 0: break;
        case 1: printf("Digite um inteiro.\n");
                scanf("%d",&tmp);
                tmp = inserir(tmp,&p);
                break;

        case 2: printf("Digite inteiro a ser retirado.\n");
                scanf("%d",&tmp);
                Retira(tmp,&p);
                break;


        case 3: printf("Digite o numero para pesqusa.\n");
                scanf("%d",&tmp);
                Pesquisa(tmp,&p);
                break;

        case 4: count = Altura(p);
                print2D(&p);
                break;

        default:    printf("Opção inválida\n");
                    break;
    }


    }while(x != 0);


return 0;
}
