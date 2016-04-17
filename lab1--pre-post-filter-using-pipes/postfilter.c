/*************************************************************
* Author:       Tanna McClure
* File name:    postfilter.c
* Date Created: 3/31/2016
* Modifications:4/5/2016
*
* Overview:
*   removes all the characters after the last occurrence of a char
*
* Input:
*   command line will get the character to find and stdin gets the
*   lines to run
*
* Output:
*   sends the resulting string to stdout
*
**************************************************************/

#define MAX_SIZE 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char ** argv)
{
    if(argc < 2)
    {
        fprintf(stderr, "wrong number of command line arguments");
        exit(1);
    }
    char buff[MAX_SIZE];
    int pid = getpid();

    while (fgets(buff, MAX_SIZE, stdin))
    {
        char *substr = strrchr(buff, *argv[1]);
        if(fprintf(stderr, "%i post %c: %s",pid,*argv[1],buff) < 0 )
            exit(1);
        if(substr != NULL)
        {
            *(++substr) = '\0';

            if(fprintf(stderr, "%i rest: %s\n", pid, buff) < 0)
                exit(1);
            if(printf("%s\n", buff) < 0)
                exit(1);
        }
        else
        {
            if(fprintf(stderr, "%i rest: %s", pid, buff) < 0)
                exit(1);
            if(printf("%s", buff) < 0)
                exit(1);
        }

        if( fflush(stdout) != 0 ||
            fflush(stderr) != 0)
            exit(1);
    }

    return 0;
}

