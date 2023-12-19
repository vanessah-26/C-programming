CC = clang
CFLAGS =  -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic
LFLAGS =
EXEC = hangman
HEADERS = helpers.h

all: $(EXEC)

$(EXEC): $(EXEC).o helpers.o
	$(CC) $^ $(LFLAGS) -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(EXEC) *.o

format:
	clang-format -i -style=file *.[ch]

.PHONY: all clean format
