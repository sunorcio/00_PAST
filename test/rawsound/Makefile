

test: play
	./play
	aplay sound -f S16 -r 48000 -c 1 -d 10
	make clean




sound.o: sound.c
	clang -c sound.c -O3 -march=native -std=gnu89 -Wall -Wextra -pedantic

play: sound.o
	clang -o play sound.o -lm

clean: play
	rm sound.o
	rm play
	rm sound
