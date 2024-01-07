#include <stdint.h>
#include <err.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

#define MAXUSERS 2048
#define MAXREC 16384

struct user_format
{
        int     uid;
        int     longest_session;
        int printed;
};


struct dformat
{
        uint32_t uid;
        uint16_t empty_1;
        uint16_t empty_2;
        uint32_t begin_time;
        uint32_t end_time;
};


int current_users = 0;
int current_records = 0;
int total_time = 0;
struct user_format user_array[MAXUSERS];
struct dformat data[MAXREC];

int find_user(int uid);
int find_user(int uid)
{
        for(int i = 0 ; i < current_users; i++)
        {
                if(user_array[i].uid == uid)
                        return i;
        }
        return -1;
}

void process_input(int fd);
void process_input(int fd)
{
        struct dformat curr;

        while(read(fd,&curr,sizeof(curr)))
        {
                int session = curr.end_time - curr.begin_time;
                total_time += session;
                data[current_records++] = curr;
                int user_pos = find_user(curr.uid);

                if(user_pos == -1)
                {
                        struct user_format new_user;
                        new_user.uid = curr.uid;
                        new_user.longest_session = session;
                        new_user.printed = 0;
                        user_array[current_users++] = new_user;
                }
                else
                {
                        if(user_array[user_pos].longest_session < session)
                                user_array[user_pos].longest_session = session;
                }

        }

}
int calculate_dispersion(int avg);
int calculate_dispersion(int avg)
{
        int sum = 0;
        for(int i = 0 ; i < current_records;  i++)
        {
                int session = data[i].end_time - data[i].begin_time;
                        sum += (session - avg)*(session - avg);
        }
        return sum/avg;
}
void print_user(int pos);
void print_user(int pos)
{
        if(user_array[pos].printed == 0)
        {
                printf("uid:%d  time:%d",user_array[pos].uid, user_array[pos].longest_session);
                user_array[pos].printed = 1;
        }
}

int main(int argc, char** argv)
{
        if( argc != 2)
        {
                errx(1,"Invalid arguments!");
        }
        int fd = open(argv[1],O_RDONLY);

        if(fd == -1)
        {
                errx(2, "Could not open file!");
        }

        struct stat s;
        fstat(fd,&s);

        if( s.st_size % 16 != 0)
        {
                errx(3,"Invalid file format!");
        }

        process_input(fd);

        int     avg = total_time / current_records;
        int dis = calculate_dispersion(avg);

        for(int i = 0 ; i < current_records; i++)
        {
                int user_pos = find_user(data[i].uid);
                int session = data[i].end_time - data[i].begin_time;

                if(session > dis)
                {
                        print_user(user_pos);
                }

        }


        close(fd);
        return 0;
}
