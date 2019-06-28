#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>  //htons的头文件
#include <fcntl.h>

void get_filename(char buff[],char filename[])
{
    if(buff == NULL || filename == NULL	)
    {
	return;
    }
    
    char* s = strtok(buff," ");
    if(s == NULL)
    {
	return;
    }
    
    printf("method:%s\n",s);
    s = strtok(NULL," ");
    if(s == NULL || strcmp(s,"/") == 0)
    {
	strcpy(filename,"/index.html");
	return;
    }

    strcpy(filename,s);

    return;
}

int main()
{
    int sockfd = socket(AF_INET,SOCK_STREAM,0);  // 创建套接字；SOCK_STREAM 流式套接字，提供面向连接的、可靠的数据报服务
    assert( sockfd != -1);
    
    struct sockaddr_in saddr,caddr;
    memset(&saddr,0,sizeof(saddr)); //初始化saddr
    
    saddr.sin_family = AF_INET;  //地址族
    saddr.sin_port = htons(80); //端口号,http端口号为80; htons() 将主机字节序转换为网络字节序
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP地址 
						    //sockaddr_in结构体中套了一个in_addr结构体，in_addr中只有一个参数s_addr
						    //inet_addr() 将字符串"127.0.0.1"转换为一个整型值

    int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));  //将saddr的地址与套接字sockfd绑定 即命名
    assert(res != -1);  //出错的情况：1.IP地址不对； 2.端口号被占用或没有权限使用

    listen(sockfd,5);  //启动监听

    while(1)
    {
	int len = sizeof(caddr);
	int c = accept(sockfd,(struct sockaddr*)&caddr,&len);  //从已完成的连接队列中取出一个客户端进行读取数据
	if(c < 0)
	{
	    continue; //跳出本次循环，进行下一次循环
	}

	printf("accept ip:%s\n",inet_ntoa(caddr.sin_addr));

	char recvbuff[1024] = {0};  //存放从客户端读取的数据
	if( recv(c,recvbuff,1023,0) <= 0 )  //recv() 会阻塞运行
	{
	    close(c);
	    continue;
	}

	printf("recv:\n%s\n",recvbuff);

	char filename[128] = {0};
	get_filename(recvbuff,filename);
	if(filename[0] == 0)
	{
	    char sendbuff[512] = {0};
	    strcpy(sendbuff,"HTTP/1.1 200 OK\r\n");
	    strcat(sendbuff,"Server: myhttp\r\n");
	    strcat(sendbuff,"Content-Length: 12\r\n");
	    strcat(sendbuff,"\r\n");
	    strcat(sendbuff,"NO filename!");

	    send(c,sendbuff,strlen(sendbuff),0);
	    close(c);
	    continue;
	}

	char path[256] = {"/home/stu/src/test03_04s"};
	strcat(path,filename);
	printf("path=%s\n",path);

	int fd = open(path,O_RDONLY);
	if(fd == -1)
	{
	
	    char sendbuff[512] = {0};
	    strcpy(sendbuff,"HTTP/1.1 404 Not Found\r\n");
	    strcat(sendbuff,"Server: myhttp\r\n");
	    strcat(sendbuff,"Content-Length: 14\r\n");
	    strcat(sendbuff,"\r\n");
	    strcat(sendbuff,"not find file!");

	    send(c,sendbuff,strlen(sendbuff),0);
	    close(c);
	    continue;
	}

	int size = lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_SET);

	char sendbuff[512] = {0};
	strcpy(sendbuff,"HTTP/1.1 200 OK\r\n");
	strcat(sendbuff,"Server: myhttp\r\n");
	sprintf(sendbuff+strlen(sendbuff),"Content-Length:%d\r\n",size);
	strcat(sendbuff,"\r\n");

	printf("sendbuff:\n%s",sendbuff);
	send(c,sendbuff,strlen(sendbuff),0);

	char databuff[1024] = {0};
	int num = 0;
	while((num = read(fd,databuff,1024)) >0)
	{
	    send(c,databuff,num,0);
	}
	close(fd);
	close(c);
    }
}
