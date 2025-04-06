jogo:
	gcc main.c -o jogo -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g

clean: 
	rm jogo

testar: testes.c main.c
	gcc -o testes testes.c main.c -DTEST_MODE -lcunit
	./testes
