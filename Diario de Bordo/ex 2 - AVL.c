#include <stdio.h>
#include <stdlib.h>

// Autor: Matheus Kuster Rosa
// Vocês deverão desenvolver a codificação em Linguagem C, da estrutura em Árvore AVL.

// Estrutura de um nó da árvore AVL
typedef struct No {
    int valor;
    struct No* esquerda;
    struct No* direita;
    int altura;
} No;

// Função para criar um novo nó
No* criarNo(int valor) {
    No* no = (No*)malloc(sizeof(No));
    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1; // Altura inicial é 1
    return no;
}

// Função para obter a altura de um nó
int obterAltura(No* no) {
    if (no == NULL)
        return 0;
    return no->altura;
}

// Função para calcular o fator de balanceamento de um nó
int obterFatorBalanceamento(No* no) {
    if (no == NULL)
        return 0;
    return obterAltura(no->esquerda) - obterAltura(no->direita);
}

// Função para obter o maior valor entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Rotação à direita para corrigir desbalanceamento
No* rotacaoDireita(No* y) {
    No* x = y->esquerda;
    No* T2 = x->direita;

    // Executando rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualizando as alturas
    y->altura = max(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;
    x->altura = max(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;

    // Retornando novo nó raiz
    return x;
}

// Rotação à esquerda para corrigir desbalanceamento
No* rotacaoEsquerda(No* x) {
    No* y = x->direita;
    No* T2 = y->esquerda;

    // Executando rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualizando as alturas
    x->altura = max(obterAltura(x->esquerda), obterAltura(x->direita)) + 1;
    y->altura = max(obterAltura(y->esquerda), obterAltura(y->direita)) + 1;

    // Retornando novo nó raiz
    return y;
}

// Função para inserir um valor na árvore AVL
No* inserir(No* no, int valor) {
    // Passo 1: Inserir o valor como em uma árvore binária de busca comum
    if (no == NULL)
        return criarNo(valor);

    if (valor < no->valor)
        no->esquerda = inserir(no->esquerda, valor);
    else if (valor > no->valor)
        no->direita = inserir(no->direita, valor);
    else // Valores duplicados não são permitidos
        return no;

    // Passo 2: Atualizar a altura do nó ancestral
    no->altura = 1 + max(obterAltura(no->esquerda), obterAltura(no->direita));

    // Passo 3: Obter o fator de balanceamento e verificar se o nó está desbalanceado
    int fatorBalanceamento = obterFatorBalanceamento(no);

    // Se o nó estiver desbalanceado, existem 4 casos possíveis:

    // Caso 1: Desbalanceamento à esquerda (Rotação à direita)
    if (fatorBalanceamento > 1 && valor < no->esquerda->valor)
        return rotacaoDireita(no);

    // Caso 2: Desbalanceamento à direita (Rotação à esquerda)
    if (fatorBalanceamento < -1 && valor > no->direita->valor)
        return rotacaoEsquerda(no);

    // Caso 3: Desbalanceamento à esquerda-direita (Rotação à esquerda-direita)
    if (fatorBalanceamento > 1 && valor > no->esquerda->valor) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso 4: Desbalanceamento à direita-esquerda (Rotação à direita-esquerda)
    if
