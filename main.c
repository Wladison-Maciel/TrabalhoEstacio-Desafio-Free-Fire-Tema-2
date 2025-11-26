/*
  Torre de Resgate - Ordenação e Busca
  - Implementa: Bubble Sort (nome), Insertion Sort (tipo), Selection Sort (prioridade)
  - Busca binária após ordenar por nome
  - Mostra número de comparações e tempo de execução (clock)
  - Uso de fgets para entrada de strings (até 20 componentes)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20
#define NOME_TAM 30
#define TIPO_TAM 20

typedef struct {
    char nome[NOME_TAM];
    char tipo[TIPO_TAM];
    int prioridade; // 1..10
} Componente;

/* ----- Funções utilitárias ----- */

// Remove '\n' final deixado por fgets
void trimNewline(char *s) {
    size_t len = strlen(s);
    if (len == 0) return;
    if (s[len - 1] == '\n') s[len - 1] = '\0';
}

// Mostra o vetor de componentes formatado
void mostrarComponentes(Componente vet[], int n) {
    if (n == 0) {
        printf("\n[!] Nenhum componente cadastrado.\n");
        return;
    }
    printf("\n--- Componentes (total: %d) ---\n", n);
    printf("%-3s | %-28s | %-12s | %-9s\n", "ID", "NOME", "TIPO", "PRIORIDADE");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-3d | %-28s | %-12s | %-9d\n", i, vet[i].nome, vet[i].tipo, vet[i].prioridade);
    }
    printf("----------------------------------------------------------------\n");
}

/* ----- Algoritmos de ordenação (retornam comparações e tempo) ----- */

/*
  Bubble Sort por nome (alfabético)
  conta comparações de strings (cada strcmp conta 1 comparação lógica aqui)
*/
void bubbleSortNome(Componente vet[], int n, long long *comparacoes, double *tempoSegundos) {
    *comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < n - 1; i++) {
        // otimização: parar se já estiver ordenado
        int trocou = 0;
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++; // comparação entre vet[j].nome e vet[j+1].nome
            if (strcmp(vet[j].nome, vet[j + 1].nome) > 0) {
                Componente tmp = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = tmp;
                trocou = 1;
            }
        }
        if (!trocou) break;
    }

    clock_t fim = clock();
    *tempoSegundos = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

/*
  Insertion Sort por tipo (string)
  cada comparação de tipo é contada
*/
void insertionSortTipo(Componente vet[], int n, long long *comparacoes, double *tempoSegundos) {
    *comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 1; i < n; i++) {
        Componente key = vet[i];
        int j = i - 1;
        // enquanto vet[j].tipo > key.tipo (alfabético)
        while (j >= 0) {
            (*comparacoes)++; // contagem da comparação de strings
            if (strcmp(vet[j].tipo, key.tipo) > 0) {
                vet[j + 1] = vet[j];
                j--;
            } else {
                break;
            }
        }
        vet[j + 1] = key;
    }

    clock_t fim = clock();
    *tempoSegundos = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

/*
  Selection Sort por prioridade (inteiro)
  contando comparações entre prioridades
*/
void selectionSortPrioridade(Componente vet[], int n, long long *comparacoes, double *tempoSegundos) {
    *comparacoes = 0;
    clock_t inicio = clock();

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (vet[j].prioridade < vet[minIdx].prioridade) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Componente tmp = vet[i];
            vet[i] = vet[minIdx];
            vet[minIdx] = tmp;
        }
    }

    clock_t fim = clock();
    *tempoSegundos = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

/* ----- Busca binária por nome (após ordenar por nome) ----- 
   Retorna índice se encontrado, -1 caso contrário.
   comparacoes recebe o número de comparações realizadas.
*/
int buscaBinariaPorNome(Componente vet[], int n, const char *chave, long long *comparacoes) {
    int inicio = 0, fim = n - 1;
    *comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        (*comparacoes)++; // comparação entre chave e vet[meio].nome
        int cmp = strcmp(chave, vet[meio].nome);
        if (cmp == 0) {
            return meio;
        } else if (cmp > 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    return -1;
}

/* ----- Entrada de dados ----- */

// Cadastra 1 componente (usa fgets)
void cadastrarComponente(Componente vet[], int *n) {
    if (*n >= MAX_COMPONENTES) {
        printf("\n[!] Capacidade máxima atingida (%d componentes).\n", MAX_COMPONENTES);
        return;
    }
    char buffer[128];

    printf("\nCadastro do componente #%d\n", (*n));
    printf("Nome (max %d chars): ", NOME_TAM - 1);
    if (!fgets(buffer, sizeof(buffer), stdin)) return;
    trimNewline(buffer);
    strncpy(vet[*n].nome, buffer, NOME_TAM);
    vet[*n].nome[NOME_TAM - 1] = '\0';

    printf("Tipo (max %d chars): ", TIPO_TAM - 1);
    if (!fgets(buffer, sizeof(buffer), stdin)) return;
    trimNewline(buffer);
    strncpy(vet[*n].tipo, buffer, TIPO_TAM);
    vet[*n].tipo[TIPO_TAM - 1] = '\0';

    printf("Prioridade (1-10): ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return;
    vet[*n].prioridade = atoi(buffer);
    if (vet[*n].prioridade < 1) vet[*n].prioridade = 1;
    if (vet[*n].prioridade > 10) vet[*n].prioridade = 10;

    (*n)++;
    printf("[OK] Componente cadastrado.\n");
}

/* ----- Função principal (menu) ----- */

int main() {
    Componente componentes[MAX_COMPONENTES];
    int qtd = 0;
    int opcao;
    int rodando = 1;
    // flag para saber se vetor está ordenado por nome (para busca binária)
    int ordenadoPorNome = 0;

    printf("=== MÓDULO: MONTAGEM DA TORRE DE RESGATE ===\n");

    while (rodando) {
        printf("\nMenu principal:\n");
        printf("1 - Cadastrar componente\n");
        printf("2 - Listar componentes\n");
        printf("3 - Ordenar com Bubble Sort (por NOME)\n");
        printf("4 - Ordenar com Insertion Sort (por TIPO)\n");
        printf("5 - Ordenar com Selection Sort (por PRIORIDADE)\n");
        printf("6 - Busca binária por NOME (requer ordenação por NOME)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");

        char linha[64];
        if (!fgets(linha, sizeof(linha), stdin)) break;
        opcao = atoi(linha);

        switch (opcao) {
            case 1:
                cadastrarComponente(componentes, &qtd);
                ordenadoPorNome = 0;
                break;

            case 2:
                mostrarComponentes(componentes, qtd);
                break;

            case 3: {
                if (qtd == 0) { printf("\n[!] Nenhum componente para ordenar.\n"); break; }
                long long comps = 0; double tempo = 0.0;
                bubbleSortNome(componentes, qtd, &comps, &tempo);
                printf("\n[OK] Bubble Sort (por NOME) concluído.\n");
                printf("Comparações: %lld | Tempo: %.6f s\n", comps, tempo);
                ordenadoPorNome = 1;
                mostrarComponentes(componentes, qtd);
                break;
            }

            case 4: {
                if (qtd == 0) { printf("\n[!] Nenhum componente para ordenar.\n"); break; }
                long long comps = 0; double tempo = 0.0;
                insertionSortTipo(componentes, qtd, &comps, &tempo);
                printf("\n[OK] Insertion Sort (por TIPO) concluído.\n");
                printf("Comparações: %lld | Tempo: %.6f s\n", comps, tempo);
                ordenadoPorNome = 0;
                mostrarComponentes(componentes, qtd);
                break;
            }

            case 5: {
                if (qtd == 0) { printf("\n[!] Nenhum componente para ordenar.\n"); break; }
                long long comps = 0; double tempo = 0.0;
                selectionSortPrioridade(componentes, qtd, &comps, &tempo);
                printf("\n[OK] Selection Sort (por PRIORIDADE) concluído.\n");
                printf("Comparações: %lld | Tempo: %.6f s\n", comps, tempo);
                ordenadoPorNome = 0;
                mostrarComponentes(componentes, qtd);
                break;
            }

            case 6: {
                if (qtd == 0) { printf("\n[!] Nenhum componente cadastrado.\n"); break; }
                if (!ordenadoPorNome) {
                    printf("\n[!] ATENÇÃO: a busca binária exige que o vetor esteja ordenado por NOME.\n");
                    printf("Deseja ordenar agora com Bubble Sort por NOME? (s/n): ");
                    char resp[8];
                    if (!fgets(resp, sizeof(resp), stdin)) break;
                    if (resp[0] == 's' || resp[0] == 'S') {
                        long long compsTemp; double tempoTemp;
                        bubbleSortNome(componentes, qtd, &compsTemp, &tempoTemp);
                        printf("[OK] Ordenado por NOME. Comparações: %lld | Tempo: %.6f s\n", compsTemp, tempoTemp);
                        ordenadoPorNome = 1;
                    } else {
                        printf("[!] Cancelado: não foi feita a ordenação por NOME.\n");
                        break;
                    }
                }

                // pedir nome chave
                char chave[128];
                printf("\nDigite o NOME do componente-chave para buscar (ex: chip central): ");
                if (!fgets(chave, sizeof(chave), stdin)) break;
                trimNewline(chave);

                long long compsBusca = 0;
                int idx = buscaBinariaPorNome(componentes, qtd, chave, &compsBusca);
                if (idx >= 0) {
                    printf("\n[ENCONTRADO] Componente-chave:\n");
                    printf("Nome: %s | Tipo: %s | Prioridade: %d\n",
                           componentes[idx].nome, componentes[idx].tipo, componentes[idx].prioridade);
                    printf("Comparações (busca binária): %lld\n", compsBusca);
                } else {
                    printf("\n[NAO ENCONTRADO] O componente '%s' não está presente.\n", chave);
                    printf("Comparações (busca binária): %lld\n", compsBusca);
                }
                break;
            }

            case 0:
                rodando = 0;
                break;

            default:
                printf("\n[ERRO] Opção inválida. Tente novamente.\n");
        }
    }

    printf("\nEncerrando módulo. Boa sorte na montagem da torre!\n");
    return 0;
}
