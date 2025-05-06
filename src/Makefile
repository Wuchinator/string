CC=gcc
AR=ar
ARGLAGS=rcs
CFLAGS=-Wall -Werror -Wextra -std=c11 -g
LIBFLAGS=-lm -lcheck
GCOV_FLAGS=--coverage
BIN=s21_test

OS=$(shell uname -s)
ifeq ($(OS), Linux)
	LIBFLAGS+=-lsubunit
endif

.PHONY: all test gcov_report rebuild clean clang

all: test

s21_string.a: 
	$(CC) -c $(CFLAGS) func/*.c
	$(AR) $(ARGLAGS) s21_string.a *.o
	rm *.o

test: s21_string.a
	cp s21_string.a tests/s21_string.a
	$(CC) $(CFLAGS) -o $(BIN) tests/*.c s21_string.a $(LIBFLAGS)
	./$(BIN)

gcov_report: s21_string.a
	cp s21_string.a tests/s21_string.a
	$(CC) $(GCOV_FLAGS) $(CFLAGS) -o $(BIN) tests/*.c s21_string.a $(LIBFLAGS)
	./$(BIN)
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	genhtml -o report gcov_report.info
	rm -rf *.g* *.info
	open ./report/index.html

rebuild: clean all

clean:
	rm -rf a.out *.a $(BIN) *.o report *.g* *.info
	rm -rf tests/*.a

clang:
	clang-format --style=Google -n func/*.c func/*.h tests/*.c tests/*.h s21_string.h
	clang-format --style=Google -i func/*.c func/*.h tests/*.c tests/*.h s21_string.h
