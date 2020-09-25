all:avm

avm:
	gcc binary.c avm_code.c -g -o avm -lm
clean:
	rm -rf avm