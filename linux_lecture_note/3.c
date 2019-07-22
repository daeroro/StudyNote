#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	int fd, nw;
	char text[64] = "Hello Linux System Programming!\n";

	fd = open("text.txt", O_CREAT | O_WRONLY, 0644);
//
	printf("fd = %d\n", fd);	

	nw = write(fd, text, strlen(text));
	printf("nw = %d\n", nw);

//	write(fd, "\0", 1);

	close(fd);
	return 0;
}
