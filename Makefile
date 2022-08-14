include Make.inc

SRCS = gc.c init.c main.c alloc.c task.c
OBJS = $(SRCS:%.c=%.o)

default: gc_main

HEADERS = $(wildcard *.h)


%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -Ilib -c $^ -o $@

gc_main: $(OBJS)
	rm -rf $@
	$(CC) $^ -o $@  -Llib -lsupport

clean:
	rm -f *.o
	rm -f gc_main
	rm -f *~ *#
	rm -f core*
