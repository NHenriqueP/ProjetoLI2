#include <stdio.h>
#include <ctype.h> // Para usar a função toupper
#include <string.h> // Para usar a função strcmp
#include <stdlib.h>

// Estrutura para armazenar o histórico de comandos
typedef struct {
    char tipoComando;  // Tipo do comando ('r', 'b', 'g', 'l', etc.)
    int x, y;          // Coordenadas da célula (se aplicável)
    char **estadoMatriz; // Estado completo da matriz antes do comando
    int L, C;          // Dimensões da matriz no momento do comando
} Historico;

// Pilha para armazenar o histórico
Historico *pilha = NULL;
int topo = -1; // Índice do topo da pilha

// Funcao para salvar o estado atual da matriz na pilha
char **copiarMatriz(int L, int C, char **carac) {
    char **copia = (char **)malloc(L * sizeof(char *));
    for (int i = 0; i < L; i++) {
        copia[i] = (char *)malloc((C + 1) * sizeof(char));
        strcpy(copia[i], carac[i]);
    }
    return copia;
}

void liberarMatriz(int L, char **matriz) {
    for (int i = 0; i < L; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void empilharComando(char tipoComando, int x, int y, int L, int C, char **carac) {
    topo++;
    pilha = realloc(pilha, (topo + 1) * sizeof(Historico));
    if (pilha == NULL) {
        printf("Erro ao alocar memória para o histórico de comandos!\n");
        exit(1);
    }
    pilha[topo].tipoComando = tipoComando;
    pilha[topo].x = x;
    pilha[topo].y = y;
    pilha[topo].L = L;
    pilha[topo].C = C;
    pilha[topo].estadoMatriz = copiarMatriz(L, C, carac);
}

void printMatriz(int L, int C, char **carac) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C && carac[i][j] != '\0'; j++) {
            printf("%c ", carac[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void salvarJogo(char *nomeArquivo, int L, int C, char **carac) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar o jogo!\n");
        return;
    }

    // Salvar as dimensões da matriz
    fprintf(arquivo, "%d %d\n", L, C);

    // Salvar o conteúdo da matriz
    for (int i = 0; i < L; i++) {
        fprintf(arquivo, "%s\n", carac[i]);
    }

    fclose(arquivo);
    printf("\nJogo salvo com sucesso no arquivo '%s'.\n\n", nomeArquivo);
}

int carregarJogo(char *nomeArquivo, int *L, int *C, char ***carac) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para carregar o jogo!\n");
        return 0; // Retorna 0 para indicar falha
    }

    // Ler as dimensões da matriz
    if (fscanf(arquivo, "%d %d\n", L, C) != 2) {
        printf("Erro ao ler as dimensões do jogo no arquivo!\n");
        fclose(arquivo);
        return 0;
    }
    printf("Dimensões lidas: L = %d, C = %d\n", *L, *C);

    // Alocar memória para a matriz
    *carac = malloc(*L * sizeof(char *));
    if (*carac == NULL) {
        printf("Erro ao alocar memória para a matriz!\n");
        fclose(arquivo);
        return 0;
    }

    for (int i = 0; i < *L; i++) {
        (*carac)[i] = malloc((*C + 1) * sizeof(char));
        if ((*carac)[i] == NULL) {
            printf("Erro ao alocar memória para a linha %d da matriz!\n", i);
            fclose(arquivo);
            return 0;
        }
    }

    // Ler o conteúdo da matriz
    for (int i = 0; i < *L; i++) {
        if (fscanf(arquivo, "%s", (*carac)[i]) != 1) {
            printf("Erro ao ler a linha %d do jogo no arquivo!\n", i);
            fclose(arquivo);
            return 0;
        }
        printf("Linha %d lida: %s\n", i, (*carac)[i]); // Log de depuração
    }

    fclose(arquivo);
    printf("\nJogo carregado com sucesso do arquivo '%s'.\n\n", nomeArquivo);
    return 1; // Retorna 1 para indicar sucesso
}

// Função para determinar as coordenadas da matriz a partir de uma entrada no formato "<letra><número>"
int determinarCoordenadas(char *coordenada, int *x, int *y) {
    if (strlen(coordenada) < 2) {
        printf("Coordenada inválida!\n");
        return 0; // Retorna 0 para indicar falha
    }

    // A primeira parte da coordenada é a letra (linha)
    char linha = coordenada[0];
    if (!islower(linha)) { // Verifica se a letra não é minúscula
        printf("Coordenada inválida!\n");
        return 0;
    }

    // A segunda parte da coordenada é o número (coluna)
    int coluna = atoi(&coordenada[1]); // Converte a parte numérica para inteiro
    if (coluna <= 0) {
        printf("Coordenada inválida!\n");
        return 0;
    }

    // Converte a letra para o índice da linha (0-indexado)
    *x = linha - 'a';

    // Converte o número para o índice da coluna (0-indexado)
    *y = coluna - 1;

    return 1; // Retorna 1 para indicar sucesso
}

void executarComandoR(int L, int C, char **carac, char *comando) {
    char coordenada[10];
    if (sscanf(comando, "r %s", coordenada) != 1) {
        printf("Comando inválido!\n");
        return;
    }

    int x, y;
    if (!determinarCoordenadas(coordenada, &x, &y)) {
        printf("Erro ao determinar as coordenadas!\n");
        return;
    }

    if (x < 0 || x >= L || y < 0 || y >= C) {
        printf("Coordenadas fora dos limites da matriz!\n");
        return;
    }

    // Salvar o estado atual no histórico
    empilharComando('r', x, y, L, C, carac);

    // Modificar a matriz
    carac[x][y] = '#';
    printf("Posição (%c, %d) alterada para '#'.\n", 'a' + x, y + 1);
}

void executarComandoB(int L, int C, char **carac, char *comando) {
    char coordenada[10];
    if (sscanf(comando, "b %s", coordenada) != 1) {
        printf("Comando inválido!\n");
        return;
    }

    int x, y;
    if (!determinarCoordenadas(coordenada, &x, &y)) {
        printf("Erro ao determinar as coordenadas!\n");
        return;
    }

    if (x < 0 || x >= L || y < 0 || y >= C) {
        printf("Coordenadas fora dos limites da matriz!\n");
        return;
    }

    // Salvar o estado atual no histórico
    empilharComando('b', x, y, L, C, carac);

    // Modificar a matriz
    carac[x][y] = toupper(carac[x][y]);
    printf("Posição (%c, %d) alterada para '%c'.\n", 'a' + x, y + 1, carac[x][y]);
}

// Função para desfazer o último comando
void desfazerComando(char ***carac, int *L, int *C) {
    if (topo == -1) {
        printf("Nenhum comando para desfazer!\n");
        return;
    }

    // Recuperar o último comando
    Historico ultimo = pilha[topo];
    topo--;

    // Liberar a matriz atual
    liberarMatriz(*L, *carac);

    // Restaurar o estado anterior da matriz
    *carac = ultimo.estadoMatriz;
    *L = ultimo.L;
    *C = ultimo.C;

    printf("Comando '%c' desfeito. Estado anterior restaurado.\n", ultimo.tipoComando);
}