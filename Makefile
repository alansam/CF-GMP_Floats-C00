all: main

CC = clang
#CC = gcc
#override CFLAGS += -g -Wno-everything -pthread -lm -lgmp
override CFLAGS += -g -Wall -Wpedantic -Werror=vla -fsanitize=address -std=gnu2x -lgmp -pthread -lm -lmpfr -lgmp
#-Wl,--print-memory-usage

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
HEADERS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.h' -print)

main: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) $(SRCS) -o "$@"

main-debug: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -O0 $(SRCS) -o "$@"

clean:
	rm -f main main-debug