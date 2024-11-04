#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura do nó da Treap
typedef struct No {
    int chave;          // Chave para BST
    int prioridade;     // Prioridade para heap
    struct No *esq;     // Filho esquerdo
    struct No *dir;     // Filho direito
} No;

// Função para criar um novo nó
No* novoNo(int chave) {
    No* temp = (No*)malloc(sizeof(No));
    temp->chave = chave;
    temp->prioridade = rand();  // Gera prioridade aleatória
    temp->esq = temp->dir = NULL;
    return temp;
}

// Função para rotação à direita
No* rotacaoDireita(No* y) {
    No* x = y->esq;
    No* T2 = x->dir;

    // Realiza rotação
    x->dir = y;
    y->esq = T2;

    return x;  // Nova raiz após rotação
}

// Função para rotação à esquerda
No* rotacaoEsquerda(No* x) {
    No* y = x->dir;
    No* T2 = y->esq;

    // Realiza rotação
    y->esq = x;
    x->dir = T2;

    return y;  // Nova raiz após rotação
}

// Função recursiva para inserir um nó
No* inserir(No* raiz, int chave) {
    // Se a árvore está vazia, retorna um novo nó
    if (raiz == NULL)
        return novoNo(chave);

    // Inserção normal de BST
    if (chave < raiz->chave) {
        raiz->esq = inserir(raiz->esq, chave);
        
        // Verifica propriedade de heap máximo
        if (raiz->esq->prioridade > raiz->prioridade)
            raiz = rotacaoDireita(raiz);
    }
    else {
        raiz->dir = inserir(raiz->dir, chave);
        
        // Verifica propriedade de heap máximo
        if (raiz->dir->prioridade > raiz->prioridade)
            raiz = rotacaoEsquerda(raiz);
    }
    
    return raiz;
}

// Função recursiva para remover um nó
No* remover(No* raiz, int chave) {
    if (raiz == NULL)
        return raiz;

    // Busca recursiva do nó a ser removido
    if (chave < raiz->chave)
        raiz->esq = remover(raiz->esq, chave);
    else if (chave > raiz->chave)
        raiz->dir = remover(raiz->dir, chave);
    else {  // Encontrou o nó a ser removido
        // Caso 1: Nó folha
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }
        // Caso 2: Nó com um filho
        else if (raiz->esq == NULL) {
            No* temp = raiz->dir;
            free(raiz);
            return temp;
        }
        else if (raiz->dir == NULL) {
            No* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        // Caso 3: Nó com dois filhos
        else {
            // Decide qual rotação fazer baseado nas prioridades
            if (raiz->esq->prioridade > raiz->dir->prioridade) {
                raiz = rotacaoDireita(raiz);
                raiz->dir = remover(raiz->dir, chave);
            }
            else {
                raiz = rotacaoEsquerda(raiz);
                raiz->esq = remover(raiz->esq, chave);
            }
        }
    }
    return raiz;
}

// Função para buscar um valor na treap
No* buscar(No* raiz, int chave) {
    // Caso base: raiz é nula ou a chave está na raiz
    if (raiz == NULL || raiz->chave == chave)
        return raiz;

    // Chave é maior que a raiz
    if (raiz->chave < chave)
        return buscar(raiz->dir, chave);

    // Chave é menor que a raiz
    return buscar(raiz->esq, chave);
}

// Função para percorrer a árvore em ordem
void percorrerEmOrdem(No* raiz) {
    if (raiz != NULL) {
        percorrerEmOrdem(raiz->esq);
        printf("Chave: %d, Prioridade: %d\n", raiz->chave, raiz->prioridade);
        percorrerEmOrdem(raiz->dir);
    }
}

// Função principal para teste
int main() {
    srand(time(NULL));  // Inicializa gerador de números aleatórios
    No* raiz = NULL;

    // Inserindo alguns valores
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);

    printf("Árvore em ordem:\n");
    percorrerEmOrdem(raiz);

    // Removendo um valor
    printf("\nRemovendo 30...\n");
    raiz = remover(raiz, 30);

    printf("\nÁrvore após remoção:\n");
    percorrerEmOrdem(raiz);

    return 0;
}