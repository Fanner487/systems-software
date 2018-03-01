CC=gcc -g 
objects=main.o backup.o date.o syncfiles.o permissions.o
headers=backup.h date.h syncfiles.h permissions.h

myprog: $(objects)
	$(CC) -o daemon_process $(objects) -lm

main.o: main.c $(headers)
	$(CC) -c -Wall main.c

syncfiles.o: syncfiles.c
	$(CC) -c -Wall syncfiles.c

backup.o: backup.c
	$(CC) -c -Wall backup.c

date.o: date.c
	$(CC) -c -Wall date.c

permissions.o: permissions.c
	$(CC) -c -Wall permissions.c

clean:
	rm program $(objects)