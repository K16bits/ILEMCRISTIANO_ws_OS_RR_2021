text_editor: main.o editor.o buffer.o threads.o
	gcc -std=c99 main.o editor.o buffer.o threads.o -lncurses -pthread -o text_editor
	-rm *.o
	
main.o:
	gcc -std=c99 -c src/main.c -o main.o
	
editor.o:
	gcc -std=c99 -c src/editor.c -o editor.o
	
buffer.o:
	gcc -std=c99 -c src/buffer.c -o buffer.o

threads.o:
	gcc -std=c99 -c src/threads.c -o threads.o
	
clean:
	rm -f *.o
	