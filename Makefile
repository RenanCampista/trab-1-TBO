all:
	gcc -Wall -Wextra -Werror -g -pg -o trab1 *.c -lm
clean:
	rm trab1
run:
	./trab1 in-exemplos/0.txt 3 saida_00.txt
	./trab1 in-exemplos/1.txt 2 saida_01.txt
	./trab1 in-exemplos/2.txt 4 saida_02.txt
	./trab1 in-exemplos/3.txt 5 saida_03.txt
	./trab1 in-exemplos/4.txt 5 saida_04.txt
	./trab1 in-exemplos/5.txt 10 saida_05.txt
extra:
	./trab1 input/Teste_Extra_01.txt 5 saida_extra_01.txt
	./trab1 input/Teste_Extra_02.txt 10 saida_extra_02.txt
valgrind:
	valgrind --track-origins=yes --leak-check=full ./trab1 in-exemplos/0.txt 3 saida_00.txt
gprof:
	./trab1 in-exemplos/5.txt 10 saida_05.txt
	gprof trab1 gmon.out > analysis.txt