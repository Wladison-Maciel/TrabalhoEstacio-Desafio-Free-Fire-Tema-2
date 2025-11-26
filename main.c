#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// ------------------------------------------------------------
// STRUCT DO ITEM
// ------------------------------------------------------------
// Representa um objeto dentro da mochila do jogador
typedef struct {
    char nome[30];
    char tipo[20];     // ex: arma, munição, cura
    int quantidade;
} Item;

// Vetor global de itens e contador
Item mochila[MAX_ITENS];
int totalItens = 0;

// ------------------------------------------------------------
// FUNÇÃO PARA INSERIR ITEM
// ------------------------------------------------------------
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\n[ERRO] A mochila está cheia! Nao é possível adicionar mais itens.\n\n");
        return;
    }

    Item novo;

    printf("\n=== CADASTRO DE ITEM ===\n");
    printf("Nome do item: ");
    scanf("%s", novo.nome);

    printf("Tipo do item (arma, municao, cura...): ");
    scanf("%s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochila[totalItens] = novo;
    totalItens++;

    printf("\n[SUCESSO] Item cadastrado com sucesso!\n\n");
}

// ------------------------------------------------------------
// FUNÇÃO PARA LISTAR ITENS
// ------------------------------------------------------------
void listarItens() {
    printf("\n=== ITENS NA MOCHILA ===\n");

    if (totalItens == 0) {
        printf("A mochila está vazia.\n\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf("[%d] Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("\n");
}

// ------------------------------------------------------------
// FUNÇÃO DE BUSCA SEQUENCIAL POR NOME
// ------------------------------------------------------------
void buscarItem() {
    if (totalItens == 0) {
        printf("\n[AVISO] A mochila está vazia, não há itens para buscar.\n\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item para buscar: ");
    scanf("%s", nomeBusca);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n=== ITEM ENCONTRADO ===\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\n[ERRO] Item '%s' não encontrado na mochila.\n\n", nomeBusca);
}

// ------------------------------------------------------------
// FUNÇÃO PARA REMOVER ITEM POR NOME
// ------------------------------------------------------------
void removerItem() {
    if (totalItens == 0) {
        printf("\n[ERRO] A mochila está vazia, nada para remover.\n\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf("%s", nomeRemover);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            // Deslocar os itens para a esquerda
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("\n[SUCESSO] Item removido com sucesso!\n\n");
            return;
        }
    }

    printf("\n[ERRO] Não foi possível remover, item não encontrado.\n\n");
}

// ------------------------------------------------------------
// FUNÇÃO PRINCIPAL (MENU)
// ------------------------------------------------------------
int main() {
    int opcao;

    do {
        printf("====================================\n");
        printf("        SISTEMA DE INVENTÁRIO       \n");
        printf("====================================\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\n[ERRO] Opção inválida!\n\n");
        }

    } while (opcao != 0);

    return 0;
}
