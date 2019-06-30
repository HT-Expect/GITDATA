#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <signal.h>

int main()
{
    while( 1 )
    {
        char buff[128] = {0};// pwd, ls -l, cp a.c b.c 
        printf("[stu@localhost ~]$ ");
        fflush(stdout);

        fgets(buff,128,stdin);

        buff[strlen(buff)-1] = 0;

        char* myargv[10] = {0};
        char * p = strtok(buff," ");
        int i = 0;
        while( p != NULL )
        {
            myargv[i++] = p;
            p = strtok(NULL," ");
        }

        if ( myargv[0] == NULL )
        {
            continue;
        }
        else if ( strcmp(myargv[0],"exit") == 0  )
         {
             break;
         }
        else
        {
            pid_t pid = fork();
            if ( pid == -1 )
            {
                printf("fork error\n");
                continue;
            }

            if ( pid == 0 )
            {
                execvp(myargv[0],myargv);
                perror("exec error");
                exit(0);
            }

            wait(NULL);
        }

    }
}
