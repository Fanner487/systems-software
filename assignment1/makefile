CC=gcc -g 
objects=main.o backup.o date.o syncfiles.o
headers=backup.h date.h syncfiles.h

myprog: $(objects)
	$(CC) -o daemon_process $(objects) -lm

main.o: main.c $(headers)
	$(CC) -c -Wall main.c

syncfiles.o: syncfiles.c
	$(CC) -c -Wall syncfiles.c

backup.o: backup.c $(headers)
	$(CC) -c -Wall backup.c

date.o: date.c
	$(CC) -c -Wall date.c

clean:
	rm program $(objects)