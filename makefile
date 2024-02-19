# Not my finest work.
CFLAGS=-std=c89 -Wall -pedantic
EXECUTABLES=event_demo stack_demo driver_demo
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXECUTABLES):
	$(CC) $(CFLAGS) -o $@ $^

# Header dependencies
driver.o: driver.h event.h stack.h
driver_demo.o: driver.h event.h stack.h
event.o: event.h
event_demo.o: event.h
stack.o: stack.h
stack_demo.o: stack.h

# Executable dependencies
event_demo: event.o event_demo.o
stack_demo: stack.o stack_demo.o
driver_demo: driver.o event.o stack.o driver_demo.o

# Oh dear
all: $(EXECUTABLES)

clean:
	rm --force *.o $(EXECUTABLES)

.PHONY: all clean
