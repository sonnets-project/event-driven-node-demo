# Not my finest work.
CFLAGS=-std=c89 -Wall -Wextra -Wpedantic -Wvla -Wconversion -Warith-conversion
EXECUTABLES=event_demo stack_demo ebc_node_demo
.DEFAULT_GOAL := all

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXECUTABLES):
	$(CC) $(CFLAGS) -o $@ $^

# Header dependencies
driver.o: driver.h event.h stack.h
ebc_node_demo.o: driver.h event.h stack.h
event.o: event.h
event_demo.o: event.h
stack.o: stack.h
stack_demo.o: stack.h

# Executable dependencies
event_demo: event.o event_demo.o
stack_demo: stack.o stack_demo.o
ebc_node_demo: driver.o event.o stack.o ebc_node_demo.o

# Oh dear
all: $(EXECUTABLES)

clean:
	rm --force *.o $(EXECUTABLES)

.PHONY: all clean
