#include <stdio.h>
#include <ctype.h> // Para usar a função toupper
#include <string.h> // Para usar a função strcmp


// Funções auxiliares (printMatriz, selecionaPosicao, alteraPosicao) permanecem iguais...

void printMatriz(int L, int C, char carac[][C + 1]) {
        for (int i = 0; i < L; i++) {
            for (int j = 0; j < C && carac[i][j] != '\0'; j++)
                printf("%c ", carac[i][j]);
            printf("\n");
        }
        printf("\n");
    }

void salvarJogo( char *nomeArquivo, int L, int C, char carac[][C + 1]) {
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
#include <stdio.h>
#include <stdlib.h>

int carregarJogo(const char *nomeArquivo, int *L, int *C, char ***carac) {
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


