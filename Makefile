#makefile

all : #target
	gcc stack.c trie.c splaytree.c splaytree_freq.c main.c -o main

clean : 
	rm *.o
