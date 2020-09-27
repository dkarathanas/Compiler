
CC=gcc
F=flex

all: lexical syntax

lexical:  project.l
		flex --outfile=scanner.c project.l

syntax:	parser.y symbol_table.c
	bison -v --yacc --defines --output=parser.c parser.y
	$(CC) -g scanner.c parser.c symbol_table.c i_code.c -o icode

clean:	
		rm icode parser.c scanner.c
