//UDP Client
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<error.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#define PORT 7899
#define MAX_DATA 1024

void showError(const char* msg){

	printf("Error: %s\n",msg);
	exit(0);
} 

int main(){


    struct sockaddr_in client,server;
    int createSocket,len;
    unsigned int length;
    char input[MAX_DATA];
    char output[MAX_DATA];

    createSocket = socket(AF_INET,SOCK_DGRAM,0);

    if(createSocket<0) showError("socket opening failed...");
    
    length = sizeof(struct sockaddr_in);
    bzero(&client,length);
    client.sin_family = AF_INET;
    client.sin_port = htons(PORT);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");;
    
    while(1){

    	bzero(input,MAX_DATA);
    	printf("Client(Enter 'quit' to close connection): ");
    	scanf("%[^\n]%*c",input);
    	sendto(createSocket,input,strlen(input),0,(struct sockaddr*)&client,length);

        if(strcmp(input,"quit")==0){
            
            close(createSocket);
            printf("Disconnected from server...\n");
            exit(0);
        }
        
    	bzero(output,MAX_DATA);
    	len = recvfrom(createSocket,output,MAX_DATA,0,(struct sockaddr*)&server,&length);
    	output[len] = '\0';
    	printf("Server: %s\n",output);
    }
    
}
