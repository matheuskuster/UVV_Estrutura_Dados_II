#include <stdio.h>
#include <stdlib.h>

// Define a ordem da árvore B (ordem mínima = 3)
#define ORDEM 3

// Estrutura de um nó da árvore B
typedef struct No {
    int *chaves;            // Array de chaves
    struct No **filhos;     // Array de ponteiros para os filhos
    int n_chaves;           // Número atual de chaves
    int eh_folha;           // Flag para indicar se é nó folha
} No;

// Estrutura da árvore B
typedef struct ArvoreB {
    No *raiz;              // Ponteiro para a raiz
    int ordem;             // Ordem da árvore
    int min_chaves;        // Mínimo de chaves por nó (exceto raiz)
    int max_chaves;        // Máximo de chaves por nó
} ArvoreB;

// Função para criar um novo nó
No* criarNo(int eh_folha) {
    No* no = (No*)malloc(sizeof(No));
    
    // Aloca arrays com tamanho baseado na ordem
    no->chaves = (int*)malloc(sizeof(int) * (ORDEM - 1));
    no->filhos = (No**)malloc(sizeof(No*) * ORDEM);
    no->n_chaves = 0;
    no->eh_folha = eh_folha;
    
    return no;
}

// Função para criar uma nova árvore B
ArvoreB* criarArvoreB() {
    ArvoreB* arvore = (ArvoreB*)malloc(sizeof(ArvoreB));
    No* raiz = criarNo(1);  // Inicialmente a raiz é uma folha
    
    arvore->raiz = raiz;
    arvore->ordem = ORDEM;
    arvore->min_chaves = ORDEM/2 - 1;
    arvore->max_chaves = ORDEM - 1;
    
    return arvore;
}

// Função para dividir um nó filho
void dividirFilho(No* pai, int indice, No* filho) {
    // Cria novo nó que vai receber metade das chaves
    No* novo = criarNo(filho->eh_folha);
    novo->n_chaves = ORDEM/2 - 1;
    
    // Copia as chaves maiores para o novo nó
    for (int j = 0; j < ORDEM/2 - 1; j++)
        novo->chaves[j] = filho->chaves[j + ORDEM/2];
    
    // Se não for folha, move também os ponteiros dos filhos
    if (!filho->eh_folha) {
        for (int j = 0; j < ORDEM/2; j++)
            novo->filhos[j] = filho->filhos[j + ORDEM/2];
    }
    
    filho->n_chaves = ORDEM/2 - 1;
    
    // Move os ponteiros do pai para abrir espaço para o novo nó
    for (int j = pai->n_chaves; j >= indice + 1; j--)
        pai->filhos[j + 1] = pai->filhos[j];
    
    pai->filhos[indice + 1] = novo;
    
    // Move as chaves do pai para inserir a chave mediana
    for (int j = pai->n_chaves - 1; j >= indice; j--)
        pai->chaves[j + 1] = pai->chaves[j];
    
    pai->chaves[indice] = filho->chaves[ORDEM/2 - 1];
    pai->n_chaves++;
}

// Função auxiliar para inserção em nó não cheio
void inserirNaoCheio(No* no, int chave) {
    int i = no->n_chaves - 1;
    
    if (no->eh_folha) {
        // Encontra a posição correta e move as chaves maiores
        while (i >= 0 && no->chaves[i] > chave) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        
        no->chaves[i + 1] = chave;
        no->n_chaves++;
    } else {
        // Encontra o filho correto para descer
        while (i >= 0 && no->chaves[i] > chave)
            i--;
        i++;
        
        // Se o filho está cheio, divide primeiro
        if (no->filhos[i]->n_chaves == ORDEM - 1) {
            dividirFilho(no, i, no->filhos[i]);
            if (chave > no->chaves[i])
                i++;
        }
        inserirNaoCheio(no->filhos[i], chave);
    }
}

// Função principal de inserção
void inserir(ArvoreB* arvore, int chave) {
    No* raiz = arvore->raiz;
    
    // Se a raiz está cheia, cria nova raiz
    if (raiz->n_chaves == ORDEM - 1) {
        No* nova_raiz = criarNo(0);
        arvore->raiz = nova_raiz;
        nova_raiz->filhos[0] = raiz;
        dividirFilho(nova_raiz, 0, raiz);
        inserirNaoCheio(nova_raiz, chave);
    } else {
        inserirNaoCheio(raiz, chave);
    }
}

// Função para buscar uma chave na árvore
No* buscar(No* no, int chave) {
    int i = 0;
    
    // Encontra a primeira chave maior ou igual
    while (i < no->n_chaves && chave > no->chaves[i])
        i++;
    
    // Se encontrou a chave
    if (i < no->n_chaves && chave == no->chaves[i])
        return no;
    
    // Se é folha e não encontrou, não existe
    if (no->eh_folha)
        return NULL;
    
    // Desce para o filho apropriado
    return buscar(no->filhos[i], chave);
}

// Função para percorrer a árvore em ordem
void percorrerEmOrdem(No* no) {
    int i;
    
    if (no != NULL) {
        for (i = 0; i < no->n_chaves; i++) {
            if (!no->eh_folha)
                percorrerEmOrdem(no->filhos[i]);
            printf("%d ", no->chaves[i]);
        }
        
        if (!no->eh_folha)
            percorrerEmOrdem(no->filhos[i]);
    }
}

// Função principal para teste
int main() {
    ArvoreB* arvore = criarArvoreB();
    
    // Inserindo alguns valores de teste
    inserir(arvore, 10);
    inserir(arvore, 20);
    inserir(arvore, 5);
    inserir(arvore, 6);
    inserir(arvore, 12);
    inserir(arvore, 30);
    inserir(arvore, 7);
    inserir(arvore, 17);
    
    printf("Percorrendo a árvore em ordem:\n");
    percorrerEmOrdem(arvore->raiz);
    printf("\n");
    
    // Testando a busca
    int chave_busca = 6;
    No* resultado = buscar(arvore->raiz, chave_busca);
    if (resultado != NULL)
        printf("Chave %d encontrada!\n", chave_busca);
    else
        printf("Chave %d não encontrada.\n", chave_busca);
    
    return 0;
}