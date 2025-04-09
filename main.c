#include "funcoes.c"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    #ifdef TEST_MODE
    
    #else
        // Modo normal
        int L, C;
        char comando[20];
        char **carac = NULL; // Ponteiro duplo para a matriz

        // Ler dimensões da matriz
        if (scanf("%d %d", &L, &C) != 2) {
            printf("Erro ao ler as dimensões da matriz!\n");
            return 1;
        }

        // Alocar memória para a matriz
        carac = (char **)malloc(L * sizeof(char *));
        if (carac == NULL) {
            printf("Erro ao alocar memória para a matriz!\n");
            return 1;
        }
        for (int i = 0; i < L; i++) {
            carac[i] = (char *)malloc((C + 1) * sizeof(char));
            if (carac[i] == NULL) {
                printf("Erro ao alocar memória para a linha %d da matriz!\n", i);
                return 1;
            }
        }

        for (int i = 0; i < L; i++) {
            if (scanf("%s", carac[i]) != 1) {
                printf("Erro ao ler a linha %d\n", i);
                return 1;
            }
        }

        // Limpar o buffer de entrada após o uso de scanf
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    
        // Loop principal
        while (1) {
            printMatriz(L, C, carac); // Imprime a matriz atual
    
            printf("Digite um comando:\n-s para sair\n-g para guardar o jogo\n-l para carregar o jogo\n-r <coordenada> para riscar uma posição\n-b <coordenada> para colocar em maiusculas uma posição\n");
            if (fgets(comando, sizeof(comando), stdin) == NULL) {
                printf("Erro ao ler o comando!\n");
                return 1;
            }
    
            // Verifica se o comando é "s" para sair
            if (comando[0] == 's' && comando[1] == '\n') {
                printf("Encerrar o programa.\n");
                break;
            }
    
            // Verifica se o comando é 'g' para salvar o jogo
            if (comando[0] == 'g' && comando[1] == '\n') {
                salvarJogo("jogo.txt", L, C, carac);
                continue;
            }
    
            // Verifica se o comando é 'l' para carregar o jogo
            if (comando[0] == 'l' && comando[1] == '\n') {
                // Liberar a memória da matriz atual antes de carregar um novo jogo
                for (int i = 0; i < L; i++) {
                    free(carac[i]);
                }
                free(carac);

                if (carregarJogo("jogo.txt", &L, &C, &carac)) {
                    printf("Jogo carregado com sucesso.\n");
                } else {
                    printf("Falha ao carregar o jogo.\n");
                }
                continue;
            }
    
            // Verifica se o comando é "r <coordenada>"
            if (comando[0] == 'r' && comando[1] == ' ') {
                executarComandoR(L, C, carac, comando);
                continue;
            }

            // Verifica se o comando é "b <coordenada>"
            if (comando[0] == 'b' && comando[1] == ' ') {
                executarComandoB(L, C, carac, comando);
                continue;
            }
        }

        // Liberar a memória da matriz antes de encerrar o programa
        for (int i = 0; i < L; i++) {
            free(carac[i]);
        }
        free(carac);
    
    #endif
    return 0;
}