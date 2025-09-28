CC = gcc
CFLAGS = `pkg-config --cflags gtk4` -Iheaders -Wall -g -MMD -MP -fsanitize=address
LDFLAGS = `pkg-config --libs gtk4` -fsanitize=address

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)
TARGET = gtkapp

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

-include $(DEP)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f src/*.o src/*.d $(TARGET)

