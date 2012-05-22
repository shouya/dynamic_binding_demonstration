SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -ansi -pedantic -g

all: $(OBJS)
	gcc $(CFLAGS) -o main $^ -lm


%.o: %.c
	gcc $(CFLAGS) -c $<

rebuild: clean all

clean:
	rm -f main
	rm -f $(OBJS)