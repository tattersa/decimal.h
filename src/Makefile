CC = gcc
STDFLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS=--coverage
CHECK_FLAGS=-lcheck -lm -lpthread
ALL_FLAGS=$(CFLAGS) $(GCOV_FLAGS) $(CHECK_FLAGS)
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
NAME = test
REPORT_NAME = report


all: s21_decimal.a 


test: $(OBJS) ./tests/*.c 
	$(CC) $(CFLAGS) $(CHECK_FLAGS) ./tests/*.c  $(OBJS) -o $(NAME)
	./test

linter:
		cp ../materials/linters/.clang-format .clang-format
		clang-format -n *.c

s21_decimal.a: $(OBJS)
	ar rc s21_decimal.a $(OBJS) 
	ranlib s21_decimal.a

gcov_report: ./tests/*.c
	$(CC) -o $(NAME) $(SRCS) ./tests/*.c  $(ALL_FLAGS) 
	./$(NAME)
	geninfo *.gcda *.gcno -b . -o check_res 
	genhtml check_res -o report
	open ./report/index.html

clean: 
	rm -rf *.gcda *.gcno *.gcov *.a test check_res *.out *.o ./report *.info

rebuild: clean all

