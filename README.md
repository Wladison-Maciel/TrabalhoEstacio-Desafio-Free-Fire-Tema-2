# 🚀 Ultimate Escape Tower — Sistema de Ordenação e Busca em C

Este projeto implementa o módulo avançado de organização dos componentes da **torre de fuga**, simulando um momento crítico de um jogo de sobrevivência.  
O objetivo é demonstrar na prática:

- Comparação de diferentes **algoritmos de ordenação**
- Aplicação de **busca binária otimizada**
- **Análise de desempenho** (comparações + tempo)
- Priorização inteligente de componentes para ativação da torre de resgate

---

## 🧠 Funcionalidades

- 🛠️ Cadastro de até **20 componentes**
- 🔤 **Três algoritmos de ordenação**, cada um com critério diferente:
  - **Bubble Sort** → ordenação por *nome*
  - **Insertion Sort** → ordenação por *tipo*
  - **Selection Sort** → ordenação por *prioridade*
- 🔍 **Busca binária** após ordenação por nome
- 📊 Contagem de comparações em:
  - Ordenações
  - Busca binária
- ⏱️ Medição de tempo com `clock()`
- 📋 Exibição organizada dos componentes
- 🧭 Verificação automática da presença do componente-chave

---

## 📦 Estrutura da `struct Componente`

| Campo        | Tipo        | Descrição                                  |
|--------------|-------------|----------------------------------------------|
| `nome`       | `char[30]`  | Nome do componente (ex: "chip central")     |
| `tipo`       | `char[20]`  | Tipo/categoria (controle, suporte...)       |
| `prioridade` | `int`       | Grau de importância (1 a 10)                |

---

## 🔧 Funções principais

| Função | Descrição |
|--------|-----------|
| `bubbleSortNome()` | Ordena componentes por nome (Bubble Sort) |
| `insertionSortTipo()` | Ordena por tipo (Insertion Sort) |
| `selectionSortPrioridade()` | Ordena por prioridade (Selection Sort) |
| `buscaBinariaPorNome()` | Busca específica por nome, via busca binária |
| `mostrarComponentes()` | Lista todos os componentes formatados |
| `medirTempo()` | Mede tempo + comparações de cada algoritmo |

---

## 🔍 Comparação de estratégias de ordenação

O sistema permite que o jogador escolha a estratégia mais eficiente para seu cenário, analisando:

- Quantidade de comparações realizadas  
- Tempo total gasto  
- Eficiência geral de cada algoritmo  

Ideal para entender, na prática, as diferenças entre ordenação simples e mais eficiente.

---

## 🛠️ Tecnologias Utilizadas

- **Linguagem C**
- Bibliotecas:
  - `stdio.h`
  - `stdlib.h`
  - `string.h`
  - `time.h`

---

## ▶️ Como executar

Compile o programa usando GCC:

```bash
gcc main.c -o main
```

```bash
./main
```