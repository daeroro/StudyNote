#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
	int rfd, wfd;
	ssize_t nr;
	char buf[32] = {0};

	rfd = open(argv[1], O_RDONLY);
	wfd = open(argv[2], O_CREAT | O_RDWR | O_TRUNC, 0644);
	
	while(nr = read(rfd, (char *)buf, sizeof(buf)))
	{
		write(wfd, buf, nr);
	} 

	close(rfd);
	close(wfd);

	unlink(argv[1]);
		
	return 0;
}
