#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MARCA 21
#define MAX_MODELO 31
#define MAX_SMARTPHONES 100

typedef struct {
    char marca[MAX_MARCA];
    char modelo[MAX_MODELO];
    int ano;
    int memoria;
    float valor;
} smartphone;

// Fun��o que insere um smartphone no vetor em ordem crescente de pre�o
void inserir_ordenado_por_preco(smartphone lista[], int *quantidade, smartphone novo) {
    int i = *quantidade - 1;
    while (i >= 0 && lista[i].valor > novo.valor) {
        lista[i + 1] = lista[i];  // Desloca o elemento para a direita
        i--;
    }

    lista[i + 1] = novo;  // Insere o novo na posi��o correta
    (*quantidade)++;
}

// Fun��o para ler o arquivo e preencher o vetor ordenado
void ler_arquivo(FILE *arquivo, smartphone lista[], int *quantidade) {
    int qtd_arquivo;
    char c;
    fscanf(arquivo, "%d", &qtd_arquivo);
    do c = fgetc(arquivo); while (c != '\n');  // descarta at� o fim da linha

    for (int i = 0; i < qtd_arquivo; i++) {
        smartphone temp;

        fgets(temp.marca, MAX_MARCA, arquivo);
        temp.marca[strcspn(temp.marca, "\r\n")] = '\0';

        fgets(temp.modelo, MAX_MODELO, arquivo);
        temp.modelo[strcspn(temp.modelo, "\r\n")] = '\0';

        fscanf(arquivo, "%d", &temp.ano);
        fscanf(arquivo, "%d", &temp.memoria);
        fscanf(arquivo, "%f", &temp.valor);
        do c = fgetc(arquivo); while (c != '\n');

        inserir_ordenado_por_preco(lista, quantidade, temp);
    }
}

// Fun��o para exibir todos os smartphones
void exibir_smartphones(smartphone lista[], int quantidade) {
    printf("\n--- LISTA DE SMARTPHONES ---\n");
    for (int i = 0; i < quantidade; i++) {
        printf("Marca: %s\n", lista[i].marca);
        printf("Modelo: %s\n", lista[i].modelo);
        printf("Ano: %d\n", lista[i].ano);
        printf("Memoria: %d GB\n", lista[i].memoria);
        printf("Preco: R$ %.2f\n", lista[i].valor);
        printf("-------------------------\n");
    }
}

// Fun��o para exibir smartphones de uma marca espec�fica
void exibir_por_marca(smartphone lista[], int quantidade, const char *marca) {
    printf("\n--- SMARTPHONES DA MARCA %s ---\n", marca);
    int encontrou = 0;
    for (int i = 0; i < quantidade; i++) {
        if (strcmp(lista[i].marca, marca) == 0) {
            printf("Modelo: %s, Ano: %d, Memoria: %d GB, Preco: R$ %.2f\n", lista[i].modelo, lista[i].ano, lista[i].memoria, lista[i].valor);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum smartphone encontrado para a marca %s.\n", marca);
    }
}

// Fun��o para exibir smartphones dentro de um intervalo de pre�os
void exibir_por_preco(smartphone lista[], int quantidade, float min, float max) {
    printf("\n--- SMARTPHONES COM PRECO ENTRE R$ %.2f E R$ %.2f ---\n", min, max);
    int encontrou = 0;
    for (int i = 0; i < quantidade; i++) {
        if (lista[i].valor >= min && lista[i].valor <= max) {
            printf("Marca: %s, Modelo: %s, Ano: %d, Memoria: %d GB, Preco: R$ %.2f\n", lista[i].marca, lista[i].modelo, lista[i].ano, lista[i].memoria, lista[i].valor);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum smartphone encontrado nesse intervalo de pre�o.\n");
    }
}

// Fun��o para remover smartphones com mem�ria inferior ao valor fornecido
void remover_por_memoria(smartphone lista[], int *quantidade, int memoria_min) {
    int i = 0;
    while (i < *quantidade) {
        if (lista[i].memoria < memoria_min) {
            for (int j = i; j < *quantidade - 1; j++) {
                lista[j] = lista[j + 1];  // Desloca os elementos para a esquerda
            }
            (*quantidade)--;  // Reduz a quantidade de smartphones
        } else {
            i++;
        }
    }
}

// Fun��o para inserir um novo smartphone
void inserir_novo_smartphone(smartphone lista[], int *quantidade) {
    smartphone novo;
    printf("\nDigite a marca do smartphone: ");
    fgets(novo.marca, MAX_MARCA, stdin);
    novo.marca[strcspn(novo.marca, "\r\n")] = '\0';

    printf("Digite o modelo do smartphone: ");
    fgets(novo.modelo, MAX_MODELO, stdin);
    novo.modelo[strcspn(novo.modelo, "\r\n")] = '\0';

    printf("Digite o ano de fabricacao: ");
    scanf("%d", &novo.ano);

    printf("Digite a capacidade de memoria (GB): ");
    scanf("%d", &novo.memoria);

    printf("Digite o preco: ");
    scanf("%f", &novo.valor);
    getchar();  // Limpa o buffer de entrada

    inserir_ordenado_por_preco(lista, quantidade, novo);
}

int main() {
    FILE *arquivo = fopen("smartphones.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    smartphone listaSmartphones[MAX_SMARTPHONES];
    int quantidade = 0;

    ler_arquivo(arquivo, listaSmartphones, &quantidade);
    fclose(arquivo);

    int opcao;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Exibir todos os smartphones\n");
        printf("2. Exibir smartphones de uma marca\n");
        printf("3. Exibir smartphones por faixa de preco\n");
        printf("4. Inserir um novo smartphone\n");
        printf("5. Remover smartphones com memoria inferior a um valor\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();  // Limpa o buffer de entrada

        switch (opcao) {
            case 1:
                exibir_smartphones(listaSmartphones, quantidade);
                break;
            case 2: {
                char marca[MAX_MARCA];
                printf("Digite a marca: ");
                fgets(marca, MAX_MARCA, stdin);
                marca[strcspn(marca, "\r\n")] = '\0';
                exibir_por_marca(listaSmartphones, quantidade, marca);
                break;
            }
            case 3: {
                float min, max;
                printf("Digite o preco m�nimo: ");
                scanf("%f", &min);
                printf("Digite o preco m�ximo: ");
                scanf("%f", &max);
                exibir_por_preco(listaSmartphones, quantidade, min, max);
                break;
            }
            case 4:
                inserir_novo_smartphone(listaSmartphones, &quantidade);
                break;
            case 5: {
                int memoria_min;
                printf("Digite o valor minimo de memoria (GB): ");
                scanf("%d", &memoria_min);
                remover_por_memoria(listaSmartphones, &quantidade, memoria_min);
                break;
            }
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Op��o inv�lida, tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}


