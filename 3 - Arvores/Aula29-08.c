#include <stdio.h>
#include <stdlib.h>

// Estrutura de um nó da árvore AVL
typedef struct No {
    int valor;
    struct No *esquerda;
    struct No *direita;
    int altura;
} No;

// Função para obter a altura de um nó
int altura(No *n) {
    if (n == NULL)
        return 0;
    return n->altura;
}

// Função para obter o maior valor entre dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para criar um novo nó
No* novoNo(int valor) {
    No* no = (No*) malloc(sizeof(No));
    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1; // novo nó é inicialmente inserido na folha
    return(no);
}

// Rotação à direita
No *rotacaoDireita(No *y) {
    No *x = y->esquerda;
    No *T2 = x->direita;

    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;

    // Atualiza as alturas
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    // Retorna o novo nó raiz
    return x;
}

// Rotação à esquerda
No *rotacaoEsquerda(No *x) {
    No *y = x->direita;
    No *T2 = y->esquerda;

    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;

    // Atualiza as alturas
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    // Retorna o novo nó raiz
    return y;
}

// Função para obter o fator de balanceamento de um nó
int obterFatorBalanceamento(No *n) {
    if (n == NULL)
        return 0;
    return altura(n->esquerda) - altura(n->direita);
}

// Função para inserir um valor na árvore AVL
No* inserir(No* no, int valor) {
    // 1. Inserção normal de uma BST
    if (no == NULL)
        return(novoNo(valor));

    if (valor < no->valor)
        no->esquerda = inserir(no->esquerda, valor);
    else if (valor > no->valor)
        no->direita = inserir(no->direita, valor);
    else // Valores duplicados não são permitidos na árvore AVL
        return no;

    // 2. Atualiza a altura do nó ancestral
    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

    // 3. Obtém o fator de balanceamento desse nó ancestral para verificar
    // se este nó se tornou desbalanceado
    int balanceamento = obterFatorBalanceamento(no);

    // Se o nó se tornou desbalanceado, então existem 4 casos

    // Caso Esquerda-Esquerda
    if (balanceamento > 1 && valor < no->esquerda->valor)
        return rotacaoDireita(no);

    // Caso Direita-Direita
    if (balanceamento < -1 && valor > no->direita->valor)
        return rotacaoEsquerda(no);

    // Caso Esquerda-Direita
    if (balanceamento > 1 && valor > no->esquerda->valor) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }

    // Caso Direita-Esquerda
    if (balanceamento < -1 && valor < no->direita->valor) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }

    // Retorna o ponteiro do nó (inalterado)
    return no;
}

// Função para encontrar o nó com o valor mínimo
No *valorMinimoNo(No* no) {
    No* atual = no;

    // Loop para encontrar o filho mais à esquerda
    while (atual->esquerda != NULL)
        atual = atual->esquerda;

    return atual;
}

// Função para excluir um nó da árvore AVL
No* excluir(No* raiz, int valor) {
    // PASSO 1: Realiza a exclusão padrão de BST
    if (raiz == NULL)
        return raiz;

    // Se o valor a ser excluído for menor que o valor da raiz,
    // então está na subárvore esquerda
    if (valor < raiz->valor)
        raiz->esquerda = excluir(raiz->esquerda, valor);

    // Se o valor a ser excluído for maior que o valor da raiz,
    // então está na subárvore direita
    else if (valor > raiz->valor)
        raiz->direita = excluir(raiz->direita, valor);

    // Se o valor for igual ao valor da raiz, então este é o nó
    // a ser excluído
    else {
        // Nó com apenas um filho ou sem filhos
        if ((raiz->esquerda == NULL) || (raiz->direita == NULL)) {
            No *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;

            // Caso sem filhos
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            }
            else // Caso com um filho
                *raiz = *temp; // Cópia do conteúdo do filho não vazio

            free(temp);
        }
        else {
            // Nó com dois filhos: Obtém o sucessor (menor valor na subárvore direita)
            No* temp = valorMinimoNo(raiz->direita);

            // Copia o valor do sucessor para este nó
            raiz->valor = temp->valor;

            // Exclui o sucessor
            raiz->direita = excluir(raiz->direita, temp->valor);
        }
    }

    // Se a árvore tiver apenas um nó, então retorna
    if (raiz == NULL)
        return raiz;

    // PASSO 2: Atualiza a altura do nó atual
    raiz->altura = max(altura(raiz->esquerda), altura(raiz->direita)) + 1;

    // PASSO 3: Obtém o fator de balanceamento desse nó para verificar
    // se este nó se tornou desbalanceado
    int balanceamento = obterFatorBalanceamento(raiz);

    // Se o nó se tornou desbalanceado, então existem 4 casos

    // Caso Esquerda-Esquerda
    if (balanceamento > 1 && obterFatorBalanceamento(raiz->esquerda) >= 0)
        return rotacaoDireita(raiz);

    // Caso Esquerda-Direita
    if (balanceamento > 1 && obterFatorBalanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    // Caso Direita-Direita
    if (balanceamento < -1 && obterFatorBalanceamento(raiz->direita) <= 0)
        return rotacaoEsquerda(raiz);

    // Caso Direita-Esquerda
    if (balanceamento < -1 && obterFatorBalanceamento(raiz->direita) > 0) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

// Função para imprimir a árvore AVL em ordem (in-order)
void imprimirEmOrdem(No *raiz) {
    if (raiz != NULL) {
        imprimirEmOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        imprimirEmOrdem(raiz->direita);
    }
}

// Função principal
int main() {
    No *raiz = NULL;

    // Inserção dos valores na árvore AVL
    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 25);

    printf("Árvore AVL em ordem:\n");
    imprimirEmOrdem(raiz);
    printf("\n");

    // Excluindo um nó
    raiz = excluir(raiz, 40);

    printf("Árvore AVL após exclusão de 40:\n");
    imprimirEmOrdem(raiz);
    printf("\n");

    return 0;
}
