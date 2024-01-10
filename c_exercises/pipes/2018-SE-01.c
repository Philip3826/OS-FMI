#include <unistd.h>
#include <err.h>
#include <stdint.h>

int main(int argc, char** argv)
{
        if(argc != 2)
        {
                errx(1, "Invalid arguments!");
        }

        int find_pipe[2];

        if(pipe(find_pipe) == -1)
        {
                err(2,"Error with pipe!");
        }

        const pid_t find_pid = fork();
        if(find_pid == -1)
        {
                err(3,"Error with fork!");
        }
        if(find_pid == 0)
        {
                close (find_pipe[0]);

                if(dup2(find_pipe[1],1) == -1)
                {
                        err(4,"Error with dup!");
                }
                if(execlp("find", "find", argv[1], "-type", "f" , "-printf", "%T@ %f\n", NULL) == -1 )
                {
                        err(5, "Error with execlp!");
                }

        }
        close(find_pipe[1]);
        int sort_pipe[2];

        if(pipe(sort_pipe) == -1)
        {
                err(2,"Error with pipe!");
        }

        const pid_t sort_pid = fork();
        if(sort_pid  == -1)
        {
                err(3,"Error with fork!");
        }
        if(sort_pid == 0)
        {
                close (sort_pipe[0]);

                if(dup2(find_pipe[0],0) == -1)
                {
                        err(4,"Error with dup!");
                }
                if(dup2(sort_pipe[1],1) == -1)
                {
                        err(4,"Error with dup!");
                }
                if(execlp("sort","sort","-n","-k1,1",NULL) == -1)
                {
                        err(5, "Error with execlp!");
                }
        }
        close(sort_pipe[1]);
        close(find_pipe[0]);

        int head_pipe[2];
        if(pipe(head_pipe) == -1)
        {
                err(2,"Error with pipe!");
        }

        const pid_t head_pid = fork();
        if(head_pid   == -1)
        {
                err(3,"Error with fork!");
        }
        if(head_pid == 0)
        {
                close(head_pipe[0]);

                if(dup2(sort_pipe[0],0) == -1)
                {
                        err(4,"Error with dup!");
                }
                if(dup2(head_pipe[1],1) == -1)
                {
                        err(4,"Error with dup!");
                }
                if(execlp("head","head","-n1",NULL) == -1)
                {
                        err(5,"Error with execlp!");
                }
        }
        close(sort_pipe[0]);
        close(head_pipe[1]);
        if(dup2(head_pipe[0],0) == -1)
        {
                err(4,"Error with dup!");
        }
        if(execlp("cut","cut", "-d", " ", "-f2",NULL) == -1)
        {
                err(5,"Error with execlp!");
        }
        return 0;
}
