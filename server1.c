//Assignment A Grading Rubrics
//Program of the server which receives messages from the client.
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h> 
#include <time.h>
#include<sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "inet.h"
#define MAX 100
int main(){
	int bindfd,sockfd;
	int recvfd,sendfd;
	char s[MAX];
	time_t now,this_time;
	struct tm *current_time;
	int pid_val;
 	int clilen;
	char buffer;

	struct sockaddr_in serv_addr,client_addr;

	//initialize the server address
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(0); //Not sure of the port
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	//create socket
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if (sockfd < 0){
		perror("Socket failed");
		return 1;
	}

	//bind port to IP address
	bindfd = bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	if (bindfd < 0){
                perror("Bind failed");
                return 1;
        }

	for(;;){
		clilen = sizeof(client_addr);
		int buff_size = sizeof(s);//might be wron
		recvfd = recvfrom(sockfd,(char *)&buffer,sizeof(buffer),0,(struct sockaddr *)&client_addr,&clilen);
		if (recvfd < 0){
                	perror("Recieved failed");
                	return 1;
        }
		switch(buffer)
		{
			case '1':this_time = time(&now);
				 current_time = localtime(&this_time);
				 strftime(s,MAX,"%D -%T \n",current_time);
				break;
			case '2': sprintf(s,"%d",getpid());
				break;
			case '3':sprintf(s,"%d",rand()%51);
				break;
			default:
				printf("Incorrect input value");
		}
		
		
		if (sendfd = sendto(sockfd,&s,buff_size,0,(struct sockaddr *) &client_addr,clilen) < 0){
		perror("Sent failed");
		return 1;
		}
	}

return 0;
}

