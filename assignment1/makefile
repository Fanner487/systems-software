CC=gcc -g 
objects=backuptest.o date.o
headers=date.h

myprog: $(objects)
	$(CC) -o program $(objects) -lm

backup_test.o: backup_test.c $(headers)
	$(CC) -c -Wall backuptest.c

date.o: date.c
	$(CC) -c -Wall date.c