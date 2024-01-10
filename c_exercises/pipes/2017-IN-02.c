#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <string.h>

#define CHECK_ERR(result, err_code, msg) if(result == -1) err(err_code,msg)
static void read_input (char* buff, int fd)
{
        char c;
        int i = 0;
        while(read(fd,&c,1))
        {

                if(c == '\n' || c == ' ' || i == 4)
                {
                        break;
                }
                buff[i++] = c;

        }
        buff[i] = '\0';

}
//ADD CHECKS FOR EXECLP
int main (int argc , char** argv)
{

        const char* cmd = "echo";
        if(argc >= 2)
        {
                cmd = argv[1];
        }

        char p1[5];
        char p2[5];
        while(1)
        {
                read_input(p1,0);
                if(strlen(p1) == 0)
                {
                        break;
                }
                read_input(p2,0);
                if(strlen(p2) == 0)
                {
                        const pid_t pid = fork();
                        CHECK_ERR(pid, 3, "Could not fork!");
                        if(pid == 0)
                        {
                                execlp(cmd,cmd,p1,NULL);
                                CHECK_ERR(execlp,4,"Could not execlp!");
                        }
                }
                else
                {
                        const pid_t pid = fork();
                        CHECK_ERR(pid, 3, "Could not fork!");
                        if(pid == 0)
                        {
                                execlp(cmd,cmd,p1,p2,NULL);
                                CHECK_ERR(execlp,4,"Could not execlp!");
                        }
                }
                wait(NULL);
        }

        return 0;
}
