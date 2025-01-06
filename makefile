CC = gcc
RM = rm -rf

PROG = btexp

CFLAGS = -Wall -Wextra -O3 -fsanitize=address
CPPFLAGS = -Ilib
LDFLAGS = -lm -g -fsanitize=address

SOURCES = $(wildcard ./*.c)

OBJ = $(SOURCES:.c=.o)

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROG)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(PROG)



