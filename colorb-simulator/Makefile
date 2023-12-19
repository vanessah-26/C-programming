CC = clang  
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -gdwarf-4
LFLAGS = -lm 
EXEC1 = colorb
OBJS1 = io.o bmp.o colorb.o

EXEC2 = iotest
OBJS2 = io.o iotest.o

.PHONY = all clean format

all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1)
	$(CC) $(LFLAGS) -o $(EXEC1) $(OBJS1)

$(EXEC2): $(OBJS2)
	$(CC) $(LFLAGS) -o $(EXEC2) $(OBJS2)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXEC1) $(OBJS1) $(EXEC2) $(OBJS2)

format:
	clang-format -i --style=file *.[ch]
