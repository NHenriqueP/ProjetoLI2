#include "funcoes.c"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

// Função de teste
void test_alteraPosicao() {
    char matriz[2][6] = {"abcde", "fghij"};

    // Testar "riscado"
    alteraPosicao(5, matriz, 0, 1, "riscado"); // deve alterar 'b' para '#'
    CU_ASSERT_EQUAL(matriz[0][1], '#');

    // Testar "branco"
    matriz[1][2] = 'k';
    alteraPosicao(5, matriz, 1, 2, "branco"); // deve alterar 'k' para 'K'
    CU_ASSERT_EQUAL(matriz[1][2], 'K');
}

int main() {
#ifdef TEST_MODE
    // Modo de testes
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Testes de alteraPosicao", 0, 0);
    CU_add_test(suite, "Teste de alteraPosicao", test_alteraPosicao);

    CU_basic_run_tests();
    CU_cleanup_registry();
#else
    // Modo normal
    int i, L, C, x, y;
    char acao[10];
    if (scanf("%d %d", &L, &C) != 2) return 1;

    char carac[L][C + 1];

    for (i = 0; i < L; i++) {
        if (scanf(" %s", carac[i]) != 1) return 1;
    }

    printMatriz(L, C, carac);

    if (selecionaPosicao(L, C, &x, &y)) {
        printf("Digite a ação (branco ou riscado): ");
        if (scanf("%s", acao) != 1) {
            printf("Erro ao ler a ação!\n");
            return 1;
        }
        alteraPosicao(C, carac, x, y, acao);
        printMatriz(L, C, carac); // Imprime a matriz após a alteração
    }
#endif
    return 0;
}