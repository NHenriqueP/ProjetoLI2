#include "funcoes.c"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
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

    // Limpa o buffer antes de usar fgets
    while (getchar() != '\n');

    // Loop principal
    while (1) {
        printMatriz(L, C, carac); // Imprime a matriz atual

        printf("Digite um comando:\n");
        printf("- s para sair\n");
        printf("- g para guardar o jogo\n");
        printf("- l para carregar o jogo\n");
        printf("- r <coordenada> para riscar uma posição\n");
        printf("- b <coordenada> para colocar em maiúsculas uma posição\n");
        printf("- d para desfazer o último comando\n");
        printf("- a para ajudar mudando o estado de todas as casas que se conseguem inferir através do estado atual do tabuleiro\n");
        printf("- A invocar o comando a enquanto o jogo sofrer alterações\n");
        printf("- v para verificar as restrições\n");
        printf("- R para resolver o jogo automaticamente\n");


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
            // Salvar o estado atual no histórico antes de carregar o novo jogo
            empilharComando('l', L, C, carac);

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

        // Verifica se o comando é "d" para desfazer o último comando
        if (comando[0] == 'd' && comando[1] == '\n') {
            desfazerComando(&carac, &L, &C);
            continue;
        }

        // Verifica se o comando é "a" para ajudar
        if (comando[0] == 'a' && comando[1] == '\n') {
            executarComandoa(L, C, carac);
            continue;
        }

        // Verifica se o comando é "v" para verificar as restrições
        if (comando[0] == 'v' && comando[1] == '\n') {
            executarComandov(L, C, carac);
            continue;
        }

        // Verifica se o comando é "R" para resolver o jogo automaticamente
        if (comando[0] == 'R' && comando[1] == '\n') {
            resolverJogo(L, C, carac);
            continue;
        }

        if (comando[0]== 'A' && comando[1] == '\n') {
            executarComandoA(L, C, carac);
            continue;
        }
    }

    // Liberar a memória da matriz antes de encerrar o programa
    for (int i = 0; i < L; i++) {
        free(carac[i]);
    }
    free(carac);

    return 0;
}
