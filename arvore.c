#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
   int valor;
   struct nodo *esq;
   struct nodo *dir;
}Nodo;

Nodo* criarNodo(int v){
   Nodo *p = (Nodo*)malloc(sizeof(Nodo));
   p->valor = v;
   p->esq = NULL;
   p->dir = NULL;
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
        //printf(" |#| "); 
    }
    else{
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
    else if(p->esq != NULL || p->dir != NULL){
        printf("NODO NAO EH UMA FOLHA\n");
    }else{
        free(p);
        p = NULL;
    }
    return p;

}

int main(){
   Nodo *raiz = NULL, *atual = NULL;
   int op, v;

   do{
        printf("[1]: MOSTRAR NODO ATUAL \n");
        printf("[2]: NAVEGAR PARA A ESQUERDA \n");
        printf("[3]: NAVEGAR PARA A DIREITA \n");
        printf("[4]: INSERIR NOVO NODO \n");
        printf("[5]: NAVEGAR PARA A RAIZ\n");
        printf("[6]: MOSTRAR ARVORE\n");
        printf("[7]: EXCLUIR NODO\n");
        printf("[0]: SAIR \n ");
        printf("opcao: ");
        scanf("%d", &op);

        switch (op){
        case 1:
            printf("MOSTRANDO NODO ATUAL \n");
            mostraAtual(atual);
            break;
        case 2:
            printf("NAVEGANDO PARA A ESQUERDA \n");
            if(raiz == NULL || atual->esq == NULL)
                printf("NAO EXISTE\n");
            else
                atual = atual->esq;
            mostraAtual(atual);
            break;
        case 3:
            printf("NAVEGANDO PARA A DIREITA \n");
            if(raiz == NULL || atual->dir == NULL)
                printf("NAO EXISTE\n");
            else
                atual = atual->dir;
            mostraAtual(atual);
            break;
        case 4:
            printf("CRIANDO NOVO NODO \n");
            printf("Valor: ");
            scanf("%d", &v);
            if(raiz == NULL){
                raiz = criarNodo(v);
                atual = raiz;
            }else{
                printf("[1]: PARA INSERIR A ESQUERDA\n");
                printf("[2]: PARA INSERIR A DIREITA\n");
                scanf("%d", &op);
                if(op == 1 && atual->esq == NULL)
                    atual->esq = criarNodo(v);

                if(op == 2 && atual->dir == NULL)
                    atual->dir = criarNodo(v);
                mostraAtual(atual);
            }
            break;
        case 5:
            printf("\nNAVEGANDO PARA A RAIZ");
            atual = raiz;
            mostraAtual(atual);
            break;
        case 6:
            printf("MOSTRANDO ARVORE");
            mostraArvore(raiz, 0);
            break;
        case 7:
            if(raiz == NULL){
                printf("ARVORE VAZIA");
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
        case 0:
            printf("SAIR \n");
            break;

        default:
            printf("OPCAO INVALIDA \n");
            break;
        }
        printf("\n\n");
   }while(op != 0);

return 0;
}
