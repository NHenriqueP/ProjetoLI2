#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>
#include <ctype.h>



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



