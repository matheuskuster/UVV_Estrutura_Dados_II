#include <stdio.h>
#include <stdlib.h>

// Autor: Matheus Kuster Rosa
// Vocês deverão desenvolver a codificação em Linguagem C, da estrutura em Árvore AVL.

// Definição da estrutura do nó da árvore AVL
typedef struct No {
    int dado;
    struct No *esquerda;
    struct No *direita;
    int altura;
} No;

// Função para obter a altura de um nó
int obterAltura(No *n) {
    if (n == NULL)
        return 0;
    return n->altura;
}

// Função para obter o valor máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para criar um novo nó
No* criarNo(int dado) {
    No* no = (No*) malloc(sizeof(No));
    no->dado = dado;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1; // Novo nó é inicialmente adicionado na folha
    return no;
}

// Função para rotacionar à direita
No* rotacionarDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza as alturas
    y->altura = max(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;
    x->altura = max(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;

    // Retorna a nova raiz
    return x;
}

// Função para rotacionar à esquerda
No* rotacionarEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza as alturas
    x->altura = max(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;
    y->altura = max(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;

    // Retorna a nova raiz
    return y;
}

// Função para obter o fator de balanceamento de um nó
int obterFatorBalanceamento(No *n) {
    if (n == NULL)
        return 0;
    return obterAltura(n->esquerda) - obterAltura(n->direita);
}

// Função para inserir um nó na árvore AVL
No* inserir(No* no, int dado) {
    // Passo 1: Realiza a inserção normal de uma BST
    if (no == NULL)
        return criarNo(dado);

    if (dado < no->dado)
        no->esquerda = inserir(no->esquerda, dado);
    else if (dado > no->dado)
        no->direita = inserir(no->direita, dado);
    else // Valores iguais não são permitidos em BST
        return no;

    // Passo 2: Atualiza a altura do ancestral
    no->altura = 1 + max(obterAltura(no->esquerda), obterAltura(no->direita));

    // Passo 3: Obtém o fator de balanceamento
    int balanceamento = obterFatorBalanceamento(no);

    // Passo 4: Verifica os casos de desbalanceamento

    // Caso Esquerda-Esquerda
    if (balanceamento > 1 && dado < no->esquerda->dado)
        return rotacionarDireita(no);

    // Caso Direita-Direita
    if (balanceamento < -1 && dado > no->direita->dado)
        return rotacionarEsquerda(no);

    // Caso Esquerda-Direita
    if (balanceamento > 1 && dado > no->esquerda->dado) {
        no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }

    // Caso Direita-Esquerda
    if (balanceamento < -1 && dado < no->direita->dado) {
        no->direita = rotacionarDireita(no->direita);
        return rotacionarEsquerda(no);
    }

    // Retorna o ponteiro do nó (inalterado)
    return no;
}

// Função para percorrer a árvore em ordem
void emOrdem(No *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);
        printf("%d ", raiz->dado);
        emOrdem(raiz->direita);
    }
}

// Função principal
int main() {
    No *raiz = NULL;

    // Inserção de elementos na árvore AVL
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 25);
    raiz = inserir(raiz, 28);
    raiz = inserir(raiz, 27);
    raiz = inserir(raiz, 5);

    printf("Percorrendo a árvore em ordem: ");
    emOrdem(raiz);
    printf("\n");

    return 0;
}
