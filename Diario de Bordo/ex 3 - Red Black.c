#include <stdio.h>
#include <stdlib.h>

// Autor: Matheus Kuster Rosa
// Nesta etapa, vocês vão implementar, em Linguagem C, a estrutura de uma Árvore Red-Black.

enum Cor
{
  VERMELHO,
  PRETO
};

typedef struct No
{
  int dado;
  enum Cor cor;
  struct No *esquerda, *direita, *pai;
} No;

// Função para criar um novo nó
No *criarNo(int dado)
{
  No *novo = (No *)malloc(sizeof(No));
  novo->dado = dado;
  novo->cor = VERMELHO; // Novos nós são sempre vermelhos na inserção inicial
  novo->esquerda = novo->direita = novo->pai = NULL;
  return novo;
}

// Função para rotacionar à esquerda
void rotacionarEsquerda(No **raiz, No *x)
{
  No *y = x->direita;
  x->direita = y->esquerda;
  if (y->esquerda != NULL)
    y->esquerda->pai = x;
  y->pai = x->pai;
  if (x->pai == NULL)
    *raiz = y;
  else if (x == x->pai->esquerda)
    x->pai->esquerda = y;
  else
    x->pai->direita = y;
  y->esquerda = x;
  x->pai = y;
}

// Função para rotacionar à direita
void rotacionarDireita(No **raiz, No *y)
{
  No *x = y->esquerda;
  y->esquerda = x->direita;
  if (x->direita != NULL)
    x->direita->pai = y;
  x->pai = y->pai;
  if (y->pai == NULL)
    *raiz = x;
  else if (y == y->pai->direita)
    y->pai->direita = x;
  else
    y->pai->esquerda = x;
  x->direita = y;
  y->pai = x;
}

// Função para corrigir violações após a inserção
void corrigirInsercao(No **raiz, No *k)
{
  No *tio;
  while (k->pai != NULL && k->pai->cor == VERMELHO)
  {
    if (k->pai == k->pai->pai->esquerda)
    {
      tio = k->pai->pai->direita;
      if (tio != NULL && tio->cor == VERMELHO)
      {
        // Caso 1: o tio é vermelho
        k->pai->cor = PRETO;
        tio->cor = PRETO;
        k->pai->pai->cor = VERMELHO;
        k = k->pai->pai;
      }
      else
      {
        if (k == k->pai->direita)
        {
          // Caso 2: o tio é preto e o nó é filho direito
          k = k->pai;
          rotacionarEsquerda(raiz, k);
        }
        // Caso 3: o tio é preto e o nó é filho esquerdo
        k->pai->cor = PRETO;
        k->pai->pai->cor = VERMELHO;
        rotacionarDireita(raiz, k->pai->pai);
      }
    }
    else
    {
      tio = k->pai->pai->esquerda;
      if (tio != NULL && tio->cor == VERMELHO)
      {
        // Caso 1: o tio é vermelho
        k->pai->cor = PRETO;
        tio->cor = PRETO;
        k->pai->pai->cor = VERMELHO;
        k = k->pai->pai;
      }
      else
      {
        if (k == k->pai->esquerda)
        {
          // Caso 2: o tio é preto e o nó é filho esquerdo
          k = k->pai;
          rotacionarDireita(raiz, k);
        }
        // Caso 3: o tio é preto e o nó é filho direito
        k->pai->cor = PRETO;
        k->pai->pai->cor = VERMELHO;
        rotacionarEsquerda(raiz, k->pai->pai);
      }
    }
  }
  (*raiz)->cor = PRETO; // A raiz deve ser sempre preta
}

// Função para inserir um novo nó na árvore
void inserir(No **raiz, int dado)
{
  No *novo = criarNo(dado);
  No *y = NULL;
  No *x = *raiz;

  // Percorre a árvore para encontrar a posição de inserção
  while (x != NULL)
  {
    y = x;
    if (novo->dado < x->dado)
      x = x->esquerda;
    else
      x = x->direita;
  }

  // Define o pai do novo nó
  novo->pai = y;
  if (y == NULL)
    *raiz = novo; // A árvore estava vazia
  else if (novo->dado < y->dado)
    y->esquerda = novo;
  else
    y->direita = novo;

  // Corrige possíveis violações das propriedades Red-Black
  corrigirInsercao(raiz, novo);
}

// Função para percorrer a árvore em ordem
void emOrdem(No *raiz)
{
  if (raiz != NULL)
  {
    emOrdem(raiz->esquerda);
    printf("%d ", raiz->dado);
    emOrdem(raiz->direita);
  }
}

// Função principal
int main()
{
  No *raiz = NULL;

  inserir(&raiz, 10);
  inserir(&raiz, 20);
  inserir(&raiz, 30);
  inserir(&raiz, 15);
  inserir(&raiz, 25);
  inserir(&raiz, 5);

  printf("Percorrendo a árvore em ordem: ");
  emOrdem(raiz);
  printf("\n");

  return 0;
}
