#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

// ==========================================================
// STRUCT DO ITEM
// ==========================================================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ==========================================================
// STRUCT DO NÓ (LISTA ENCADEADA)
// ==========================================================
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ==========================================================
// VARIÁVEIS GLOBAIS
// ==========================================================
Item mochilaVetor[MAX];
int totalVetor = 0;

No* mochilaLista = NULL;

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;


// ==========================================================
// FUNÇÕES PARA O VETOR
// ==========================================================

// Inserir item no vetor
void inserirItemVetor() {
    if (totalVetor >= MAX) {
        printf("\n[ERRO] Vetor cheio.\n");
        return;
    }

    Item novo;
    printf("\nNome: ");
    scanf("%s", novo.nome);
    printf("Tipo: ");
    scanf("%s", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[totalVetor] = novo;
    totalVetor++;

    printf("\n[SUCESSO] Item inserido no vetor.\n");
}

// Remover item pelo nome no vetor
void removerItemVetor() {
    if (totalVetor == 0) {
        printf("\n[ERRO] Vetor vazio.\n");
        return;
    }

    char nome[30];
    printf("\nNome do item para remover: ");
    scanf("%s", nome);

    for (int i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < totalVetor - 1; j++) {
                mochilaVetor[j] = mochilaVetor[j + 1];
            }
            totalVetor--;
            printf("\n[SUCESSO] Item removido.\n");
            return;
        }
    }

    printf("\n[ERRO] Item não encontrado.\n");
}

// Listar itens do vetor
void listarItensVetor() {
    printf("\n=== Itens no Vetor ===\n");
    if (totalVetor == 0) {
        printf("Vazio.\n");
        return;
    }

    for (int i = 0; i < totalVetor; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
}

// Busca sequencial no vetor
void buscarSequencialVetor() {
    comparacoesSequencial = 0;
    char nome[30];
    printf("\nNome do item para buscar: ");
    scanf("%s", nome);

    for (int i = 0; i < totalVetor; i++) {
        comparacoesSequencial++;

        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochilaVetor[i].nome, mochilaVetor[i].tipo, mochilaVetor[i].quantidade);
            printf("Comparações: %d\n", comparacoesSequencial);
            return;
        }
    }

    printf("\nItem NÃO encontrado.\n");
    printf("Comparações: %d\n", comparacoesSequencial);
}

// Ordenar vetor por nome (Bubble Sort)
void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = 0; j < totalVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
            }
        }
    }
    printf("\n[OK] Vetor ordenado alfabeticamente.\n");
}

// Busca binária no vetor
void buscarBinariaVetor() {
    comparacoesBinaria = 0;
    char nome[30];
    printf("\nNome para busca binária: ");
    scanf("%s", nome);

    int inicio = 0, fim = totalVetor - 1;

    while (inicio <= fim) {
        comparacoesBinaria++;

        int meio = (inicio + fim) / 2;
        int cmp = strcmp(nome, mochilaVetor[meio].nome);

        if (cmp == 0) {
            printf("\nItem encontrado (BINÁRIA):\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochilaVetor[meio].nome, mochilaVetor[meio].tipo, mochilaVetor[meio].quantidade);
            printf("Comparações: %d\n", comparacoesBinaria);
            return;
        }
        else if (cmp > 0) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }

    printf("\nItem NÃO encontrado.\n");
    printf("Comparações: %d\n", comparacoesBinaria);
}



// ==========================================================
// FUNÇÕES PARA A LISTA ENCADEADA
// ==========================================================

// Inserir na lista encadeada
void inserirItemLista() {
    No* novo = (No*)malloc(sizeof(No));

    printf("\nNome: ");
    scanf("%s", novo->dados.nome);
    printf("Tipo: ");
    scanf("%s", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = mochilaLista;
    mochilaLista = novo;

    printf("\n[SUCESSO] Item inserido na lista encadeada.\n");
}

// Remover item da lista encadeada
void removerItemLista() {
    if (mochilaLista == NULL) {
        printf("\n[ERRO] Lista vazia.\n");
        return;
    }

    char nome[30];
    printf("\nNome para remover: ");
    scanf("%s", nome);

    No* atual = mochilaLista;
    No* anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("\n[ERRO] Item não encontrado.\n");
        return;
    }

    if (anterior == NULL)
        mochilaLista = atual->proximo;
    else
        anterior->proximo = atual->proximo;

    free(atual);
    printf("\n[SUCESSO] Item removido da lista.\n");
}

// Listar itens da lista
void listarItensLista() {
    printf("\n=== Itens da Lista Encadeada ===\n");

    No* atual = mochilaLista;
    if (atual == NULL) {
        printf("Vazia.\n");
        return;
    }

    while (atual != NULL) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);

        atual = atual->proximo;
    }
}

// Busca sequencial na lista encadeada
void buscarSequencialLista() {
    comparacoesSequencial = 0;
    char nome[30];
    printf("\nNome para buscar: ");
    scanf("%s", nome);

    No* atual = mochilaLista;

    while (atual != NULL) {
        comparacoesSequencial++;

        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("\nItem encontrado:\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   atual->dados.nome,
                   atual->dados.tipo,
                   atual->dados.quantidade);
            printf("Comparações: %d\n", comparacoesSequencial);
            return;
        }

        atual = atual->proximo;
    }

    printf("\nItem NÃO encontrado.\n");
    printf("Comparações: %d\n", comparacoesSequencial);
}



// ==========================================================
// MENU PRINCIPAL
// ==========================================================

int main() {
    int estrutura = -1;
    int opcao;

    while (estrutura != 0) {
        printf("\n====================================\n");
        printf("   ESCOLHA A ESTRUTURA DA MOCHILA   \n");
        printf("====================================\n");
        printf("1 - Mochila com Vetor\n");
        printf("2 - Mochila com Lista Encadeada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &estrutura);

        if (estrutura == 1) {
            do {
                printf("\n--- MENU (VETOR) ---\n");
                printf("1 - Inserir\n");
                printf("2 - Remover\n");
                printf("3 - Listar\n");
                printf("4 - Buscar Sequencial\n");
                printf("5 - Ordenar\n");
                printf("6 - Busca Binária\n");
                printf("0 - Voltar\n");
                printf("Opção: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirItemVetor(); break;
                    case 2: removerItemVetor(); break;
                    case 3: listarItensVetor(); break;
                    case 4: buscarSequencialVetor(); break;
                    case 5: ordenarVetor(); break;
                    case 6: buscarBinariaVetor(); break;
                }
            } while (opcao != 0);
        }

        else if (estrutura == 2) {
            do {
                printf("\n--- MENU (LISTA ENCADEADA) ---\n");
                printf("1 - Inserir\n");
                printf("2 - Remover\n");
                printf("3 - Listar\n");
                printf("4 - Buscar Sequencial\n");
                printf("0 - Voltar\n");
                printf("Opção: ");
                scanf("%d", &opcao);

                switch (opcao) {
                    case 1: inserirItemLista(); break;
                    case 2: removerItemLista(); break;
                    case 3: listarItensLista(); break;
                    case 4: buscarSequencialLista(); break;
                }
            } while (opcao != 0);
        }
    }

    printf("\nEncerrando...\n");
    return 0;
}
