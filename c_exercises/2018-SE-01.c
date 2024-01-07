#include <stdint.h>
#include <string.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>

int inString(char c, char* string);
int inString(char c, char* string)
{
        int len = strlen(string);

        for(int i = 0 ; i < len ; i++)
        {
                if(string[i] == c)
                        return i;
        }


        return -1;

}



void delete_chars(char* format_string);
void delete_chars(char* format_string)
{
        char c;

        while(read(0,&c,1))
        {
                if(inString(c, format_string) == -1)
                {
                        write(1,&c,1);
                }
        }

}

void squash_repeats(char* format_string);
void squash_repeats(char* format_string)
{
        char c;
        char prev;
        while(read(0,&c,1))
        {

                if(c != prev)
                {
                        write(1,&c,1);
                }
                else if(inString(c, format_string) == -1)
                {
                        write(1,&c,1);
                }

                prev = c;
        }
}
void replace_chars(char* old_format, char* new_format);
void replace_chars(char* old_format, char* new_format)
{
        int len_old = strlen(old_format);
        int len_new = strlen(new_format);
        char c;

        if(len_old != len_new)
        {
                errx(3,"format strings lenghts must match!");
        }

        while(read(0,&c,1))
        {
                int pos = inString(c,old_format);
                if(pos != -1)
                {
                        c = new_format[pos];
                }
                write(1,&c,1);
        }
}

int main(int argc, char** argv)
{

        if(argc != 3)
        {
                errx(1, "Invalid arguments!");
        }
        if(strcmp(argv[1], "-d") == 0)
        {
                delete_chars(argv[2]);
                return 0;
        }

        if(strcmp(argv[1], "-s") == 0)
        {
                squash_repeats(argv[2]);
                return 0;
        }

        replace_chars(argv[1],argv[2]);

        return 0;
}
