#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 6000
#define IPSTR "127.0.0.1"

int create_socket();
int run_cmd(int sockfd,char * s );

int main()
{
    int sockfd = create_socket();
    if(sockfd == -1)
    {
	printf("connect ser faild!\n");
	exit(0);
    }

    while( 1 )
    {
	printf("Connect >>");
	fflush(stdout);

	char buff[128] = {0};
	fgets(buff,128,stdin);

	buff[strlen(buff)-1] = 0;
	
	int i = 0;
	char sendbuff[128] = {0};
	strcpy(sendbuff,buff);

	char* myargv[10] = {0};
	char* s = strtok(buff," ");
	while ( s != NULL)
	{
	    myargv[i++] = s;
	    s = strtok(NULL," ");
	}

	if(myargv[0] == NULL)
	{
	    continue;
	}
	else if(strcmp(myargv[0],"exit") == 0 )
	{
	   exit(0); //
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
	    if(run_cmd(sockfd,sendbuff) == -1)
	    {
		break;
	    }

	}
    }
    close(sockfd);
    exit(0);
}

int run_cmd(int sockfd,char * s )
{
    if(s == NULL || sockfd <= 0)
    {
	return -1;
    }

    send(sockfd,s,strlen(s),0);
    char recvbuff[4096] = {0};
    int n = recv(sockfd,recvbuff,4095,0);
    if(n <= 0)
    {
	return -1;
    }
    if(strncmp(recvbuff,"ok#",3) == 0)
    {
	printf("%s\n",recvbuff+3);
    }
    else
    {
	printf("recvbuff error!\n");
    }

    return 0;
}
int create_socket()
{
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1)
    {
	return -1;
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(PORT);
    saddr.sin_addr.s_addr = inet_addr(IPSTR);

    int res = connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
    assert(res != -1);

    return sockfd;
}


