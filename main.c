
#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment (lib, "Ws2_32.lib")

#define MAX_REQUEST_LENGHT 2000

int main(int argc,char *argv[])
{
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
  //  char message[MAX_REQUEST_LENGHT];
    char *message , server_reply[2000];
    int recv_size;

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    printf("Socket created.\n");


   // printf("Enter the ip:");
    char *ip="127.0.0.1";
  //  scanf("%s",ip);
   // printf("\nEnter the port:\n");
    int port=3000;
   // scanf("%d",&port);
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons( port );

    if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return 1;
    }

    puts("Connected");
/*
    printf("Enter the api:");
    char api[30]="";
    scanf("%s",api);
    sprintf(message,"POST /%s HTTP/1.1\r\n",api);
    char *header="";
    int ln;
    while(1){
        printf("add headers:\n Enter \"finish\" to go to the next step\n");
        fgets(header,100,stdin);
        if(strcmp(header,"\n")==0){
            fgets(header,100,stdin);
        }
        ln = strlen(header) - 1;
        header[ln] = '\0';
        if(strcmp("finish",header)==0){
            break;
        }
        else{
            strcat(message,header);
            strcat(message,"\r\n");
        }
        printf("====%s",header);
    }
    strcat(message,"cookie:");
    char *cookie="";
    while (1){
        printf("add cookies:\n Enter \"finish\" to go to the next step\n");
        scanf("%s",cookie);
        if(strcmp("finish",cookie)==0){
            strcat(message,"\r\n\r\n");
            break;
        }
        else{
            strcat(message," ");
            strcat(message,cookie);
        }
    }
    char *json="";
    printf("add json:\n");
    scanf("%s",json);
    strcat(message,json); */
    message = "POST /test HTTP/1.1\r\n\r\n";
    if( send(s , message , strlen(message) , 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts("Data Send\n");
    puts(message);
    if((recv_size = recv(s , server_reply , 2000 , 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
    }

    puts("Reply received\n");

    server_reply[recv_size] = 'b0';
    puts(server_reply);
    closesocket(s);
    WSACleanup();

    return 0;
}
