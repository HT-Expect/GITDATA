#include "pthread.h"
#include <sys/wait.h>

void *pthread_work(void* arg)
{
    int socket_c = (int)arg;

    while(1)
    {
	char buff[128] = {0};
	int n = recv(socket_c,buff,127,0);
	if( n <= 0 )
	{
	    pthread_exit(NULL);
	}
	
	char * myargv[10] = {0};
	char * ptr = NULL;
	int i = 0;

	char* s = strtok_r(buff," ",&ptr);
	while( s != NULL )
	{
	    myargv[i++] = s;
	    s = strtok_r(NULL," ",&ptr);
	}

	if(myargv[0] == NULL)
	{
	    send(socket_c,"error",5,0);
	    continue;
	}
	else if(strcmp(myargv[0],"get") == 0)
	{
	    //
	}
	else if(strcmp(myargv[0],"put") == 0)
	{
	    //
	}
	else
	{
	    int pipefd[2];
	    pipe(pipefd);

	    int pid = fork();

	    if(pid == -1)
	    {
		send(socket_c,"error",5,0);
		continue;
	    }
	    if(pid == 0)
	    {
		dup2(pipefd[1],1);
		dup2(pipefd[1],2);
	    
		execvp(myargv[0],myargv);
		perror("exec error");
		exit(0);
	    }
	    close(pipefd[1]);
	    wait(NULL);

	    char readbuff[4096] = {"ok#"};
	    read(pipefd[0],readbuff+3,4092);

	    send(socket_c,readbuff,strlen(readbuff),0);
	    close(pipefd[0]);

	}
    }
    close(socket_c);
    printf("one cline over!\n");
}
void create_pthread(int socket_c)
{
    pthread_t id;
    pthread_create(&id,NULL,pthread_work,(void *)socket_c);
}
