#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Definição da struct Componente.
 * Armazena informações de um componente para a torre de fuga:
 * - nome: Nome do componente (string de até 29 caracteres + null terminator, pode conter espaços).
 * - tipo: Tipo do componente (ex: controle, suporte, propulsão; string de até 19 caracteres + null terminator, pode conter espaços).
 * - prioridade: Prioridade do componente (inteiro de 1 a 10).
 */
struct Componente {
    char nome[30];
    char tipo[20];
    int prioridade;
};

/*
 * Função para remover o caractere de nova linha de uma string lida com fgets.
 */
void removerNovaLinha(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/*
 * Função para inserir um componente no vetor.
 * Verifica se há espaço e cadastra os dados do componente usando fgets para strings.
 * Retorna 1 se a inserção for bem-sucedida, 0 caso contrário.
 */
int inserirComponente(struct Componente* torre, int* totalComponentes, int capacidade) {
    if (*totalComponentes >= capacidade) {
        printf("Capacidade maxima atingida! Nao e possivel adicionar mais componentes.\n");
        return 0;
    }

    struct Componente novoComponente;

    printf("=== Cadastro de Componente ===\n");
    printf("Digite o nome do componente: ");
    fgets(novoComponente.nome, sizeof(novoComponente.nome), stdin);
    removerNovaLinha(novoComponente.nome);

    printf("Digite o tipo do componente (ex: controle, suporte, propulsao): ");
    fgets(novoComponente.tipo, sizeof(novoComponente.tipo), stdin);
    removerNovaLinha(novoComponente.tipo);

    printf("Digite a prioridade (1 a 10): ");
    scanf("%d", &novoComponente.prioridade);
    while (novoComponente.prioridade < 1 || novoComponente.prioridade > 10) {
        printf("Prioridade invalida! Digite um numero entre 1 e 10: ");
        scanf("%d", &novoComponente.prioridade);
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer após scanf

    torre[*totalComponentes] = novoComponente;
    (*totalComponentes)++;
    printf("Componente '%s' adicionado com sucesso!\n", novoComponente.nome);
    return 1;
}

/*
 * Função para listar todos os componentes no vetor.
 * Exibe os dados de cada componente com formatação clara.
 */
void mostrarComponentes(struct Componente* torre, int totalComponentes) {
    printf("\n=== Componentes da Torre ===\n");
    if (totalComponentes == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }
    for (int i = 0; i < totalComponentes; i++) {
        printf("Componente %d:\n", i + 1);
        printf("  Nome: %s\n", torre[i].nome);
        printf("  Tipo: %s\n", torre[i].tipo);
        printf("  Prioridade: %d\n", torre[i].prioridade);
        printf("\n");
    }
}

/*
 * Função de ordenação Bubble Sort por nome (string).
 * Conta o número de comparações realizadas.
 */
void bubbleSortNome(struct Componente* torre, int totalComponentes, int* comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < totalComponentes - 1; i++) {
        for (int j = 0; j < totalComponentes - i - 1; j++) {
            (*comparacoes)++;
            if (strcmp(torre[j].nome, torre[j + 1].nome) > 0) {
                struct Componente temp = torre[j];
                torre[j] = torre[j + 1];
                torre[j + 1] = temp;
            }
        }
    }
    printf("Ordenacao por nome (Bubble Sort) concluida.\n");
}

/*
 * Função de ordenação Insertion Sort por tipo (string).
 * Conta o número de comparações realizadas.
 */
void insertionSortTipo(struct Componente* torre, int totalComponentes, int* comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < totalComponentes; i++) {
        struct Componente key = torre[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (strcmp(torre[j].tipo, key.tipo) > 0) {
                torre[j + 1] = torre[j];
                j--;
            } else {
                break;
            }
        }
        torre[j + 1] = key;
    }
    printf("Ordenacao por tipo (Insertion Sort) concluida.\n");
}

/*
 * Função de ordenação Selection Sort por prioridade (int).
 * Conta o número de comparações realizadas.
 */
void selectionSortPrioridade(struct Componente* torre, int totalComponentes, int* comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < totalComponentes - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < totalComponentes; j++) {
            (*comparacoes)++;
            if (torre[j].prioridade < torre[min_idx].prioridade) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            struct Componente temp = torre[i];
            torre[i] = torre[min_idx];
            torre[min_idx] = temp;
        }
    }
    printf("Ordenacao por prioridade (Selection Sort) concluida.\n");
}

/*
 * Função para buscar um componente no vetor por nome (busca binária).
 * Requer vetor ordenado por nome. Conta o número de comparações.
 * Retorna 1 se encontrado, 0 caso contrário.
 */
int buscaBinariaPorNome(struct Componente* torre, int totalComponentes, const char* nome, int* comparacoes) {
    *comparacoes = 0;
    int esquerda = 0, direita = totalComponentes - 1;
    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        (*comparacoes)++;
        int cmp = strcmp(torre[meio].nome, nome);
        if (cmp == 0) {
            printf("\n=== Componente Encontrado (Busca Binaria) ===\n");
            printf("Nome: %s\n", torre[meio].nome);
            printf("Tipo: %s\n", torre[meio].tipo);
            printf("Prioridade: %d\n", torre[meio].prioridade);
            printf("Comparacoes realizadas: %d\n\n", *comparacoes);
            printf("Componente-chave encontrado! Torre de fuga pode ser ativada.\n");
            return 1;
        } else if (cmp < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    printf("Componente '%s' nao encontrado. Comparacoes: %d\n", nome, *comparacoes);
    printf("Componente-chave ausente! Nao e possivel ativar a torre.\n");
    return 0;
}

int main() {
    // Declaração do vetor de structs para os componentes com capacidade para 20
    struct Componente torre[20];
    int totalComponentes = 0;
    const int capacidade = 20;
    char opcao;
    char nomeBusca[30];
    int comparacoes = 0;
    int sortedByName = 0; // Flag para indicar se o vetor está ordenado por nome

    do {
        // Exibe menu de opções
        printf("\n=== Sistema de Montagem da Torre de Fuga ===\n");
        printf("1. Inserir componente\n");
        printf("2. Ordenar por nome (Bubble Sort)\n");
        printf("3. Ordenar por tipo (Insertion Sort)\n");
        printf("4. Ordenar por prioridade (Selection Sort)\n");
        printf("5. Mostrar componentes\n");
        printf("6. Buscar componente-chave (Binaria - requer ordenacao por nome)\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao (1-7): ");
        scanf(" %c", &opcao);
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer

        switch (opcao) {
            case '1':
                inserirComponente(torre, &totalComponentes, capacidade);
                sortedByName = 0; // Reset flag após inserção
                mostrarComponentes(torre, totalComponentes);
                break;
            case '2':
                {
                    clock_t start = clock();
                    bubbleSortNome(torre, totalComponentes, &comparacoes);
                    clock_t end = clock();
                    double tempo = (double)(end - start) / CLOCKS_PER_SEC;
                    printf("Comparacoes: %d\n", comparacoes);
                    printf("Tempo de execucao: %.6f segundos\n", tempo);
                    sortedByName = 1; // Set flag
                    mostrarComponentes(torre, totalComponentes);
                }
                break;
            case '3':
                {
                    clock_t start = clock();
                    insertionSortTipo(torre, totalComponentes, &comparacoes);
                    clock_t end = clock();
                    double tempo = (double)(end - start) / CLOCKS_PER_SEC;
                    printf("Comparacoes: %d\n", comparacoes);
                    printf("Tempo de execucao: %.6f segundos\n", tempo);
                    sortedByName = 0; // Reset flag
                    mostrarComponentes(torre, totalComponentes);
                }
                break;
            case '4':
                {
                    clock_t start = clock();
                    selectionSortPrioridade(torre, totalComponentes, &comparacoes);
                    clock_t end = clock();
                    double tempo = (double)(end - start) / CLOCKS_PER_SEC;
                    printf("Comparacoes: %d\n", comparacoes);
                    printf("Tempo de execucao: %.6f segundos\n", tempo);
                    sortedByName = 0; // Reset flag
                    mostrarComponentes(torre, totalComponentes);
                }
                break;
            case '5':
                mostrarComponentes(torre, totalComponentes);
                break;
            case '6':
                if (!sortedByName) {
                    printf("O vetor precisa ser ordenado por nome primeiro para usar busca binaria!\n");
                    break;
                }
                printf("Digite o nome do componente-chave a buscar: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                removerNovaLinha(nomeBusca);
                buscaBinariaPorNome(torre, totalComponentes, nomeBusca, &comparacoes);
                break;
            case '7':
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != '7');

    return 0;
}