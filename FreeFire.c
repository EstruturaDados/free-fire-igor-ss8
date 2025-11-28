*
 * Sistema simples de inventário para um jogo estilo Battle Royale.
 * O jogador tem uma mochila com espaço limitado e pode inserir,
 * remover, listar e buscar itens.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_ITENS 10   // Capacidade máxima da mochila

// Estrutura básica de um item do inventário
typedef struct {
    char nome[30];
    char tipo[20];   // Pode ser: Arma, Munição, Cura...
    int quantidade;
} Item;

// Protótipos das funções
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);
void limparBuffer();

// Programa principal
int main() {
    setlocale(LC_ALL, "Portuguese");

    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    do {
        printf("\n=== MOCHILA (Itens: %d/%d) ===\n", totalItens, MAX_ITENS);
        printf("1 - Coletar item\n");
        printf("2 - Descartar item\n");
        printf("3 - Ver mochila\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 0:
                printf("\nFechando mochila... Boa partida!\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    return 0;
}

// Função para limpar o buffer deixado pelo scanf
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Inserção de um novo item na mochila
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\n[!] A mochila está cheia!\n");
        return;
    }

    printf("\n--- Adicionar Item ---\n");

    printf("Nome: ");
    scanf("%29[^\n]", mochila[*total].nome);
    limparBuffer();

    printf("Tipo (Arma, Municao, Cura...): ");
    scanf("%19[^\n]", mochila[*total].tipo);
    limparBuffer();

    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    limparBuffer();

    (*total)++;

    printf("\nItem adicionado!\n");
    listarItens(mochila, *total);
}

// Remoção de item pelo nome
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\n[!] A mochila está vazia.\n");
        return;
    }

    char nomeRemover[30];
    printf("\n--- Remover Item ---\n");
    printf("Nome do item: ");
    scanf("%29[^\n]", nomeRemover);
    limparBuffer();

    int encontrado = 0;

    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;

            // Desloca os itens para "tampar" o espaço removido
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            (*total)--;
            printf("[OK] Item '%s' removido.\n", nomeRemover);
            break;
        }
    }

    if (!encontrado) {
        printf("[!] Item não encontrado.\n");
    } else {
        listarItens(mochila, *total);
    }
}

// Exibe o conteúdo da mochila
void listarItens(Item mochila[], int total) {
    printf("\n--- Itens da Mochila ---\n");

    if (total == 0) {
        printf("(vazia)\n");
        return;
    }

    printf("%-3s | %-20s | %-15s | %s\n", "ID", "Nome", "Tipo", "Qtd");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i < total; i++) {
        printf("%02d  | %-20s | %-15s | %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }

    printf("-----------------------------------------------------\n");
}

// Busca um item pelo nome
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\n[!] Mochila vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- Buscar Item ---\n");
    printf("Nome do item: ");
    scanf("%29[^\n]", nomeBusca);
    limparBuffer();

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n[Encontrado!]\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            return;
        }
    }

    printf("\n[!] Item '%s' não está na mochila.\n", nomeBusca);
}
