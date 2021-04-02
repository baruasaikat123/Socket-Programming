//TCP Client
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<error.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 7891
#define MAX_DATA 1024

void showError(const char* msg){

    printf("Error: %s\n",msg);
    exit(0);
} 

int main(){

	struct sockaddr_in server;
	char input[MAX_DATA];
	char output[MAX_DATA];
	int createSocket,len;
    unsigned int length;

    createSocket =  socket(AF_INET,SOCK_STREAM,0);

    if(createSocket<0) showError("socket opening failed...");
    
    length = sizeof(struct sockaddr_in);
    bzero(&server,length);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if(connect(createSocket,(struct sockaddr*)&server,length)<0) showError("failed on connecting...");

    printf("Connected to server...\n");
   
    while(1){
        
        bzero(input,MAX_DATA);
    	printf("Client(Enter 'quit' to close connection): ");
        scanf("%[^\n]%*c",input);
	   	send(createSocket,input,strlen(input),0);

        if(strcmp(input,"quit")==0){
            
            close(createSocket);
            printf("Disconnected from server...\n");
            exit(0);
        }
        bzero(output,MAX_DATA);
	   	len = recv(createSocket,output,MAX_DATA,0);
	    output[len] = '\0';
	    printf("Server: %s\n",output);
    }
    
    return 0;
}