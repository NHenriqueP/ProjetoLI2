#include "funcoes.c"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>


int main() {
#ifdef TEST_MODE

#else
    // Modo normal
    int L, C, x, y;
    char acao[10];
    char comando;

    // Ler dimensões da matriz

    // Ler dimensões e matriz
    if (scanf("%d %d", &L, &C) != 2) {
        printf("Erro ao ler as dimensões da matriz!\n");
        return 1;
    }
    char carac[L][C+1]; // Tamanho máximo para a matriz

    for (int i = 0; i < L; i++) {
        if (scanf("%s", carac[i]) != 1) {
            printf("Erro ao ler a linha %d\n", i);
            return 1;
        }
    }
    
    

    // Loop principal
    while (1) {
        printMatriz(L, C, carac); // Imprime a matriz atual

        printf("Digite um comando:\n-s para sair\n-g para guardar o jogo\n-l para carregar o jogo\n");
        if (scanf(" %c", &comando) != 1) { // Added a space before %c
            printf("Erro ao ler o comando!\n");
            return 1;
        }

        // Verifica se o comando é "s" para sair
        if (comando == 's') {
            printf("Encerrar o programa.\n");
            break;
        }
        // Verifica se o comando é 'g' para salvar o jogo
        if (comando == 'g') {
            salvarJogo("jogo.txt", L, C, carac);
            continue;
        }
        // Verifica se o comando é 'l' para dar load no jogo
        if (carregarJogo("jogo.txt", &L, &C, carac)) {
            for (int i = 0; i < L; i++) {
                printf("%s\n", carac[i]);
            }
        } else {
            printf("Falha ao carregar o jogo.\n");
        }


        // Executa a ação
        //alteraPosicao(C, carac, x, y, acao);
    }

#endif
    return 0;
}