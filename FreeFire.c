#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Definição da struct Item.
 * Armazena informações de um item na mochila do jogador:
 * - nome: Nome do item (string de até 29 caracteres + null terminator).
 * - tipo: Tipo do item (ex: arma, munição, cura; string de até 19 caracteres + null terminator).
 * - quantidade: Quantidade do item (inteiro positivo).
 */
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

/*
 * Função para inserir um item na mochila.
 * Verifica se há espaço disponível e cadastra os dados do item.
 * Retorna 1 se a inserção for bem-sucedida, 0 caso contrário.
 */
int inserirItem(struct Item* mochila, int* totalItens, int capacidade) {
    if (*totalItens >= capacidade) {
        printf("Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return 0;
    }

    struct Item novoItem;
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer

    printf("=== Cadastro de Item ===\n");
    printf("Digite o nome do item: ");
    scanf("%s", novoItem.nome);

    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    scanf("%s", novoItem.tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &novoItem.quantidade);
    while (novoItem.quantidade < 0) { // Valida quantidade não negativa
        printf("Quantidade invalida! Digite um numero maior ou igual a 0: ");
        scanf("%d", &novoItem.quantidade);
    }

    mochila[*totalItens] = novoItem;
    (*totalItens)++;
    printf("Item '%s' adicionado com sucesso!\n", novoItem.nome);
    return 1;
}

/*
 * Função para remover um item da mochila pelo nome.
 * Reorganiza o vetor após remoção para manter a lista contígua.
 * Retorna 1 se a remoção for bem-sucedida, 0 caso contrário.
 */
int removerItem(struct Item* mochila, int* totalItens, const char* nome) {
    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            // Move os itens subsequentes para preencher o espaço
            for (int j = i; j < *totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*totalItens)--;
            printf("Item '%s' removido com sucesso!\n", nome);
            return 1;
        }
    }
    printf("Item '%s' nao encontrado na mochila.\n", nome);
    return 0;
}

/*
 * Função para listar todos os itens na mochila.
 * Exibe os dados de cada item com formatação clara.
 */
void listarItens(struct Item* mochila, int totalItens) {
    printf("\n=== Itens na Mochila ===\n");
    if (totalItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }
    for (int i = 0; i < totalItens; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochila[i].nome);
        printf("  Tipo: %s\n", mochila[i].tipo);
        printf("  Quantidade: %d\n", mochila[i].quantidade);
        printf("\n");
    }
}

/*
 * Função para buscar um item na mochila pelo nome.
 * Realiza busca sequencial e exibe os dados se encontrado.
 * Retorna 1 se encontrado, 0 caso contrário.
 */
int buscarItem(struct Item* mochila, int totalItens, const char* nome) {
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\n=== Item Encontrado ===\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n\n", mochila[i].quantidade);
            return 1;
        }
    }
    printf("Item '%s' nao encontrado na mochila.\n", nome);
    return 0;
}

int main() {
    // Declaração do vetor de structs para a mochila com capacidade para 10 itens
    struct Item mochila[10];
    int totalItens = 0; // Contador de itens na mochila
    const int capacidade = 10; // Capacidade máxima da mochila
    char opcao;
    char nomeBusca[30];

    do {
        // Exibe menu de opções
        printf("\n=== Sistema de Inventario ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao (1-5): ");
        scanf(" %c", &opcao);
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer

        switch (opcao) {
            case '1':
                inserirItem(mochila, &totalItens, capacidade);
                listarItens(mochila, totalItens);
                break;
            case '2':
                printf("Digite o nome do item a remover: ");
                scanf("%s", nomeBusca);
                removerItem(mochila, &totalItens, nomeBusca);
                listarItens(mochila, totalItens);
                break;
            case '3':
                listarItens(mochila, totalItens);
                break;
            case '4':
                printf("Digite o nome do item a buscar: ");
                scanf("%s", nomeBusca);
                buscarItem(mochila, totalItens, nomeBusca);
                break;
            case '5':
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != '5');

    return 0;
}