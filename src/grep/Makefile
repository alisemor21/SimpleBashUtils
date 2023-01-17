CC=gcc
CFLAGS=-Wall -Wextra -Werror #-Wclang-format-violations

# all: s21_cat

s21_grep: s21_grep.c

	$(CC) $(CFLAGS) s21_grep.c -o s21_grep
	rm -rf *.o

clean:
	rm -rf *.o

rebuild:
	clean all
