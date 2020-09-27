
CC=gcc
F=flex

all: lexical syntax

lexical:  project.l
		flex --outfile=scanner.c project.l

syntax:	parser.y symbol_table.c
	bison -v --yacc --defines --output=parser.c parser.y
	$(CC) -g scanner.c parser.c symbol_table.c -o syntax

clean:	
		rm syntax parser.c scanner.c
