all:
	gcc -Wall -Wextra -Werror -g -pg -o trab1 *.c -lm
clean:
	rm trab1
run:
	./trab1
valgrind:
	valgrind --track-origins=yes --leak-check=full ./trab1 0.txt 3 saida.txt
gprof:
	./trab1 0.txt 3 saida.txt
	gprof trab1 gmon.out > analysis.txt