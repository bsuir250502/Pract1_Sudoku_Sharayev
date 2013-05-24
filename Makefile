OBJ = main.o
CFLAGS = -Wall -std=c99 -pedantic
BINARY = main
all: $(BINARY)

$(BINARY): $(OBJ)
	gcc $(CFLAGS) $(OBJ) -o $(BINARY)

%.o : %.c
	gcc $(CFLAGS) -c $<

clean:
	rm $(BINARY) $(OBJ)
