CC=gcc -g 
objects=backup_test.o date.o
headers=date.h

myprog: $(objects)
	$(CC) -o program $(objects) -lm

backup_test.o: backup_test.c $(headers)
	$(CC) -c -Wall backup_test.c

date.o: date.c
	$(CC) -c -Wall date.c