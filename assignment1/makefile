CC=gcc -g 
objects=main.o backup.o filewatch.o date.o syncfiles.o permissions.o log.o 
headers=backup.h date.h syncfiles.h permissions.h log.h filewatch.h

myprog: $(objects)
	$(CC) -o daemon_process $(objects) -lm -lrt

main.o: main.c $(headers)
	$(CC) -c -Wall main.c -lrt 

syncfiles.o: syncfiles.c
	$(CC) -c -Wall syncfiles.c

backup.o: backup.c
	$(CC) -c -Wall backup.c

filewatch.o: filewatch.c
	$(CC) -c -Wall filewatch.c

date.o: date.c
	$(CC) -c -Wall date.c

permissions.o: permissions.c
	$(CC) -c -Wall permissions.c

log.o: log.c
	$(CC) -c -Wall log.c

clean:
	rm program $(objects)