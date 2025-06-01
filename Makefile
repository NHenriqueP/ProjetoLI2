CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g
COVFLAGS = -fprofile-arcs -ftest-coverage

# Alvo principal: jogo com ASAN (sem cobertura)
jogo:
	$(CC) main.c -o jogo $(CFLAGS) -O1 -fsanitize=address -fno-omit-frame-pointer

# Alvo para compilar testes
testar:
	$(CC) testes.c -o testes -lcunit $(CFLAGS)
	./testes

# Limpeza
clean:
	rm -f jogo testes programa *.o *.gcda *.gcno *.gcov res.txt

# Recompilar tudo e correr o jogo
tudo:
	make clean
	make jogo
	./jogo


cobertura-testes:
	$(CC) -c testes.c $(CFLAGS) $(COVFLAGS)
	$(CC) testes.o  -o testes -lcunit $(CFLAGS) $(COVFLAGS)
	./testes
	gcov testes.c

