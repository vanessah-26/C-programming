CC = clang
CFLAGS = -Wall -Wextra -Wstrict-prototypes -Werror -pedantic

.PHONY: all clean format
all: pig

pig: pig.o
	$(CC) $(CFLAGS) $< -o $@
pig.o: pig.c names.h
	$(CC) $(CFLAGS) -c pig.c 
format: 
	clang-format -i -style=file *.[ch]
clean:
	rm -f pig *.o


