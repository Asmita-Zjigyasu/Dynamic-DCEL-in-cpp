
CC = g++

CFLAGS = -Wall -g

DEPS = dcel_parity_of_points_header.hpp

OBJ = dcel_parity_of_points.cpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
assignment3: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	
clean:
	rm -rf *o assignment3
