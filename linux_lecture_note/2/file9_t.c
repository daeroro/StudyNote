#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

long replace_text(int fd, char *tstr, char *cstr)
{
	char buf[32] = {0};
	int tlen = strlen(tstr);
	int clen = strlen(cstr);
	int diff = tlen - clen;
	int cnt = 0;
	int nr;
	int i;
	off_t idx, iidx;

	while(nr = read(fd, buf, sizeof(buf)))
	{
		for(i=0; i<nr; i++)
		{
			if(!strncmp(&buf[i], tstr, tlen))
			{
				lseek(fd, (off_t)tlen, SEEK_CUR);
				nr = read(fd, buf, sizeof(buf));

				iidx = lseek(fd, (off_t)i + (32 * cnt), SEEK_SET);
				write(fd, cstr, clen);

				idx = lseek(fd, (off_t)0, SEEK_CUR);

				write(fd, buf, sizeof(buf));
				idx = lseek(fd, (off_t)diff, SEEK_CUR);

				while(nr = read(fd, buf, sizeof(buf)))
				{
					lseek(fd, (off_t)diff, SEEK_CUR);
					write(fd, buf, sizeof(buf));
					lseek(fd, (off_t)(-diff), SEEK_CUR);
				}			
			}
		}
		lseek(fd, iidx, SEEK_SET);
		cnt++;
	}
}

int main(int argc, char **argv)
{
	int fd;
	long pos;

	if(argc != 3)
	{
		fprintf(stderr, "Usage : exe target_text, changing_txt\n");
		exit(-1);
	}

	if((fd = open("reading2.txt", O_RDWR))<0)
	{
		printf("There is no reading2.txt\n");
		exit(-1);
	}

	pos = replace_text(fd, argv[1], argv[2]);
	
	close(fd);
	return 0;
}	
