CC=gcc
CXX=g++
CFLAGS=-g
LDFLAGS= -lm -lbenchtool -pthread -lstdc++

all: constant rand

constant: constant.c
	$(CC) $(CFLAGS) constant.c -o xconstant $(LDFLAGS)

rand: rand.c
	$(CC) $(CFLAGS) rand.c -o xrand $(LDFLAGS)

clean:
	rm xconstant xrand
