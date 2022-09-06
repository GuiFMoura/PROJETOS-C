#include <stdio.h>

typedef struct nodo{
    int valor;
    struct nodo *esq;
    struct nodo *dir;
} Nodo;

Nodo* criarNodo(int v){
    Nodo *p = (Nodo*)malloc(sizeof(Nodo));
    p->valor = v;
    p->esq = NULL;
    p->dir = NULL;
    return p;
}

void mostraArvore(Nodo *p, int nivel){
    int i;
    if(p == NULL){
        for(i = 0; i < nivel; i++)
            printf("  ");
        printf("#\n");
    }else{
        for(i = 0; i < nivel; i++)
            printf("  ");
        printf("%i\n", p->valor);
        nivel++;
        mostraArvore(p->esq, nivel);
        mostraArvore(p->dir, nivel);
    }
}

Nodo* inserirNodo(Nodo *raiz, int v){
    if(!raiz)
        raiz = criarNodo(v);
    else{
        if(v <= raiz->valor)
            raiz->esq = inserirNodo(raiz->esq, v);
        else
            raiz->dir = inserirNodo(raiz->dir, v);
    }
    return raiz;
}

Nodo* busca(Nodo *raiz, int v){
    if(raiz){
        if(v == raiz->valor)
            return raiz;
        else if(v < raiz->valor)
            return busca(raiz->esq, v);
        else
            return busca(raiz->dir, v);
    }else
        return NULL;
}

Nodo* excluir(Nodo *raiz, int v){
    if(raiz){
        if(v < raiz->valor){
            raiz->esq = excluir(raiz->esq, v);
        }else if(v > raiz->valor){
            raiz->dir = excluir(raiz->dir, v);
        }else{
            Nodo *aux = raiz;
            if(!raiz->esq){
                raiz = raiz->dir;
                free(aux);
            }else if(!raiz->dir){
                raiz = raiz->esq;
                free(aux);
            }else{
                Nodo *menorDir = raiz->dir;
                while(menorDir->esq)
                    menorDir = menorDir->esq;
                raiz->valor = menorDir->valor;
                raiz->dir = excluir(raiz->dir, menorDir->valor);
            }
        }
    }
    return raiz;
}

int main(){
    Nodo *raiz = NULL, *aux = NULL /**atual = NULL, *pai = NULL*/;
    int op, v;

    do{
        printf("[1]: INSERIR NOVO NODO\n");
        printf("[2]: MOSTRAR ARVORE\n");
        printf("[3]: BUSCA DE NODO\n");
        printf("[4]: EXCLUIR FILHO (SOMENTE FOLHA)\n");
        printf("[0]: SAIR\n");
        printf("OPCAO: ");
        scanf("%d",&op);

        switch(op){
        case 1:
            printf("\nCRIANDO NOVO NODO\n");
            printf("VALOR: ");
            scanf("%d", &v);
            raiz = inserirNodo(raiz, v);
            break;
        case 2:
            mostraArvore(raiz, 0);
            break;
        case 3:
            printf("VALOR DE BUSCA: ");
            scanf("%d", &v);
            aux = busca(raiz, v);
            if(aux)
                printf("\nVALOR %i ENCONTRADO", aux->valor);
            else
                printf("\nVALOR NAO ESTA NA ARVORE");
            break;
        case 4:
            printf("\nVALOR A SER EXCLUIDO: ");
            scanf("%d", &v);
            raiz = excluir(raiz, v);
            mostraArvore(raiz, 0);
            break;
        case 0:
            printf("SAIR\n");
            break;
        default:
            printf("OPCAO INVALIDA\n");
        }
        printf("\n\n\n");
    }while(op != 0);

    return 0;
}

