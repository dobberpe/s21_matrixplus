CC = g++
CFLAGS = -Wall -Wextra -Werror -std=c++17
TFLAGS = -lgtest
LIB_NAME = s21_matrix_oop.a
LIB_SRC = $(wildcard *.cpp)
LIB_OBJ = $(LIB_SRC:.c=.o)
TEST_SRC = $(wildcard ./tests/*.c)
TEST_GCDA = $(LIB_SRC:.c=.gcda)
TEST_OBJ = $(TEST_SRC:.c=.o)

all: $(LIB_NAME)

test: $(TEST_OBJ) $(LIB_NAME)
	@$(CC) $(CFLAGS) $(TEST_OBJ) -o test -L. -l:$(LIB_NAME) $(TFLAGS)
	@rm -f $(TEST_OBJ)
	@./test
	@cat pics/keyboard_cat.txt

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIB_NAME): $(LIB_OBJ)
	@ar rcs $(LIB_NAME) $(LIB_OBJ)
	@ranlib $(LIB_NAME)
	@rm -f $(LIB_OBJ)
	@cat pics/pika.txt

style_check:
	@cp ../materials/linters/.clang-format .
	@clang-format -n *.c *.h tests/*
	@#cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h tests/*

leak_check:
	@valgrind --tool=memcheck --leak-check=yes ./test

clean:
	@rm -f $(LIB_OBJ) $(LIB_NAME) $(TEST_OBJ) test gcov* coverage.info *.gcda *.gcno tests/*.gcno
	@rm -rf coverage_report
	@rm -rf .clang-format

add_coverage:
	$(eval CFLAGS:=$(CFLAGS) $(GFLAGS))

re: clean all
