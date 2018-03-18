CC=gcc -g 
objects=main.o backup.o fileaudit.o date.o syncfiles.o permissions.o log.o messagequeue.o
headers=backup.h date.h syncfiles.h permissions.h log.h fileaudit.h messagequeue.h

myprog: $(objects)
	$(CC) -o daemon_process $(objects) -lm -lrt

main.o: main.c $(headers)
	$(CC) -c -Wall main.c -lrt 

syncfiles.o: syncfiles.c
	$(CC) -c -Wall syncfiles.c

backup.o: backup.c
	$(CC) -c -Wall backup.c

fileaudit.o: fileaudit.c
	$(CC) -c -Wall fileaudit.c

date.o: date.c
	$(CC) -c -Wall date.c

permissions.o: permissions.c
	$(CC) -c -Wall permissions.c

log.o: log.c
	$(CC) -c -Wall log.c

messagequeue.o: messagequeue.c
	$(CC) -c -Wall messagequeue.c -lrt

clean:
	rm program $(objects)