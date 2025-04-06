#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>
#include <ctype.h>
#include "main.h" // Include the header file with function prototypes

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

#ifndef MAIN_PROGRAM // Compila o main apenas se MAIN_PROGRAM não estiver definido
int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Testes de alteraPosicao", 0, 0);
    CU_add_test(suite, "Teste de alteraPosicao", test_alteraPosicao);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
#endif
