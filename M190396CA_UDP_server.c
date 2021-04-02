//UDP Server
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
    int createSocket,newSocket,length,len;
    unsigned int client_len;
    char data[MAX_DATA];
 
    createSocket =  socket(AF_INET,SOCK_DGRAM,0);

    if(createSocket<0) showError("socket opening failed...");
    
    length = sizeof(server);
    bzero(&server,length);   
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(createSocket,(struct sockaddr*)&server,length)<0) showError("socket binding failed...");
    
    printf("Server is running...\n");

    client_len = sizeof(struct sockaddr_in);

    while(1){
             
        do{
            
            bzero(data,MAX_DATA);
        	len= recvfrom(createSocket,data,MAX_DATA,0,(struct sockaddr*)&client,&client_len);

            if(strcmp(data,"quit")==0){
                    
                break;
            }
            else{

    	       if(len){
    
    	       	  printf("Client: %s\n",data);
    		      reverse(data,len);
    		      sendto(createSocket,data,len,0,(struct sockaddr*)&client,client_len);
    		      data[len] = '\0';
                  printf("Server: %s\n",data);
    	        }
            }

    	}while(len);

    }

    return 0;
}
