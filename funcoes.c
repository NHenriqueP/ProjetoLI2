#include <stdio.h>
#include <ctype.h> // Para usar a função toupper
#include <string.h> // Para usar a função strcmp
#include <stdlib.h>


// Funções auxiliares (printMatriz, selecionaPosicao, alteraPosicao) permanecem iguais...

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
    *carac = (char **)malloc(*L * sizeof(char *));
    if (*carac == NULL) {
        printf("Erro ao alocar memória para a matriz!\n");
        fclose(arquivo);
        return 0;
    }

    for (int i = 0; i < *L; i++) {
        (*carac)[i] = (char *)malloc((*C + 1) * sizeof(char));
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
    char linha = toupper(coordenada[0]); // Converte para maiúscula
    if (linha < 'A') {
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
    *x = linha - 'A';

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

    // Verifica se as coordenadas estão dentro dos limites da matriz
    if (x < 0 || x >= L || y < 0 || y >= C) {
        printf("Coordenadas fora dos limites da matriz!\n");
        return;
    }

    // Altera a posição na matriz para '#'
    carac[x][y] = '#';

    // Converte o índice da linha (x) de volta para uma letra
    char linha = 'a' + x;

    // Imprime a mensagem no formato solicitado
    printf("Posição (%c, %d) alterada para '#'.\n", linha, y + 1);
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

    // Verifica se as coordenadas estão dentro dos limites da matriz
    if (x < 0 || x >= L || y < 0 || y >= C) {
        printf("Coordenadas fora dos limites da matriz!\n");
        return;
    }

    // Converte a letra na posição especificada para maiúscula
    carac[x][y] = toupper(carac[x][y]);

    // Converte o índice da linha (x) de volta para uma letra minúscula
    char linha = 'a' + x;

    // Imprime a mensagem no formato solicitado
    printf("Posição (%c, %d) alterada para '%c'.\n", linha, y + 1, carac[x][y]);
}