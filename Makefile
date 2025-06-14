# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -O2
TARGET = grid_sim
SRC = main.c
OBJ = $(SRC:.c=.o)

# Default rule
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) *.o

# Optional: Force rebuild
rebuild: clean all
