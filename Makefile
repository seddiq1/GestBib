CC = gcc
CFLAGS = -Wall -Wextra -std=c11
SRCS = $(wildcard include/*.c)
TARGET = gestbib

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
