#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int valor;
    struct nodo *esq;
    struct nodo *dir;
    struct nodo *pai;
    int h;
} Nodo;

Nodo* criarNodo(int v){
    Nodo *p = (Nodo*)malloc(sizeof(Nodo));
    p->valor = v;
    p->esq = NULL;
    p->dir = NULL;
    p->pai = NULL;
    p->h = 0;
    return p;
}

int fb(Nodo *p){
    int he, hd;

    if(p->esq)
        he = p->esq->h;
    else   
        he = 0;

    if(p->pai->dir)
        he = p->dir->h;
    else   
        hd = 0;

    if(he>hd)
        p->h = he+1;
    else
        p->h = hd+1;
    
    return he-hd;
}

void mostraArvore(Nodo *p, int nivel){
    int i;
    if(p == NULL){
        for(i=0;i<nivel;i++)
            printf("  ");
        printf("#\n");
    }else{
        for(i=0;i<nivel;i++)
            printf("  ");
        printf("%i [%i]\n",p->valor, fb(p));
        nivel++;
        mostraArvore(p->esq,nivel);
        mostraArvore(p->dir,nivel);
    }
}

Nodo* inserirNodo(Nodo *raiz, int v){
    if(!raiz){
        raiz = criarNodo(v);
        fb(raiz);

    }else{
        if(v <= raiz->valor){
            raiz->esq = inserirNodo(raiz->esq,v);
            raiz->esq->pai = raiz;
            fb(raiz->esq);
        }else{
            raiz->dir = inserirNodo(raiz->dir,v);
            raiz->dir->pai = raiz;
            fb(raiz->dir);
        }
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
            raiz->esq->pai = raiz;
            fb(raiz->esq);
        }
        else if(v > raiz->valor){
            raiz->dir = excluir(raiz->dir, v);
            raiz->dir->pai = raiz;
            fb(raiz->dir);
        }
        else{ //encontrou v
            Nodo *aux = raiz;
            if(!raiz->esq && !raiz->dir){
                free(aux);
            }
            else if(!raiz->dir){
                raiz->dir->pai = raiz->pai;
                raiz = raiz->esq;
                fb(raiz->dir);
                free(aux);
            }
            else if(!raiz->esq){
                raiz->esq->pai = raiz->pai;
                raiz = raiz->dir;
                fb(raiz->esq);
                free(aux);
            }
            else{
                Nodo *menorDir = raiz->dir;
                while(menorDir->esq)
                    menorDir = menorDir->esq;
                
                raiz->valor = menorDir->valor;
                raiz->dir = excluir(raiz->dir, menorDir->valor);
            }
        }
        return raiz;
    }
    else
        return raiz;
}

int main(){
    Nodo *raiz = NULL, *atual = NULL, *pai, *aux;
    int op, v;

    do{
        printf("1 - inserir novo nodo\n");
        printf("2 - mostrar arvore\n");
        printf("3 - busca nodo\n");
        printf("4 - Excluir nodo\n");

        printf("0 - sair\n");
        printf("opcao: ");
        scanf("%d",&op);

        switch(op){
        case 1:
            printf("\nCriando novo nodo\n");
            printf("valor: ");
            scanf("%d",&v);
            raiz = inserirNodo(raiz,v);
            break;

        case 2:
            mostraArvore(raiz,0);
            break;

        case 3:
            printf("\nDigite o valor para a busca: ");
            scanf("%d", &v);
            aux = busca(raiz, v);
            if(aux)
                printf("\nValor %i encontrado\n", aux->valor);
            else
                printf("\nValor nao esta na arvore.\n");
            break;
        
        case 4:
            printf("\nDigite um valor para excluir: ");
            scanf("%d", &v);
            aux = busca(raiz, v);
            if(aux){
                printf("\nValor %i encontrado\n", aux->valor);
                raiz = excluir(raiz, v);
                printf("\nValor %i excluido\n", v);
                mostraArvore(raiz, 0);
            }
            else
                printf("\nValor nao esta na arvore.\n");
            
            mostraArvore(raiz, 0);
            break;

        case 0:
            printf("Sair\n");
            break;
        default:
            printf("opcao invalida\n");
        }
        printf("\n\n\n");
    }while(op!=0);

    return 0;
}
