CC = clang 
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -gdwarf-4
#LFLAGS = -lm 
EXEC1 = xd 
EXEC2 = short_xd

.PHONY: all clean format

all: $(EXEC1) $(EXEC2)

$(EXEC1): xd.c
	$(CC) $(CFLAGS) -o $(EXEC1) xd.c

$(EXEC2): short_xd.c
	$(CC) $(CFLAGS) -o $(EXEC2) short_xd.c

#%.o: %.c 
#	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(EXEC1) $(EXEC2)

format:
	clang-format -i --style=file *.[ch]

