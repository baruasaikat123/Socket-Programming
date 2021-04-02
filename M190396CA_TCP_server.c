//TCP Server
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
#define MAX_CLIENT 5
#define MAX_DATA 1024

void showError(const char* msg){

    printf("Error: %s\n",msg);
    exit(0);
} 

void reverse(char s[],int len){

	int n = len;

	for(int i=0;i<n/2;i++){

		char temp = s[i];
		s[i] = s[n-i-1];
		s[n-i-1] = temp;
	}
}
int main(){

	struct sockaddr_in server,client;
	unsigned int length;
    int createSocket,newSocket,len=1;
    char data[MAX_DATA];
    pid_t child;

    createSocket =  socket(AF_INET,SOCK_STREAM,0);      //Create a TCP socket

    if(createSocket<0) showError("socket opening failed...");
    
    length = sizeof(struct sockaddr_in);        //size of the structure
    bzero(&server,length);
    server.sin_family = AF_INET;               //Define address family(Ipv4) 
    server.sin_port = htons(PORT);             //Define port no.
    server.sin_addr.s_addr = INADDR_ANY;       //Define IP address(0.0.0.0)
    
    //Bind the socket to the server
    if(bind(createSocket,(struct sockaddr* )&server,sizeof(server))<0) showError("failed on binding...");
    
    //Listing
    if(listen(createSocket,MAX_CLIENT)<0) showError("failed on listening...");

    printf("Server is running...\n"); 


    while(1){
        
    	newSocket = accept(createSocket,(struct sockaddr*)&client,&length);
    	if(newSocket<0) exit(0);
    	printf("New client connected from port %d and IP %s\n", ntohs(client.sin_port),inet_ntoa(client.sin_addr));

    	if((child=fork())==0){

    		close(createSocket);

    		while(len){

    			bzero(data,MAX_DATA);
    		    len = recv(newSocket,data,MAX_DATA,0);

    		    if(strcmp(data,"quit")==0){
                    
    		    	printf("Client disconnected from port %d and IP %s\n",ntohs(client.sin_port),inet_ntoa(client.sin_addr));
    		    	break;
    		    }
    		    else{

                    printf("Client: %s\n",data);

    		    	if(len){
                        
    		    		reverse(data,len);
    					send(newSocket,data,len,0);
    					data[len] = '\0';
    					printf("Server: %s\n",data);
    		    	}
    		    }
    		}
    	}
    }
    close(newSocket);

    return 0;
}
