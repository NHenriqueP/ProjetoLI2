
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
}

int selecionaPosicao(int L, int C, int *x, int *y) {
    printf("Digite a linha e a coluna da posição desejada (começa em 0): ");
    if (scanf("%d %d", x, y) != 2 || *x < 0 || *x >= L || *y < 0 || *y >= C) {
        printf("Posição inválida!\n");
        return 0; // Retorna 0 para indicar falha
    }
    return 1; // Retorna 1 para indicar sucesso
}

void alteraPosicao (int C, char carac[][C + 1], int x, int y, char *acao) {
    if (acao == NULL) return;

    if (strcmp(acao, "riscado") == 0) {
        carac[x][y] = '#'; // Altera para "#"
    } else if (strcmp(acao, "branco") == 0) {
        carac[x][y] = toupper(carac[x][y]); // Altera para a letra maiúscula
    } else {
        printf("Ação inválida!\n");
    }
}



