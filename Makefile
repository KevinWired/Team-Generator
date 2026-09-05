.PHONY: clean run

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99

TARGET = tgen

OBJS = teams.o team_generator.o sort.o shuffle.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
