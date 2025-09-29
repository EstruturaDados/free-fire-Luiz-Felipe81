#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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
 * Definição da struct No para lista encadeada.
 * Contém um Item e um ponteiro para o próximo nó.
 */
struct No {
    struct Item dados;
    struct No* proximo;
};

/*
 * Contadores globais para comparações nas buscas.
 * Usados para comparar desempenho entre busca sequencial e binária.
 */
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

/* === Funções para Vetor (Lista Sequencial) === */

/*
 * Função para inserir um item no vetor.
 * Verifica se há espaço e cadastra os dados do item.
 * Retorna 1 se a inserção for bem-sucedida, 0 caso contrário.
 */
int inserirItemVetor(struct Item* mochila, int* totalItens, int capacidade) {
    if (*totalItens >= capacidade) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
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
        printf("Quantidade inválida! Digite um número maior ou igual a 0: ");
        scanf("%d", &novoItem.quantidade);
    }

    mochila[*totalItens] = novoItem;
    (*totalItens)++;
    printf("Item '%s' adicionado com sucesso!\n", novoItem.nome);
    return 1;
}

/*
 * Função para remover um item do vetor pelo nome.
 * Reorganiza o vetor após remoção para manter a lista contígua.
 * Retorna 1 se a remoção for bem-sucedida, 0 caso contrário.
 */
int removerItemVetor(struct Item* mochila, int* totalItens, const char* nome) {
    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*totalItens)--;
            printf("Item '%s' removido com sucesso!\n", nome);
            return 1;
        }
    }
    printf("Item '%s' não encontrado na mochila.\n", nome);
    return 0;
}

/*
 * Função para listar todos os itens no vetor.
 */
void listarItensVetor(struct Item* mochila, int totalItens) {
    printf("\n=== Itens na Mochila (Vetor) ===\n");
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
 * Função para ordenar o vetor por nome usando Selection Sort.
 * Garante que a busca binária funcione corretamente.
 */
void ordenarVetor(struct Item* mochila, int totalItens) {
    for (int i = 0; i < totalItens - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < totalItens; j++) {
            if (strcmp(mochila[j].nome, mochila[min_idx].nome) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            struct Item temp = mochila[i];
            mochila[i] = mochila[min_idx];
            mochila[min_idx] = temp;
        }
    }
    printf("Mochila ordenada por nome.\n");
}

/*
 * Função para buscar um item no vetor por nome (busca sequencial).
 * Conta o número de comparações realizadas.
 * Retorna 1 se encontrado, 0 caso contrário.
 */
int buscarSequencialVetor(struct Item* mochila, int totalItens, const char* nome) {
    comparacoesSequencial = 0;
    for (int i = 0; i < totalItens; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\n=== Item Encontrado (Busca Sequencial) ===\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("Comparações realizadas: %d\n\n", comparacoesSequencial);
            return 1;
        }
    }
    printf("Item '%s' não encontrado na mochila. Comparações: %d\n", nome, comparacoesSequencial);
    return 0;
}

/*
 * Função para buscar um item no vetor por nome (busca binária).
 * Requer vetor ordenado. Conta o número de comparações.
 * Retorna 1 se encontrado, 0 caso contrário.
 */
int buscarBinariaVetor(struct Item* mochila, int totalItens, const char* nome) {
    comparacoesBinaria = 0;
    int esquerda = 0, direita = totalItens - 1;
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) {
            printf("\n=== Item Encontrado (Busca Binária) ===\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Comparações realizadas: %d\n\n", comparacoesBinaria);
            return 1;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    printf("Item '%s' não encontrado na mochila. Comparações: %d\n", nome, comparacoesBinaria);
    return 0;
}

/* === Funções para Lista Encadeada === */

/*
 * Função para inserir um item na lista encadeada.
 * Adiciona no início para simplicidade e eficiência.
 * Retorna o novo início da lista.
 */
struct No* inserirItemLista(struct No* inicio) {
    struct No* novoNo = (struct No*)malloc(sizeof(struct No));
    if (novoNo == NULL) {
        printf("Erro na alocação de memória!\n");
        return inicio;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer

    printf("=== Cadastro de Item ===\n");
    printf("Digite o nome do item: ");
    scanf("%s", novoNo->dados.nome);

    printf("Digite o tipo do item (ex: arma, municao, cura): ");
    scanf("%s", novoNo->dados.tipo);

    printf("Digite a quantidade: ");
    scanf("%d", &novoNo->dados.quantidade);
    while (novoNo->dados.quantidade < 0) {
        printf("Quantidade inválida! Digite um número maior ou igual a 0: ");
        scanf("%d", &novoNo->dados.quantidade);
    }

    novoNo->proximo = inicio;
    printf("Item '%s' adicionado com sucesso!\n", novoNo->dados.nome);
    return novoNo;
}

/*
 * Função para remover um item da lista encadeada pelo nome.
 * Retorna o novo início da lista após a remoção.
 */
struct No* removerItemLista(struct No* inicio, const char* nome) {
    struct No* atual = inicio;
    struct No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) {
                inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Item '%s' removido com sucesso!\n", nome);
            return inicio;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item '%s' não encontrado na mochila.\n", nome);
    return inicio;
}

/*
 * Função para listar todos os itens na lista encadeada.
 */
void listarItensLista(struct No* inicio) {
    printf("\n=== Itens na Mochila (Lista Encadeada) ===\n");
    if (inicio == NULL) {
        printf("Mochila vazia.\n");
        return;
    }
    struct No* atual = inicio;
    int i = 1;
    while (atual != NULL) {
        printf("Item %d:\n", i++);
        printf("  Nome: %s\n", atual->dados.nome);
        printf("  Tipo: %s\n", atual->dados.tipo);
        printf("  Quantidade: %d\n", atual->dados.quantidade);
        printf("\n");
        atual = atual->proximo;
    }
}

/*
 * Função para buscar um item na lista encadeada por nome (busca sequencial).
 * Conta o número de comparações realizadas.
 * Retorna 1 se encontrado, 0 caso contrário.
 */
int buscarSequencialLista(struct No* inicio, const char* nome) {
    comparacoesSequencial = 0;
    struct No* atual = inicio;
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("\n=== Item Encontrado (Busca Sequencial) ===\n");
            printf("Nome: %s\n", atual->dados.nome);
            printf("Tipo: %s\n", atual->dados.tipo);
            printf("Quantidade: %d\n", atual->dados.quantidade);
            printf("Comparações realizadas: %d\n\n", comparacoesSequencial);
            return 1;
        }
        atual = atual->proximo;
    }
    printf("Item '%s' não encontrado na mochila. Comparações: %d\n", nome, comparacoesSequencial);
    return 0;
}

/*
 * Função para liberar a memória da lista encadeada.
 */
void liberarLista(struct No* inicio) {
    struct No* atual = inicio;
    while (atual != NULL) {
        struct No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}

int main() {
    // Estruturas para vetor
    struct Item mochilaVetor[10];
    int totalItensVetor = 0;
    const int capacidadeVetor = 10;

    // Estrutura para lista encadeada
    struct No* mochilaLista = NULL;

    char opcao, estrutura;
    char nomeBusca[30];

    do {
        // Escolha entre vetor e lista
        printf("\n=== Sistema de Inventário ===\n");
        printf("Escolha a estrutura de dados:\n");
        printf("1. Vetor\n");
        printf("2. Lista Encadeada\n");
        printf("Escolha (1-2): ");
        scanf(" %c", &estrutura);
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer

        if (estrutura != '1' && estrutura != '2') {
            printf("Estrutura inválida! Tente novamente.\n");
            continue;
        }

        // Exibe menu de operações
        printf("\n=== Operações ===\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item (Sequencial)\n");
        if (estrutura == '1') printf("5. Ordenar vetor e buscar binária\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf(" %c", &opcao);
        while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer

        if (estrutura == '1') { // Vetor
            switch (opcao) {
                case '1':
                    inserirItemVetor(mochilaVetor, &totalItensVetor, capacidadeVetor);
                    listarItensVetor(mochilaVetor, totalItensVetor);
                    break;
                case '2':
                    printf("Digite o nome do item a remover: ");
                    scanf("%s", nomeBusca);
                    removerItemVetor(mochilaVetor, &totalItensVetor, nomeBusca);
                    listarItensVetor(mochilaVetor, totalItensVetor);
                    break;
                case '3':
                    listarItensVetor(mochilaVetor, totalItensVetor);
                    break;
                case '4':
                    printf("Digite o nome do item a buscar: ");
                    scanf("%s", nomeBusca);
                    buscarSequencialVetor(mochilaVetor, totalItensVetor, nomeBusca);
                    break;
                case '5':
                    ordenarVetor(mochilaVetor, totalItensVetor);
                    listarItensVetor(mochilaVetor, totalItensVetor);
                    printf("Digite o nome do item a buscar (binária): ");
                    scanf("%s", nomeBusca);
                    buscarBinariaVetor(mochilaVetor, totalItensVetor, nomeBusca);
                    break;
                case '6':
                    printf("Saindo do sistema...\n");
                    break;
                default:
                    printf("Opção inválida! Tente novamente.\n");
            }
        } else { // Lista Encadeada
            switch (opcao) {
                case '1':
                    mochilaLista = inserirItemLista(mochilaLista);
                    listarItensLista(mochilaLista);
                    break;
                case '2':
                    printf("Digite o nome do item a remover: ");
                    scanf("%s", nomeBusca);
                    mochilaLista = removerItemLista(mochilaLista, nomeBusca);
                    listarItensLista(mochilaLista);
                    break;
                case '3':
                    listarItensLista(mochilaLista);
                    break;
                case '4':
                    printf("Digite o nome do item a buscar: ");
                    scanf("%s", nomeBusca);
                    buscarSequencialLista(mochilaLista, nomeBusca);
                    break;
                case '6':
                    printf("Saindo do sistema...\n");
                    break;
                default:
                    printf("Opção inválida! Tente novamente.\n");
            }
        }
    } while (opcao != '6');

    // Libera memória da lista encadeada
    liberarLista(mochilaLista);
    return 0;
}