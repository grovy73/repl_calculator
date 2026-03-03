build:
	gcc -o rcalc src/*.c -Wall -Wextra -Iinclude -g

clean:
	rm rcalc
