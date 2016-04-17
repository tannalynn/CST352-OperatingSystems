/*************************************************************
* Author:       Tanna McClure
* File name:    process.c
* Date Created: 3/31/2016
* Modifications: 4/4/2016, 4/5/2016
* Lab/Assignment: Lab 1
*
* Overview:
*   uses processes to do post and pre filter on lines from
*   a command
*
* Input:
*   command line is prefilter char, postfilter char, command
*
* Output:
*   stdout gets the fully processed lines, stderr also gets all
*   the pre/post/rest lines
*
**************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void checkForkFailed(int rc);

int main(int argc, char ** argv)
{
    if(argc < 4)
    {
        fprintf(stderr, "process - wrong number of command line arguments");
        exit(1);
    }

    char * prefilerFile = "./prefilter";
    char * postfilerFile = "./postfilter";

    int pipe1[2], pipe2[2];

    if (pipe(pipe1) != 0)
        exit(1);
    int rc = fork();
    checkForkFailed(rc);

    if(rc == 0)//child - command
    {
        //[3] and on is the command
        if(dup2(pipe1[1], 1) < 0)
            exit(1);
        execvp(argv[3], &argv[3]);
        fprintf(stderr, "rc error");//not checking return val because exiting anyways
        exit(1);

    }
    close(pipe1[1]);

    if(pipe(pipe2) != 0)
        exit(1);
    int rc2 = fork();
    checkForkFailed(rc2);
    if(rc2 == 0)//child - prefilter        [1] is the char
    {
        if(dup2(pipe1[0], 0) < 0)
            exit(1);
        if(dup2(pipe2[1], 1) < 0)
            exit(1);

        execl(prefilerFile, prefilerFile, argv[1], NULL);
        fprintf(stderr, "rc2 error");
        exit(1);
    }
    if(close(pipe1[0]) != 0)
        exit(1);
    if(close(pipe2[1]) != 0)
        exit(1);

    int rc3 = fork();
    checkForkFailed(rc3);
    if(rc3 == 0) //child - postfilter     [2] is the char
    {
        if(dup2(pipe2[0],0) < 0)
            exit(1);

        execl(postfilerFile, postfilerFile, argv[2], NULL);
        fprintf(stderr, "rc3 error");
        exit(1);

    }
    if(close(pipe2[0]) != 0)
        exit(1);

    int wt = wait(NULL);
    wt = wait(NULL);
    wt = wait(NULL);
    return 0;
}

/*************************************************************
*   Purpose:
*      Checks whether the for failed by checking the pid passed in
*
*   Precondition:
*      The int passed in is what is returned from fork()
*
*   Postcondition:
*       the program exits 1 if the fork failed
*
**************************************************************/
void checkForkFailed(int rc)
{
    if (rc < 0)
    {
        fprintf(stderr, "fork failed");
        exit(1);
    }
}
