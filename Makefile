jogo:
	gcc main.c -o jogo -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g

clean: 
	rm jogo

testar:
	gcc main.c -o testes -DTEST_MODE -lcunit -Wall -Wextra -pedantic -g
	./testes