#include <stdio.h>
#include <stdlib.h>

// Autor: Matheus Kuster
// https://github.com/gnrochabr/Estrutura_Dados_II/issues/2
// Crie em C a estrutura de uma árvore binária cuja informação seja um inteiro.
// Escreva funções que recebam um ponteiro para a raiz da árvore e façam:

// Inserção de um elemento na árvore;
// Pesquisa de um elemento na árvore;
// Exclusão de um elemento na árvore;

// Definição da estrutura de um nó da árvore binária
typedef struct Node {
    int dado;               // Dado armazenado no nó
    struct Node *esquerda;  // Ponteiro para o nó filho à esquerda
    struct Node *direita;   // Ponteiro para o nó filho à direita
} Node;

// Função para criar um novo nó com um dado específico
Node* criarNo(int dado) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->dado = dado;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    return novoNo;
}

// Função para inserir um novo dado na árvore binária
Node* inserir(Node* raiz, int dado) {
    // Se a raiz for nula, cria um novo nó e o retorna como a nova raiz
    if (raiz == NULL) {
        return criarNo(dado);
    }

    // Se o dado for menor que o dado da raiz, insere na subárvore esquerda
    if (dado < raiz->dado) {
        raiz->esquerda = inserir(raiz->esquerda, dado);
    } 
    // Se o dado for maior que o dado da raiz, insere na subárvore direita
    else if (dado > raiz->dado) {
        raiz->direita = inserir(raiz->direita, dado);
    }

    // Retorna a raiz da árvore após a inserção
    return raiz;
}

// Função para buscar um dado na árvore binária
Node* buscar(Node* raiz, int dado) {
    // Se a raiz for nula ou se o dado for encontrado, retorna a raiz
    if (raiz == NULL || raiz->dado == dado) {
        return raiz;
    }

    // Se o dado for menor que o dado da raiz, busca na subárvore esquerda
    if (dado < raiz->dado) {
        return buscar(raiz->esquerda, dado);
    }

    // Caso contrário, busca na subárvore direita
    return buscar(raiz->direita, dado);
}

// Função para encontrar o menor valor na subárvore direita
Node* encontrarMin(Node* raiz) {
    // Continua percorrendo a subárvore esquerda até encontrar o menor valor
    while (raiz->esquerda != NULL) {
        raiz = raiz->esquerda;
    }
    return raiz;
}

// Função para deletar um nó da árvore binária
Node* deletarNo(Node* raiz, int dado) {
    // Se a raiz for nula, retorna a própria raiz (nada a deletar)
    if (raiz == NULL) {
        return raiz;
    }

    // Se o dado a ser deletado for menor, continua na subárvore esquerda
    if (dado < raiz->dado) {
        raiz->esquerda = deletarNo(raiz->esquerda, dado);
    } 
    // Se o dado a ser deletado for maior, continua na subárvore direita
    else if (dado > raiz->dado) {
        raiz->direita = deletarNo(raiz->direita, dado);
    } 
    // Se o dado for igual ao dado da raiz, esse é o nó a ser deletado
    else {
        // Caso 1: Nó com zero ou um filho
        if (raiz->esquerda == NULL) {
            Node* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            Node* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }

        // Caso 2: Nó com dois filhos
        Node* temp = encontrarMin(raiz->direita);
        raiz->dado = temp->dado;
        raiz->direita = deletarNo(raiz->direita, temp->dado);
    }

    // Retorna a raiz da árvore após a deleção
    return raiz;
}

// Função para imprimir a árvore em ordem (inorder traversal)
void emOrdem(Node* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerda);      // Percorre a subárvore esquerda
        printf("%d ", raiz->dado);    // Imprime o dado do nó atual
        emOrdem(raiz->direita);       // Percorre a subárvore direita
    }
}

int main() {
    Node* raiz = NULL;

    // Inserindo dados na árvore
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 70);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 60);
    raiz = inserir(raiz, 80);

    // Imprimindo a árvore em ordem
    printf("Árvore em ordem: ");
    emOrdem(raiz);
    printf("\n");

    // Deletando alguns nós e imprimindo a árvore em ordem após cada deleção
    printf("Excluindo 20\n");
    raiz = deletarNo(raiz, 20);
    printf("Árvore em ordem: ");
    emOrdem(raiz);
    printf("\n");

    printf("Excluindo 30\n");
    raiz = deletarNo(raiz, 30);
    printf("Árvore em ordem: ");
    emOrdem(raiz);
    printf("\n");

    printf("Excluindo 50\n");
    raiz = deletarNo(raiz, 50);
    printf("Árvore em ordem: ");
    emOrdem(raiz);
    printf("\n");

    return 0;
}
