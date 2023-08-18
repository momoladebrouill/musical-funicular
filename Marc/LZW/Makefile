all:
	gcc main.c -o main.o 	
	./main.o
	
clean:
	rm ./main.o
sanit:
	gcc main.c -o main.o -fsanitize=address
	./main.o
