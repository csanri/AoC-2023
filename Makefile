CC = gcc
CFLAGS = -Wall -Wextra -std=c99

TARGET = day1

SRC = $(TARGET)/day1.c

$(TARGET)/$(TARGET): $(TARGET)
	$(CC) $(CFLAGS) -o $@ @<

run: $(TARGET)/$(TARGET)
	@./$(TARGET)/$(TARGET)

