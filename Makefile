all: build run clean
build: sequence.c sequence.h
	gcc sequence.h sequence.c -o sequence
run:
	./sequence
clean:
	rm -f sequence