CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = --coverage
AR = ar
ARFLAGS = rcs

LIB_NAME = s21_string.a

SRC = s21_string.c s21_sprintf.c
OBJ = $(SRC:.c=.o)

TEST_DIR = tests
TEST_SRC = $(TEST_DIR)/test_string.c
TEST_BIN = test_string

OS := $(shell uname)

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -lm -lpthread -lrt -lsubunit
else
	CHECK_FLAGS = -lcheck
endif

.PHONY: all clean test gcov_report rebuild s21_string.a \
        clang-format cppcheck valgrind

# ================= MAIN =================

all: s21_string.a

s21_string.a: $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ================= TESTS =================

test: s21_string.a
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(SRC) $(TEST_SRC) -o $(TEST_BIN) $(CHECK_FLAGS)
	./$(TEST_BIN)

# ================= GCOV =================

gcov_report: test
	gcovr --html --html-details -o gcov_report.html

# ================= STATIC ANALYSIS =================

format:
	clang-format -i *.c *.h tests/*.c

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem \
	         --language=c --std=c11 *.c *.h tests/*.c

# ================= MEMORY CHECK =================

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all \
	         --track-origins=yes ./$(TEST_BIN)

# ================= CLEAN =================

clean:
	rm -f *.o *.a *.gcda *.gcno *.gcov $(TEST_BIN)
	rm -f gcov_report*

rebuild: clean all
