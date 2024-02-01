s21_cat : s21_cat.o
	gcc s21_cat.o -o s21_cat

s21_cat.o : s21_cat.c 
	gcc -c -Wall -Wextra -Werror s21_cat.c -o s21_cat.o

clean : 
	rm s21_cat *.o

test :
	bash tests.sh

rebuild : clean s21_cat