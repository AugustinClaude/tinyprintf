CC = gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror -Wvla -pedantic -fsanitize=address
LDFLAGS=-fsanitize=address
LDLIBS=-lcriterion

NAME=src/tinyprintf
TESTNAME=testsuite
TESTSUITE=tests/testsuite

all: $(NAME).c
	$(CC) $(CFLAGS) -c -o $(NAME).o $^

check: $(NAME).o $(TESTSUITE).o
	$(CC) $(CFLAGS) -o $(TESTNAME) $^ $(LDFLAGS) $(LDLIBS)
	./$(TESTNAME)

$(TESTSUITE).o: $(TESTSUITE).c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) tests/*.o src/*.o $(TESTNAME)
	$(RM) *.html *.css tests/*.gcno src/*.gcno tests/*.gcda src/*.gcda
