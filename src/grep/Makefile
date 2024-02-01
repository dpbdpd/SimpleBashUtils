s21_grep : s21_grep.o
	gcc s21_grep.o -o s21_grep

s21_grep.o : s21_grep.c 
	gcc -c -Wall -Wextra -Werror -std=c11 s21_grep.c -o s21_grep.o

clean : 
	rm s21_grep *.o

test :
	bash tests.sh

test_leaks :
	leaks -atExit -- ./s21_grep

rebuild : clean s21_grep