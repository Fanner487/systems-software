#include <sys/types.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int file_select();
extern int alphasort();

int main(int argc, char **argv){

	int count, i;
	struct direct **files;

	char pathname[MAXPATHLEN];
	int t = 1;

	getcwd(pathname, sizeof(pathname));
	printf("PWD=%s\n", pathname);
	count = scandir(pathname, &files, file_select, alphasort);

	if(count <= 0){
		printf("No files in dir");
		exit(0);
	}

	printf("Number of files = %d\n", count);

	for(i = 1; i < count; ++i){
		printf("\n%s\n", files[i-1] -> d_name);
	}

	printf("\n");

}

int file_select(struct direct *entry){
	return(1);
}
