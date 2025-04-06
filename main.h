#ifndef MAIN_H
#define MAIN_H
// as duas primeiras linhas evitam inclusões múltiplas do mesmo arquivo de cabeçalho, o que pode causar erros de compilação, como redefinições de funções ou variáveis.



// Declaração das funções utilizadas no programa
void printMatriz(int L, int C, char carac[][C + 1]);
int selecionaPosicao(int L, int C, int *x, int *y);
void alteraPosicao(int C, char carac[][C + 1], int x, int y, const char *acao);

#endif // MAIN_H



