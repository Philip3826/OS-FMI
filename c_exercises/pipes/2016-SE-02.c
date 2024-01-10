#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <err.h>
#include <assert.h>
#include <sys/wait.h>
int main(void)
{
        char buffer[256] = "/bin/";
        int i = 5;
        while(1)
        {
                char c;
                while(1)
                {
                        if(write(1,"> ",2) == -1)
                        {
                                err(1, "Could not write to stdout!");
                        }

                        if(read(0,&c,sizeof(c)) == -1)
                        {
                                err(2,"Could not read!");
                        }

                        if(c == '\n')
                                break;
                        else
                        {
                                buffer[i] = c;
                                i++;
                                assert(i < 255);
                        }

                }
                buffer[i] = '\0';
                i = 5;
                if (strcmp(buffer, "/bin/exit") == 0)
                {
                        break;
                }
                const pid_t pid = fork();
                if(pid == 0)
                {
                        //Exec
                        if(execl(buffer,buffer,NULL) == -1)
                        {
                                err(3,"Could not exec!");
                        }
                }
                int status;
                wait(&status);
                if(!WIFEXITED(status))
                {
                        errx(4,"err");
                }
        }
        return 0;
}
