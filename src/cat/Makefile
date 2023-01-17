CC=gcc
CFLAGS=-Wall -Wextra -Werror #-Wclang-format-violations

# all: s21_cat

s21_cat: s21_cat.c

	$(CC) $(CFLAGS) s21_cat.c -o s21_cat
	rm -rf *.o

clean:
	rm -rf *.o

rebuild:
	clean all
