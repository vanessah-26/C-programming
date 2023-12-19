CC=clang
debug:   CFLAGS=-Wall -Wextra -Wstrict-prototypes -Werror -pedantic -gdwarf-4
release: CFLAGS=-Wall -Wextra -Wstrict-prototypes -Werror -pedantic
LDFLAGS=-lm

EXECBIN=sorting
OBJS=\
    batcher.o \
    heap.o \
    insert.o \
    quick.o \
    set.o \
    shell.o \
    sorting.o \
    stats.o \


.PHONY: all debug release clean

all: debug

debug: $(EXECBIN)

release: $(EXECBIN)

$(EXECBIN): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(EXECBIN) $(OBJS)

format:
	clang-format -i --style=file *.[ch]
