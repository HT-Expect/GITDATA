#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "socket.h"
#include "pthread.h"

int main()
{
   int sockfd = create_socket();
   assert(sockfd != -1);

   struct sockaddr_in caddr;

   while ( 1 )
   {
	int len = sizeof(caddr);
	int c = accept(sockfd,(struct sockaddr*)&caddr,&len);
	if(c < 0)
	{
	    continue;
	}
	create_pthread(c);
   }
}
