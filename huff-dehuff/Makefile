CC = clang 
CFLAGS = -Werror -Wall -Wextra -Wconversion -Wdouble-promotion -Wstrict-prototypes -pedantic -gdwarf-4

TEST1 = brtest
OBJS1 = brtest.o bitreader.o

TEST2 = bwtest
OBJS2 = bwtest.o bitwriter.o

TEST3 = nodetest
OBJS3 = nodetest.o node.o

TEST4 = pqtest
OBJS4 = pqtest.o pq.o node.o

EXEC1 = huff
EXEC2 = dehuff 

HUFF_OBJS = huff.o pq.o node.o bitwriter.o bitreader.o

DEHUFF_OBJS = dehuff.o pq.o node.o bitwriter.o bitreader.o

.PHONY: all clean format

all: $(TEST1) $(TEST2) $(TEST3) $(TEST4) $(EXEC1) $(EXEC2)

$(TEST1): $(OBJS1)
	$(CC) $(CFLAGS) -o $(TEST1) $(OBJS1)

$(TEST2): $(OBJS2)
	$(CC) $(CFLAGS) -o $(TEST2) $(OBJS2)

$(TEST3): $(OBJS3)
	$(CC) $(CFLAGS) -o $(TEST3) $(OBJS3)

$(TEST4): $(OBJS4)
	$(CC) $(CFLAGS) -o $(TEST4) $(OBJS4)

$(EXEC1): $(HUFF_OBJS)
	$(CC) $(CFLAGS) -o huff $(HUFF_OBJS)

$(EXEC2): $(DEHUFF_OBJS)
	$(CC) $(CFLAGS) -o dehuff $(DEHUFF_OBJS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $<

clean: 
	rm -f $(TEST1) $(TEST2) $(TEST3) $(TEST4) $(EXEC1) $(EXEC2) *.o

format:
	clang-format -i --style=file *.c *.h
