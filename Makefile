CC = gcc
CFLAGS = -g
OBJ = wordcount.o loadfile.o

pwordcount: $(OBJ) pwordcount.c
	@echo "Creating pwordcount ..."
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c %.h
	@echo "Creating object files ..."
	$(CC) -c $< -o $@

clean:
	@echo "Deleting object and binary files ..."
	rm -rvf *.o pwordcount
