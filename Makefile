GCC = gcc

threads: threads.o
	$(GCC) -o threads threads.o

main.o: threads.c
	$(GCC) -c threads.c

.PHONY: clean
clean:
	rm -f *.o threads
