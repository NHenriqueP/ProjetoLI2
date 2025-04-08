#include "funcoes.c"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <string.h>


int main() {
    #ifdef TEST_MODE
    
    #else
        // Modo normal
        int L, C;
        char comando[20];
    
        // Ler dimensões da matriz
        if (scanf("%d %d", &L, &C) != 2) {
            printf("Erro ao ler as dimensões da matriz!\n");
            return 1;
        }
        char carac[L][C + 1]; // Tamanho máximo para a matriz
    
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
                if (carregarJogo("jogo.txt", &L, &C, carac)) {
                    for (int i = 0; i < L; i++) {
                        printf("%s\n", carac[i]);
                    }
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
    
    #endif
        return 0;
    }