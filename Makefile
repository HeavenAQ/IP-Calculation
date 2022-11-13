SHELL := /bin/bash
FLAG = -g -Wall -Wextra
TARGET = ip_math
CC = gcc

all: $(TARGET).o main.o
	$(CC) $(FLAGS) $^ -o $(TARGET)

%: %.c
	$(CC) $(FLAGS) -c $<

.PHONY: clean
clean:
	rm -rf *.o
	rm -rf $(TARGET)
