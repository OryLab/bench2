bench2: bench2.c
	gcc -o bench2 -lpthread bench2.c || clang -o bench2 bench2.c || clang -o bench2 -lpthread bench2.c
