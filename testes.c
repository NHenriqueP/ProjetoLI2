#include "funcoes.c"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <string.h>
#include <ctype.h>

void test_determinarCoordenadas() {
    int x, y;
    CU_ASSERT_TRUE(determinarCoordenadas("A1", &x, &y));
    CU_ASSERT_EQUAL(x, 0);
    CU_ASSERT_EQUAL(y, 0);

    CU_ASSERT_TRUE(determinarCoordenadas("c3", &x, &y));
    CU_ASSERT_EQUAL(x, 2);
    CU_ASSERT_EQUAL(y, 2);

    CU_ASSERT_FALSE(determinarCoordenadas("1A", &x, &y));
    CU_ASSERT_FALSE(determinarCoordenadas("A0", &x, &y));
    CU_ASSERT_FALSE(determinarCoordenadas("", &x, &y));
}


int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Suite Jogo", NULL, NULL);

    CU_add_test(suite, "Test determinarCoordenadas", test_determinarCoordenadas);
   // CU_add_test(suite, "Test salvar e carregar jogo", test_salvar_e_carregar_jogo);
   // CU_add_test(suite, "Test executarComandoR e B", test_executarComandoR_B);
    //CU_add_test(suite, "Test printMatriz", test_printMatriz);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}

