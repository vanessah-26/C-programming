CC = clang
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS = -lm
EXEC = calc
TESTS = tests

HEADERS = stack.h operators.h messages.h mathlib.h

.PHONY: all clean format

all: $(EXEC) $(TESTS)

$(EXEC): $(EXEC).o stack.o mathlib.o operators.o
	$(CC) $^ $(LFLAGS) -o $@

$(TESTS): $(TESTS).o stack.o mathlib.o operators.o
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC) $(TESTS) *.o

format:
	clang-format -i -style=file $(wildcard *.[ch])
