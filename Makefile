jogo:
	gcc main.c -o jogo -Wall -Wextra -pedantic -O1 -fsanitize=address -fno-omit-frame-pointer -g

clean: 
	rm jogo
	
testar:
	gcc testes.c -o testes -lcunit -Wall -Wextra -pedantic -g
	./testes

tudo:
	make clean
	make jogo
	./jogo