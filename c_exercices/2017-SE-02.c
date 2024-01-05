#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFSIZE 4096


int line = 1;
void read_input(int fd, int num_option);
void read_input(int fd, int num_option)
{
        char buf[BUFFSIZE];
        int len;
        while((len = read(fd, &buf,BUFFSIZE)) > 0)
        {
                for(int i = 0 ; i < len ; i++)
                {
                        if(line == 1 && num_option == 1)
                        {
                                char num[12];
                                int newLen = snprintf(num,12, "%d", line++);
                                write(1,&num, newLen);
                        }
                        write(1,&buf[i],1);
                        if(buf[i] == '\n' && num_option == 1)
                        {
                                char num[12];
                                int newLen = snprintf(num,12, "%d", line++);
                                write(1,&num, newLen);
                        }
                }
        }
        if(fd != 0) close(fd);
}

int main( int argc, char** argv)
{
        int num_option = 0;
        if (argc == 1)
        {
                read_input(0,num_option);
                return 0;
        }

        int file_start = 1;
        if(strcmp(argv[1],"-n") == 0)
        {
                num_option = 1;
                file_start++;
        }

        if(argc == 2 && num_option == 1)
        {
                read_input(0,num_option);
                return 0;
        }


        while(file_start < argc)
        {
                if(strcmp(argv[file_start],"-") == 0)
                {
                        read_input(0,num_option);
                        file_start++;
                        continue;
                }
                int fd = open(argv[file_start], O_RDONLY);
                if( fd == -1)
                {
                        printf("Error: File '%s' is missing.\n", argv[file_start]);
                }
                read_input(fd,num_option);
                file_start++;
        }

        return 0;
}
