#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
   int valor;
   struct nodo *esq;
   struct nodo *dir;
   struct nodo *pai;
}Nodo;

Nodo* criarNodo(int v){
   Nodo *p = (Nodo*)malloc(sizeof(Nodo));
   p->valor = v;
   p->esq = NULL;
   p->dir = NULL;
   p->pai = NULL;
   return p;
}

void mostraAtual(Nodo *atual){
    if(atual == NULL)
        printf("TEM NODO NAO\n");
    else{
    printf(" |%d|\n", atual->valor);
        if(atual->esq == NULL)
            printf(" |#| ");
        else
            printf(" |%d| ", atual->esq->valor);

        if(atual->dir == NULL)
            printf(" |#| ");
        else
            printf(" |%d| ", atual->dir->valor);
    }
}

void mostraArvore(Nodo *p, int nivel){
    int i;
    if(p == NULL){
    }else{
        for(i = 0; i < nivel; i++)
            printf("  ");
        printf("%3i\n", p->valor);
        nivel++;
        mostraArvore(p->esq, nivel);
        mostraArvore(p->dir, nivel);
    }
}

Nodo* excluirFilho(Nodo *p){
    if(p == NULL)
        printf("NODO NAO EXISTE\n");
    else if(p->esq != NULL || p->dir != NULL)
        printf("NODO NAO EH UMA FOLHA\n");
    else
        free(p);
    return p;
}

void excluirAtual(Nodo *p){
    if(p != NULL && (p->esq != NULL || p->dir != NULL)){
        excluirAtual(p->esq);
        excluirAtual(p->dir);
    }if(p != NULL && p->pai != NULL){
        if(p->pai->esq == p)
            p->pai->esq = NULL;
        else
            p->pai->esq = NULL;
    }
    free(p);
}

typedef struct fila{
    Nodo *no;
    struct fila *prox;
}Fila;

Fila* criarFila(Nodo* novo){
   Fila *f = (Fila*)malloc(sizeof(Fila));
   f->no = novo;
   f->prox = NULL;
   return f;
}

Fila* enfileirar(Fila *f, Nodo *p){
    if(p){
        if(f){
            Fila *aux = f;
            while(aux->prox)
                aux = aux->prox;
            aux->prox = criarFila(p);
        }else{
            f = criarFila(p);
        }
    }
    return f;
}

Fila* desenfileirar(Fila *f){
    if(f){
        Fila *aux = f;
        f = f->prox;
        free(aux);
    }
    return f;
}

Nodo* buscaLarg(Nodo* raiz, int v){
    if(raiz){
        Fila *f = NULL;
        f = enfileirar(f, raiz);
        while(f && f->no->valor != v){
            f = enfileirar(f, f->no->esq);
            f = enfileirar(f, f->no->dir);
            printf("%i ->", f->no->valor);
            f = desenfileirar(f);
        }
        if(f){
            Nodo *aux = f->no;
            printf("\nDESENFILEIRAR");
            while(f)
                f = desenfileirar(f);
            return aux;
        }else
            return NULL;
    }
    return raiz;
}

int main(){
   Nodo *raiz = NULL, *atual = NULL, *pai = NULL, *aux = NULL;
   int op, v;

   do{
        printf("[1]: MOSTRAR NODO ATUAL\n");
        printf("[2]: NAVEGAR PARA A ESQUERDA\n");
        printf("[3]: NAVEGAR PARA A DIREITA\n");
        printf("[4]: INSERIR NOVO NODO\n");
        printf("[5]: NAVEGAR PARA A RAIZ\n");
        printf("[6]: MOSTRAR ARVORE\n");
        printf("[7]: EXCLUIR FILHO\n");
        printf("[8]: EXCLUIR NODO ATUAL\n");
        printf("[9]: SUBIR 1 NIVEL NA ARVORE\n");
        printf("[10]: BUSCA EM LARGURA\n");
        printf("[0]: SAIR\n ");
        printf("\nOPCAO: ");
        scanf("%d", &op);

        switch (op){
        case 1:
            printf("MOSTRANDO NODO ATUAL\n");
            mostraAtual(atual);
            break;
        case 2:
            printf("NAVEGANDO PARA A ESQUERDA\n");
            if(raiz == NULL || atual->esq == NULL)
                printf("NAO EXISTE\n");
            else
                atual = atual->esq;
            mostraAtual(atual);
            break;
        case 3:
            printf("NAVEGANDO PARA A DIREITA\n");
            if(raiz == NULL || atual->dir == NULL)
                printf("NAO EXISTE\n");
            else
                atual = atual->dir;
            mostraAtual(atual);
            break;
        case 4:
            printf("CRIANDO NOVO NODO\n");
            printf("VALOR: ");
            scanf("%d", &v);
            if(raiz == NULL){
                raiz = criarNodo(v);
                atual = raiz;
            }else{
                printf("[1]: PARA INSERIR A ESQUERDA\n");
                printf("[2]: PARA INSERIR A DIREITA\n");
                scanf("%d", &op);
                if(op == 1 && atual->esq == NULL){
                    atual->esq = criarNodo(v);
                    atual->esq->pai = atual;
                }
                if(op == 2 && atual->dir == NULL){
                    atual->dir = criarNodo(v);
                    atual->dir->pai =atual;
                }
                mostraAtual(atual);
            }
            break;
        case 5:
            printf("NAVEGANDO PARA A RAIZ\n");
            atual = raiz;
            mostraAtual(atual);
            break;
        case 6:
            printf("MOSTRANDO ARVORE\n");
            mostraArvore(raiz, 0);
            break;
        case 7:
            if(raiz == NULL){
                printf("ARVORE VAZIA\n");
                break;
            }
            printf("[1]: PARA EXCLUIR FILHO ESQUERDA\n[2]: PARA EXCLUIR FILHO DIREITA\n");
            printf("OPCAO: ");
            scanf("%d", &op);
            if(op == 1){
                atual->esq = excluirFilho(atual->esq);
            }if(op == 2){
                atual->dir = excluirFilho(atual->dir);
            }
            mostraAtual(atual);
            break;
        case 8:
            if(raiz == NULL)
                printf("ARVORE VAZIA\n");
            else{
                if(atual == raiz){
                    excluirAtual(raiz);
                    raiz = NULL;
                    atual = NULL;
                }else{
                    pai = atual->pai;
                    excluirAtual(atual);
                    atual = pai;
                }
            }
            mostraAtual(atual);
            break;
        case 9:
            if(atual && !atual->pai){
                atual = atual->pai;
            }
            mostraAtual(atual);
            break;
        case 10:
            printf("\nBUSCANMDO EM LARGURA\n");
                printf("VALOR: ");
                scanf("%d", &v);
                if(aux = buscaLarg(raiz, v)){
                    printf("\nVALOR %d ENCONTRADO\n", aux->valor);
                }else
                    printf("\nVALOR NAO ESTA NA ARVORE");
            break;
        case 0:
            printf("SAIR\n");
            break;
        default:
            printf("OPCAO INVALIDA\n");
            break;
        }
        printf("\n\n");
   }while(op != 0);
return 0;
}
