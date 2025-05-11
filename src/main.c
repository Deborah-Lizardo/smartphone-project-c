#include <locale.h>
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
void inserir_ordenado_por_preco(smartphone lista[], int *quantidade,
                                smartphone novo) {
  int i = *quantidade - 1;

  while (i >= 0 && lista[i].valor > novo.valor) {
    lista[i + 1] = lista[i]; // Desloca o elemento para a direita
    i--;
  }

  lista[i + 1] = novo; // Insere o novo na posi��o correta
  (*quantidade)++;
}

// Fun��o para ler o arquivo e preencher o vetor ordenado
void ler_arquivo(FILE *arquivo, smartphone lista[], int *quantidade) {
  int qtd_arquivo;
  char c;
  fscanf(arquivo, "%d", &qtd_arquivo);
  do
    c = fgetc(arquivo);
  while (c != '\n'); // descarta at� o fim da linha

  for (int i = 0; i < qtd_arquivo; i++) {
    smartphone temp;

    fgets(temp.marca, MAX_MARCA, arquivo);
    temp.marca[strcspn(temp.marca, "\r\n")] = '\0';

    fgets(temp.modelo, MAX_MODELO, arquivo);
    temp.modelo[strcspn(temp.modelo, "\r\n")] = '\0';

    fscanf(arquivo, "%d", &temp.ano);
    fscanf(arquivo, "%d", &temp.memoria);
    fscanf(arquivo, "%f", &temp.valor);
    do
      c = fgetc(arquivo);
    while (c != '\n');

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
    printf("Memória: %d GB\n", lista[i].memoria);
    printf("Preço: R$ %.2f\n", lista[i].valor);
    printf("-------------------------\n");
  }
}

// Fun��o para exibir smartphones de uma marca espec�fica
void exibir_por_marca(smartphone lista[], int quantidade, const char *marca) {
  printf("\n--- SMARTPHONES DA MARCA %s ---\n", marca);
  int encontrou = 0;
  for (int i = 0; i < quantidade; i++) {
    if (strcasecmp(lista[i].marca, marca) == 0) {
      printf("Modelo: %s, Ano: %d, Memoria: %d GB, Preco: R$ %.2f\n",
             lista[i].modelo, lista[i].ano, lista[i].memoria, lista[i].valor);
      encontrou = 1;
    }
  }
  if (!encontrou) {
    printf("Nenhum smartphone encontrado para a marca %s.\n", marca);
  }
}

// Fun��o para exibir smartphones dentro de um intervalo de pre�os
void exibir_por_preco(smartphone lista[], int quantidade, float min,
                      float max) {
  printf("\n--- SMARTPHONES COM PREÇO ENTRE R$ %.2f E R$ %.2f ---\n", min, max);
  int encontrou = 0;
  for (int i = 0; i < quantidade; i++) {
    if (lista[i].valor >= min && lista[i].valor <= max) {
      printf("Marca: %s, Modelo: %s, Ano: %d, Memoria: %d GB, Preço: R$ %.2f\n",
             lista[i].marca, lista[i].modelo, lista[i].ano, lista[i].memoria,
             lista[i].valor);
      encontrou = 1;
    }
  }
  if (!encontrou) {
    printf("Nenhum smartphone encontrado nesse intervalo de preço.\n");
  }
}

// Fun��o para remover smartphones com mem�ria inferior ao valor fornecido
void remover_por_memoria(smartphone lista[], int *quantidade, int memoria_min) {
  int i = 0;
  while (i < *quantidade) {
    if (lista[i].memoria < memoria_min) {
      for (int j = i; j < *quantidade - 1; j++) {
        lista[j] = lista[j + 1]; // Desloca os elementos para a esquerda
      }
      (*quantidade)--; // Reduz a quantidade de smartphones
    } else {
      i++;
    }
  }
}

// Fun��o para inserir um novo smartphone
// Função segura para ler inteiros
int ler_inteiro(const char *mensagem, int minimo, int maximo) {
  int valor;
  char buffer[100];
  while (1) {
    printf("%s", mensagem);
    if (fgets(buffer, sizeof(buffer), stdin) != NULL &&
        sscanf(buffer, "%d", &valor) == 1 &&
        valor >= minimo && valor <= maximo) {
      return valor;
    } else {
      printf("Entrada inválida. Tente novamente.\n");
    }
  }
}

// Função segura para ler float
float ler_float(const char *mensagem, float minimo, float maximo) {
  float valor;
  char buffer[100];
  while (1) {
    printf("%s", mensagem);
    if (fgets(buffer, sizeof(buffer), stdin) != NULL &&
        sscanf(buffer, "%f", &valor) == 1 &&
        valor >= minimo && valor <= maximo) {
      return valor;
    } else {
      printf("Entrada inválida. Tente novamente.\n");
    }
  }
}

// Função segura para ler strings
void ler_string(const char *mensagem, char *destino, int tamanho) {
  printf("%s", mensagem);
  fgets(destino, tamanho, stdin);
  destino[strcspn(destino, "\r\n")] = '\0'; // Remove \n
}

int memoria_valida(int memoria) {
  int opcoes_validas[] = {32, 64, 128, 256, 512, 1024, 2048};
  int total_opcoes = sizeof(opcoes_validas) / sizeof(opcoes_validas[0]);
  for (int i = 0; i < total_opcoes; i++) {
    if (memoria == opcoes_validas[i]) {
      return 1;
    }
  }
  return 0;
}

int ler_memoria_valida(const char *mensagem) {
  int memoria;
  char buffer[100];
  while (1) {
    printf("%s", mensagem);
    if (fgets(buffer, sizeof(buffer), stdin) != NULL &&
        sscanf(buffer, "%d", &memoria) == 1 &&
        memoria_valida(memoria)) {
      return memoria;
    } else {
      printf("Memória inválida. Use apenas valores como 32, 64, 128, 256, 512, etc.\n");
    }
  }
}

// Função modificada para inserir smartphone com validação
void inserir_novo_smartphone(smartphone lista[], int *quantidade) {
  smartphone novo;

  ler_string("Digite a marca do smartphone: ", novo.marca, MAX_MARCA);
  ler_string("Digite o modelo do smartphone: ", novo.modelo, MAX_MODELO);

  int ano_atual = 2025; // Atualize conforme necessário
  novo.ano = ler_inteiro("Digite o ano de fabricação: ", 1990, ano_atual);

  novo.memoria = ler_memoria_valida("Digite a capacidade de memória (ex: 128, 256): ");

  novo.valor = ler_float("Digite o preço (positivo): ", 0.01, 100000.0);

  inserir_ordenado_por_preco(lista, quantidade, novo);
}

int main() {

  setlocale(LC_ALL, "");
  FILE *arquivo = fopen("data/smartphone.txt", "r");
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
    printf("3. Exibir smartphones por faixa de preço\n");
    printf("4. Inserir um novo smartphone\n");
    printf("5. Remover smartphones com memória inferior a um valor\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar(); // Limpa o buffer de entrada

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
      printf("Digite o preco mínimo: ");
      scanf("%f", &min);
      printf("Digite o preco máximo: ");
      scanf("%f", &max);
      exibir_por_preco(listaSmartphones, quantidade, min, max);
      break;
    }
    case 4:
      inserir_novo_smartphone(listaSmartphones, &quantidade);
      break;
    case 5: {
      int memoria_min;
      printf("Digite o valor mínimo de memória (GB): ");
      scanf("%d", &memoria_min);
      remover_por_memoria(listaSmartphones, &quantidade, memoria_min);
      break;
    }
    case 6:
      printf("Saindo...\n");
      break;
    default:
      printf("Opção inválida, tente novamente.\n");
    }
  } while (opcao != 6);

  return 0;
}
