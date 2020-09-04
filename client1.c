//Assignment A Grading Rubrics
//Program to send menu request from client  and receive a response from server.
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#include"inet.h"
#define MAX 100

void signal_handler(int);
int menu_request();

int sockfd;
struct sockaddr_in client_addr,serv_addr;

int main(){
	
	//int *sockfd;
	//struct sockaddr_in *client_addr,*serv_addr;
	char request;
	char s[MAX];
	int val_send;
	int nreads;
	int cli_len, bind_val;
	//Call Signal
	signal(SIGINT,signal_handler);
	//define server address
	memset(&serv_addr,0,sizeof(serv_addr));//confirm (memset(void *str,arg,arg)),how to assign this with pointer
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(UDP_PORT_NUM); 
	serv_addr.sin_addr.s_addr = inet_addr(SERVER_IPADD);// should s_addr be in it

	//define client address
	memset(&client_addr,0,sizeof(client_addr));//confirm (memset(void *str,arg,arg)),,how to assign this with pointer
	client_addr.sin_family = AF_INET;
        client_addr.sin_port = htons(0); //not sure of this 
        client_addr.sin_addr.s_addr = htonl(0);// should s_addr be in it

	//define my socket
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if (sockfd < 0){
	
		perror("Socket failed");
		return 1;
	}
	else{
		printf("Socket was success\n");
	}

	//bind socket to ip_address
	cli_len = sizeof(client_addr);
	bind_val = bind(sockfd, (struct sockaddr *)(&client_addr),cli_len ); //int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	if (bind_val < 0){
		perror("Bind failed");
		return 1;
	}
	else{
		printf("Bind was successful \n");
	}
	

	//communicate with server
	while(1){
	//get the request to send to server.
		request = menu_request();
		request = (char)('0'+ request);
	 	int serv_len = sizeof(serv_addr);

	//send to server
		val_send = sendto(sockfd,&request,sizeof(request),0,(struct sockaddr *)(&serv_addr),serv_len); //(int socket, const void *message, size_t length,int flags, const struct sockaddr *dest_addr, socklen_t dest_len);
		if (val_send == -1){
	 		perror("Sendto failed \n");
	 		return 1;
	}

	
	//receive from server
		nreads = recvfrom(sockfd,&s,sizeof(s),0,(struct sockaddr *)(&serv_addr),&(serv_len));//(int socket, void *restrict buffer, size_t length,int flags, struct sockaddr *restrict address,socklen_t *restrict address_len);

		if (nreads > 0){
			printf("%s \n",s);
		
		}
		else{
			printf("No incoming message \n");
			//return 1;
		}
	
	
	
	}

return 0;
}

int menu_request(){
	int val = 0;
	char s[MAX];

	printf(" \n");
	printf("*******************************************************\n");
	//printf("*******************************************************\n");
	printf("Main Menu \n");
	printf("*******************************************************\n");
	printf("For Current Time: Choose 1 \n");
	printf("For PID: Choose 2 \n");
	printf("For random number between 1 and 50,inclusive, Choose 3 \n");
	printf("*******************************************************\n");

	scanf("%s",s);
	//printf("Val is %s \n",s);
	val = atoi(s);
	//printf("Val is %d \n",val);
	if (val >0 && val < 4){
		return(val);
	
	}
	else if (val < 0 && val > 3)
	{
		printf("Incorrent integer input,choose correct input between 1 and 3\n");
		menu_request();
	}
	else {
		printf("Incorrect input, choose an integer value between 1 and 3\n");
		menu_request();
	}
}

void signal_handler(int signum){
	char request = 0;
	int val_send;
	request = (char)('0'+ request);
        int serv_len = sizeof(serv_addr);
	//send to server
                val_send = sendto(sockfd,&request,sizeof(request),0,(struct sockaddr *)(&serv_addr),serv_len); //(int socket, const void *message, size_t length,int flags, const struct sockaddr *dest_addr, socklen_t dest_len);
                if (val_send == -1){
                        perror("Sendto failed \n");
                        exit(0);
        }
	printf("Goodbye...\n");
	exit(0);



}
