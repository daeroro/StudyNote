#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
	int fd;
	char buf[64];
	int ret;
	
	fd = open("myfifo", O_RDONLY);

	fcntl(0, F_SETFL, O_NONBLOCK);
	fcntl(fd, F_SETFL, O_NONBLOCK);

	for(;;)
	{
		if((ret = read(0, buf, sizeof(buf)))>0)
		{
			buf[ret - 1] = 0;
			printf("[Keyboard In] = %s\n", buf);
		}

		if((ret = read(fd, buf, sizeof(buf)))>0)
		{
			buf[ret - 1] = 0;
			printf("[Pipe In] = %s\n", buf);
		}
	}
	return 0;
}
