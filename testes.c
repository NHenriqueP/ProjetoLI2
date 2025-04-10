#include "funcoes.c"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>
#include <ctype.h>

void test_determinarCoordenadas() {
    int x, y;
    CU_ASSERT_TRUE(determinarCoordenadas("a1", &x, &y));
    CU_ASSERT_EQUAL(x, 0);
    CU_ASSERT_EQUAL(y, 0);

    CU_ASSERT_TRUE(determinarCoordenadas("c3", &x, &y));
    CU_ASSERT_EQUAL(x, 2);
    CU_ASSERT_EQUAL(y, 2);

    CU_ASSERT_FALSE(determinarCoordenadas("1a", &x, &y));
    CU_ASSERT_FALSE(determinarCoordenadas("a0", &x, &y));
    CU_ASSERT_FALSE(determinarCoordenadas("", &x, &y));
}

void test_salvar_e_carregar_jogo() {
    int L = 2, C = 3;
    char **matriz = malloc(L * sizeof(char *));
    matriz[0] = strdup("abc");
    matriz[1] = strdup("def");

    salvarJogo("teste_jogo.txt", L, C, matriz);

    char **carregado = NULL;
    int l2, c2;

    CU_ASSERT_TRUE(carregarJogo("teste_jogo.txt", &l2, &c2, &carregado));
    CU_ASSERT_EQUAL(l2, L);
    CU_ASSERT_EQUAL(c2, C);
    CU_ASSERT_STRING_EQUAL(carregado[0], "abc");
    CU_ASSERT_STRING_EQUAL(carregado[1], "def");

 // Liberar memória
    free(matriz[0]); free(matriz[1]); free(matriz);
    free(carregado[0]); free(carregado[1]); free(carregado);
    remove("teste_jogo.txt");
}

void test_executarComandoR_B() {
    int L = 2, C = 3;
    char **matriz = malloc(L * sizeof(char *));
    matriz[0] = strdup("abc");
    matriz[1] = strdup("def");

    executarComandoR(L, C, matriz, "r a2");
    CU_ASSERT_EQUAL(matriz[0][1], '#');

    executarComandoB(L, C, matriz, "b b3");
    CU_ASSERT_EQUAL(matriz[1][2], 'F'); // 'f' vira 'F'

    free(matriz[0]); free(matriz[1]); free(matriz);
}

void test_printMatriz() {
    // Apenas verificar se a função roda sem erros
    char **matriz = malloc(2 * sizeof(char *));
    matriz[0] = strdup("ab");
    matriz[1] = strdup("cd");

    printMatriz(2, 2, matriz);

    free(matriz[0]); free(matriz[1]); free(matriz);
}




int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Suite Jogo", NULL, NULL);

    CU_add_test(suite, "Test determinarCoordenadas", test_determinarCoordenadas);
    CU_add_test(suite, "Test salvar e carregar jogo", test_salvar_e_carregar_jogo);
    CU_add_test(suite, "Test executarComandoR e B", test_executarComandoR_B);
    CU_add_test(suite, "Test printMatriz", test_printMatriz);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}

