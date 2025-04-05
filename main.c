#include <stdio.h>

void printMatriz(int L, int C, char carac[][C + 1]) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < C && carac[i][j] != '\0'; j++)
            printf("%c ", carac[i][j]);
        printf("\n");
    }
}

int main() {
    int i,L, C;
    if (scanf("%d %d", &L, &C) != 2) return 1;

    char carac[L][C + 1];

    for (i = 0; i < L; i++) {
        if (scanf(" %s", carac[i]) != 1) return 1;
    }

    printMatriz(L, C, carac);
    return 0;
}
