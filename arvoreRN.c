#include <stdio.h>
#include <stdlib.h>

typedef struct No* Apontador;

typedef struct No{
    int chave,color; // 0 -> preto 1-> vermelho
    Apontador pEsq,pDir,parent;
}No;

int count = 0;

void insert_case1(Apontador n);
void insert_case2(Apontador n);
void insert_case3(Apontador n);
void insert_case4(Apontador n);
void insert_case5(Apontador n);

void inicializa(Apontador *p){
    *p = NULL;
}

Apontador inserir(int novo, Apontador *p, Apontador pai){ //falta dar um pai pra esses bixo
    if(*p == NULL){
        *p = malloc(sizeof(No));
        (*p)->chave = novo;
        (*p)->pEsq = NULL;
        (*p)->pDir = NULL;
        (*p)->parent = pai;
        return *p;
    }

    else if(novo < (*p)->chave){
        pai = *p;
        inserir(novo,&(*p)->pEsq,pai);
        return *p;
    }

    else if(novo > (*p)->chave){
        pai = *p;
        inserir(novo,&(*p)->pDir,pai);
        return *p;
    }
    else{
        printf("Registro já existente\n");
        return NULL;
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

void RSE(Apontador ppRaiz){

    No *pAux;
    pAux = ppRaiz->pDir;
    ppRaiz->pDir = pAux->pEsq;
    pAux->pEsq = ppRaiz;
    ppRaiz = pAux;
}

void RSD(Apontador ppRaiz){

    No *pAux;
    pAux = ppRaiz->pEsq;
    ppRaiz->pEsq = pAux->pDir;
    pAux->pDir = ppRaiz;
    ppRaiz = pAux;
}

Apontador grandparent(Apontador n){

    if ((n != NULL) && (n->parent != NULL))
        return n->parent->parent;
    else
        return NULL;

}

Apontador uncle(Apontador n){

    Apontador g = grandparent(n);

    if (g == NULL)
        return NULL; // No grandparent means no uncle
    if (n->parent == g->pEsq)
        return g->pDir;
    else
        return g->pEsq;
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

void insert_case1(Apontador n){
    printf("Insert case 1\n");
    if (n->parent == NULL)
        n->color = 0;
    else
        insert_case2(n);

}

void insert_case2(Apontador n){
    printf("Insert case 2\n");
    if (n->parent->color == 0)
        return; /* Tree is still valid */
    else
        insert_case3(n);
}

void insert_case3(Apontador n){
    printf("Insert case 3\n");
    Apontador u = uncle(n), g;

    if ((u != NULL) && (u->color == 1)) {
        n->parent->color = 0;
        u->color = 0;
        g = grandparent(n);
        g->color = 1;
        insert_case1(g);
    } else {
        insert_case4(n);
    }
}

void insert_case4(Apontador n){
    printf("Insert case 4\n");
    Apontador g = grandparent(n);
    if ((n == n->parent->pDir) && (n->parent == g->pEsq)) {
        RSE(n->parent);
        n = n->pEsq;
    } else if ((n == n->parent->pEsq) && (n->parent == g->pDir)) {
        RSD(n->parent);
        n = n->pDir;
    }
    insert_case5(n);
}

void insert_case5(Apontador n){
    printf("Insert case 5\n");
    Apontador g = grandparent(n);
    n->parent->color = 0;
    g->color = 1;
    if ((n == n->parent->pEsq) && (n->parent == g->pEsq)) {
        RSD(g);
    } else {
        /*
        * Here, (n == n->parent->pDir) && (n->parent == g->pDir).
        */
        RSE(g);
    }
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
                insert_case1(inserir(tmp,&p,NULL));
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
