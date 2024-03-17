TARGETS=*.c
CFLAGS=-std=c11 -Wall -Werror -Wextra 
TESTS=s21_math_tests.c
FLAG_TEST=-lcheck
SRCS=$(wildcard s21_math.c)
OBJS=$(SRCS:.c=.o)
ifeq ($(shell uname), Linux)
	FLAG_TEST +=-lsubunit -lm
endif

all: clean s21_math.a gcov_report


s21_math.a:$(OBJS)
	ar -rc s21_math.a $^
	ranlib s21_math.a
	rm -rf *.o

clean:
	-rm -rf *.o *.gcno *.gcda *.info  test s21_math.a gcov_report report greport a.out *.txt *.dSYM
	
test: clean s21_math.a
	gcc --coverage $(CFLAGS) $(TESTS) s21_math.a $(FLAG_TEST) -o test -g
	./test

gcov_report:
	gcc --coverage $(TARGETS) $(FLAG_TEST) -o greport
	./greport
	lcov -t "test" -o s21_math.info -c -d .
	genhtml -o ./report s21_math.info
	open ./report/index.html

style:
	clang-format -n --style=google *.c *.h
