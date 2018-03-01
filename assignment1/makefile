CC=gcc -g 
objects=backup.o date.o
headers=date.h

myprog: $(objects)
	$(CC) -o program $(objects) -lm

backup.o: backup.c $(headers)
	$(CC) -c -Wall backup.c

date.o: date.c
	$(CC) -c -Wall date.c

clean:
	rm program $(objects)